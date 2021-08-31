#include <alias/cpp.h>

#include <alias/ui.h>
#include <alias/ash.h>

// ====================================================================================================================
// structs
#define MAX_SCOPES 32

struct scope {
  alias_R     font_size;
  alias_Color font_color;

  alias_R flex;
  alias_R total_flex;
  
  void (* begin_child)(alias_ui *);
  void (* end_child)(alias_ui *);
  void (* end_scope)(alias_ui *);
};

struct alias_ui {
  alias_ash_Program layout_program;

  alias_MemoryCB * mcb;

  uint32_t scope_index_p1;
  struct scope scopes[MAX_SCOPES];
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

// ====================================================================================================================
// lifetime
alias_ui_Result alias_ui_initialize(alias_MemoryCB * mcb, alias_ui * * ui_ptr) {
  alias_ui * ui = alias_malloc(mcb, sizeof(*ui), alignof(*ui));
  if(ui == NULL) {
    return alias_ui_ErrorOutOfMemory;
  }

  alias_ash_Program_initialize(&ui->layout_program);
  alias_ash_Program_begin_library(&ui->layout_program, mcb);

  ALIAS_ASH_EMIT(&ui->layout_program, mcb
    , fn(dip // [a] b f([a] -- ?) -- ? b
       , swap, r_push, call, r_pop)

    , fn(dip2 // [a] b c f([a] -- ?) -- ? b c
       , rot, r_push, r_push, call, r_pop, r_pop)

    , fn(keep // [a] b f([a] b -- ?) -- ? b
       , swap, dup, r_push, call, r_pop)
 
    , fn(f2_zip // a b c d f(x y -- z) -- f(a c) f(b d)
       , r_push        // a b c d
       , ( swap ), dip // a b c d -> a c b d
       , r_at, call    // a c f(b d)
       , rot           // f(b d) a c
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

  alias_ash_Program_end_library(&ui->layout_program);

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
 
  // -- minw minh maxw maxh
  alias_ash_Program * lp = &ui->layout_program;
  ALIAS_ASH_EMIT(lp, ui->mcb
    , f(input->screen_size.width)
    , f(input->screen_size.height)
    , dup2
  );

  ui->scope_index_p1 = 0;
  _begin_scope(ui, NULL, NULL, NULL);

  return alias_ui_Success;
}

// ====================================================================================================================
// center
static inline void _center_end_child(alias_ui * ui) {
  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb
    // end child: maxw maxh childw childh -- maxw maxh
    , ( dup2 ), dip2
    , ( f_sub, f(0.5), f_mul ), f2_zip // (max - child) * 0.5
    , drop2                            // TODO store offset so render program can see it

    // end self: maxw maxh -- w h
    /* nothing, our size is max size */
    );

  _end_scope(ui);
  _end_child(ui);
}

void alias_ui_center(alias_ui * ui) {
  _begin_child(ui);
  _begin_scope(ui, NULL, _center_end_child, NULL);

  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb
    // setup: minw minh maxw maxh -- maxw maxh
    , swap2, drop2

    // begin child: maxw maxh -- maxw maxh 0 0 maxw maxh
    , dup2, loose_constraint
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
    , dup2, dup2
  );
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
void alias_ui_textv(alias_ui * ui, const char * format, va_list ap) {
  (void)format;
  (void)ap;

  _begin_child(ui);

  alias_R width = 100;
  alias_R height = 80;

  ALIAS_ASH_EMIT(&ui->layout_program, ui->mcb
    // self: minw minh maxw mwxh -- w h
    , f(width), f(height), fit
    );

  _end_child(ui);
}

// ====================================================================================================================
// frame (end)
alias_ui_Result alias_ui_end_frame(alias_ui * ui, alias_MemoryCB * mcb, alias_ui_Output * output) {
  (void)output;

  _end_scope(ui);

  alias_ash_Program_end_shader(&ui->layout_program, mcb);

  return alias_ui_Success;
}
