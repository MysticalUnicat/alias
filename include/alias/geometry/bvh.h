#ifndef _ALIAS_GEOMETRY_BVH_H_
#define _ALIAS_GEOMETRY_BVH_H_

#include <alias/data_structure/soa.h>
#include <alias/geometry/aabb.h>

ALIAS_DECLARE_CLOSURE(alias_BVH_QueryCB, void, uint32_t leaf_index, uint64_t payload)

typedef struct alias_BVH2D {
  alias_SOA nodes;
  alias_SOA leafs;

  int32_t root;
  alias_AABB2D root_box;

  uint32_t free_node;
  uint32_t free_leaf;
} alias_BVH2D;

bool alias_BVH2D_initialize(alias_BVH2D * bvh, alias_MemoryCB * mcb);
void alias_BVH2D_free(alias_BVH2D * bvh, alias_MemoryCB * mcb);

bool alias_BVH2D_insert(alias_BVH2D * bvh, alias_MemoryCB * mcb, alias_AABB2D box, uint64_t payload, uint32_t * leaf_index);
bool alias_BVH2D_move(alias_BVH2D * bvh, alias_MemoryCB * mcb, uint32_t leaf_index, alias_AABB2D box);
void alias_BVH2D_remove(alias_BVH2D * bvh, uint32_t leaf_index);

void alias_BVH2D_query(const alias_BVH2D * bvh, alias_AABB2D box, alias_BVH_QueryCB cb);

#endif
