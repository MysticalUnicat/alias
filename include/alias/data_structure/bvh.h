#ifndef _ALIAS_DATA_STRUCTURE_BVH_H_
#define _ALIAS_DATA_STRUCTURE_BVH_H_

#include <alias/data_structure/aabb.h>
#include <alias/data_structure/soa.h>

/*           (P)        */
/*            |         */
/*           (A)        */
/*        /      \      */
/*     (B)       (C)    */
/*    /  \      /  \    */
/* (D)   (E) (F)    (G) */

typedef struct alias_BVH2D_NodeRef {
  union {
    struct {
      uint32_t is_node : 1;
      uint32_t index : 31;
    };
    uint32_t value;
  };
} alias_BVH2D_NodeRef;

#define ALIAS_BVH2D_NODE_X(X) \
  X(uint32_t,               P_row) \
  /* A_row is the current row */ \
  /* A_box is constructed from B_box and C_box */ \
  X(alias_AABB2D,           B_box) \
  X(alias_AABB2D,           C_box) \
  X(alias_BVH2D_NodeRef,    B_row) \
  X(alias_BVH2D_NodeRef,    C_row) \
  /* {D,E,F,G}_{row,box} are looked up */

#define X(A, B) alias_BVH2D_NodeColumn_##B,
typedef enum alias_BVH2D_NodeColumn {
  ALIAS_BVH2D_NODE_X(X)
} alias_BVH2D_NodeColumn;
#undef X

typedef struct alias_BVH2D {
  alias_SOA nodes;
  alias_BVH2D_NodeRef root;
} alias_BVH2D;

static inline void alias_BVH2D__remove(alias_BVH2D * bvh, uint32_t leaf) {
  uint32_t parent = *(const uint32_t *)alias_SOA_read(&bvh->nodes, leaf, alias_BVH2D_NodeColumn_P_row);
  alias_BVH2D_NodeRef * parent_B_row = (alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, parent, alias_BVH2D_NodeColumn_B_row);
  alias_BVH2D_NodeRef * parent_C_row = (alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, parent, alias_BVH2D_NodeColumn_C_row);
  if(leaf == parent_B_row->index) {
    parent_B_row->value = 0;
  }
  if(leaf == parent_C_row->index) {
    parent_C_row->value = 0;
  }
}

static inline uint32_t alias_BVH2D__allocate_node(alias_BVH2D * bvh, alias_MemoryAllocationCallback * cb) {
  return alias_SOA_allocate(&bvh->nodes, cb);
}

static inline void alias_BVH2D__insert(alias_BVH2D * bvh, alias_MemoryAllocationCallback * cb, uint32_t leaf_row, alias_AABB2D leaf_box) {
  // stage 1: find best sibling
  alias_BVH2D_NodeRef * A_row = &bvh->root
                    , * P_row = NULL, * B_row = NULL, * C_row = NULL;
  alias_AABB2D B_box = *(const alias_AABB2D *)alias_SOA_read(&bvh->nodes, A_row->value, alias_BVH2D_NodeColumn_B_box)
             , C_box = *(const alias_AABB2D *)alias_SOA_read(&bvh->nodes, A_row->value, alias_BVH2D_NodeColumn_C_box)
             , A_box = alias_AABB2D_union(B_box, C_box)
             , AL_box = alias_AABB2D_union(A_box, leaf_box)
             ;
  alias_R SU_A = alias_AABB2D_surface_area(A_box)
        , SU_AL = alias_AABB2D_surface_area(AL_box)
        , dSU_AL = SU_AL - SU_A
        ;
  alias_BVH2D_NodeColumn P_child_column;
  while(A_row->is_node) {
    B_row = (alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, A_row->value, alias_BVH2D_NodeColumn_B_row);
    C_row = (alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, A_row->value, alias_BVH2D_NodeColumn_C_row);
    B_box = *(const alias_AABB2D *)alias_SOA_read(&bvh->nodes, A_row->value, alias_BVH2D_NodeColumn_B_box);
    C_box = *(const alias_AABB2D *)alias_SOA_read(&bvh->nodes, A_row->value, alias_BVH2D_NodeColumn_C_box);
    alias_AABB2D BL_box = alias_AABB2D_union(B_box, leaf_box)
               , CL_box = alias_AABB2D_union(C_box, leaf_box);
    alias_R SU_B = alias_AABB2D_surface_area(B_box)
          , SU_C = alias_AABB2D_surface_area(C_box)
          , SU_BL = alias_AABB2D_surface_area(BL_box)
          , SU_CL = alias_AABB2D_surface_area(CL_box)
          , dSU_BL = SU_BL - SU_B
          , dSU_CL = SU_CL - SU_C
          , A_cost = SU_AL
          , B_cost = (B_row->is_node ? dSU_BL : SU_BL) + dSU_AL
          , C_cost = (C_row->is_node ? dSU_CL : SU_CL) + dSU_AL;
    if(A_cost < B_cost && A_cost < C_cost) {
      break;
    }
    P_row = A_row;
    if(B_cost < C_cost) {
      P_child_column = alias_BVH2D_NodeColumn_B_row;
      A_row = B_row;
      A_box = B_box;
      AL_box = BL_box;
      SU_AL = SU_BL;
      dSU_AL = dSU_BL;
    } else {
      P_child_column = alias_BVH2D_NodeColumn_C_row;
      A_row = C_row;
      A_box = C_box;
      AL_box = CL_box;
      SU_AL = SU_CL;
      dSU_AL = dSU_CL;
    }
  }

  // stage 2: create new parent
  /*        (P)            (P)    */
  /*         |              |     */
  /*        (A)     ->     (NP)   */
  /*     /      \        /    \   */
  /*  (B)       (C)    (A)    (L) */
  uint32_t NP_index = alias_BVH2D__allocate_node(bvh, cb);

  *(uint32_t *)alias_SOA_write(&bvh->nodes, NP_index, alias_BVH2D_NodeColumn_P_row) = P_row->index;
  *(alias_AABB2D *)alias_SOA_write(&bvh->nodes, NP_index, alias_BVH2D_NodeColumn_B_box) = B_box;
  *(alias_AABB2D *)alias_SOA_write(&bvh->nodes, NP_index, alias_BVH2D_NodeColumn_C_box) = C_box;
  *(alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, NP_index, alias_BVH2D_NodeColumn_B_row) = *A_row;
  *(alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, NP_index, alias_BVH2D_NodeColumn_C_row) = (alias_BVH2D_NodeRef) { .index = leaf_row };

  alias_BVH2D_NodeRef NP_row = (alias_BVH2D_NodeRef) { .is_node = 1, .index = NP_index };

  *(alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, A_row->index, alias_BVH2D_NodeColumn_P_row) = NP_row;
  *(alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, leaf_row, alias_BVH2D_NodeColumn_P_row) = NP_row;

  if(P_row != NULL) {
    *(alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, P_row->index, P_child_column) = NP_row;
  } else {
    bvh->root = NP_row;
  }

  // stage 3: refitting
  
}

static inline void alias_BVH2D_initialize(alias_BVH2D * bvh, alias_MemoryAllocationCallback * cb) {
  alias_SOA_create(&bvh->nodes, cb, 5, (size_t[]){ 
    #define X(A, B) sizeof(A),
    ALIAS_BVH2D_NODE_X(X)
    #undef X
  }, 0);
  bvh->root.value = 0;
}

static inline uint32_t alias_BVH2D_insert_leaf(alias_BVH2D * bvh, alias_MemoryAllocationCallback * cb, alias_AABB2D box) {
  uint32_t node = alias_BVH2D__allocate_node(bvh, cb);
  alias_BVH2D__insert(bvh, cb, node, box);
  return node;
}

static inline void alias_BVH2D_move_leaf(alias_BVH2D * bvh, alias_MemoryAllocationCallback * cb, alias_AABB2D box, uint32_t leaf_node) {
  alias_BVH2D__remove(bvh, leaf_node);
  alias_BVH2D__insert(bvh, cb, leaf_node, box);
}

static inline void alias_BVH2D_remove_leaf(alias_BVH2D * bvh, uint32_t leaf_node) {
  alias_BVH2D__remove(bvh, leaf_node);
}

#if 0
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
  //           (A)        |
  //        /      \      |
  //     (B)       (C)    |
  //    /  \      /  \    |
  // (D)   (E) (F)    (G) |
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
#endif

#endif // include/alias/data_structure/bvh_h_INCLUDED

