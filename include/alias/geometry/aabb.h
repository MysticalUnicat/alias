// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_GEOMETRY_AABB_H_
#define _ALIAS_GEOMETRY_AABB_H_

#include <alias/math.h>

typedef struct alias_AABB2D {
  struct { alias_R x; alias_R y; } min, max;
} alias_AABB2D;

static inline alias_R alias_AABB2D_surface_area(alias_AABB2D aabb) {
  return alias_R_TWO * ((aabb.max.x - aabb.min.x) + (aabb.max.y - aabb.min.y));
}

static inline alias_AABB2D alias_AABB2D_union(alias_AABB2D a, alias_AABB2D b) {
  return (alias_AABB2D) {
      .min.x = alias_min(a.min.x, b.min.x)
    , .min.y = alias_min(a.min.y, b.min.y)
    , .max.x = alias_max(a.max.x, b.max.x)
    , .max.y = alias_max(a.max.y, b.max.y)
  };
}

static inline alias_AABB2D alias_AABB2D_intersect(alias_AABB2D a, alias_AABB2D b) {
  return (alias_AABB2D) {
      .min.x = alias_max(a.min.x, b.min.x)
    , .min.y = alias_max(a.min.y, b.min.y)
    , .max.x = alias_min(a.max.x, b.max.x)
    , .max.y = alias_min(a.max.y, b.max.y)
  };
}

static inline bool alias_AABB2D_intersects(alias_AABB2D a, alias_AABB2D b) {
  return !(a.min.x > b.max.x || a.min.y > b.max.y || a.max.x < b.min.x || a.max.y < b.min.y);
}

#endif
