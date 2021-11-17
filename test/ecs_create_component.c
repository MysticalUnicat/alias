// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "local.h"

TEST(create_component, "aeRegisterComponent") {
  alias_ecs_Instance * instance;
  TEST_EQ(alias_ecs_create_instance(&g_stub_allocator.cb, &instance), ALIAS_ECS_SUCCESS, "unexpected error while creating instance");

  alias_ecs_ComponentHandle component;

  TEST_EQ(
      alias_ecs_register_component(
          instance
        , &(alias_ecs_ComponentCreateInfo) {
            .size = 0
          , .num_required_components = 0
          , .required_components = NULL
          }
        , &component
        )
    , ALIAS_ECS_ERROR_INVALID_ARGUMENT
    , "expected invalid argument (size is zero)"
    );

  TEST_EQ(
      alias_ecs_register_component(
          instance
        , &(alias_ecs_ComponentCreateInfo) {
            .size = sizeof(uint32_t)
          , .num_required_components = 1
          , .required_components = NULL
          }
        , &component
        )
    , ALIAS_ECS_ERROR_INVALID_ARGUMENT
    , "expected invalid argument (required_components is NULL while num_required_components is greater than zero)"
    );

  component = 0;
  TEST_EQ(
      alias_ecs_register_component(
          instance
        , &(alias_ecs_ComponentCreateInfo) {
            .size = sizeof(uint32_t)
          , .num_required_components = 1
          , .required_components = &component
          }
        , &component
        )
   , ALIAS_ECS_ERROR_INVALID_ARGUMENT
   , "expected invalid argument (no components have been successfully registerered, component ids start at zero so even zero should be invalid)"
   );

  TEST_EQ(
      alias_ecs_register_component(
          instance
        , &(alias_ecs_ComponentCreateInfo) {
            .size = sizeof(uint32_t)
          , .num_required_components = 0
          , .required_components = NULL
          }
        , &component
        )
  , ALIAS_ECS_SUCCESS
  , "unexpected error while creating basic 4 byte component"
  );

  TEST_EQ(
      alias_ecs_register_component(
          instance
        , &(alias_ecs_ComponentCreateInfo) {
            .size = sizeof(uint32_t)
          , .num_required_components = 1
          , .required_components = &component
          }
        , &component
        )
    , ALIAS_ECS_SUCCESS
    , "unexpected error while creating basic 4 byte component with required component"
    );

  alias_ecs_destroy_instance(instance);
}

