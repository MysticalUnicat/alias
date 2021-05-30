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

typedef struct alias_Physics2DBoundingBox {
  alias_AABB2D value;
} alias_Physics2DBoundingBox;

typedef struct alias_Physics2DBVHNode {
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

  bool inserted;
} alias_Physics2DBVHNode;

static inline void _cache_aabb_circle(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  (void)data;

  alias_Physics2DBoundingBox * aabb = (alias_Physics2DBoundingBox *)data[0];
  const alias_LocalToWorld2D * local_to_world = (const alias_LocalToWorld2D *)data[1];
  const alias_Physics2DCollisionCircle * circle = (const alias_Physics2DCollisionCircle *)data[2];

  aabb->value.min.x = local_to_world->value._13 - circle->radius;
  aabb->value.min.y = local_to_world->value._23 - circle->radius;
  aabb->value.max.x = local_to_world->value._13 + circle->radius;
  aabb->value.max.y = local_to_world->value._23 + circle->radius;
}

static inline void _cache_aabb_line(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  (void)data;

  
}

static inline void _cache_aabb_polygon(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  (void)data;


}

static inline void alias_ecs_cache_aabb(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->cache_aabb_circle_query, (alias_ecs_QueryCB) { _cache_aabb_circle, NULL });
  alias_ecs_execute_query(instance, bundle->cache_aabb_line_query, (alias_ecs_QueryCB) { _cache_aabb_line, NULL });
  alias_ecs_execute_query(instance, bundle->cache_aabb_polygon_query, (alias_ecs_QueryCB) { _cache_aabb_polygon, NULL });
}

#endif
