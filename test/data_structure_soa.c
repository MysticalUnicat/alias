// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "local.h"

#include <alias/data_structure/soa.h>

TEST(data_structure_soa, "SOA macro and function tests") {
  alias_SOA test;

  TEST_EQ(alias_SOA_initialize(
      &test
    , alias_default_MemoryCB()
    , 2
    , (size_t[]){ sizeof(const char *), sizeof(uint32_t) }
    , (size_t[]){ alignof(const char *), alignof(uint32_t) }
    ), true, "");

  TEST_EQ(alias_SOA_set_capacity(&test, alias_default_MemoryCB(), 1), true, "");
  uint32_t index = alias_SOA_push(&test);
  *(const char * *)alias_SOA_write(&test, index, 0) = "unicat";

  alias_SOA_free(&test, alias_default_MemoryCB());
}

