// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "local.h"

struct Position {
  int x;
  int y;
};

TEST(spawn, "alias_ecs_spawn") {
  alias_ecs_Instance * instance;
  TEST_EQ(alias_ecs_create_instance(NULL, &instance), ALIAS_ECS_SUCCESS, "error while setting up testing instance");

  alias_ecs_ComponentHandle Position_component;
  TEST_EQ(
      alias_ecs_register_component(
          instance
        , &(alias_ecs_ComponentCreateInfo) { .size = sizeof(struct Position) }
        , &Position_component
        )
    , ALIAS_ECS_SUCCESS
    , "error while setting up position component"
    );

  alias_ecs_EntityHandle entity;

  TEST_EQ(
      alias_ecs_spawn(
          instance
        , &(alias_ecs_EntitySpawnInfo) {
            .layer = ALIAS_ECS_INVALID_LAYER
          , .count = 1
          , .num_components = 1
          , .components = (alias_ecs_EntitySpawnComponent[]) {
                {
                    .component = Position_component
                  , .stride = 0
                  , .data = (const void *)(struct Position[]) { { 0, 0 } }
                  }
              }
          }
        , &entity
        )
    , ALIAS_ECS_SUCCESS
    , "unexpected error from simple spawn"
    );

  alias_ecs_destroy_instance(instance);
}

