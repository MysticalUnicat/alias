#ifndef _ALIAS_COLOR_H_
#define _ALIAS_COLOR_H_

#include <stdint.h>
#include <alias/math.h>

typedef struct alias_Color {
  alias_R r;
  alias_R g;
  alias_R b;
  alias_R a;
} alias_Color;

extern const alias_Color alias_Color_WHITE;
extern const alias_Color alias_Color_GRAY;
extern const alias_Color alias_Color_BLACK;
extern const alias_Color alias_Color_TRANSPARENT_BLACK;

#define u8_to_R(X) ((alias_R)(X) / (alias_R)255)

static inline alias_Color alias_Color_from_rgb_u8(uint8_t r, uint8_t g, uint8_t b) {
  return (alias_Color) { u8_to_R(r), u8_to_R(g), u8_to_R(b), alias_R_ONE };
}

#endif
