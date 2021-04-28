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
