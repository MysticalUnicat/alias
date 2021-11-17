// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "local.h"

#include "../src/ecs_local.h"

TEST(component_set, "test for internal aeComponentSet") {
  alias_ecs_Instance * instance;
  alias_ecs_create_instance(&g_stub_allocator.cb, &instance);
  
  alias_ecs_ComponentSet set_singleton, set_all;

  alias_ecs_ComponentHandle fake_component_1 = 0;
  alias_ecs_ComponentHandle fake_component_2 = 1;
  alias_ecs_ComponentHandle fake_component_3 = 2;

  TEST_EQ(alias_ecs_ComponentSet_init(instance, &set_singleton, 1, &fake_component_1), ALIAS_ECS_SUCCESS, "failed creating one component component set");

  TEST_EQ(
      alias_ecs_ComponentSet_init(
          instance
        , &set_all
        , 3
        , (alias_ecs_ComponentHandle[]) {
              fake_component_1
            , fake_component_3
            , fake_component_2
            }
        )
    , ALIAS_ECS_SUCCESS
    , "failed creating one component component set"
    );

  alias_ecs_ComponentSet_free(instance, &set_singleton);
  alias_ecs_ComponentSet_free(instance, &set_all);

  alias_ecs_destroy_instance(instance);
}

TEST(component_set_compare, "test for internal aeComponentSet") {
  alias_ecs_ComponentHandle component_a = 0;
  alias_ecs_ComponentHandle component_b = 1;
  alias_ecs_ComponentHandle component_c = 2;

  alias_ecs_ComponentSet set_a = { .count = 1, .index = &component_a };
  alias_ecs_ComponentSet set_b = { .count = 1, .index = &component_b };
  alias_ecs_ComponentSet set_c = { .count = 1, .index = &component_c };

  alias_ecs_ComponentSet set_ab = { .count = 2, .index = (alias_ecs_ComponentHandle[]) { component_a, component_b } };
  alias_ecs_ComponentSet set_ac = { .count = 2, .index = (alias_ecs_ComponentHandle[]) { component_a, component_c } };
  alias_ecs_ComponentSet set_bc = { .count = 2, .index = (alias_ecs_ComponentHandle[]) { component_b, component_c } };

  alias_ecs_ComponentSet set_abc = { .count = 3, .index = (alias_ecs_ComponentHandle[]) { component_a, component_b, component_c } };

  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_a, &set_a), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_a, &set_b), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_a, &set_c), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_a, &set_ab), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_a, &set_ac), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_a, &set_bc), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_a, &set_abc), 0, "invalid is_subset result");

  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_b, &set_a), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_b, &set_b), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_b, &set_c), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_b, &set_ab), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_b, &set_ac), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_b, &set_bc), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_b, &set_abc), 0, "invalid is_subset result");

  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_c, &set_a), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_c, &set_b), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_c, &set_c), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_c, &set_ab), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_c, &set_ac), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_c, &set_bc), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_c, &set_abc), 0, "invalid is_subset result");

  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_ab, &set_a), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_ab, &set_b), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_ab, &set_c), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_ab, &set_ab), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_ab, &set_ac), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_ab, &set_bc), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_ab, &set_abc), 0, "invalid is_subset result");

  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_ac, &set_a), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_ac, &set_b), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_ac, &set_c), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_ac, &set_ab), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_ac, &set_ac), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_ac, &set_bc), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_ac, &set_abc), 0, "invalid is_subset result");

  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_bc, &set_a), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_bc, &set_b), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_bc, &set_c), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_bc, &set_ab), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_bc, &set_ac), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_bc, &set_bc), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_bc, &set_abc), 0, "invalid is_subset result");

  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_abc, &set_a), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_abc, &set_b), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_abc, &set_c), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_abc, &set_ab), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_abc, &set_ac), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_abc, &set_bc), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_is_subset(&set_abc, &set_abc), 1, "invalid is_subset result");


  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_a, &set_a), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_a, &set_b), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_a, &set_c), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_a, &set_ab), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_a, &set_ac), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_a, &set_bc), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_a, &set_abc), 1, "invalid is_subset result");

  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_b, &set_a), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_b, &set_b), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_b, &set_c), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_b, &set_ab), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_b, &set_ac), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_b, &set_bc), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_b, &set_abc), 1, "invalid is_subset result");

  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_c, &set_a), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_c, &set_b), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_c, &set_c), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_c, &set_ab), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_c, &set_ac), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_c, &set_bc), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_c, &set_abc), 1, "invalid is_subset result");

  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_ab, &set_a), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_ab, &set_b), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_ab, &set_c), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_ab, &set_ab), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_ab, &set_ac), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_ab, &set_bc), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_ab, &set_abc), 1, "invalid is_subset result");

  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_ac, &set_a), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_ac, &set_b), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_ac, &set_c), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_ac, &set_ab), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_ac, &set_ac), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_ac, &set_bc), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_ac, &set_abc), 1, "invalid is_subset result");

  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_bc, &set_a), 0, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_bc, &set_b), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_bc, &set_c), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_bc, &set_ab), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_bc, &set_ac), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_bc, &set_bc), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_bc, &set_abc), 1, "invalid is_subset result");

  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_abc, &set_a), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_abc, &set_b), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_abc, &set_c), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_abc, &set_ab), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_abc, &set_ac), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_abc, &set_bc), 1, "invalid is_subset result");
  TEST_EQ(alias_ecs_ComponentSet_intersects(&set_abc, &set_abc), 1, "invalid is_subset result");
}

