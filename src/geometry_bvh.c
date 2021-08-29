#include <alias/geometry/bvh.h>
#include <alias/cpp.h>
#include <alias/log.h>

extern int abs(int);

// value == 0       - null
// value > 0        - node ((value >> 1) - 1)
// (value & 1) == 0 - b child
// (value & 1) == 1 - c child
typedef struct { uint32_t _; } ParentRef;
static const ParentRef ParentRef_INVALID = { 0 };
//static inline ParentRef ParentRef_from_raw(uint32_t i)  { return (ParentRef){ i }; }
static inline ParentRef ParentRef_for_b(uint32_t i) { return (ParentRef){ ((i + 1) << 1) | 0 }; }
static inline ParentRef ParentRef_for_c(uint32_t i) { return (ParentRef){ ((i + 1) << 1) | 1 }; }
//static inline ParentRef ParentRef_for_side(uint32_t i, int32_t s) { return (ParentRef){ ((i + 1) << 1) | !!s }; }
//static inline uint32_t ParentRef_to_raw(ParentRef p) { return p._; }
static inline bool ParentRef_is_valid(ParentRef p) { return p._ != 0; }
static inline bool ParentRef_is_b(ParentRef p) { return (p._ & 1) == 0 && p._ != 0; } // extra check to make sure it is also valid
static inline bool ParentRef_is_c(ParentRef p) { return (p._ & 1) == 1; }
//static inline bool ParentRef_is_side(ParentRef p, int32_t s) { return (p._ & 1) == !!s && p._ != 0; }
static inline int32_t ParentRef_unwrap_side(ParentRef p) { return (p._ & 1); }
static inline uint32_t ParentRef_unwrap_node_index(ParentRef p) { return (p._ >> 1) - 1; }

// value == 0 - null
// value > 0  - node (value - 1)
// value < 0  - leaf (-value - 1)
typedef struct { int32_t _; } ChildRef;
#define ChildRef_INVALID ((ChildRef){0})
static inline ChildRef ChildRef_from_raw(int32_t i) { return (ChildRef){ i }; }
static inline ChildRef ChildRef_from_node_index(uint32_t i) { return (ChildRef){ i + 1 }; }
static inline ChildRef ChildRef_from_leaf_index(uint32_t i) { return (ChildRef){ -((int32_t)i + 1) }; }
static inline int32_t ChildRef_to_raw(ChildRef child) { return child._; }
static inline bool ChildRef_is_valid(ChildRef child) { return child._ != 0; }
static inline bool ChildRef_is_node(ChildRef child) { return child._ > 0; }
static inline bool ChildRef_is_leaf(ChildRef child) { return child._ < 0; }
static inline uint32_t ChildRef_unwrap_node_index(ChildRef child) { return child._ - 1; }
static inline uint32_t ChildRef_unwrap_leaf_index(ChildRef child) { return -child._ - 1; }
static inline uint32_t ChildRef_unwrap_index(ChildRef child) { return (uint32_t)abs(child._) - 1; }
//static inline bool ChildRef_eq(ChildRef a, ChildRef b) { return a._ == b._; }

static inline ChildRef ChildRef_from_ParentRef(ParentRef parent) { return ChildRef_from_node_index(ParentRef_unwrap_node_index(parent)); }
static inline ParentRef ParentRef_from_ChildRef_b(ChildRef child) { return ParentRef_for_b(ChildRef_unwrap_node_index(child)); }
static inline ParentRef ParentRef_from_ChildRef_c(ChildRef child) { return ParentRef_for_c(ChildRef_unwrap_node_index(child)); }
//static inline ParentRef ParentRef_from_ChildRef_side(ChildRef child, int32_t s) { return ParentRef_for_side(ChildRef_unwrap_node_index(child), s); }

#define ALIAS_SOA_HELPER_SIZEOF(I, T, N) sizeof(T),
#define ALIAS_SOA_HELPER_ALIGNOF(I, T, N) alignof(T),

#define NODE_FIELDS(X) \
  X(0, ParentRef, parent) \
  X(1, alias_AABB2D, aabb1) \
  X(2, alias_AABB2D, aabb2) \
  X(3, ChildRef, child1) \
  X(4, ChildRef, child2)

#define LEAF_FIELDS(X) \
  X(0, ParentRef, parent) \
  X(1, uint64_t, payload)

static inline ParentRef * _parent_2d(alias_BVH2D * bvh, ChildRef self) {
  return (ParentRef *)alias_SOA_write(ChildRef_is_node(self) ? &bvh->nodes : &bvh->leafs, ChildRef_unwrap_index(self), 0);
}

static inline alias_AABB2D * _aabb_2d(alias_BVH2D * bvh, ChildRef self, int32_t side) {
  return (alias_AABB2D *)alias_SOA_write(&bvh->nodes, ChildRef_unwrap_node_index(self), 1 + !!side);
}

static inline ChildRef * _child_2d(alias_BVH2D * bvh, ChildRef self, int32_t side) {
  return (ChildRef *)alias_SOA_write(&bvh->nodes, ChildRef_unwrap_node_index(self), 3 + !!side);
}

/*
static inline uint64_t * _payload_2d(alias_BVH2D * bvh, ChildRef self) {
  return (uint64_t *)alias_SOA_write(&bvh->nodes, ChildRef_unwrap_leaf_index(self), 1);
}
*/

static inline ParentRef _read_parent_2d(const alias_BVH2D * bvh, ChildRef self) {
  return *(ParentRef *)alias_SOA_read(ChildRef_is_node(self) ? &bvh->nodes : &bvh->leafs, ChildRef_unwrap_index(self), 0);
}

static inline alias_AABB2D _read_aabb_2d(const alias_BVH2D * bvh, ChildRef self, int32_t side) {
  return *(alias_AABB2D *)alias_SOA_read(&bvh->nodes, ChildRef_unwrap_node_index(self), 1 + !!side);
}

static inline ChildRef _read_child_2d(const alias_BVH2D * bvh, ChildRef self, int32_t side) {
  return *(ChildRef *)alias_SOA_read(&bvh->nodes, ChildRef_unwrap_node_index(self), 3 + !!side);
}

/*
static inline uint64_t _read_payload_2d(const alias_BVH2D * bvh, ChildRef self) {
  return *(uint64_t *)alias_SOA_read(&bvh->nodes, ChildRef_unwrap_leaf_index(self), 1);
}
*/

bool alias_BVH2D_initialize(alias_BVH2D * bvh, alias_MemoryCB * mcb) {
  if(!alias_SOA_initialize(
      &bvh->nodes, mcb, 5
    , (size_t[]){ NODE_FIELDS(ALIAS_SOA_HELPER_SIZEOF) }
    , (size_t[]){ NODE_FIELDS(ALIAS_SOA_HELPER_ALIGNOF) }
    )) {
    return false;
  }

  if(!alias_SOA_initialize(
      &bvh->leafs, mcb, 2
    , (size_t[]){ LEAF_FIELDS(ALIAS_SOA_HELPER_SIZEOF) }
    , (size_t[]){ LEAF_FIELDS(ALIAS_SOA_HELPER_ALIGNOF) }
    )) {
    return false;
  }

  bvh->root = ChildRef_INVALID._;
  bvh->free_node = UINT32_MAX;
  bvh->free_leaf = UINT32_MAX;
  
  return true;
}

void alias_BVH2D_free(alias_BVH2D * bvh, alias_MemoryCB * mcb) {
  alias_SOA_free(&bvh->nodes, mcb);
  alias_SOA_free(&bvh->leafs, mcb);
}

static bool _allocate_node_2d(alias_BVH2D * bvh, alias_MemoryCB * mcb, ChildRef * result) {
  uint32_t node_index;
  if(bvh->free_node != UINT32_MAX) {
    node_index = bvh->free_node;
    bvh->free_node = *(uint32_t *)alias_SOA_read(&bvh->nodes, node_index, 0);
  } else {
    if(!alias_SOA_space_for(&bvh->nodes, mcb, 1)) {
      return false;
    }
    node_index = alias_SOA_push(&bvh->nodes);
  }
  *result = ChildRef_from_node_index(node_index);
  return true;
}

static void _free_node_2d(alias_BVH2D * bvh, ChildRef nr) {
  uint32_t node_index = ChildRef_unwrap_node_index(nr);
  *(uint32_t *)alias_SOA_read(&bvh->nodes, node_index, 0) = bvh->free_node;
  bvh->free_node = node_index;
}

static bool _allocate_leaf_2d(alias_BVH2D * bvh, alias_MemoryCB * mcb, ChildRef * result) {
  uint32_t leaf_index;
  if(bvh->free_leaf != UINT32_MAX) {
    leaf_index = bvh->free_leaf;
    bvh->free_leaf = *(uint32_t *)alias_SOA_read(&bvh->leafs, leaf_index, 0);
  } else {
    if(!alias_SOA_space_for(&bvh->leafs, mcb, 1)) {
      return false;
    }
    leaf_index = alias_SOA_push(&bvh->leafs);
  }
  *result = ChildRef_from_leaf_index(leaf_index);
  return true;
}

static void _free_leaf_2d(alias_BVH2D * bvh, ChildRef nr) {
  uint32_t leaf_index = ChildRef_unwrap_leaf_index(nr);
  *(uint32_t *)alias_SOA_read(&bvh->leafs, leaf_index, 0) = bvh->free_leaf;
  bvh->free_leaf = leaf_index;
}

static bool _insert_2d(alias_BVH2D * bvh, alias_MemoryCB * mcb, ChildRef leaf_nr, alias_AABB2D box) {
  // -----------------------------------------------------------------------------------------------------------------------------------------------------------
  // if the tree is empty, use the leaf as root
  if(bvh->root == ChildRef_INVALID._) {
    *_parent_2d(bvh, leaf_nr) = ParentRef_INVALID;
    bvh->root = leaf_nr._;
    bvh->root_box = box;
    return true;
  }

  // -----------------------------------------------------------------------------------------------------------------------------------------------------------
  // .       (P)       .
  // .        |        .
  // .       (A)       .
  // .     /     \     .
  // .   (B)     (C)   .
  // .   /  \    /  \  .
  // . (D) (E) (F) (G) .
  struct {
    ChildRef     ref;
    alias_AABB2D box;
    alias_R      box_sa;
  } A, B, C;
  ParentRef A_parent;

  // -----------------------------------------------------------------------------------------------------------------------------------------------------------
  // alocate here so pointers will be valid
  ChildRef new_node_ref;
  if(!_allocate_node_2d(bvh, mcb, &new_node_ref)) {
    return false;
  }

  // -----------------------------------------------------------------------------------------------------------------------------------------------------------
  // step 1: find the best sibling for the new leaf
  A.ref = ChildRef_from_raw(bvh->root);
  A.box = bvh->root_box;
  A.box_sa = alias_AABB2D_surface_area(A.box);
  A_parent = ParentRef_INVALID;
  while(ChildRef_is_node(A.ref)) {
    B.ref = _read_child_2d(bvh, A.ref, 0);
    B.box = _read_aabb_2d(bvh, A.ref, 0);
    B.box_sa = alias_AABB2D_surface_area(B.box);

    C.ref = _read_child_2d(bvh, A.ref, 1);
    C.box = _read_aabb_2d(bvh, A.ref, 1);
    C.box_sa = alias_AABB2D_surface_area(C.box);

    alias_AABB2D 
        AL_box = alias_AABB2D_union(A.box, box)
      , BL_box = alias_AABB2D_union(B.box, box)
      , CL_box = alias_AABB2D_union(C.box, box);

    alias_R
        AL_sa = alias_AABB2D_surface_area(AL_box)
      , BL_sa = alias_AABB2D_surface_area(BL_box)
      , CL_sa = alias_AABB2D_surface_area(CL_box)
      , AL_delta = AL_sa - A.box_sa
      , A_cost = AL_sa
      , B_cost = (ChildRef_is_node(B.ref) ? BL_sa - B.box_sa : BL_sa) + AL_delta 
      , C_cost = (ChildRef_is_node(B.ref) ? CL_sa - C.box_sa : CL_sa) + AL_delta;

    if(A_cost < B_cost && A_cost < C_cost) {
      break;
    }

    if(B_cost < C_cost) {
      A_parent = ParentRef_from_ChildRef_b(A.ref);
      A = B;
    } else {
      A_parent = ParentRef_from_ChildRef_c(A.ref);
      A = C;
    }
  }

  // -----------------------------------------------------------------------------------------------------------------------------------------------------------
  // step 2: setup new parent
  C.ref = leaf_nr;
  C.box = box;
  
  B = A;

  A.ref = new_node_ref;

  // write to P
  if(ParentRef_is_valid(A_parent)) {
    *_child_2d(bvh, ChildRef_from_ParentRef(A_parent), ParentRef_unwrap_side(A_parent)) = A.ref;
  } else {
    bvh->root = ChildRef_to_raw(A.ref);
  }

  // write to A
  *_parent_2d(bvh, A.ref) = A_parent;
  *_aabb_2d(bvh, A.ref, 0) = B.box;
  *_child_2d(bvh, A.ref, 0) = B.ref;
  *_aabb_2d(bvh, A.ref, 1) = C.box;
  *_child_2d(bvh, A.ref, 1) = C.ref;

  // write to B
  *_parent_2d(bvh, B.ref) = ParentRef_from_ChildRef_b(A.ref);

  // write to C
  *_parent_2d(bvh, C.ref) = ParentRef_from_ChildRef_c(A.ref);

  // -----------------------------------------------------------------------------------------------------------------------------------------------------------
  // step 3: walk back up refitting the AABBs
  #if 1
  while(ChildRef_is_valid(A.ref)) {
    A_parent = _read_parent_2d(bvh, A.ref);

    A.box = alias_AABB2D_union(B.box, C.box);
    if(ParentRef_is_valid(A_parent)) {
      *_aabb_2d(bvh, ChildRef_from_ParentRef(A_parent), ParentRef_unwrap_side(A_parent)) = A.box;

      if(ParentRef_is_b(A_parent)) {
        B.box = A.box;
        C.box = _read_aabb_2d(bvh, ChildRef_from_ParentRef(A_parent), !ParentRef_unwrap_side(A_parent));
      } else if(ParentRef_is_b(A_parent)) {
        B.box = _read_aabb_2d(bvh, ChildRef_from_ParentRef(A_parent), !ParentRef_unwrap_side(A_parent));
        C.box = A.box;
      }
    } else {
      bvh->root_box = A.box;
    }

    A.ref = ChildRef_from_ParentRef(A_parent);
  }
  #else
  while(A.is_valid) {
    // load P
    UNLOAD(P);
    LOAD(P, *A.parent);

    // load B and C if needed
    LOAD(B, *A.child1);
    LOAD(C, *A.child2);

    // while calculating scores, we also optionally need to use an intermediate for swapping
    alias_AABB2D F_C_box, G_C_box, D_B_box, E_B_box;

    // scores are from 0 if a leaf or -inf to some value to measure gain for a swap. only values over 0 are considered for a swap
    alias_R B_no_swap_score = alias_AABB2D_surface_area(*A.aabb2);
    alias_R F_score = C.is_leaf ? alias_R_ZERO : B_no_swap_score - alias_AABB2D_surface_area(F_C_box = alias_AABB2D_union(*A.aabb1, *C.aabb2));
    alias_R G_score = C.is_leaf ? alias_R_ZERO : B_no_swap_score - alias_AABB2D_surface_area(G_C_box = alias_AABB2D_union(*A.aabb1, *C.aabb1));

    alias_R C_no_swap_score = alias_AABB2D_surface_area(*A.aabb1);
    alias_R D_score = B.is_leaf ? alias_R_ZERO : C_no_swap_score - alias_AABB2D_surface_area(D_B_box = alias_AABB2D_union(*A.aabb2, *B.aabb2));
    alias_R E_score = B.is_leaf ? alias_R_ZERO : C_no_swap_score - alias_AABB2D_surface_area(E_B_box = alias_AABB2D_union(*A.aabb2, *B.aabb1));

    // only one swap happens per round of refit
    if(F_score > alias_R_ZERO && F_score > G_score && F_score > D_score && F_score > E_score) {
    // rotate B and F
      // store B box
      alias_AABB2D B_box = *A.aabb1;

      // move F
      _set_parent_2d(bvh, *C.child1, A.index);
      *A.aabb1 = *C.aabb1;
      *A.child1 = *C.child1;

      // move B
      *B.parent = C.index;
      *C.aabb1 = B_box;
      *C.child1 = B.index;

      // adjust C's box
      *A.aabb2 = F_C_box;
    } else if(G_score > alias_R_ZERO && G_score > F_score && G_score > D_score && G_score > E_score) {
    // rotate B and G
      // store B box
      alias_AABB2D B_box = *A.aabb1;

      // move G
      _set_parent_2d(bvh, *C.child2, A.index);
      *A.aabb1 = *C.aabb2;
      *A.child1 = *C.child2;

      // move B
      *B.parent = C.index;
      *C.aabb2 = B_box;
      *C.child2 = B.index;

      // adjust C's box
      *A.aabb2 = G_C_box;
    } else if(D_score > alias_R_ZERO && D_score > E_score && D_score > F_score && E_score > G_score) {
    // rotate C and D
      // store C box
      alias_AABB2D C_box = *A.aabb2;

      // move D
      _set_parent_2d(bvh, *B.child1, A.index);
      *A.aabb2 = *B.aabb1;
      *A.child2 = *B.child1;

      // move C
      *C.parent = B.index;
      *B.aabb1 = C_box;
      *B.child1 = C.index;

      // adjust B's box
      *A.aabb1 = D_B_box;
    } else if(E_score > alias_R_ZERO && E_score > D_score && E_score > F_score && E_score > G_score) {
    // rotate C and E
      // store C box
      alias_AABB2D C_box = *A.aabb2;

      // move E
      _set_parent_2d(bvh, *B.child2, A.index);
      *A.aabb2 = *B.aabb2;
      *A.child2 = *B.child2;

      // move C
      *C.parent = B.index;
      *B.aabb2 = C_box;
      *B.child2 = C.index;

      // adjust B's box
      *A.aabb1 = E_B_box;
    }

    // refit A into it's parent
    if(*P.child1 == A.index) {
      *P.aabb1 = alias_AABB2D_union(*A.aabb1, *A.aabb2);
      B = A;
      UNLOAD(C);
    } else {
      *P.aabb2 = alias_AABB2D_union(*A.aabb1, *A.aabb2);
      UNLOAD(B);
      C = A;
    }

    A = P;
  }
  #endif

  #undef LOAD
  #undef UNLOAD
  #undef PRINT

  return true;
}

static void _remove_2d(alias_BVH2D * bvh, ChildRef leaf_nr) {
  ParentRef L_parent = _read_parent_2d(bvh, leaf_nr);
  int32_t L_side = ParentRef_is_c(L_parent) ? 1 : 0;
  int32_t S_side = !L_side;

  if(!ParentRef_is_valid(L_parent)) {
    // root was this leaf, root is now invalid
    bvh->root = ChildRef_INVALID._;
    return;
  }

  ChildRef P_ref = ChildRef_from_ParentRef(L_parent);
  ParentRef P_parent = _read_parent_2d(bvh, P_ref);
  int32_t P_side = ParentRef_is_c(P_parent);

  ChildRef S_ref = _read_child_2d(bvh, P_ref, S_side);
  alias_AABB2D S_box = _read_aabb_2d(bvh, P_ref, S_side);

  if(!ParentRef_is_valid(P_parent)) {
    // this was a two leaf bvh
    // sibling becomes root
    bvh->root = ChildRef_to_raw(S_ref);
    bvh->root_box = S_box;
    return;
  }

  ChildRef PP_ref = ChildRef_from_ParentRef(P_parent);

  // move sibling to parent's old spot
  *_parent_2d(bvh, S_ref) = P_parent;
  *_aabb_2d(bvh, PP_ref, P_side) = S_box;
  *_child_2d(bvh, PP_ref, P_side) = S_ref;

  _free_node_2d(bvh, P_ref);
}

bool alias_BVH2D_insert(alias_BVH2D * bvh, alias_MemoryCB * mcb, alias_AABB2D box, uint64_t payload, uint32_t * leaf_index) {
  ChildRef leaf_ref;
  if(!_allocate_leaf_2d(bvh, mcb, &leaf_ref)) {
    return false;
  }

  *leaf_index = ChildRef_unwrap_leaf_index(leaf_ref);
  *(uint64_t *)alias_SOA_write(&bvh->leafs, *leaf_index, 1) = payload;

  return _insert_2d(bvh, mcb, leaf_ref, box);
}

bool alias_BVH2D_move(alias_BVH2D * bvh, alias_MemoryCB * mcb, uint32_t leaf_index, alias_AABB2D box) {
  ChildRef leaf_ref = ChildRef_from_leaf_index(leaf_index);
  _remove_2d(bvh, leaf_ref);
  return _insert_2d(bvh, mcb, leaf_ref, box);
}

void alias_BVH2D_remove(alias_BVH2D * bvh, uint32_t leaf_index) {
  ChildRef leaf_ref = ChildRef_from_leaf_index(leaf_index);
  _remove_2d(bvh, leaf_ref);
  _free_leaf_2d(bvh, leaf_ref);
}

static void _query_2d(const alias_BVH2D * bvh, alias_AABB2D query_box, alias_BVH_QueryCB cb, ChildRef index) {
  if(ChildRef_is_leaf(index)) {
    uint32_t leaf_index = ChildRef_unwrap_leaf_index(index);
    uint64_t payload = *(uint64_t *)alias_SOA_read(&bvh->leafs, leaf_index, 1);

    alias_Closure_call(&cb, leaf_index, payload);
  } else if(ChildRef_is_node(index)) {
    alias_AABB2D B_box = _read_aabb_2d(bvh, index, 0);
    alias_AABB2D C_box = _read_aabb_2d(bvh, index, 1);

    bool B_intersects = alias_AABB2D_intersects(query_box, B_box);
    bool C_intersects = alias_AABB2D_intersects(query_box, C_box);

    if(B_intersects) {
      ChildRef B_index = _read_child_2d(bvh, index, 0);
      _query_2d(bvh, query_box, cb, B_index);
    }
    if(C_intersects) {
      ChildRef C_index = _read_child_2d(bvh, index, 1);
      _query_2d(bvh, query_box, cb, C_index);
    }
  }
}

void alias_BVH2D_query(const alias_BVH2D * bvh, alias_AABB2D box, alias_BVH_QueryCB cb) {
  _query_2d(bvh, box, cb, ChildRef_from_raw(bvh->root));
}

