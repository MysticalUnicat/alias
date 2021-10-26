#include <alias/cpp.h>

#include <alias/ui.h>
#include <alias/ash.h>
#include <alias/data_structure/vector.h>
#include <alias/log.h>

// for vsnprintf
#include <stdio.h>

// ====================================================================================================================
// structs
#define MAX_SCOPES 32

struct scope {
  alias_R     font_size;
  alias_Color font_color;

  uint32_t shape;

  alias_R flex;
  alias_R total_flex;
  
  void (* begin_child)(alias_ui *);
  void (* end_child)(alias_ui *);
  void (* end_scope)(alias_ui *);
};

struct shape {
  alias_R x, y, w, h;
};

struct alias_ui {
  alias_ash_Program layout_program;
  alias_ash_Program render_program;

  alias_MemoryCB * mcb;

  uint32_t scope_index_p1;
  struct scope scopes[MAX_SCOPES];

  alias_Vector(uint8_t) memory;

  alias_ui_TextSizeFn text_size;
  alias_ui_TextDrawFn text_draw;
};

// ====================================================================================================================
// private functions
static struct scope * _scope(alias_ui * ui) {
  return ui->scope_index_p1 > 0 ? &ui->scopes[ui->scope_index_p1 - 1] : NULL;
}

static inline void _begin_child(alias_ui * ui) {
  struct scope * s = _scope(ui);
  if(s && s->begin_child) {
    s->begin_child(ui);
  }
}

static inline void _end_child(alias_ui * ui) {
  struct scope * s = _scope(ui);
  if(s->end_child) {
    s->end_child(ui);
  }
}

static inline void _begin_scope(alias_ui * ui, void (* begin_child)(alias_ui *), void (* end_child)(alias_ui *), void (* end_scope)(alias_ui *)) {
  struct scope * p = _scope(ui);
  struct scope * s = &ui->scopes[ui->scope_index_p1++];

  s->font_size = p ? p->font_size : 10;
  s->font_color = p ? p->font_color : alias_Color_WHITE;
  s->flex = alias_R_ZERO;
  s->total_flex = alias_R_ZERO;
  s->begin_child = begin_child;
  s->end_child = end_child;
  s->end_scope = end_scope;
}

static inline void _end_scope(alias_ui * ui) {
  struct scope * s = _scope(ui);
  if(s) {
    ui->scope_index_p1--;
    if(s->end_scope) {
      s->end_scope(ui);
    }
  }
}

static inline uint32_t _alloc(alias_ui * ui, uint32_t size) {
  alias_Vector_space_for(&ui->memory, ui->mcb, size);
  uint32_t result = ui->memory.length;
  ui->memory.length += size;
  return result;
}

static inline void * _mem(alias_ui * ui, uint32_t position) {
  return ui->memory.data + position;
}

// ====================================================================================================================
// lifetime

#define SHAPE(X) ((struct shape *)(ui->memory.data + (X)))

static void _layout_shape_set_x(alias_ash * ash) {
  alias_ui * ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  uint32_t x = alias_ash_pop(ash);
  SHAPE(ptr)->x = *(alias_R *)&x;
}

static void _layout_shape_set_y(alias_ash * ash) {
  alias_ui * ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  uint32_t y = alias_ash_pop(ash);
  SHAPE(ptr)->y = *(alias_R *)&y;
}

static void _layout_shape_set_w(alias_ash * ash) {
  alias_ui * ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  uint32_t w = alias_ash_pop(ash);
  SHAPE(ptr)->w = *(alias_R *)&w;
}

static void _layout_shape_set_h(alias_ash * ash) {
  alias_ui * ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  uint32_t h = alias_ash_pop(ash);
  SHAPE(ptr)->h = *(alias_R *)&h;
}

static void _render_shape_get_x(alias_ash * ash) {
  alias_ui * ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  alias_ash_push_R(ash, SHAPE(ptr)->x);
}

static void _render_shape_get_y(alias_ash * ash) {
  alias_ui * ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  alias_ash_push_R(ash, SHAPE(ptr)->y);
}

static void _render_shape_get_w(alias_ash * ash) {
  alias_ui * ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  alias_ash_push_R(ash, SHAPE(ptr)->w);
}

static void _render_shape_get_h(alias_ash * ash) {
  alias_ui * ui = (alias_ui *)ash->user_data;
  uint32_t ptr = alias_ash_pop(ash);
  alias_ash_push_R(ash, SHAPE(ptr)->h);
}

static void _textv_layout(alias_ash * ash);
static void _textv_render(alias_ash * ash);

static void _standard_library(alias_ash_Program * program, alias_MemoryCB * mcb) {
  ALIAS_ASH_EMIT(program, mcb
    , fn(dip // [a] b f([a] -- ?) -- ? b
       , swap, r_push, call, r_pop)

    , fn(dip2 // [a] b c f([a] -- ?) -- ? b c
       , rot, r_push, r_push, call, r_pop, r_pop)

    , fn(keep // [a] b f([a] b -- ?) -- ? b
       , swap, dup, r_push, call, r_pop)
 
    , fn(f2_zip // a b c d f(x y -- z) -- f(a c) f(b d)
       , r_push        // a b c d
       , rot, swap     // a b c d -> a c b d
       , r_at, call    // a c f(b d)
       , irot          // f(b d) a c
       , r_pop, call   // f(b d) f(a c)
       , swap)

    , fn(f2_min // a b c d -- min(a, c) min(b, d)
       , ( f_min ), f2_zip)

    , fn(f2_max // a b c d -- max(a, c) max(b,d)
       , ( f_max ), f2_zip)

    , fn(fit // minw minh maxw maxh w h -- w h
       , f2_min, f2_max)

   , fn(loose_constraint // w h -- 0 0 w h
       , f(0), dup, swap2)
  );
}

alias_ui_Result alias_ui_initialize(alias_MemoryCB * mcb, alias_ui * * ui_ptr) {
  alias_ui * ui = alias_malloc(mcb, sizeof(*ui), alignof(*ui));
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
  _standard_library(&ui->render_program, mcb);
  alias_ash_Program_end_library(&ui->render_program);

  alias_memory_clear(&ui->memory, sizeof(ui->memory));

  *ui_ptr = ui;
  return alias_ui_Success;
}

alias_ui_Result alias_ui_free(alias_ui * ui, alias_MemoryCB * mcb) {
  (void)ui;
  (void)mcb;

  return alias_ui_Success;
}

// ====================================================================================================================
// frame (begin)
alias_ui_Result alias_ui_begin_frame(alias_ui * ui, alias_MemoryCB * mcb, const alias_ui_Input * input) {
  ui->mcb = mcb;
  
  alias_ash_Program_begin_shader(&ui->layout_program, mcb);
  alias_ash_Program_begin_shader(&ui->render_program, mcb);
  alias_Vector_clear(&ui->memory);
 
  // -- minw minh maxw maxh
  alias_ash_Program * lp = &ui->layout_program;
  ALIAS_ASH_EMIT(lp, ui->mcb
    , f(input->screen_size.width)
    , f(input->screen_size.height)
    , dup2
  );
 
  // -- minw minh maxw maxh
  ALIAS_ASH_EMIT(&ui->render_program, ui->mcb
    , f(0), dup
    , f(input->screen_size.width)
    , f(input->screen_size.height)
  );

  ui->scope_index_p1 = 0;
  _begin_scope(ui, NULL, NULL, NULL);

  ui->text_size = input->text_size;
  ui->text_draw = input->text_draw;

  return alias_ui_Success;
}

// ====================================================================================================================
// center
static inline void _center_end_child(alias_ui * ui) {
  uint32_t shape = _scope(ui)->shape;
  
  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb
    // end child: maxw maxh childw childh -- maxw maxh
    , over2                            // a b c d a b
    , over2                            // a b c d a b c d
    , ( f_sub, f(0.5), f_mul ), f2_zip // a b c d e f -- (max - child) * 0.5
    , i(shape), sety                   // a b c d e
    , i(shape), setx                   // a b c d
    , i(shape), seth                   // a b c
    , i(shape), setw                   // a b

    // end self: maxw maxh -- w h
    /* nothing, our size is max size */
    );

  _end_scope(ui);
  _end_child(ui);
}

void alias_ui_center(alias_ui * ui) {
  _begin_child(ui);
  _begin_scope(ui, NULL, _center_end_child, NULL);

  uint32_t shape = _alloc(ui, sizeof(struct shape));
  _scope(ui)->shape = shape;

  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb
    // setup: minw minh maxw maxh -- maxw maxh
    , swap2, drop2

    // begin child: maxw maxh -- maxw maxh 0 0 maxw maxh
    , dup2, loose_constraint
    );

  ALIAS_ASH_EMIT(&ui->render_program, ui->mcb
    // setup: minx miny maxx maxy -- childminx childminy childmaxx childmaxy
    , drop2               // a b c d -> a b
    , i(shape), getx      // a b e
    , i(shape), gety      // a b e f
    , ( f_add ), f2_zip   // e f
    , dup2                // e f e f
    , i(shape), getw      // e f e f g h
    , i(shape), geth      // e f e f g h
    , ( f_add ), f2_zip   // e f j k
    );
}

// ====================================================================================================================
// override size
// state: w h
static inline void _override_size_end_child(alias_ui * ui) {
  // w h _ _ -- w h
  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb, drop2);

  _end_scope(ui);
  _end_child(ui);
}

void alias_ui_override_size(alias_ui * ui, alias_R width, alias_R height) {
  _begin_child(ui);
  _begin_scope(ui, NULL, _override_size_end_child, NULL);

  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb
    // setup: minw minh maxw maxh -- w h
    , f(width), f(height), fit

    // begin child: w h -- w h 0 0 w h
    , dup2, f(0), dup, swap2
  );
}

// ====================================================================================================================
// vertical layout
static inline void _vertical_begin_child(alias_ui * ui) {
  int shape = _alloc(ui, sizeof(struct shape));
  _scope(ui)->shape = shape;

  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb
    // minw minh maxw maxh w h -- minw minh maxw maxh w h minw minh maxw maxh
    , i(5), pick
    , i(5), pick
    , i(5), pick
    , i(5), pick
    , i(6), pick
    , f_sub
  );
  
  ALIAS_ASH_EMIT(&ui->render_program, ui->mcb
    // x1 y1 x2 y2 -- x1 y1 x2 y2 (x1+x) (y1+y) (x1+x+w) (y1+y+h)
    , over2
    , r_push, i(shape), getx, f_add
    , r_pop, i(shape), gety, f_add
    , over, i(shape), getw, f_add
    , over, i(shape), geth, f_add
  );
}

static inline void _vertical_end_child(alias_ui * ui) {
  int shape = _scope(ui)->shape;

  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb
    // minw minh maxw maxh w h childw childh -- minw minh maxw maxh max(w childw) (h + childh)
    , dup, i(shape), seth         // a b maxw maxh w h childw childh
    , swap, dup, i(shape), setw   // a b maxw maxh w h childh childw
    , dup, i(4), pick             // a b maxw maxh w h childh childw childw maxw
    , swap, f_sub, f(0.5f), f_mul // a b maxw maxh w h childh childw (maxw - childw)*0.5
    , i(shape), setx              // a b maxw maxh w h childh childw
    , r_push                     // a b maxw maxh w h childh
    , over, i(shape), sety       // a b maxw maxh w h childh (copy current h to y)
    , f_add                      // a b maxw maxh w (h + childh)
    , swap, r_pop                // a b maxw maxh (h + childh) w childw
    , f_max, swap                // a b maxw maxh max(w childw) (h + childh)
  );
}

static inline void _vertical_end_scope(alias_ui * ui) {
  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb
    // minw minh maxw maxh max(childw) sum(childh) -- w h
    , fit
  );
  
  ALIAS_ASH_EMIT(&ui->render_program, ui->mcb
    // x1 y1 x2 y2 --
    , drop2, drop2
  );
}

void alias_ui_begin_vertical(alias_ui * ui) {
  _begin_child(ui);
  _begin_scope(ui, _vertical_begin_child, _vertical_end_child, _vertical_end_scope);

  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb
    // setup: minw minh maxw maxh -- minw minh maxw maxh 0 0 (current width, height)
    , i(0), dup
    );
}

void alias_ui_end(alias_ui * ui) {
  _end_scope(ui);
}

// ====================================================================================================================
// font
void alias_ui_font_size(alias_ui * ui, alias_R size) {
  _scope(ui)->font_size = size;
}

void alias_ui_font_color(alias_ui * ui, alias_Color color) {
  _scope(ui)->font_color = color;
}

// ====================================================================================================================
// text
static void _textv_layout(alias_ash * ash) {
  float size = alias_ash_pop_R(ash);
  uint32_t text = alias_ash_pop(ash);
  float maxh = alias_ash_pop_R(ash);
  float maxw = alias_ash_pop_R(ash);
  float minh = alias_ash_pop_R(ash);
  float minw = alias_ash_pop_R(ash);
  float w, h;
  alias_ui * ui = (alias_ui *)ash->user_data;
  ui->text_size(_mem(ui, text), size, maxw, &w, &h);
  alias_ash_push_R(ash, alias_max(minw, alias_min(maxw, w)));
  alias_ash_push_R(ash, alias_max(minh, alias_min(maxh, h)));
}

static void _textv_render(alias_ash * ash) {
  float a = alias_ash_pop_R(ash);
  float b = alias_ash_pop_R(ash);
  float g = alias_ash_pop_R(ash);
  float r = alias_ash_pop_R(ash);
  float size = alias_ash_pop_R(ash);
  uint32_t text = alias_ash_pop(ash);
  float maxy = alias_ash_pop_R(ash);
  float maxx = alias_ash_pop_R(ash);
  float miny = alias_ash_pop_R(ash);
  float minx = alias_ash_pop_R(ash);
  (void)maxy;
  alias_ui * ui = (alias_ui *)ash->user_data;
  ui->text_draw(_mem(ui, text), minx, miny, maxx - minx, size, (alias_Color){ r, g, b, a });
}

void alias_ui_textv(alias_ui * ui, const char * format, va_list ap) {
  uint32_t text;
  {
    va_list ap2;
    va_copy(ap2, ap);
    size_t length = vsnprintf(NULL, 0, format, ap2);
    va_end(ap2);
    text = _alloc(ui, length + 1);
    vsnprintf(_mem(ui, text), length + 1, format, ap);
  }

  _begin_child(ui);

  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb
    // self: minw minh maxw mwxh -- w h
    , i(text)
    , f(_scope(ui)->font_size)
    , textv_layout
      /*
    , i(text), f(_scope(ui)->font_size), ( over ), dip2, text_size
    , fit
      */
    );

  ALIAS_ASH_EMIT(&ui->render_program, ui->mcb
    // self: minx miny maxx maxy --
    , i(text) 
    , f(_scope(ui)->font_size)
    , f(_scope(ui)->font_color.r)
    , f(_scope(ui)->font_color.g)
    , f(_scope(ui)->font_color.b)
    , f(_scope(ui)->font_color.a)
    , textv_render
        /*
    , r_push            // x y c R: d
    , drop              // x y R: d
    , ( i(text) ), dip2 // text x y R: d
    , dup               // text x y y R: d
    , r_pop             // text x y y d
    , swap, f_sub       // text x y w 
    , f(_scope(ui)->font_size)
    , i(alias_Color_to_rgba_u8_packed(_scope(ui)->font_color)
    , text_draw
        */
    );

  _end_child(ui);
}

// ====================================================================================================================
// frame (end)
alias_ui_Result alias_ui_end_frame(alias_ui * ui, alias_MemoryCB * mcb, alias_ui_Output * output) {
  (void)output;

  _end_scope(ui);

  alias_ash_Program_end_shader(&ui->layout_program, mcb);
  alias_ash_Program_end_shader(&ui->render_program, mcb);

  alias_ash ash;
  ash.user_data = ui;

  alias_ash_initialize(&ash, &ui->layout_program);
  while(alias_ash_step(&ash)) ;

  alias_ash_initialize(&ash, &ui->render_program);
  while(alias_ash_step(&ash)) ;

  return alias_ui_Success;
}
