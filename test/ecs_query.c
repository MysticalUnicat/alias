#include "local.h"

struct Position {
  int x;
  int y;
};

void _query(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)instance;
  (void)entity;
  (void)data;

  uint32_t * count = (uint32_t *)ud;
  (*count)++;
}

TEST(query, "alias_ecs_Query") {
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

  alias_ecs_Query * query;

  TEST_EQ(
      alias_ecs_create_query(
          instance
        , &(alias_ecs_QueryCreateInfo) {
            .num_read_components = 1
          , .read_components = &Position_component
          }
        , &query
        )
    , ALIAS_ECS_SUCCESS
    , "failed to create query"
    );

  uint32_t count = 0;

  TEST_EQ(
      alias_ecs_execute_query(
          instance
        , query
        , (alias_ecs_QueryCB) { _query, &count }
        )
    , ALIAS_ECS_SUCCESS
    , "failed to execute query"
    );

  TEST_EQ(count, 1, "expected query to be ran once");

  alias_ecs_destroy_query(
      instance
    , query
    );

  alias_ecs_destroy_instance(instance);
}

