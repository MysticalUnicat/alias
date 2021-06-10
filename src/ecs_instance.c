#include "ecs_local.h"

static void * _default_allocation(void * ud, void * ptr, size_t old_size, size_t new_size, size_t alignment) {
  UNUSED(ud);
  UNUSED(old_size);
  UNUSED(alignment);
  if(new_size == 0) {
    free(ptr);
    return NULL;
  } else {
    return realloc(ptr, new_size);
  }
}

static alias_MemoryAllocationCallback _default_allocation_cb = { _default_allocation, NULL };

alias_ecs_Result alias_ecs_create_instance(
    const alias_MemoryAllocationCallback * memory_callback
  , alias_ecs_Instance *                 * instance_ptr
) {
  if(memory_callback == NULL) {
    memory_callback = &_default_allocation_cb;
  }

  return_ERROR_INVALID_ARGUMENT_if(memory_callback->fn == NULL);
  return_ERROR_INVALID_ARGUMENT_if(instance_ptr == NULL);

  alias_ecs_Instance * instance;
  instance = alias_Closure_call(memory_callback, NULL, 0, sizeof(*instance), alignof(*instance));
  if(instance == NULL) {
    return ALIAS_ECS_ERROR_OUT_OF_MEMORY;
  }

  memset(instance, 0, sizeof(*instance));
  instance->memory_allocation_cb = *memory_callback;

  {
    alias_ecs_EntityHandle e;
    alias_ecs_create_entity(instance, &e);
    alias_ecs_ComponentSet cs;
    alias_ecs_ComponentSet_init(instance, &cs, 0, NULL);
    alias_ecs_ArchetypeHandle a;
    alias_ecs_resolve_archetype(instance, cs, &a);
    alias_ecs_set_entity_archetype(instance, e, a);
  }

  *instance_ptr = instance;

  return ALIAS_ECS_SUCCESS;
}

void alias_ecs_destroy_instance(alias_ecs_Instance * instance) {
  alias_MemoryAllocationCallback memory_callback = instance->memory_allocation_cb;

  if(instance->layer.capacity > 0) {
    alias_Vector_free(&instance->layer.free_indexes, &instance->memory_allocation_cb);

    alias_ecs_free(instance, instance->layer.generation, sizeof(*instance->layer.generation) * instance->layer.capacity, alignof(*instance->layer.generation));

    for(uint32_t i = 0; i < instance->layer.length; i++) {
      alias_Vector_free(&instance->layer.data[i].entities, &instance->memory_allocation_cb);
    }
    alias_ecs_free(instance, instance->layer.data, sizeof(*instance->layer.data) * instance->layer.capacity, alignof(*instance->layer.data));
  }

  for(uint32_t i = 0; i < instance->component.length; i++) {
    FREE(instance, instance->component.data[i].num_required_components, instance->component.data[i].required_components);
  }
  alias_Vector_free(&instance->component, &instance->memory_allocation_cb);

  FREE(instance, instance->entity.capacity, instance->entity.generation);
  FREE(instance, instance->entity.capacity, instance->entity.layer_index);
  FREE(instance, instance->entity.capacity, instance->entity.archetype_index);
  FREE(instance, instance->entity.capacity, instance->entity.archetype_code);

  for(uint32_t i = 0; i < instance->archetype.length; i++) {
    alias_ecs_Archetype * archetype = &instance->archetype.data[i];
    alias_ecs_ComponentSet_free(instance, &archetype->components);
    FREE(instance, archetype->components.count, archetype->offset_size);
    alias_Vector_free(&archetype->free_indexes, &instance->memory_allocation_cb);
    for(uint32_t j = 0; j < archetype->blocks.length; j++) {
      FREE(instance, 1, archetype->blocks.data[j]);
    }
    alias_Vector_free(&archetype->blocks, &instance->memory_allocation_cb);
  }
  FREE(instance, instance->archetype.capacity, instance->archetype.components_index);
  FREE(instance, instance->archetype.capacity, instance->archetype.data);

  alias_Closure_call(&memory_callback, instance, sizeof(*instance), 0, alignof(*instance));
}

