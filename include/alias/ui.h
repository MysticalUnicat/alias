#ifndef _ALIAS_UI_H_
#define _ALIAS_UI_H_

#include <stdarg.h>

#include <alias/memory.h>
#include <alias/color.h>

#ifndef ALIAS_UI_INDEX_SIZE
#define ALIAS_UI_INDEX_SIZE 16
#endif

typedef struct alias_ui alias_ui;

typedef enum alias_ui_Result {
  alias_ui_Success,
  alias_ui_ErrorOutOfMemory
} alias_ui_Result;

typedef struct alias_ui_Size {
  alias_R width;
  alias_R height;
} alias_ui_Size;

typedef struct alias_ui_Constraint {
  alias_ui_Size min;
  alias_ui_Size max;
} alias_ui_Constraint;

typedef void (* alias_ui_TextSizeFn)(const char * buffer, alias_R size, alias_R max_width, alias_R * out_width, alias_R * out_height);
typedef void (* alias_ui_TextDrawFn)(const char * buffer, alias_R x, alias_R y, alias_R width, alias_R size, alias_Color color);

typedef struct alias_ui_Input {
  alias_ui_Size screen_size;

  alias_ui_TextSizeFn text_size;
  alias_ui_TextDrawFn text_draw;
} alias_ui_Input;

typedef struct alias_ui_OutputData {
  uint32_t length;
} alias_ui_OutputData;

typedef struct alias_ui_Output {
  uint32_t num_triangles;
  alias_memory_SubBuffer index_sub_buffer;

  uint32_t num_vertexes;
  alias_memory_SubBuffer xy_sub_buffer;
  alias_memory_SubBuffer rgba_sub_buffer;
  alias_memory_SubBuffer st_sub_buffer;
} alias_ui_Output;

// lifetime
alias_ui_Result alias_ui_initialize(alias_MemoryCB * mcb, alias_ui * * ui_ptr);
alias_ui_Result alias_ui_free(alias_ui * ui, alias_MemoryCB * mcb);

// frame
alias_ui_Result alias_ui_begin_frame(alias_ui * ui, alias_MemoryCB * mcb, const alias_ui_Input * input);
alias_ui_Result alias_ui_end_frame(alias_ui * ui, alias_MemoryCB * mcb, alias_ui_Output * output);

// layouting
// alias_ui_align_fractions(ui, x [0..1], y [0..1])
// alias_ui_center(...) -> alias_ui_align_fractions(ui, 0.5, 0.5)
void alias_ui_center(alias_ui * ui);
void alias_ui_override_size(alias_ui * ui, alias_R width, alias_R height);

void alias_ui_begin_vertical(alias_ui * ui);
void alias_ui_begin_horizontal(alias_ui * ui);
void alias_ui_begin_stack(alias_ui * ui);
void alias_ui_end(alias_ui * ui);

// per scope parameters
void alias_ui_font_size(alias_ui * ui, alias_R size);
void alias_ui_font_color(alias_ui * ui, alias_Color color);

// create elements
void alias_ui_textv(alias_ui * ui, const char * format, va_list ap);
void alias_ui_fill(alias_ui * ui, alias_Color color);

static inline void alias_ui_text(alias_ui * ui, const char * format, ...) {
  va_list ap;
  va_start(ap, format);
  alias_ui_textv(ui, format, ap);
  va_end(ap);
}
 
#endif
