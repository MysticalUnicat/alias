#ifndef _ALIAS_COLOR_H_
#define _ALIAS_COLOR_H_

#include <alias/math.h>

typedef struct alias_Color {
  alias_R r;
  alias_R g;
  alias_R b;
  alias_R a;
} alias_Color;

extern const alias_Color alias_Color_WHITE;
extern const alias_Color alias_Color_BLACK;
extern const alias_Color alias_Color_TRANSPARENT_BLACK;

#endif
