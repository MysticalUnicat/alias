#ifndef _ALIAS_UI_H_
#define _ALIAS_UI_H_

#include <alias/geometry/aabb.h>
#include <alias/util.h>

#define ALIAS_UI_MAX_DEPTH 64
#define ALIAS_UI_MAX_NODES (64 * 1024)

// ====================================================================================================================
// enums
typedef enum alias_ui_Pass {
  alias_ui_Layout1_Pass,
  alias_ui_Layout2_Pass,
  alias_ui_Render_Pass,
  ALIAS_UI_PASS_COUNT
} alias_ui_Pass;

// ====================================================================================================================
// structs and callbacks
typedef struct alias_ui_Size {
  alias_R width;
  alias_R height;
} alias_ui_Size;

typedef struct alias_ui_Constraint {
  alias_ui_Size min;
  alias_ui_Size max;
} alias_ui_Constraint;

typedef struct alias_ui_Input {
  alias_ui_Size screen_size;
} alias_ui_Input;

typedef struct alias_ui_Output {
  uint32_t dummy;
} alias_ui_Output;

ALIAS_DECLARE_CLOSURE(alias_ui_PositionChildrenCB, void, uint32_t node_index);

typedef struct alias_ui_Scope {
  alias_ui_Constraint         constraint;
  alias_ui_PositionChildrenCB position_children;
} alias_ui_Scope;

typedef struct alias_ui {
  uint32_t               next_node_index;
  uint32_t               current_parent_index;
  alias_ui_WidgetClass * widget_class[ALIAS_UI_MAX_NODES];
  uint32_t               parent[ALIAS_UI_MAX_NODES];
  uint32_t               next[ALIAS_UI_MAX_NODES];

  alias_ui_Pass       pass;

  uint32_t scope_top;
  alias_ui_Scope scope[ALIAS_UI_MAX_DEPTH];
} alias_ui;

ALIAS_DECLARE_CLOSURE(alias_ui_UpdateCB, void, alias_ui_Pass pass);

// ====================================================================================================================
// constants
static const alias_ui_Size alias_ui_Size_ZERO = { alias_R_ZERO, alias_R_ZERO };

// ====================================================================================================================
// alias_ui_Size functions
static inline alias_R alias_ui_Size_aspect_ratio(alias_ui_Size size) {
  return
    !alias_R_is_zero(size.height) ? size.width / size.height :
    alias_R_is_zero(size.width)   ? alias_R_ZERO             :
    size.width > alias_R_ZERO     ? alias_R_INFINITY         :
                                    -alias_R_INFINITY        ;
}

// ====================================================================================================================
// alias_ui_Constraint functions
static inline alias_ui_Constraint alias_ui_Constraint_tight(alias_ui_Size size) {
  return (alias_ui_Constraint) { size, size };
}

// ====================================================================================================================
// private alias_ui functions
static inline void alias_ui__begin(alias_ui * ui) {
  uint32_t index = ui->next_node_index++;
  ui->parent[index] = ui->current_parent_index;
  ui->widget_class[index] = wc;
  ui->current_parent_index = index;
}

static inline void alias_ui__end(alias_ui * ui) {
  ui->next[ui->current_parent_index] = ui->next_node_index;
  ui->current_parent_index = ui->parent[ui->current_parent_index];
}

// ====================================================================================================================
// public alias_ui functions
void alias_ui_update(
    alias_ui             * ui
  , const alias_ui_Input * input
  , alias_ui_UpdateCB      cb
  , alias_ui_Output      * output
) {
  alias_ui__reset_identifiers(context);

  for(uint32_t i = 0; i < ALIAS_UI_PASS_COUNT; i++) {
    ui->pass = (alias_ui_Pass)i;
    ui->constraint = alias_ui_Constraint_tight(input->screen_size);
    alias_ui__begin(ui, 

    alias_Closure_call(cb, context->pass);
  }
}

//static inline void alias_ui_alignment
//static inline void alias_ui_padding
//static inline void alias_ui_color
//static inline void alias_ui_decoration
//static inline void alias_ui_width
//static inline void alias_ui_height
//static inline void alias_ui_constraints
//static inline void alias_ui_margin

static inline void alias_ui_center(alias_ui * ui) {
  alias_ui__push_scope(alias_ui_Constraint_loosen(ui
  ui->constraint.min = alias_ui_Size_ZERO;
}

static inline void alias_ui_text(alias_ui * ui, const char * text) {
  
}

#endif
