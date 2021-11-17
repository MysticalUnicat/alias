// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "local.h"

#include "../src/ecs_local.h"

#define COUNT 1024

static int _compar_uint32_ud(void * ud, const void * ap, const void * bp) {
  (void)ud;
  uint32_t a = *(uint32_t *)ap;
  uint32_t b = *(uint32_t *)bp;
  return (int)a - (int)b;
}

TEST(internal_bsearch, "internal bsearch function testing") {
  uint32_t * sorted;

  sorted = malloc(sizeof(*sorted) * COUNT);
  
  for(uint32_t j = 0; j < COUNT; j++) {
    sorted[j] = rand();
  }

  alias_ecs_quicksort(sorted, COUNT, sizeof(*sorted), (alias_ecs_CompareCB) { _compar_uint32_ud, NULL });

  for(uint32_t i = 0; i < COUNT; i++) {
    uint32_t key = sorted[i];
    uint32_t * found = (uint32_t *)alias_ecs_bsearch(&key, sorted, COUNT, sizeof(*sorted), (alias_ecs_CompareCB) { _compar_uint32_ud, NULL });
    TEST_NE(found, NULL, "found wasnt");
    TEST_EQ(*found, key, "invalid result given %u expected %u", *found, key);
  }

  free(sorted);
}
