#ifndef _ALIAS_PHYSICS_LOCAL_H_
#define _ALIAS_PHYSICS_LOCAL_H_

#include <alias/physics.h>

typedef struct alias_AABB2D {
  union {
    struct {
      alias_Vector2D min;
      alias_Vector2D max;
    };
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
  alias_R surface_area;
} alias_AABB2D;

static inline void alias__set_AABB2D_surface_area(alias_AABB2D * box) {
  alias_Vector2D d = alias_subtract_Vector2D_Vector2D(box->min, box->max);
  box->surface_area = alias_R_TWO * (d.x + d.y);
}

static inline alias_AABB2D alias__construct_AABB2D(alias_R minx, alias_R miny, alias_R maxx, alias_R maxy) {
  return (alias_AABB2D) {
      .min_x = minx
    , .min_y = miny
    , .max_x = maxx
    , .max_y = maxy
    , .surface_area = alias_R_TWO * (maxx - minx + maxy - miny)
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

static inline alias_R alias_AABB2D_volume(alias_AABB2D aabb) {
  alias_Vector2D d = alias_subtract_Vector2D_Vector2D(aabb.max, aabb.min);
  return (d.x * d.y);
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
struct extracted_node {
  alias_ecs_EntityHandle   entity;
  alias_Physics2DBVHNode * node;
};

static inline struct extracted_node _extract(alias_ecs_Instance * instance, alias_ecs_ComponentHandle component, alias_ecs_EntityHandle entity) {
  struct extracted_node enode;
  enode.entity = entity;
  alias_ecs_write_entity_component(instance, entity, component, (void **)&enode.node);
  return enode;
}

struct sibling_analysis {
  alias_AABB2D union_with_leaf;
  alias_R      union_delta;
};

static struct sibling_analysis _analyze_node(
    struct extracted_node enode
  , alias_AABB2D          leaf_aabb
) {
  struct sibling_analysis analysis;
  analysis.union_with_leaf = alias_AABB2D_union(enode.node->aabb, leaf_aabb);
  analysis.union_delta = analysis.union_with_leaf.surface_area - enode.node->aabb.surface_area;
  return analysis;
}

static inline void _insert(
    alias_ecs_Instance        * instance
  , alias_ecs_ComponentHandle   component
  , alias_ecs_EntityHandle    * root
  , alias_ecs_EntityHandle      _leaf
) {

  // stage 1: find best sibling
  struct extracted_node leaf = _extract(instance, component, _leaf);

  struct extracted_node parent, sibling, child1, child2;
  struct sibling_analysis parent_a, sibling_a, child1_a, child2_a;

  parent = _extract(instance, component, *root);
  parent_a = _analyze_node(parent, leaf.node->aabb);

  sibling = parent;
  sibling_a = parent_a;

  while(!sibling.node->leaf) {
    child1 = _extract(instance, component, parent.node->child_1);
    child2 = _extract(instance, component, parent.node->child_2);

    child1_a = _analyze_node(child1, leaf.node->aabb);
    child2_a = _analyze_node(child2, leaf.node->aabb);

    alias_R sibling_cost = sibling_a.union_with_leaf.surface_area;
    alias_R child1_cost = (child1.node->leaf ? child1_a.union_with_leaf.surface_area : child1_a.union_delta) + sibling_a.union_delta;
    alias_R child2_cost = (child2.node->leaf ? child2_a.union_with_leaf.surface_area : child2_a.union_delta) + sibling_a.union_delta;

    if(sibling_cost < child1_cost && sibling_cost < child2_cost) {
      break;
    }

    parent = sibling;
    if(child1_cost < child2_cost) {
      sibling = child1;
    } else {
      sibling = child2;
    }
  }

  // stage 2: create new parent
  alias_ecs_EntityHandle _new_parent;
  alias_ecs_spawn(
      instance
    , &(alias_ecs_EntitySpawnInfo) {
        .count = 1
      , .num_components = 1
      , .components = (alias_ecs_EntitySpawnComponent[]) {
          { .component = component
          , .data = (const void **)&(alias_Physics2DBVHNode) {
              .aabb = sibling_a.union_with_leaf
            , .parent = parent.entity
            , .child_1 = sibling.entity
            , .child_1 = _leaf
            }
          }
        }
      }
    , &_new_parent);

  sibling.node->parent = _new_parent;
  leaf.node->parent = _new_parent;

  if(sibling.entity != 0) {
    if(parent.node->child_1 == sibling.entity) {
      parent.node->child_1 = _new_parent;
    } else {
      parent.node->child_2 = _new_parent;
    }
  } else {
    *root = _new_parent;
  }

  parent = _extract(instance, component, _new_parent);

  // stage 3:
  //   walk back up the tree refitting AABBs
  //   in addition - we are balancing the tree as we go
  // 
  //           (A)
  //        /      \
  //     (B)       (C)
  //    /  \      /  \
  // (D)   (E) (F)    (G)
  // four possible rotations: B <-> F , B <-> G , C <-> D , C <-> E
  struct extracted_node
      A = parent
    , B = child1, D, E
    , C = child2, F, G
    ;
  enum {
    NONE,
    DE,
    FG
  } known = NONE;
  while(parent.entity != 0) {
    if(!C.node->leaf) {
      // B <-> {F,G} is possible
      if(known != FG) {
        F = _extract(instance, component, C.node->child_1);
        G = _extract(instance, component, C.node->child_2);
      }

      alias_AABB2D BF_swap_C_box = alias_AABB2D_union(B.node->aabb, G.node->aabb);
      alias_AABB2D BG_swap_C_box = alias_AABB2D_union(B.node->aabb, F.node->aabb);
    }
    if(!child1.node->leaf) {
      // C <-> {D,E} is possible
    }

    
    
    parent.node->aabb = alias_AABB2D_union(child1.node->aabb, child2.node->aabb);

    struct extracted_node prev_parent = parent;
    parent = _extract(instance, component, parent.node->parent);
    if(parent.node->child_1 == prev_parent.entity) {
      child1 = prev_parent;
      child2 = _extract(instance, component, parent.node->child_2);
    } else {
      child1 = _extract(instance, component, parent.node->child_1);
      child2 = prev_parent;
    }
  }
}

static inline void _build_bvh_leaf(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  alias_Physics2DBundle * bundle = (alias_Physics2DBundle *)ud;

  alias_Physics2DBVHNode * node = (alias_Physics2DBVHNode *)data[0];
  const alias_Physics2DBoundingBox * aabb = (alias_Physics2DBoundingBox *)data[1];

  if(!node->leaf) {
    _insert(instance, bundle->Physics2DBVHNode_component, &bundle->bvh_root, entity);
    node->leaf = true;
  } else if(!alias_AABB2D_is_contained(node->aabb, aabb->value)) {
    node->aabb = alias_AABB2D_enlarge(aabb->value, 10.0f); // TODO do by cached speed
    // REMOVE
    _insert(instance, bundle->Physics2DBVHNode_component, &bundle->bvh_root, entity);
  }
}

static inline void alias_build_bvh(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->build_bvh_query, (alias_ecs_QueryCB) { _build_bvh_leaf, bundle });
}

#endif
