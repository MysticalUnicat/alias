// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "local.h"

#include <alias/data_structure/paged_soa.h>

TEST(data_structure_paged_soa, "Paged SOA and function tests") {
  alias_PagedSOA test;

  TEST_EQ(alias_PagedSOA_initialize(
      &test
    , alias_default_MemoryCB()
    , 0
    , 2
    , (size_t[]){ sizeof(const char *), sizeof(uint32_t) }
    ), true, "");

  TEST_EQ(alias_PagedSOA_set_capacity(&test, alias_default_MemoryCB(), 1), true, "");
  uint32_t code = alias_PagedSOA_push(&test);
  *(const char * *)alias_PagedSOA_write(&test, code, 0) = "unicat";

  alias_PagedSOA_free(&test, alias_default_MemoryCB());
}

