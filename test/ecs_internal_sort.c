// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "local.h"

#include "../src/ecs_local.h"

#define NUM_ROUNDS 3
#define PER_ROUND 73

static int _is_same(uint32_t count, const uint32_t * a, const uint32_t * b) {
  int r = 1;
  for(uint32_t i = 0; i < count; ++i) {
    if(a[i] != b[i]) { r = 0; }
  }
  return r;
}

static int _compar_uint32(const void * ap, const void * bp) {
  uint32_t a = *(uint32_t *)ap;
  uint32_t b = *(uint32_t *)bp;
  return (int)a - (int)b;
}

static int _compar_uint32_ud(void * ud, const void * ap, const void * bp) {
  (void)ud;
  uint32_t a = *(uint32_t *)ap;
  uint32_t b = *(uint32_t *)bp;
  return (int)a - (int)b;
}

TEST(internal_sort, "internal sort function testing") {
  uint32_t * q_sorted;
  uint32_t * a_sorted;

  q_sorted = malloc(sizeof(*q_sorted) * NUM_ROUNDS * PER_ROUND);
  a_sorted = malloc(sizeof(*a_sorted) * NUM_ROUNDS * PER_ROUND);
  
  for(uint32_t i = 0; i < NUM_ROUNDS; i++) {
    uint32_t count = PER_ROUND * i;

    for(uint32_t j = 0; j < count; j++) {
      q_sorted[j] = a_sorted[j] = rand();
    }

    qsort(q_sorted, count, sizeof(*q_sorted), _compar_uint32);
    
    alias_ecs_quicksort(a_sorted, count, sizeof(*a_sorted), (alias_ecs_CompareCB) { _compar_uint32_ud, NULL });

    if(!_is_same(count, a_sorted, q_sorted)) {
      free(q_sorted);
      free(a_sorted);
      TEST_EQ(0, 1, "internal sort and qsort are different!");
    }
  }

  free(q_sorted);
  free(a_sorted);
}
