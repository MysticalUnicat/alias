#include "local.h"

TEST(create_instance, "aeCreateInstance and it's possible error conditions") {
  alias_ecs_Instance * instance;
  alias_MemoryAllocationCallback memory_callback = { 0, 0 };

  TEST_EQ(alias_ecs_create_instance(NULL, NULL), ALIAS_ECS_ERROR_INVALID_ARGUMENT, "expected to require result pointer to instance");

  TEST_EQ(alias_ecs_create_instance(&memory_callback, NULL), ALIAS_ECS_ERROR_INVALID_ARGUMENT, "expected to require result pointer to instance");

  // default 'internal' allocator
  TEST_EQ(alias_ecs_create_instance(NULL, &instance), ALIAS_ECS_SUCCESS, "unexpected error when creating instance (internal allocator)");
  alias_ecs_destroy_instance(instance);

  // stub allocator
  TEST_EQ(alias_ecs_create_instance(&g_stub_allocator.cb, &instance), ALIAS_ECS_SUCCESS, "unexpected error when creating instance (test stub allocator)");
  alias_ecs_destroy_instance(instance);

  // ... then stub allocator fail
  g_stub_allocator.fail = 1;
  TEST_EQ(alias_ecs_create_instance(&g_stub_allocator.cb, &instance), ALIAS_ECS_ERROR_OUT_OF_MEMORY, "expected error when creating instance (bad allocator)");
  g_stub_allocator.fail = 0;
}

