#ifndef _ALIAS_UI_H_
#define _ALIAS_UI_H_

#include <stdarg.h>

#include <alias/memory.h>
#include <alias/color.h>

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

typedef struct alias_ui_Input {
  alias_ui_Size screen_size;
} alias_ui_Input;

typedef struct alias_ui_Output {
  uint32_t things;
} alias_ui_Output;

alias_ui_Result alias_ui_initialize(alias_MemoryCB * mcb, alias_ui * * ui_ptr);
alias_ui_Result alias_ui_free(alias_ui * ui, alias_MemoryCB * mcb);

alias_ui_Result alias_ui_begin_frame(alias_ui * ui, alias_MemoryCB * mcb, const alias_ui_Input * input);
void alias_ui_center(alias_ui * ui);
void alias_ui_font_color(alias_ui * ui, alias_Color color);
void alias_ui_textv(alias_ui * ui, const char * format, va_list ap);
alias_ui_Result alias_ui_end_frame(alias_ui * ui, alias_MemoryCB * mcb, alias_ui_Output * output);

static inline void alias_ui_text(alias_ui * ui, const char * format, ...) {
  va_list ap;
  va_start(ap, format);
  alias_ui_textv(ui, format, ap);
  va_end(ap);
}
 
#endif
