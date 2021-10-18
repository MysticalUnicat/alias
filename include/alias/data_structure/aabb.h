#ifndef _ALIAS_DATA_STRUCTURE_AABB_H_
#define _ALIAS_DATA_STRUCTURE_AABB_H_

#include <alias/math.h>

typedef struct alias_AABB2D {
  union {
    struct {
      alias_R min_x;
      alias_R min_y;
      alias_R max_x;
      alias_R max_y;
    };
    struct {
      // coordinates are top left
      alias_R left;
      alias_R top;
      alias_R right;
      alias_R bottom;
    };
  };
} alias_AABB2D;

static inline alias_AABB2D alias__construct_AABB2D(alias_R minx, alias_R miny, alias_R maxx, alias_R maxy) {
  return (alias_AABB2D) {
      .min_x = minx
    , .min_y = miny
    , .max_x = maxx
    , .max_y = maxy
  };
}

static inline alias_AABB2D alias_AABB2D_union(alias_AABB2D a, alias_AABB2D b) {
  return alias__construct_AABB2D(
      alias_min(a.min_x, b.min_x)
    , alias_min(a.min_y, b.min_y)
    , alias_max(a.max_x, b.max_x)
    , alias_max(a.max_y, b.max_y)
  );
}

static inline alias_AABB2D alias_AABB2D_intersection(alias_AABB2D a, alias_AABB2D b) {
  return alias__construct_AABB2D(
      alias_max(a.min_x, b.min_x)
    , alias_max(a.min_y, b.min_y)
    , alias_min(a.max_x, b.max_x)
    , alias_min(a.max_y, b.max_y)
  );
}

static inline bool alias_AABB2D_valid(alias_AABB2D aabb) {
  return aabb.min_x < aabb.max_x && aabb.min_y < aabb.max_y;
}

static inline alias_R alias_AABB2D_surface_area(alias_AABB2D aabb) {
  return alias_R_TWO * (aabb.max_x - aabb.min_x + aabb.max_y - aabb.min_y);
}

static inline alias_R alias_AABB2D_volume(alias_AABB2D aabb) {
  float size_x = aabb.max_x - aabb.min_x;
  float size_y = aabb.max_y - aabb.min_y;
  return (size_x * size_y);
}

static inline alias_AABB2D alias_AABB2D_enlarge(alias_AABB2D aabb, alias_R uniform_amount) {
  return alias__construct_AABB2D(
      aabb.min_x - uniform_amount
    , aabb.min_y - uniform_amount
    , aabb.max_x + uniform_amount
    , aabb.max_y + uniform_amount
  );
}

static inline bool alias_AABB2D_is_contained(alias_AABB2D a, alias_AABB2D b) {
  return (a.left <= b.left && a.top <= b.top && a.right >= b.right && a.bottom >= b.bottom);
}

static inline bool alias_AABB2D_intersects(alias_AABB2D a, alias_AABB2D b) {
  return alias_AABB2D_valid(alias_AABB2D_intersection(a, b));
}

#endif // include/alias/data_structure/aabb2d_h_INCLUDED

