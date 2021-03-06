// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "ecs_local.h"

alias_ecs_Result alias_ecs_create_instance(
    const alias_MemoryCB * memory_callback
  , alias_ecs_Instance * * instance_ptr
) {
  if(memory_callback == NULL) {
    memory_callback = alias_default_MemoryCB();
  }

  return_ERROR_INVALID_ARGUMENT_if(memory_callback->fn == NULL);
  return_ERROR_INVALID_ARGUMENT_if(instance_ptr == NULL);

  alias_ecs_Instance * instance;
  instance = alias_Closure_call(memory_callback, NULL, 0, sizeof(*instance), alignof(*instance));
  if(instance == NULL) {
    return ALIAS_ECS_ERROR_OUT_OF_MEMORY;
  }

  memset(instance, 0, sizeof(*instance));
  instance->memory_cb = *memory_callback;

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
  alias_MemoryCB memory_cb = instance->memory_cb;

  if(instance->layer.capacity > 0) {
    alias_Vector_free(&instance->layer.free_indexes, &memory_cb);

    alias_ecs_free(instance, instance->layer.generation, sizeof(*instance->layer.generation) * instance->layer.capacity, alignof(*instance->layer.generation));

    for(uint32_t i = 0; i < instance->layer.length; i++) {
      alias_Vector_free(&instance->layer.data[i].entities, &memory_cb);
    }
    alias_ecs_free(instance, instance->layer.data, sizeof(*instance->layer.data) * instance->layer.capacity, alignof(*instance->layer.data));
  }

  for(uint32_t i = 0; i < instance->component.length; i++) {
    FREE(instance, instance->component.data[i].num_required_components, instance->component.data[i].required_components);
  }
  alias_Vector_free(&instance->component, &memory_cb);

  FREE(instance, instance->entity.capacity, instance->entity.generation);
  FREE(instance, instance->entity.capacity, instance->entity.layer_index);
  FREE(instance, instance->entity.capacity, instance->entity.archetype_index);
  FREE(instance, instance->entity.capacity, instance->entity.archetype_code);

  for(uint32_t i = 0; i < instance->archetype.length; i++) {
    alias_ecs_Archetype * archetype = &instance->archetype.data[i];
    alias_ecs_ComponentSet_free(instance, &archetype->components);
    alias_Vector_free(&archetype->free_codes, &memory_cb);
    alias_PagedSOA_free(&archetype->paged_soa, &memory_cb);
  }
  FREE(instance, instance->archetype.capacity, instance->archetype.components_index);
  FREE(instance, instance->archetype.capacity, instance->archetype.data);

  alias_Closure_call(&memory_cb, instance, sizeof(*instance), 0, alignof(*instance));
}

