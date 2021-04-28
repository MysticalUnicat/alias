#include "local.h"

TEST(create_layer, "aeCreateLayer") {
  alias_ecs_Instance * instance;
  TEST_EQ(alias_ecs_create_instance(&g_stub_allocator.cb, &instance), ALIAS_ECS_SUCCESS, "error while setting up testing instance");

  alias_ecs_LayerHandle unbounded, bounded, non_destroyed;

  alias_ecs_LayerCreateInfo ci;

  TEST_EQ(alias_ecs_create_layer(NULL, &ci, &unbounded), ALIAS_ECS_ERROR_INVALID_ARGUMENT, "expected invalid argument error when instance is NULL");
  TEST_EQ(alias_ecs_create_layer(instance, NULL, &unbounded), ALIAS_ECS_ERROR_INVALID_ARGUMENT, "expected invalid argument error when create_info is NULL");
  TEST_EQ(alias_ecs_create_layer(instance, &ci, NULL), ALIAS_ECS_ERROR_INVALID_ARGUMENT, "expected invalid argument error when layer_ptr is NULL");

  // create with unbounded entities
  ci.max_entities = 0;
  TEST_EQ(alias_ecs_create_layer(instance, &ci, &unbounded), ALIAS_ECS_SUCCESS, "unexpected error while creating unbounded layer");

  // create limited entities
  ci.max_entities = 32;
  TEST_EQ(alias_ecs_create_layer(instance, &ci, &bounded), ALIAS_ECS_SUCCESS, "unexpected error while creating bounded layer");

  TEST_EQ(alias_ecs_destroy_layer(instance, 0, unbounded), ALIAS_ECS_SUCCESS, "unexpected error while destroying unbounded layer");
  TEST_EQ(alias_ecs_destroy_layer(instance, 0, bounded), ALIAS_ECS_SUCCESS, "unexpected error while destroying bounded layer");

  // non-destroyed layer
  ci.max_entities = 0;
  TEST_EQ(alias_ecs_create_layer(instance, &ci, &non_destroyed), ALIAS_ECS_SUCCESS, "unexpected error while creating non-destroyed layer");

  // expect free the memory of the the non-destroyed layer
  alias_ecs_destroy_instance(instance);
}

