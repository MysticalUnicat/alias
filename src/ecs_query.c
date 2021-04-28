#include "ecs_local.h"

alias_ecs_Result alias_ecs_create_query(
    alias_ecs_Instance              * instance
  , const alias_ecs_QueryCreateInfo * create_info
  , alias_ecs_Query *               * query_ptr
) {
  alias_ecs_Query * query;

  ALLOC(instance, 1, query);

  query->component_count = create_info->num_write_components + create_info->num_read_components;
  query->first_component_read = create_info->num_write_components;

  ALLOC(instance, query->component_count, query->component);
  ALLOC(instance, query->component_count, query->size);
  ALLOC(instance, query->component_count, query->runtime);

  for(uint32_t i = 0; i < create_info->num_write_components; i++) {
    query->component[i] = create_info->write_components[i];
    query->size[i] = instance->component.data[create_info->write_components[i]].size;
  }

  for(uint32_t i = 0; i < create_info->num_read_components; i++) {
    query->component[i] = create_info->read_components[i];
    query->size[i] = instance->component.data[create_info->read_components[i]].size;
  }

  return_if_ERROR(alias_ecs_ComponentSet_init(instance, &query->component_set, query->component_count, query->component));

  *query_ptr = query;

  return ALIAS_ECS_SUCCESS;
}

alias_ecs_Result alias_ecs_execute_query(
    alias_ecs_Instance * instance
  , alias_ecs_Query    * query
  , alias_ecs_QueryCB    cb
) {
  return_ERROR_INVALID_ARGUMENT_if(instance == NULL);
  return_ERROR_INVALID_ARGUMENT_if(query == NULL);
  return_ERROR_INVALID_ARGUMENT_if(alias_Closure_is_empty(&cb));

  for(; query->last_archetype_tested < instance->archetype.length; query->last_archetype_tested++) {
    alias_ecs_Archetype * archetype = &instance->archetype.data[query->last_archetype_tested];

    if(!alias_ecs_ComponentSet_is_subset(&archetype->components, &query->component_set)) {
      continue;
    }

    if(query->archetype_length + 1 >= query->archetype_capacity) {
      uint32_t old_capacity = query->archetype_capacity;
      uint32_t new_capacity = query->archetype_length + 1;
      new_capacity += new_capacity >> 1;
      RELOC(instance,                          old_capacity,                          new_capacity, query->archetype);
      RELOC(instance, query->component_count * old_capacity, query->component_count * new_capacity, query->offset);
      query->archetype_capacity = new_capacity;
    }

    uint32_t index = query->archetype_length++;
    query->archetype[index] = query->last_archetype_tested;

    for(uint32_t k = 0; k < query->component_count; k++) {
      uint32_t archetype_component_index = alias_ecs_ComponentSet_order_of(&archetype->components, query->component[k]);
      ASSERT(archetype_component_index != UINT32_MAX);
      query->offset[index * query->component_count + k] = archetype->offset_size[archetype_component_index] >> 16;
    }
  }

  uint8_t ** runtime = query->runtime;
  const uint16_t * offset = query->offset;
  const uint16_t * size = query->size;
  const alias_ecs_ArchetypeHandle * archetype_handle = query->archetype;
  for(uint32_t i = 0; i < query->archetype_length; i++) {
    const alias_ecs_Archetype * archetype = &instance->archetype.data[*archetype_handle];

    for(uint32_t j = 0; j < archetype->blocks.length; j++) {
      alias_ecs_DataBlock * block = (alias_ecs_DataBlock *)archetype->blocks.data[j];
      if(block == NULL) {
        break;
      }
      const uint32_t * entity = (const uint32_t *)block->data;
      for(uint32_t k = 0; k < query->component_count; ++k) {
        runtime[k] = block->data + offset[k];
      }
      for(uint32_t k = 0; k < archetype->entities_per_block; k++) {
        if(*entity) {
          alias_Closure_call(&cb, instance, *entity, (void **)runtime);
        }
        entity++;
        for(uint32_t l = 0; l < query->component_count; l++) {
          runtime[l] += size[l];
        }
      }
    }

    archetype_handle++;
    offset += query->component_count;
  }

  return ALIAS_ECS_SUCCESS;
}

void alias_ecs_destroy_query(
    alias_ecs_Instance * instance
  , alias_ecs_Query    * query
) {
  if(instance == NULL || query == NULL) {
    return;
  }
  alias_ecs_ComponentSet_free(instance, &query->component_set);
  FREE(instance,                           query->component_count, query->component);
  FREE(instance,                           query->component_count, query->size);
  FREE(instance,                           query->component_count, query->runtime);
  FREE(instance, query->archetype_length                         , query->archetype);
  FREE(instance, query->archetype_length * query->component_count, query->offset);
  FREE(instance,                                                1, query);
}

