#ifndef _ALIAS_PHYSICS_LOCAL_H_
#define _ALIAS_PHYSICS_LOCAL_H_

#include <alias/physics.h>

typedef struct alias_AABB2D {
  alias_Vector2D min;
  alias_Vector2D max;
} alias_AABB2D;

static inline alias_AABB2D alias_AABB2D_union(alias_AABB2D a, alias_AABB2D b) {
  return (alias_AABB2D) {
      .min.x = alias_min(a.min.x, b.min.x)
    , .min.y = alias_min(a.min.y, b.min.y)
    , .max.x = alias_max(a.max.x, b.max.x)
    , .max.y = alias_max(a.max.y, b.max.y)
  };
}

static inline alias_R alias_AABB2D_surface_area(alias_AABB2D aabb) {
  alias_Vector2D d = alias_subtract_Vector2D_Vector2D(aabb.max, aabb.min);
  return alias_R_TWO * (d.x + d.y);
}

typedef struct alias_Physics2DLinearSpeed {
  alias_R speed;
  alias_Normal2D direction;
} alias_Physics2DLinearSpeed;

typedef struct alias_BoundingVolumeHierarchy2D_Node {
  alias_AABB2D bounding_box;

  alias_ecs_EntityHandle parent;

  union {
    struct {
      alias_AABB2D bvh_bounding_box;
    } leaf;
    struct {
      alias_ecs_EntityHandle child_1;
      alias_ecs_EntityHandle child_2;
    } node;
  };
} alias_BoundingVolumeHierarchy2D_Node;

typedef struct alias_BoundingVolumeHierarchy2D {
  alias_ecs_EntityHandle root;
} alias_BoundingVolumeHierarchy2D;

#endif
