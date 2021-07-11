#include "local.h"

#include <alias/geometry/bvh.h>
#include <alias/log.h>

static void _query_fn(void * ud, uint32_t leaf_index, uint64_t payload) {
  (void)leaf_index;
  (void)payload;
  uint32_t * bits = (uint32_t *)ud;
  (*bits) |= 1 << payload;
}

TEST(geometry_bvh, "BVH 2d tests") {
  alias_AABB2D a = { { 0, 0 }, { 10, 10 } };
  alias_AABB2D b = { { 5, 5 }, { 7, 7 } };
  alias_AABB2D c = { { 2, 11 }, { 3, 12 } };

  alias_AABB2D q1 = { { 0, 0 }, { 100, 100 } };
  alias_AABB2D q2 = { { -1, -1 }, { 1, 1 } };

  alias_BVH2D tree;

  TEST_EQ(alias_BVH2D_initialize(&tree, alias_default_MemoryCB()), true, "failed initializating tree");

  uint32_t a_index, b_index, c_index;
  TEST_EQ(alias_BVH2D_insert(&tree, alias_default_MemoryCB(), a, 0, &a_index), true, "failed to insert a");
  TEST_EQ(alias_BVH2D_insert(&tree, alias_default_MemoryCB(), b, 1, &b_index), true, "failed to insert b");
  TEST_EQ(alias_BVH2D_insert(&tree, alias_default_MemoryCB(), c, 2, &c_index), true, "failed to insert c");

  uint32_t q1_bits = 0, q2_bits = 0;

  alias_BVH2D_query(&tree, q1, (alias_BVH_QueryCB){ _query_fn, (void *)&q1_bits});
  alias_BVH2D_query(&tree, q2, (alias_BVH_QueryCB){ _query_fn, (void *)&q2_bits});

  TEST_EQ(q1_bits, 7, "query 1 failed");
  TEST_EQ(q2_bits, 1, "query 2 failed");
  
  alias_BVH2D_free(&tree, alias_default_MemoryCB());
}
