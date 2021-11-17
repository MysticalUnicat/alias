// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
#define R_to_u8(X) (alias_max(0, alias_min(1, (alias_R)(X))) * (alias_R)255)

static inline alias_Color alias_Color_from_rgb_u8(uint8_t r, uint8_t g, uint8_t b) {
  return (alias_Color) { u8_to_R(r), u8_to_R(g), u8_to_R(b), alias_R_ONE };
}

static inline uint32_t alias_Color_to_rgba_u8_packed(alias_Color c) {
  union {
    uint32_t i;
    uint8_t b[4];
  } u;
  u.b[0] = R_to_u8(c.r);
  u.b[1] = R_to_u8(c.g);
  u.b[2] = R_to_u8(c.b);
  u.b[3] = R_to_u8(c.a);
  return u.i;
}

#endif
