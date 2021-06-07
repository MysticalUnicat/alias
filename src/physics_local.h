#ifndef _ALIAS_PHYSICS_LOCAL_H_
#define _ALIAS_PHYSICS_LOCAL_H_

#include <alias/physics.h>
#include <alias/data_structure/bvh.h>

typedef struct alias_Physics2DLinearSpeed {
  alias_R speed;
  alias_Normal2D direction;
} alias_Physics2DLinearSpeed;

typedef struct alias_Physics2DBoundingBox {
  alias_AABB2D value;
} alias_Physics2DBoundingBox;

typedef struct alias_Physics2DBVHNode {
  alias_AABB2D aabb;

  alias_ecs_EntityHandle parent;

  alias_ecs_EntityHandle child_1;
  alias_ecs_EntityHandle child_2;

  bool leaf;
} alias_Physics2DBVHNode;

static inline void _cache_aabb_circle(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;

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

  alias_Physics2DBoundingBox * aabb = (alias_Physics2DBoundingBox *)data[0];
  const alias_LocalToWorld2D * local_to_world = (const alias_LocalToWorld2D *)data[1];
  const alias_Physics2DCollisionLine * line = (const alias_Physics2DCollisionLine *)data[2];

  alias_Point2D p1 = alias_multiply_Affine2D_Point2D(local_to_world->value, line->p1);
  alias_Point2D p2 = alias_multiply_Affine2D_Point2D(local_to_world->value, line->p2);

  aabb->value.min.x = alias_min(p1.x, p2.x);
  aabb->value.min.y = alias_min(p1.y, p2.y);
  aabb->value.max.x = alias_max(p1.x, p2.x);
  aabb->value.max.y = alias_max(p1.y, p2.y);
}

static inline void _cache_aabb_polygon(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;

  alias_Physics2DBoundingBox * aabb = (alias_Physics2DBoundingBox *)data[0];
  const alias_LocalToWorld2D * local_to_world = (const alias_LocalToWorld2D *)data[1];
  const alias_Physics2DCollisionPolygon * polygon = (const alias_Physics2DCollisionPolygon *)data[2];

  alias_Point2D p = alias_multiply_Affine2D_Point2D(local_to_world->value, polygon->points[0]);
  aabb->value.min.x = p.x;
  aabb->value.min.y = p.y;
  aabb->value.max.x = p.x;
  aabb->value.max.y = p.y;

  for(uint32_t i = 1; i < polygon->num_points; i++) {
    p = alias_multiply_Affine2D_Point2D(local_to_world->value, polygon->points[0]);
    aabb->value.min.x = alias_min(aabb->value.min.x, p.x);
    aabb->value.min.y = alias_min(aabb->value.min.y, p.y);
    aabb->value.max.x = alias_max(aabb->value.max.x, p.x);
    aabb->value.max.y = alias_max(aabb->value.max.y, p.y);
  }
}

static inline void alias_cache_aabb(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->cache_aabb_circle_query, (alias_ecs_QueryCB) { _cache_aabb_circle, NULL });
  alias_ecs_execute_query(instance, bundle->cache_aabb_line_query, (alias_ecs_QueryCB) { _cache_aabb_line, NULL });
  alias_ecs_execute_query(instance, bundle->cache_aabb_polygon_query, (alias_ecs_QueryCB) { _cache_aabb_polygon, NULL });
}

// =============================================================================================================================================================


static inline void _build_bvh_leaf(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;

  //alias_Physics2DBundle * bundle = (alias_Physics2DBundle *)ud;

  alias_Physics2DBVHNode * node = (alias_Physics2DBVHNode *)data[0];
  const alias_Physics2DBoundingBox * aabb = (alias_Physics2DBoundingBox *)data[1];

  if(!node->leaf) {
    //_insert(instance, bundle->Physics2DBVHNode_component, &bundle->bvh_root, entity);
    node->leaf = true;
  } else if(!alias_AABB2D_is_contained(node->aabb, aabb->value)) {
    node->aabb = alias_AABB2D_enlarge(aabb->value, 10.0f); // TODO do by cached speed
    // REMOVE
    //_insert(instance, bundle->Physics2DBVHNode_component, &bundle->bvh_root, entity);
  }
}

static inline void alias_build_bvh(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->build_bvh_query, (alias_ecs_QueryCB) { _build_bvh_leaf, bundle });
}

#endif
