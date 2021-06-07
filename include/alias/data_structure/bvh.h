#ifndef _ALIAS_DATA_STRUCTURE_BVH_H_
#define _ALIAS_DATA_STRUCTURE_BVH_H_

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
    alias_R B_noswap_score = C.node->aabb.surface_area;
    alias_R BF_swap_score = alias_R_MAX;
    alias_R BG_swap_score = alias_R_MAX;

    alias_R C_noswap_score = B.node->aabb.surface_area;
    alias_R CD_swap_score = alias_R_MAX;
    alias_R CE_swap_score = alias_R_MAX;
    
    if(!C.node->leaf) {
      // B <-> {F,G} is possible
      if(known != FG) {
        F = _extract(instance, component, C.node->child_1);
        G = _extract(instance, component, C.node->child_2);
      }

      BF_swap_score = alias_AABB2D_union(B.node->aabb, G.node->aabb).surface_area;
      BG_swap_score = alias_AABB2D_union(B.node->aabb, F.node->aabb).surface_area;
    }

    if(!child1.node->leaf) {
      // C <-> {D,E} is possible
      if(known != DE) {
        D = _extract(instance, component, B.node->child_1);
        E = _extract(instance, component, B.node->child_2);
      }

      CD_swap_score = alias_AABB2D_union(B.node->aabb, E.node->aabb).surface_area;
      CE_swap_score = alias_AABB2D_union(B.node->aabb, D.node->aabb).surface_area;
    }

    alias_R best_B_swap = ALIAS_MIN_PAIR(BF_swap_score, BG_swap_score);
    bool swap_B = B_noswap_score > best_B_swap;

    alias_R best_C_swap = ALIAS_MIN_PAIR(CD_swap_score, CE_swap_score);
    bool swap_C = C_noswap_score > best_C_swap;

    if(swap_B && swap_C) {
      if(best_B_swap < best_B_swap) {
        swap_C = false;
      } else {
        swap_B = false;
      }
    }

    struct extracted_node temp;

    if(swap_B) {
      C.node->child_1 = B.entity;
      B.node->parent = C.entity;
      if(BF_swap_score < BG_swap_score) {
        F.node->parent = A.entity;
        A.node->child_1 = F.entity;


      }
      if(BF_swap_score > BG_swap_score) {
        G.node->parent = A.entity;
        A.node->child_1 = G.entity;
      }
    }

    if(swap_C) {
      B.node->child_1 = C.entity;
      C.node->parent = B.entity;
      if(CD_swap_score < CE_swap_score) {
        D.node->parent = A.entity;
        A.node->child_1 = D.entity;
      }
      if(CD_swap_score > CE_swap_score) {
        E.node->parent = A.entity;
        A.node->child_1 = E.entity;
      }
    }
    
    parent.node->aabb = alias_AABB2D_union(B.node->aabb, C.node->aabb);

    struct extracted_node prev_A = A;
    A = _extract(instance, component, parent.node->parent);
    if(A.node->child_1 == prev_A.entity) {
      B = A;
      C = _extract(instance, component, parent.node->child_2);
    } else {
      child1 = _extract(instance, component, parent.node->child_1);
      child2 = prev_parent;
    }
  }
}
#endif // include/alias/data_structure/bvh_h_INCLUDED

