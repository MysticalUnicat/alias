// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <alias/cpp.h>

#include <alias/ash.h>
#include <alias/data_structure/vector.h>
#include <alias/log.h>
#include <alias/ui.h>

// for vsnprintf
#include <stdio.h>

// ====================================================================================================================
// structs
#define MAX_SCOPES 32

struct scope {
  alias_R font_size;
  alias_Color font_color;

  uint32_t shape;

  alias_R args[8];

  alias_R flex;
  alias_R total_flex;

  alias_R alignment;

  void (*begin_child)(alias_ui *);
  void (*end_child)(alias_ui *);
  void (*end_scope)(alias_ui *);
  void (*align)(alias_ui *, float x, float y);
};

struct shape {
  alias_R x, y, w, h;
};

struct alias_ui {
  alias_ash_Program layout_program;
  alias_ash_Program render_program;

  alias_MemoryCB *mcb;
  alias_ui_Output *output;

  uint32_t scope_index_p1;
  struct scope scopes[MAX_SCOPES];

  alias_Vector(uint8_t) memory;

  alias_ui_TextSizeFn text_size;
  alias_ui_TextDrawFn text_draw;

  uint32_t max_num_vertexes;
  uint32_t max_num_indexes;
  uint32_t max_num_groups;
};

// ====================================================================================================================
// private functions
static struct scope *_scope(alias_ui *ui) { return ui->scope_index_p1 > 0 ? &ui->scopes[ui->scope_index_p1 - 1] : NULL; }

static inline void _begin_child(alias_ui *ui) {
  struct scope *s = _scope(ui);
  if(s && s->begin_child) {
    s->begin_child(ui);
  }
}

static inline void _end_child(alias_ui *ui) {
  struct scope *s = _scope(ui);
  if(s->end_child) {
    s->end_child(ui);
  }
}

static inline void _begin_scope(alias_ui *ui, void (*begin_child)(alias_ui *), void (*end_child)(alias_ui *), void (*end_scope)(alias_ui *)) {
  struct scope *p = _scope(ui);
  struct scope *s = &ui->scopes[ui->scope_index_p1++];

  s->font_size = p ? p->font_size : 10;
  s->font_color = p ? p->font_color : alias_Color_WHITE;
  s->flex = alias_R_ZERO;
  s->total_flex = alias_R_ZERO;
  s->begin_child = begin_child;
  s->end_child = end_child;
  s->end_scope = end_scope;
  s->alignment = 0.5f;
  s->align = NULL;
}

static inline void _end_scope(alias_ui *ui) {
  struct scope *s = _scope(ui);
  if(s) {
    ui->scope_index_p1--;
    if(s->end_scope) {
      s->end_scope(ui);
    }
  }
}

static inline uint32_t _alloc(alias_ui *ui, uint32_t size) {
  alias_Vector_space_for(&ui->memory, ui->mcb, size);
  uint32_t result = ui->memory.length;
  ui->memory.length += size;
  return result;
}

static inline void *_mem(alias_ui *ui, uint32_t position) { return ui->memory.data + position; }

// ====================================================================================================================
// lifetime

#define SHAPE(X) ((struct shape *)(ui->memory.data + (X)))

static void _layout_shape_set_x(alias_ash *ash) {
  alias_ui *ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  SHAPE(ptr)->x = alias_ash_pop_R(ash);
  // ALIAS_TRACE("shape(%i)->x = %g", ptr, SHAPE(ptr)->x);
}

static void _layout_shape_set_y(alias_ash *ash) {
  alias_ui *ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  SHAPE(ptr)->y = alias_ash_pop_R(ash);
  // ALIAS_TRACE("shape(%i)->y = %g", ptr, SHAPE(ptr)->y);
}

static void _layout_shape_set_w(alias_ash *ash) {
  alias_ui *ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  SHAPE(ptr)->w = alias_ash_pop_R(ash);
  // ALIAS_TRACE("shape(%i)->w = %g", ptr, SHAPE(ptr)->w);
}

static void _layout_shape_set_h(alias_ash *ash) {
  alias_ui *ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  SHAPE(ptr)->h = alias_ash_pop_R(ash);
  // ALIAS_TRACE("shape(%i)->h = %g", ptr, SHAPE(ptr)->h);
}

static void _render_shape_get_x(alias_ash *ash) {
  alias_ui *ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  alias_ash_push_R(ash, SHAPE(ptr)->x);
  // ALIAS_TRACE("shape(%i)->x == %g", ptr, SHAPE(ptr)->x);
}

static void _render_shape_get_y(alias_ash *ash) {
  alias_ui *ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  alias_ash_push_R(ash, SHAPE(ptr)->y);
  // ALIAS_TRACE("shape(%i)->y == %g", ptr, SHAPE(ptr)->y);
}

static void _render_shape_get_w(alias_ash *ash) {
  alias_ui *ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  alias_ash_push_R(ash, SHAPE(ptr)->w);
  // ALIAS_TRACE("shape(%i)->w == %g", ptr, SHAPE(ptr)->w);
}

static void _render_shape_get_h(alias_ash *ash) {
  alias_ui *ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  alias_ash_push_R(ash, SHAPE(ptr)->h);
  // ALIAS_TRACE("shape(%i)->h == %g", ptr, SHAPE(ptr)->h);
}

static void _textv_layout(alias_ash *ash);
static void _textv_render(alias_ash *ash);

static int _emit_point(alias_ui *ui, float x, float y, float r, float g, float b, float a, float s, float t) {
  float xy[] = {x, y};
  float rgba[] = {r, g, b, a};
  float st[] = {s, t};
  alias_memory_SubBuffer_write(&ui->output->xy_sub_buffer, ui->output->num_vertexes, 1, alias_memory_Format_Float32, 0, xy);
  alias_memory_SubBuffer_write(&ui->output->rgba_sub_buffer, ui->output->num_vertexes, 1, alias_memory_Format_Float32, 0, rgba);
  alias_memory_SubBuffer_write(&ui->output->st_sub_buffer, ui->output->num_vertexes, 1, alias_memory_Format_Float32, 0, st);
  return ui->output->num_vertexes++;
}

static void _emit_triangle(alias_ui *ui, int p1, int p2, int p3) {
  int p[] = {p1, p2, p3};
  alias_memory_SubBuffer_write(&ui->output->index_sub_buffer, ui->output->num_indexes, 3, alias_memory_Format_Sint32, 0, p);
  ui->output->num_indexes += 3;
}

void alias_ui_SetTexture(alias_ui *ui, uint32_t texture_id) {
  if(ui->output->groups[ui->output->num_groups - 1].texture_id != texture_id) {
    if(ui->output->groups[ui->output->num_groups - 1].index != ui->output->num_indexes) {
      ui->output->groups[ui->output->num_groups - 1].length = ui->output->num_indexes - ui->output->groups[ui->output->num_groups - 1].index;
      ui->output->num_groups++;
    }
    ui->output->groups[ui->output->num_groups - 1].texture_id = texture_id;
    ui->output->groups[ui->output->num_groups - 1].index = ui->output->num_indexes;
  }
}

static void _set_texture(alias_ash *ash) {
  uint32_t texture_id = alias_ash_pop(ash);
  alias_ui *ui = (alias_ui *)ash->user_data;
  alias_ui_SetTexture(ui, texture_id);
}

static void _rect_fill_c(alias_ash *ash) {
  float a = alias_ash_pop_R(ash);
  float b = alias_ash_pop_R(ash);
  float g = alias_ash_pop_R(ash);
  float r = alias_ash_pop_R(ash);
  float h = alias_ash_pop_R(ash);
  float w = alias_ash_pop_R(ash);
  float y = alias_ash_pop_R(ash);
  float x = alias_ash_pop_R(ash);
  alias_ui *ui = (alias_ui *)ash->user_data;
  int p1 = _emit_point(ui, x, y, r, g, b, a, 0, 0);
  int p2 = _emit_point(ui, x + w, y, r, g, b, a, 1, 0);
  int p3 = _emit_point(ui, x + w, y + h, r, g, b, a, 1, 1);
  int p4 = _emit_point(ui, x, y + h, r, g, b, a, 0, 1);
  _emit_triangle(ui, p2, p1, p3);
  _emit_triangle(ui, p3, p1, p4);
}

static void _rect_fill_st(alias_ash *ash) {
  float t1 = alias_ash_pop_R(ash);
  float s1 = alias_ash_pop_R(ash);
  float t0 = alias_ash_pop_R(ash);
  float s0 = alias_ash_pop_R(ash);
  float h = alias_ash_pop_R(ash);
  float w = alias_ash_pop_R(ash);
  float y = alias_ash_pop_R(ash);
  float x = alias_ash_pop_R(ash);
  alias_ui *ui = (alias_ui *)ash->user_data;
  int p1 = _emit_point(ui, x, y, 1, 1, 1, 1, s0, t0);
  int p2 = _emit_point(ui, x + w, y, 1, 1, 1, 1, s1, t0);
  int p3 = _emit_point(ui, x + w, y + h, 1, 1, 1, 1, s1, t1);
  int p4 = _emit_point(ui, x, y + h, 1, 1, 1, 1, s0, t1);
  _emit_triangle(ui, p2, p1, p3);
  _emit_triangle(ui, p3, p1, p4);
}

void alias_ui_EmitRect(alias_ui *ui, float x, float y, float w, float h, float s0, float t0, float s1, float t1, float r, float g, float b, float a) {
  int p1 = _emit_point(ui, x, y, r, g, b, a, s0, t0);
  int p2 = _emit_point(ui, x + w, y, r, g, b, a, s1, t0);
  int p3 = _emit_point(ui, x + w, y + h, r, g, b, a, s1, t1);
  int p4 = _emit_point(ui, x, y + h, r, g, b, a, s0, t1);
  _emit_triangle(ui, p2, p1, p3);
  _emit_triangle(ui, p3, p1, p4);
}

static void _standard_library(alias_ash_Program *program, alias_MemoryCB *mcb) {
  ALIAS_ASH_EMIT(program, mcb,
                 fn(dip // [a] b f([a] -- ?) -- ? b
                    ,
                    swap, r_push, call, r_pop)

                     ,
                 fn(dip2 // [a] b c f([a] -- ?) -- ? b c
                    ,
                    rot, r_push, r_push, call, r_pop, r_pop)

                     ,
                 fn(keep // [a] b f([a] b -- ?) -- ? b
                    ,
                    swap, dup, r_push, call, r_pop)

                     ,
                 fn(f2_zip // a b c d f(x y -- z) -- f(a c) f(b d)
                    ,
                    r_push // a b c d
                    ,
                    rot, swap // a b c d -> a c b d
                    ,
                    r_at, call // a c f(b d)
                    ,
                    irot // f(b d) a c
                    ,
                    r_pop, call // f(b d) f(a c)
                    ,
                    swap)

                     ,
                 fn(f2_add // a b c d -- (a + c) (b + d)
                    ,
                    (f_add), f2_zip)

                     ,
                 fn(f2_sub // a b c d -- (a + c) (b + d)
                    ,
                    (f_sub), f2_zip)

                     ,
                 fn(f2_min // a b c d -- min(a, c) min(b, d)
                    ,
                    (f_min), f2_zip)

                     ,
                 fn(f2_max // a b c d -- max(a, c) max(b,d)
                    ,
                    (f_max), f2_zip)

                     ,
                 fn(fit // minw minh maxw maxh w h -- w h
                    ,
                    f2_min, f2_max)

                     ,
                 fn(loose_constraint // w h -- 0 0 w h
                    ,
                    f(0), dup, swap2));
}

alias_ui_Result alias_ui_initialize(alias_MemoryCB *mcb, alias_ui **ui_ptr) {
  alias_ui *ui = alias_malloc(mcb, sizeof(*ui), alignof(*ui));
  if(ui == NULL) {
    return alias_ui_ErrorOutOfMemory;
  }

  alias_ash_Program_initialize(&ui->layout_program);
  alias_ash_Program_begin_library(&ui->layout_program, mcb);
  alias_ash_Program_define_cfun(&ui->layout_program, mcb, "setx", _layout_shape_set_x);
  alias_ash_Program_define_cfun(&ui->layout_program, mcb, "sety", _layout_shape_set_y);
  alias_ash_Program_define_cfun(&ui->layout_program, mcb, "setw", _layout_shape_set_w);
  alias_ash_Program_define_cfun(&ui->layout_program, mcb, "seth", _layout_shape_set_h);
  alias_ash_Program_define_cfun(&ui->layout_program, mcb, "textv_layout", _textv_layout);
  _standard_library(&ui->layout_program, mcb);
  alias_ash_Program_end_library(&ui->layout_program);

  alias_ash_Program_initialize(&ui->render_program);
  alias_ash_Program_begin_library(&ui->render_program, mcb);
  alias_ash_Program_define_cfun(&ui->render_program, mcb, "getx", _render_shape_get_x);
  alias_ash_Program_define_cfun(&ui->render_program, mcb, "gety", _render_shape_get_y);
  alias_ash_Program_define_cfun(&ui->render_program, mcb, "getw", _render_shape_get_w);
  alias_ash_Program_define_cfun(&ui->render_program, mcb, "geth", _render_shape_get_h);
  alias_ash_Program_define_cfun(&ui->render_program, mcb, "textv_render", _textv_render);
  alias_ash_Program_define_cfun(&ui->render_program, mcb, "set_texture", _set_texture);
  alias_ash_Program_define_cfun(&ui->render_program, mcb, "rect_fill_c", _rect_fill_c);
  alias_ash_Program_define_cfun(&ui->render_program, mcb, "rect_fill_st", _rect_fill_st);
  _standard_library(&ui->render_program, mcb);
  alias_ash_Program_end_library(&ui->render_program);

  alias_memory_clear(&ui->memory, sizeof(ui->memory));

  *ui_ptr = ui;
  return alias_ui_Success;
}

alias_ui_Result alias_ui_free(alias_ui *ui, alias_MemoryCB *mcb) {
  (void)ui;
  (void)mcb;

  return alias_ui_Success;
}

// ====================================================================================================================
// frame (begin)
alias_ui_Result alias_ui_begin_frame(alias_ui *ui, alias_MemoryCB *mcb, const alias_ui_Input *input) {
  ui->mcb = mcb;

  alias_ash_Program_begin_shader(&ui->layout_program, mcb);
  alias_ash_Program_begin_shader(&ui->render_program, mcb);
  alias_Vector_clear(&ui->memory);

  // -- minw minh maxw maxh
  alias_ash_Program *lp = &ui->layout_program;
  ALIAS_ASH_EMIT(lp, ui->mcb, f(input->screen_size.width), f(input->screen_size.height), dup2);

  // -- minw minh maxw maxh
  ALIAS_ASH_EMIT(&ui->render_program, ui->mcb, f(0), dup, f(input->screen_size.width), f(input->screen_size.height));

  ui->scope_index_p1 = 0;
  _begin_scope(ui, NULL, NULL, NULL);

  ui->text_size = input->text_size;
  ui->text_draw = input->text_draw;

  return alias_ui_Success;
}

// ====================================================================================================================
// align fractions (center)
static inline void _align_fractions_end_child(alias_ui *ui) {
  struct scope *scope = _scope(ui);
  uint32_t shape = scope->shape;

  ALIAS_ASH_EMIT(&ui->layout_program,
                 ui->mcb
                 // end child: maxw maxh childw childh -- maxw maxh
                 ,
                 over2 // a b c d a b
                 ,
                 over2 // a b c d a b c d
                 //, ( f_sub, f(0.5), f_mul ), f2_zip // a b c d e f -- (max - child) * 0.5
                 ,
                 rot, swap, f_sub, f(scope->args[1]), f_mul, irot, f_sub, f(scope->args[0]), f_mul, swap, i(shape), sety // a b c d e
                 ,
                 i(shape), setx // a b c d
                 ,
                 i(shape), seth // a b c
                 ,
                 i(shape), setw // a b

                 // end self: maxw maxh -- w h
                 /* nothing, our size is max size */
  );

  _end_scope(ui);
  _end_child(ui);
}

void alias_ui_align_fractions(alias_ui *ui, float x, float y) {
  if(_scope(ui)->align != NULL) {
    _scope(ui)->align(ui, x, y);
    return;
  }

  _begin_child(ui);
  _begin_scope(ui, NULL, _align_fractions_end_child, NULL);

  struct scope *scope = _scope(ui);

  uint32_t shape = _alloc(ui, sizeof(struct shape));
  scope->shape = shape;
  scope->args[0] = x;
  scope->args[1] = y;

  ALIAS_ASH_EMIT(&ui->layout_program,
                 ui->mcb
                 // setup: minw minh maxw maxh -- maxw maxh
                 ,
                 swap2,
                 drop2

                 // begin child: maxw maxh -- maxw maxh 0 0 maxw maxh
                 ,
                 dup2, loose_constraint);

  ALIAS_ASH_EMIT(&ui->render_program,
                 ui->mcb
                 // setup: x y w h -- cx cy cw ch
                 ,
                 drop2 // a b c d -> a b
                 ,
                 i(shape), getx // a b e
                 ,
                 i(shape), gety // a b e f
                 ,
                 f2_add // e f
                 ,
                 i(shape), getw // e f g h
                 ,
                 i(shape), geth // e f g h
  );
}

// ====================================================================================================================
// override size
// state: w h
static inline void _override_size_end_child(alias_ui *ui) {
  // w h childw childh -- w h
  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb, drop2);

  _end_scope(ui);
  _end_child(ui);
}

void alias_ui_override_size(alias_ui *ui, alias_R width, alias_R height) {
  _begin_child(ui);
  _begin_scope(ui, NULL, _override_size_end_child, NULL);

  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb,
                 // setup: minw minh maxw maxh -- w h
                 f(width), f(height), fit,

                 // begin child: w h -- w h 0 0 w h
                 dup2, f(0), dup, swap2);
}

// ====================================================================================================================
// override width
// state: w
static inline void _override_width_end_child(alias_ui *ui) {
  // w childw childh -- w childh
  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb, nip);

  _end_scope(ui);
  _end_child(ui);
}

void alias_ui_override_width(alias_ui *ui, alias_R width) {
  _begin_child(ui);
  _begin_scope(ui, NULL, _override_width_end_child, NULL);

  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb,
                 // setup: minw minh maxw maxh -- minh maxh w
                 // begin child: minh maxh w -- w 0 minh w maxh
                 // setup and begin child: minw minh maxw maxh -- w 0 minh w maxh
                 (nip, f(0), swap, f(width), irot), dip2, nip, f(width), swap);
}

// ====================================================================================================================
// override height
// state: h
static inline void _override_height_end_child(alias_ui *ui) {
  // h childw childh -- childw h
  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb, drop, swap);

  _end_scope(ui);
  _end_child(ui);
}

void alias_ui_override_height(alias_ui *ui, alias_R height) {
  _begin_child(ui);
  _begin_scope(ui, NULL, _override_height_end_child, NULL);

  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb,
                 // setup: minw minh maxw maxh -- minw maxw h
                 // begin child: minw maxw h -- h minw 0 maxw h
                 // setup and begin child: minw minh maxw maxh -- h minw 0 maxw h
                 drop, (drop, f(height), swap, f(0)), dip, f(height));
}

// ====================================================================================================================
// vertical layout
static inline void _vertical_begin_child(alias_ui *ui) {
  int shape = _alloc(ui, sizeof(struct shape));
  _scope(ui)->shape = shape;

  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb,
                 // minw minh maxw maxh w h -- minw minh maxw maxh w h minw minh maxw maxh-h
                 i(5), pick, i(5), pick, i(5), pick, i(5), pick, i(4), pick, f_sub);

  ALIAS_ASH_EMIT(&ui->render_program, ui->mcb,
                 // x y w h -- x y w h (x+(w-cw)/2) (y+cy) cw ch
                 i(3), pick,               // x y w h x
                 f(_scope(ui)->alignment), // x y w h x 0.5
                 i(3), pick,               // x y w h x 0.5 w
                 i(shape), getw,           // x y w h x 0.5 w cw
                 f_sub, f_mul, f_add,      // x y w h cx
                 i(3), pick,               // x y w h cx y
                 i(shape), gety,           // x y w h cx y cy
                 f_add, i(shape), getw, i(shape), geth);

  _scope(ui)->alignment = 0.5f;
}

static inline void _vertical_end_child(alias_ui *ui) {
  int shape = _scope(ui)->shape;

  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb,
                 // minw minh maxw maxh w h childw childh -- minw minh maxw maxh max(w childw) (h + childh)
                 dup, i(shape), seth,       // a b maxw maxh w h childw childh
                 swap, dup, i(shape), setw, // a b maxw maxh w h childh childw
                 r_push,                    // a b maxw maxh w h childh
                 over, i(shape), sety,      // a b maxw maxh w h childh (copy current h to y)
                 f_add,                     // a b maxw maxh w (h + childh)
                 swap, r_pop,               // a b maxw maxh (h + childh) w childw
                 f_max, swap                // a b maxw maxh max(w childw) (h + childh)
  );
}

static inline void _vertical_end_scope(alias_ui *ui) {
  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb,
                 // minw minh maxw maxh max(childw) sum(childh) -- w h
                 fit);

  ALIAS_ASH_EMIT(&ui->render_program, ui->mcb,
                 // x y w h --
                 drop2, drop2);

  _end_child(ui);
}

static inline void _vertical_align(alias_ui *ui, float x, float y) {
  (void)y;
  _scope(ui)->alignment = x;
}

void alias_ui_begin_vertical(alias_ui *ui) {
  _begin_child(ui);
  _begin_scope(ui, _vertical_begin_child, _vertical_end_child, _vertical_end_scope);

  _scope(ui)->align = _vertical_align;
  _scope(ui)->alignment = 0.5f;

  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb,
                 // setup: minw minh maxw maxh -- minw minh maxw maxh 0 0 (current width, height)
                 i(0), dup);
}

// ====================================================================================================================
// horizontal layout
static inline void _horizontal_begin_child(alias_ui *ui) {
  int shape = _alloc(ui, sizeof(struct shape));
  _scope(ui)->shape = shape;

  ALIAS_ASH_EMIT(&ui->layout_program,
                 ui->mcb
                 // minw minh maxw maxh w h -- minw minh maxw maxh w h minw minh maxw-w maxh
                 ,
                 i(5), pick, i(5), pick, i(5), pick, i(4), pick, f_sub, i(5), pick);

  ALIAS_ASH_EMIT(&ui->render_program,
                 ui->mcb
                 // x y w h -- x y w h (x+cx) (y+(h-ch)/2) cw ch
                 ,
                 i(3), pick // x y w h x
                 ,
                 i(shape), getx // x y w h x cx
                 ,
                 f_add // x y w h cx
                 ,
                 i(3), pick // x y w h cx y
                 ,
                 f(_scope(ui)->alignment) // x y w h cx y 0.5
                 ,
                 i(3), pick // x y w h cx y 0.5 h
                 ,
                 i(shape), geth // x y w h cx y 0.5 h ch
                 ,
                 f_sub, f_mul, f_add // x y w h cx cy
                 ,
                 i(shape), getw, i(shape), geth);

  _scope(ui)->alignment = 0.5f;
}

static inline void _horizontal_end_child(alias_ui *ui) {
  int shape = _scope(ui)->shape;

  ALIAS_ASH_EMIT(&ui->layout_program,
                 ui->mcb
                 // minw minh maxw maxh w h childw childh -- minw minh maxw maxh max(w childw) (h + childh)
                 ,
                 dup, i(shape), seth // a b maxw maxh w h childw childh
                 ,
                 swap, dup, i(shape), setw // a b maxw maxh w h childh childw
                 ,
                 r_push // a b maxw maxh w h childh
                 ,
                 i(2), pick, i(shape), setx // a b maxw maxh w h childh (copy current w to x)
                 ,
                 f_max // a b maxw maxh w max(h childh)
                 ,
                 swap, r_pop // a b maxw maxh max(h childh) w childw
                 ,
                 f_add, swap // a b maxw maxh (w + childw) max(h childh)
  );
}

static inline void _horizontal_end_scope(alias_ui *ui) {
  ALIAS_ASH_EMIT(&ui->layout_program,
                 ui->mcb
                 // minw minh maxw maxh sum(childw) max(childh) -- w h
                 ,
                 fit);

  ALIAS_ASH_EMIT(&ui->render_program,
                 ui->mcb
                 // x y w h --
                 ,
                 drop2, drop2);

  _end_child(ui);
}

static inline void _horizontal_align(alias_ui *ui, float x, float y) {
  (void)x;
  _scope(ui)->alignment = y;
}

void alias_ui_begin_horizontal(alias_ui *ui) {
  _begin_child(ui);
  _begin_scope(ui, _horizontal_begin_child, _horizontal_end_child, _horizontal_end_scope);

  _scope(ui)->align = _horizontal_align;
  _scope(ui)->alignment = 0.5f;

  ALIAS_ASH_EMIT(&ui->layout_program,
                 ui->mcb
                 // setup: minw minh maxw maxh -- minw minh maxw maxh 0 0 (current width, height)
                 ,
                 i(0), dup);
}

// ====================================================================================================================
// stack layout
static inline void _stack_begin_child(alias_ui *ui) {
  int shape = _alloc(ui, sizeof(struct shape));
  _scope(ui)->shape = shape;

  ALIAS_ASH_EMIT(&ui->layout_program,
                 ui->mcb
                 // minw minh maxw maxh w h -- minw minh maxw maxh w h 0 0 maxw maxh
                 ,
                 f(0), dup, i(5), pick, i(5), pick);

  ALIAS_ASH_EMIT(&ui->render_program,
                 ui->mcb
                 // x y w h -- x y w h (x+cx) (y+cy) cw ch
                 ,
                 over2, i(shape), getw, i(shape), geth);
}

static inline void _stack_end_child(alias_ui *ui) {
  int shape = _scope(ui)->shape;

  ALIAS_ASH_EMIT(&ui->layout_program,
                 ui->mcb
                 // minw minh maxw maxh w h childw childh -- minw minh maxw maxh max(w childw) max(h childh)
                 ,
                 dup, i(shape), seth, swap, dup, i(shape), setw, swap, f2_max);
}

static inline void _stack_end_scope(alias_ui *ui) {
  ALIAS_ASH_EMIT(&ui->layout_program,
                 ui->mcb
                 // minw minh maxw maxh max(childw) max(childh) -- w h
                 ,
                 fit);

  ALIAS_ASH_EMIT(&ui->render_program,
                 ui->mcb
                 // x y w h --
                 ,
                 drop2, drop2);

  _end_child(ui);
}

void alias_ui_begin_stack(alias_ui *ui) {
  _begin_child(ui);
  _begin_scope(ui, _stack_begin_child, _stack_end_child, _stack_end_scope);

  ALIAS_ASH_EMIT(&ui->layout_program,
                 ui->mcb
                 // setup: minw minh maxw maxh -- minw minh maxw maxh 0 0 (current width, height)
                 ,
                 i(0), dup);
}

void alias_ui_end(alias_ui *ui) { _end_scope(ui); }

void alias_ui_stats(alias_ui *ui, uint32_t *num_vertexes, uint32_t *num_indexes, uint32_t *num_groups) {
  *num_vertexes = ui->max_num_vertexes;
  *num_indexes = ui->max_num_indexes;
  *num_groups = ui->max_num_groups;
}

// ====================================================================================================================
// font
void alias_ui_font_size(alias_ui *ui, alias_R size) { _scope(ui)->font_size = size; }

void alias_ui_font_color(alias_ui *ui, alias_Color color) { _scope(ui)->font_color = color; }

// ====================================================================================================================
// text
static void _textv_layout(alias_ash *ash) {
  float size = alias_ash_pop_R(ash);
  uint32_t text = alias_ash_pop(ash);
  float maxh = alias_ash_pop_R(ash);
  float maxw = alias_ash_pop_R(ash);
  float minh = alias_ash_pop_R(ash);
  float minw = alias_ash_pop_R(ash);
  float w, h;
  alias_ui *ui = (alias_ui *)ash->user_data;
  ui->text_size(ui, _mem(ui, text), size, maxw, &w, &h);
  alias_ash_push_R(ash, alias_max(minw, alias_min(maxw, w)));
  alias_ash_push_R(ash, alias_max(minh, alias_min(maxh, h)));

  // ALIAS_TRACE("textv_layout '%s' %g %g -> %g %g", _mem(ui, text), size, maxw, w, h);
}

static void _textv_render(alias_ash *ash) {
  float a = alias_ash_pop_R(ash);
  float b = alias_ash_pop_R(ash);
  float g = alias_ash_pop_R(ash);
  float r = alias_ash_pop_R(ash);
  float size = alias_ash_pop_R(ash);
  uint32_t text = alias_ash_pop(ash);
  float h = alias_ash_pop_R(ash);
  float w = alias_ash_pop_R(ash);
  float y = alias_ash_pop_R(ash);
  float x = alias_ash_pop_R(ash);
  (void)h;
  alias_ui *ui = (alias_ui *)ash->user_data;
  ui->text_draw(ui, _mem(ui, text), x, y, w, size, (alias_Color){r, g, b, a});

  // ALIAS_TRACE("textv_draw '%s' %g %g %g", _mem(ui, text), minx, miny, size);
}

void alias_ui_textv(alias_ui *ui, const char *format, va_list ap) {
  uint32_t text;
  size_t length;
  {
    va_list ap2;
    va_copy(ap2, ap);
    length = vsnprintf(NULL, 0, format, ap2);
    va_end(ap2);
    text = _alloc(ui, length + 1);
    vsnprintf(_mem(ui, text), length + 1, format, ap);
  }

  _begin_child(ui);

  ui->max_num_vertexes += 4 * length;
  ui->max_num_indexes += 6 * length;
  ui->max_num_groups++;

  ALIAS_ASH_EMIT(&ui->layout_program,
                 ui->mcb
                 // self: minw minh maxw mwxh -- w h
                 ,
                 i(text), f(_scope(ui)->font_size), textv_layout);

  ALIAS_ASH_EMIT(&ui->render_program,
                 ui->mcb
                 // self: minx miny w h --
                 ,
                 i(text), f(_scope(ui)->font_size), f(_scope(ui)->font_color.r), f(_scope(ui)->font_color.g), f(_scope(ui)->font_color.b),
                 f(_scope(ui)->font_color.a), textv_render);

  _end_child(ui);
}

// ====================================================================================================================
void alias_ui_fill(alias_ui *ui, alias_Color color) {
  _begin_child(ui);

  ui->max_num_vertexes += 4;
  ui->max_num_indexes += 6;
  ui->max_num_groups++;

  ALIAS_ASH_EMIT(&ui->layout_program,
                 ui->mcb
                 // self: minw minh maxw mwxh -- w h
                 ,
                 swap2, drop2);

  ALIAS_ASH_EMIT(&ui->render_program,
                 ui->mcb
                 // self: x y w h --
                 ,
                 i(0), set_texture, f(color.r), f(color.g), f(color.b), f(color.a), rect_fill_c);

  _end_child(ui);
}

// ====================================================================================================================
void alias_ui_image(alias_ui *ui, alias_R width, alias_R height, alias_R s0, alias_R t0, alias_R s1, alias_R t1, uint32_t texture_id) {
  _begin_child(ui);

  ui->max_num_vertexes += 4;
  ui->max_num_indexes += 6;
  ui->max_num_groups++;

  ALIAS_ASH_EMIT(&ui->layout_program,
                 ui->mcb
                 // self: minw minh maxw mwxh -- w h
                 ,
                 f(width), f(height), fit);

  ALIAS_ASH_EMIT(&ui->render_program,
                 ui->mcb
                 // self: x y w h --
                 ,
                 i(texture_id), set_texture, f(s0), f(t0), f(s1), f(t1), rect_fill_st);

  _end_child(ui);
}

// ====================================================================================================================
// frame (end)
alias_ui_Result alias_ui_end_frame(alias_ui *ui, alias_MemoryCB *mcb, alias_ui_Output *output) {
  _end_scope(ui);
  ui->output = output;

  alias_ash_Program_end_shader(&ui->layout_program, mcb);
  alias_ash_Program_end_shader(&ui->render_program, mcb);

  alias_ash ash;
  ash.user_data = ui;

  alias_ash_initialize(&ash, &ui->layout_program);
  while(alias_ash_step(&ash))
    ;

  if(output->num_groups > 0) {
    output->groups[output->num_groups - 1].length = output->num_indexes - output->groups[output->num_groups - 1].index;
  }

  output->groups[output->num_groups].index = output->num_indexes;
  output->groups[output->num_groups].length = 0;
  output->groups[output->num_groups].texture_id = 0;
  output->num_groups++;

  alias_ash_initialize(&ash, &ui->render_program);
  while(alias_ash_step(&ash))
    ;

  output->groups[output->num_groups - 1].length = output->num_indexes - output->groups[output->num_groups - 1].index;

  if(output->groups[output->num_groups - 1].length == 0) {
    output->num_groups--;
  }

  return alias_ui_Success;
}
