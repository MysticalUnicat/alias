// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_DATA_STRUCTURE_BVH_H_
#define _ALIAS_DATA_STRUCTURE_BVH_H_

#include <alias/data_structure/aabb.h>
#include <stdint.h>

typedef struct alias_BVH2D_Node {
  int32_t      p, b, c;
  alias_AABB2D A, B, C;
} alias_BVH2D_Node;

typedef struct alias_BVH2D {
  uint32_t num_nodes;
  alias_BVH2D_Node * nodes;
} alias_BVH2D;

#if 0
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
  X(uint32_t,               P_ref) \
  /* A_row is the current row */ \
  /* A_box is constructed from B_box and C_box */ \
  X(alias_AABB2D,           B_box) \
  X(alias_AABB2D,           C_box) \
  X(alias_BVH2D_NodeRef,    B_ref) \
  X(alias_BVH2D_NodeRef,    C_ref) \
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
  alias_BVH2D_NodeRef * A_ref = &bvh->root
                    , * P_ref = NULL, * B_ref = NULL, * C_ref = NULL, * D_ref = NULL, * E_ref = NULL, * F_ref = NULL, * G_ref = NULL;
  alias_AABB2D B_box = *(const alias_AABB2D *)alias_SOA_read(&bvh->nodes, A_ref->value, alias_BVH2D_NodeColumn_B_box), D_box, E_box
             , C_box = *(const alias_AABB2D *)alias_SOA_read(&bvh->nodes, A_ref->value, alias_BVH2D_NodeColumn_C_box), F_box, G_box
             , A_box = alias_AABB2D_union(B_box, C_box)
             , AL_box = alias_AABB2D_union(A_box, leaf_box)
             ;
  alias_R SU_A = alias_AABB2D_surface_area(A_box)
        , SU_AL = alias_AABB2D_surface_area(AL_box)
        , dSU_AL = SU_AL - SU_A
        ;
  alias_BVH2D_NodeColumn P_child_column;
  while(A_ref->is_node) {
    B_ref = (alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, A_ref->value, alias_BVH2D_NodeColumn_B_row);
    C_ref = (alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, A_ref->value, alias_BVH2D_NodeColumn_C_row);
    B_box = *(const alias_AABB2D *)alias_SOA_read(&bvh->nodes, A_ref->value, alias_BVH2D_NodeColumn_B_box);
    C_box = *(const alias_AABB2D *)alias_SOA_read(&bvh->nodes, A_ref->value, alias_BVH2D_NodeColumn_C_box);
    alias_AABB2D BL_box = alias_AABB2D_union(B_box, leaf_box)
               , CL_box = alias_AABB2D_union(C_box, leaf_box);
    alias_R SU_B = alias_AABB2D_surface_area(B_box)
          , SU_C = alias_AABB2D_surface_area(C_box)
          , SU_BL = alias_AABB2D_surface_area(BL_box)
          , SU_CL = alias_AABB2D_surface_area(CL_box)
          , dSU_BL = SU_BL - SU_B
          , dSU_CL = SU_CL - SU_C
          , A_cost = SU_AL
          , B_cost = (B_ref->is_node ? dSU_BL : SU_BL) + dSU_AL
          , C_cost = (C_ref->is_node ? dSU_CL : SU_CL) + dSU_AL;
    if(A_cost < B_cost && A_cost < C_cost) {
      break;
    }
    P_ref = A_ref;
    if(B_cost < C_cost) {
      P_child_column = alias_BVH2D_NodeColumn_B_row;
      A_ref = B_ref;
      A_box = B_box;
      AL_box = BL_box;
      SU_AL = SU_BL;
      dSU_AL = dSU_BL;
    } else {
      P_child_column = alias_BVH2D_NodeColumn_C_row;
      A_ref = C_ref;
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

  *(uint32_t *)alias_SOA_write(&bvh->nodes, NP_index, alias_BVH2D_NodeColumn_P_row) = P_ref->index;
  *(alias_AABB2D *)alias_SOA_write(&bvh->nodes, NP_index, alias_BVH2D_NodeColumn_B_box) = B_box;
  *(alias_AABB2D *)alias_SOA_write(&bvh->nodes, NP_index, alias_BVH2D_NodeColumn_C_box) = C_box;
  *(alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, NP_index, alias_BVH2D_NodeColumn_B_row) = *A_ref;
  *(alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, NP_index, alias_BVH2D_NodeColumn_C_row) = (alias_BVH2D_NodeRef) { .index = leaf_row };

  alias_BVH2D_NodeRef NP_row = (alias_BVH2D_NodeRef) { .is_node = 1, .index = NP_index };

  *(alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, A_ref->index, alias_BVH2D_NodeColumn_P_row) = NP_row;
  *(alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, leaf_row, alias_BVH2D_NodeColumn_P_row) = NP_row;

  if(P_ref != NULL) {
    *(alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, P_ref->index, P_child_column) = NP_row;
  } else {
    bvh->root = NP_row;
  }

  // stage 3: refitting
  /*           (A)        */
  /*        /      \      */
  /*     (B)       (C)    */
  /*    /  \      /  \    */
  /* (D)   (E) (F)    (G) */
  enum {
    NONE,
    DE,
    FG
  } known = NONE;
  B_ref = A_ref;
  B_box = A_box;
  C_ref = &(alias_BVH2D_NodeRef) { .index = leaf_row };
  C_box = leaf_box;
  A_ref = &NP_row;
  A_box = alias_AABB2D_union(B_box, C_box);
  while(A_ref->value != 0) {
    alias_R B_noswap_score = alias_AABB2D_surface_area(C_box);
    alias_R BF_swap_score = alias_R_MAX;
    alias_R BG_swap_score = alias_R_MAX;

    alias_R C_noswap_score = alias_AABB2D_surface_area(B_box);
    alias_R CD_swap_score = alias_R_MAX;
    alias_R CE_swap_score = alias_R_MAX;
    
    if(C_ref->is_node) {
      // B <-> {F,G} is possible
      if(known != FG) {
        F_ref = (alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, C_ref->index, alias_BVH2D_NodeColumn_B_ref);
        G_ref = (alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, C_ref->index, alias_BVH2D_NodeColumn_C_ref);
        F_box = *(alias_AABB2D *)alias_SOA_write(&bvh->nodes, C_ref->index, alias_BVH2D_NodeColumn_B_box);
        G_box = *(alias_AABB2D *)alias_SOA_write(&bvh->nodes, C_ref->index, alias_BVH2D_NodeColumn_C_box);
      }

      BF_swap_score = alias_AABB2D_surface_area(alias_AABB2D_union(B_box, G_box));
      BG_swap_score = alias_AABB2D_surface_area(alias_AABB2D_union(B_box, F_box));
    }

    if(!B_ref->is_node) {
      // C <-> {D,E} is possible
      if(known != DE) {
        D_ref = (alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, B_ref->index, alias_BVH2D_NodeColumn_B_ref);
        E_ref = (alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, B_ref->index, alias_BVH2D_NodeColumn_C_ref);
        D_box = *(alias_AABB2D *)alias_SOA_write(&bvh->nodes, B_ref->index, alias_BVH2D_NodeColumn_B_box);
        E_box = *(alias_AABB2D *)alias_SOA_write(&bvh->nodes, B_ref->index, alias_BVH2D_NodeColumn_C_box);
      }

      CD_swap_score = alias_AABB2D_surface_area(alias_AABB2D_union(B_box, E_box));
      CE_swap_score = alias_AABB2D_surface_area(alias_AABB2D_union(B_box, D_box));
    }

    alias_R best_B_swap = ALIAS_MIN_PAIR(BF_swap_score, BG_swap_score);
    bool swap_B = B_noswap_score > best_B_swap;

    alias_R best_C_swap = ALIAS_MIN_PAIR(CD_swap_score, CE_swap_score);
    bool swap_C = C_noswap_score > best_C_swap;

    if(swap_B && swap_C) {
      *(alias_BVH2D_NodeRef *)alias_SOA_write(&bvh->nodes, B_ref->index, alias_BVH2D_NodeColumn_P_ref)
      if(best_B_swap < best_B_swap) {
        swap_C = false;
      } else {
        swap_B = false;
      }
    }

    if(swap_B) {
      if(BF_swap_score < BG_swap_score) {
      }
      if(BF_swap_score > BG_swap_score) {
      }
    }

    if(swap_C) {
      if(CD_swap_score < CE_swap_score) {
      }
      if(CD_swap_score > CE_swap_score) {
      }
    }
  }
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
#endif

#endif
