#include "ecs_local.h"

#include <alias/log.h>

alias_ecs_Result alias_ecs_validate_entity_handle(
    const alias_ecs_Instance * instance
  , alias_ecs_EntityHandle     entity
  , uint32_t                 * index_ptr
) {
  uint32_t index = (uint32_t)(entity & 0xFFFFFFFF);
  uint32_t generation = (uint32_t)(entity >> 32);
  if(index >= instance->entity.length) {
    return ALIAS_ECS_ERROR_INVALID_ENTITY;
  }
  if(generation != instance->entity.generation[index]) {
    return ALIAS_ECS_ERROR_INVALID_ENTITY;
  }
  *index_ptr = index;
  return ALIAS_ECS_SUCCESS;
}

alias_ecs_Result alias_ecs_create_entity(
    alias_ecs_Instance     * instance
  , alias_ecs_EntityHandle * entity_ptr
) {
  uint32_t index;

  if(instance->entity.free_indexes.length > 0) {
    index = *alias_Vector_pop(&instance->entity.free_indexes);
  } else {
    index = instance->entity.length++;
  }

  if(instance->entity.length > instance->entity.capacity) {
    size_t old_capacity = instance->entity.capacity;
    size_t new_capacity = instance->entity.length + 1;
    new_capacity += new_capacity >> 1;
    RELOC(instance, old_capacity, new_capacity, instance->entity.generation);
    RELOC(instance, old_capacity, new_capacity, instance->entity.layer_index);
    RELOC(instance, old_capacity, new_capacity, instance->entity.archetype_index);
    RELOC(instance, old_capacity, new_capacity, instance->entity.archetype_code);
    instance->entity.capacity = new_capacity;
  }

  uint32_t generation = instance->entity.generation[index];

  *entity_ptr = ((uint64_t)generation << 32) | (uint64_t)index;

  return ALIAS_ECS_SUCCESS;
}

alias_ecs_Result alias_ecs_free_entity(
    alias_ecs_Instance * instance
  , uint32_t             entity_id
) {
  ++instance->entity.generation[entity_id];
  alias_Vector_space_for(&instance->entity.free_indexes, &instance->memory_allocation_cb, 1);
  *alias_Vector_push(&instance->entity.free_indexes) = entity_id;
  return ALIAS_ECS_SUCCESS;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------

static int _compar_component_index(const void * ap, const void * bp) {
  uint32_t a = *(uint32_t *)ap;
  uint32_t b = *(uint32_t *)bp;
  return a - b;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------
alias_ecs_Result alias_ecs_spawn(
    alias_ecs_Instance              * instance
  , const alias_ecs_EntitySpawnInfo * spawn_info
  , alias_ecs_EntityHandle          * entities_ptr
) {
  return_ERROR_INVALID_ARGUMENT_if(instance == NULL);
  return_ERROR_INVALID_ARGUMENT_if(spawn_info == NULL);

  return_ERROR_INVALID_ARGUMENT_if(spawn_info->count == 0);

  uint32_t layer_index = UINT32_MAX;
  if(spawn_info->layer != ALIAS_ECS_INVALID_LAYER) {
    return_if_ERROR(alias_ecs_validate_layer_handle(instance, spawn_info->layer, &layer_index));
  }

  uint32_t archetype_index;
  {
    alias_ecs_ComponentSet components;
    components.count = spawn_info->num_components;
    ALLOC(instance, components.count, components.index);
    for(uint32_t i = 0; i < components.count; ++i) {
      components.index[i] = spawn_info->components[i].component;
    }
    qsort(components.index, components.count, sizeof(*components.index), _compar_component_index);
    return_if_ERROR(alias_ecs_resolve_archetype(instance, components, &archetype_index));
  }
  alias_ecs_Archetype * archetype = &instance->archetype.data[archetype_index];

  int free_out_entities = entities_ptr == NULL;
  if(free_out_entities) {
    ALLOC(instance, spawn_info->count, entities_ptr);
  }

  for(uint32_t i = 0; i < spawn_info->count; i++) {
    alias_ecs_EntityHandle entity;
    uint32_t entity_index;

    return_if_ERROR(alias_ecs_create_entity(instance, &entity));

    return_if_ERROR(alias_ecs_validate_entity_handle(instance, entity, &entity_index));

    if(layer_index != UINT32_MAX) {
      return_if_ERROR(alias_ecs_set_entity_layer(instance, entity_index, layer_index));
    }
    return_if_ERROR(alias_ecs_set_entity_archetype(instance, entity_index, archetype_index));

    entities_ptr[i] = entity;
  }

  for(uint32_t i = 0; i < spawn_info->num_components; i++) {
    alias_ecs_EntitySpawnComponent spawn_component = spawn_info->components[i];

    uint32_t component_index = alias_ecs_ComponentSet_order_of(&archetype->components, spawn_component.component);

    ASSERT(component_index != UINT32_MAX);

    uint32_t offset_size = archetype->offset_size[component_index];
    uint32_t component_offset = offset_size >> 16;
    uint32_t component_size = offset_size & 0xFFFF;

    const uint8_t * read = spawn_component.data;
    uint32_t stride = spawn_component.stride ? spawn_component.stride : component_size;

    for(uint32_t j = 0; j < spawn_info->count; j++) {
      uint32_t entity_index = (uint32_t)(entities_ptr[j] & 0xFFFFFFFF);
      uint32_t code = ENTITY_ARCHETYPE_CODE(instance, entity_index);
      uint32_t block_index = code >> 16;
      uint32_t block_offset = code & 0xFFFF;
      void * write = (void *)(archetype->blocks.data[block_index]->data + component_offset + (component_size * block_offset));
      memcpy(write, read, component_size);
      read += stride;
    }
  }

  if(free_out_entities) {
    FREE(instance, spawn_info->count, entities_ptr);
  }
  
  return ALIAS_ECS_SUCCESS;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------

alias_ecs_Result alias_ecs_add_component_to_entity(
    alias_ecs_Instance        * instance
  , alias_ecs_EntityHandle      entity
  , alias_ecs_ComponentHandle   component_handle
  , const void                * data
) {
  uint32_t entity_index;
  
  return_ERROR_INVALID_ARGUMENT_if(instance == NULL);
  return_if_ERROR(alias_ecs_validate_entity_handle(instance, entity, &entity_index));
  return_ERROR_INVALID_ARGUMENT_if(component_handle >= instance->component.length);

  const alias_ecs_Component * component = &instance->component.data[component_handle];
  return_ERROR_INVALID_ARGUMENT_if(component->non_null && data == NULL);

  alias_ecs_Archetype * archetype = ENTITY_ARCHETYPE_DATA(instance, entity_index);

  uint32_t component_index = alias_ecs_ComponentSet_order_of(&archetype->components, component_handle);

  if(component_index != UINT32_MAX) {
    return ALIAS_ECS_ERROR_COMPONENT_EXISTS;
  }

  alias_ecs_ArchetypeHandle new_archetype;
  {
    alias_ecs_ComponentSet new_components;
    return_if_ERROR(alias_ecs_ComponentSet_add(instance, &new_components, &archetype->components, component_handle));

    return_if_ERROR(alias_ecs_resolve_archetype(instance, new_components, &new_archetype));

    // alias_ecs_resolve_archetype 'consumes' new components
  }

  return_if_ERROR(alias_ecs_set_entity_archetype(instance, entity, new_archetype));

  component_index = alias_ecs_ComponentSet_order_of(&instance->archetype.data[new_archetype].components, component_handle);
  
  if(data != NULL) {
    memcpy(alias_ecs_write(instance, entity_index, component_index), data, component->size);
  } else {
    memset(alias_ecs_write(instance, entity_index, component_index), 0, component->size);
  }

  return ALIAS_ECS_SUCCESS;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------

alias_ecs_Result alias_ecs_remove_component_from_entity(
    alias_ecs_Instance        * instance
  , alias_ecs_EntityHandle      entity
  , alias_ecs_ComponentHandle   component_handle
) {
  uint32_t entity_index;
  
  return_ERROR_INVALID_ARGUMENT_if(instance == NULL);
  return_if_ERROR(alias_ecs_validate_entity_handle(instance, entity, &entity_index));
  return_ERROR_INVALID_ARGUMENT_if(component_handle >= instance->component.length);

  alias_ecs_Archetype * archetype = ENTITY_ARCHETYPE_DATA(instance, entity_index);

  uint32_t component_index = alias_ecs_ComponentSet_order_of(&archetype->components, component_handle);

  if(component_index == UINT32_MAX) {
    return ALIAS_ECS_ERROR_COMPONENT_DOES_NOT_EXIST;
  }

  alias_ecs_ArchetypeHandle new_archetype;
  {
    alias_ecs_ComponentSet new_components;
    return_if_ERROR(alias_ecs_ComponentSet_remove(instance, &new_components, &archetype->components, component_handle));

    return_if_ERROR(alias_ecs_resolve_archetype(instance, new_components, &new_archetype));

    // alias_ecs_resolve_archetype 'consumes' new components
  }

  alias_ecs_set_entity_archetype(instance, entity, new_archetype);

  return ALIAS_ECS_SUCCESS;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------

alias_ecs_Result alias_ecs_read_entity_component(
    alias_ecs_Instance        * instance
  , alias_ecs_EntityHandle      entity
  , alias_ecs_ComponentHandle   component_handle
  , const void ** ptr
) {
  uint32_t entity_index;

  return_ERROR_INVALID_ARGUMENT_if(instance == NULL);
  return_if_ERROR(alias_ecs_validate_entity_handle(instance, entity, &entity_index));
  return_ERROR_INVALID_ARGUMENT_if(component_handle >= instance->component.length);

  alias_ecs_Archetype * archetype = ENTITY_ARCHETYPE_DATA(instance, entity_index);

  uint32_t component_index = alias_ecs_ComponentSet_order_of(&archetype->components, component_handle);
  if(component_index == UINT32_MAX) {
    return ALIAS_ECS_ERROR_COMPONENT_DOES_NOT_EXIST;
  }

  *ptr = alias_ecs_write(instance, entity_index, component_index);

  return ALIAS_ECS_SUCCESS;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------

alias_ecs_Result alias_ecs_write_entity_component(
    alias_ecs_Instance        * instance
  , alias_ecs_EntityHandle      entity
  , alias_ecs_ComponentHandle   component_handle
  , void ** ptr
) {
  uint32_t entity_index;

  return_ERROR_INVALID_ARGUMENT_if(instance == NULL);
  return_if_ERROR(alias_ecs_validate_entity_handle(instance, entity, &entity_index));
  return_ERROR_INVALID_ARGUMENT_if(component_handle >= instance->component.length);

  alias_ecs_Archetype * archetype = ENTITY_ARCHETYPE_DATA(instance, entity_index);

  uint32_t component_index = alias_ecs_ComponentSet_order_of(&archetype->components, component_handle);
  if(component_index == UINT32_MAX) {
    return ALIAS_ECS_ERROR_COMPONENT_DOES_NOT_EXIST;
  }

  *ptr = alias_ecs_write(instance, entity_index, component_index);

  return ALIAS_ECS_SUCCESS;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------

alias_ecs_Result alias_ecs_despawn(
    alias_ecs_Instance           * instance
  , uint32_t                       count
  , const alias_ecs_EntityHandle * entity
) {
  uint32_t entity_index;
  
  return_ERROR_INVALID_ARGUMENT_if(instance == NULL);
  return_ERROR_INVALID_ARGUMENT_if(count > instance->entity.length);
  return_ERROR_INVALID_ARGUMENT_if(entity == NULL);

  for(uint32_t i = 0; i < count; i++) {
    return_if_ERROR(alias_ecs_validate_entity_handle(instance, entity[i], &entity_index));

    alias_ecs_unset_entity_layer(instance, entity_index);
    alias_ecs_unset_entity_archetype(instance, entity_index);
    alias_ecs_free_entity(instance, entity_index);
  }

  return ALIAS_ECS_SUCCESS;
}
