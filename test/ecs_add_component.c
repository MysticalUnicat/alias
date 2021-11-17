// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "local.h"

struct Position {
  int x;
  int y;
};

struct Velocity {
  int x;
  int y;
};

struct Name {
  const char * name;
};

TEST(add_component, "spawn an entity and then add a component") {
  alias_ecs_Instance * instance;
  TEST_EQ(alias_ecs_create_instance(NULL, &instance), ALIAS_ECS_SUCCESS, "error while setting up testing instance");

  alias_ecs_ComponentHandle Position_component;
  TEST_EQ( alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) { .size = sizeof(struct Position) }, &Position_component)
         , ALIAS_ECS_SUCCESS
         , "error while setting up position component"
         );

  alias_ecs_ComponentHandle Velocity_component;
  TEST_EQ( alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) { .size = sizeof(struct Velocity) }, &Velocity_component)
         , ALIAS_ECS_SUCCESS
         , "error while setting up velocity component"
         );

  alias_ecs_ComponentHandle Name_component;
  TEST_EQ(
      alias_ecs_register_component(
          instance
        , &(alias_ecs_ComponentCreateInfo) { .flags = ALIAS_ECS_COMPONENT_CREATE_NOT_NULL, .size = sizeof(struct Name) }
        , &Name_component
      )
    , ALIAS_ECS_SUCCESS
    , "error while setting up velocity component"
  );

  alias_ecs_EntityHandle entity;

  // please excuse me as i play with some formatting rule ideas
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

  TEST_EQ(
      alias_ecs_add_component_to_entity(
          instance
        , entity
        , Velocity_component
        , NULL
        )
    , ALIAS_ECS_SUCCESS
    , "failed to add component with null data"
    );
  
  TEST_EQ(
      alias_ecs_add_component_to_entity(
          instance
        , entity
        , Name_component
        , NULL
        )
    , ALIAS_ECS_ERROR_INVALID_ARGUMENT
    , "expected invalid argument response (null data for component requiring it"
    );

  TEST_EQ(
      alias_ecs_add_component_to_entity(
          instance
        , entity
        , Name_component
        , &(struct Name){ .name = "a string" }
        )
    , ALIAS_ECS_SUCCESS
    , "failed to create a name component with a valid pointer"
    );

  alias_ecs_destroy_instance(instance);
}

