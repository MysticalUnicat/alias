#include "ecs_local.h"

#include <alias/log.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))

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
  ALLOC(instance, query->component_count, query->runtime);

  uint32_t ci = 0;
  for(uint32_t i = 0; i < create_info->num_write_components; i++) {
    query->component[ci] = create_info->write_components[i];
    ci++;
  }

  for(uint32_t i = 0; i < create_info->num_read_components; i++) {
    query->component[ci] = create_info->read_components[i];
    ci++;
  }

  return_if_ERROR(alias_ecs_ComponentSet_init(instance, &query->component_set, query->component_count, query->component));

  alias_Vector(uint32_t) other = { 0 };
  alias_Vector_set_capacity(&other, &instance->memory_cb, query->component_count + create_info->num_filters);

  for(uint32_t i = 0; i < query->component_count; i++) {
    bool optional = false;
    for(uint32_t j = 0; j < create_info->num_filters; j++) {
      if(create_info->filters[j].filter == ALIAS_ECS_FILTER_OPTIONAL && create_info->filters[j].component == query->component[i]) {
        optional = true;
        break;
      }
    }
    if(optional) {
      continue;
    }
    *alias_Vector_push(&other) = query->component[i];
  }
  for(uint32_t j = 0; j < create_info->num_filters; j++) {
    if(create_info->filters[j].filter != ALIAS_ECS_FILTER_MODIFIED) {
      continue;
    }
    if(!alias_ecs_ComponentSet_contains(&query->component_set, create_info->filters[j].component)) {
      *alias_Vector_push(&other) = create_info->filters[j].component;
    }
  }
  return_if_ERROR(alias_ecs_ComponentSet_init(instance, &query->require_component_set, other.length, other.data));

  other.length = 0;
  for(uint32_t j = 0; j < create_info->num_filters; j++) {
    if(create_info->filters[j].filter == ALIAS_ECS_FILTER_EXCLUDE) {
      *alias_Vector_push(&other) = create_info->filters[j].component;
    }
  }
  return_if_ERROR(alias_ecs_ComponentSet_init(instance, &query->exclude_component_set, other.length, other.data));
  
  alias_Vector_free(&other, &instance->memory_cb);

  *query_ptr = query;

  return ALIAS_ECS_SUCCESS;
}

#if 0
static void _print_component_set(alias_ecs_ComponentSet * set) {
  printf("{");
  for(uint32_t i = 0; i < set->count; i++) {
    printf("%s%u", i == 0 ? "" : ", ", set->index[i]);
  }
  putchar('}');
}
#endif

static alias_ecs_Result alias_ecs_update_query(
    alias_ecs_Instance * instance
  , alias_ecs_Query * query
) {
  return_ERROR_INVALID_ARGUMENT_if(instance == NULL);
  return_ERROR_INVALID_ARGUMENT_if(query == NULL);

  for(; query->last_archetype_tested < instance->archetype.length; query->last_archetype_tested++) {
    alias_ecs_Archetype * archetype = &instance->archetype.data[query->last_archetype_tested];

    bool skip = false;

    if(!alias_ecs_ComponentSet_is_subset(&archetype->components, &query->require_component_set)) {
      skip = true;
    }

    if(!skip && query->exclude_component_set.count > 0 && alias_ecs_ComponentSet_intersects(&archetype->components, &query->exclude_component_set)) {
      skip = true;
    }

    if(skip) {
      continue;
    }

    if(query->archetype_length + 1 >= query->archetype_capacity) {
      uint32_t old_capacity = query->archetype_capacity;
      uint32_t new_capacity = query->archetype_length + 1;
      new_capacity += new_capacity >> 1;
      RELOC(instance,                          old_capacity,                          new_capacity, query->archetype);
      RELOC(instance, query->component_count * old_capacity, query->component_count * new_capacity, query->offset_size);
      query->archetype_capacity = new_capacity;
    }

    uint32_t index = query->archetype_length++;
    query->archetype[index] = query->last_archetype_tested;

    for(uint32_t k = 0; k < query->component_count; k++) {
      uint32_t archetype_component_index = alias_ecs_ComponentSet_order_of(&archetype->components, query->component[k]);
      if(archetype_component_index != UINT32_MAX) {
        query->offset_size[index * query->component_count + k] = archetype->offset_size[archetype_component_index];
      }
    }
  }

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

  return_if_ERROR(alias_ecs_update_query(instance, query));

  uint8_t ** runtime = query->runtime;
  const uint32_t * offset_size = query->offset_size;
  const alias_ecs_ArchetypeHandle * archetype_handle = query->archetype;
  for(uint32_t i = 0; i < query->archetype_length; i++) {
    const alias_ecs_Archetype * archetype = &instance->archetype.data[*archetype_handle];

    for(uint32_t j = 0; j < archetype->blocks.length; j++) {
      alias_ecs_DataBlock * block = (alias_ecs_DataBlock *)archetype->blocks.data[j];
      if(block == NULL) {
        break;
      }
      const uint32_t * entity = (const uint32_t *)block->data;
      for(uint32_t c = 0, C = query->component_count; c < C; c++) {
        runtime[c] = offset_size[c] ? block->data + (offset_size[c] >> 16) : NULL;
      }
      for(uint32_t k = 0, K = block->live_count; k < K; ) {
        if(*entity) {
          alias_Closure_call(&cb, instance, *entity, (void **)runtime);
          k++;
        }
        entity++;
        for(uint32_t c = 0, C = query->component_count; c < C; c++) {
          runtime[c] += offset_size[c] & 0xFFFF;
        }
      }
    }

    archetype_handle++;
    offset_size += query->component_count;
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
  alias_ecs_ComponentSet_free(instance, &query->require_component_set);
  alias_ecs_ComponentSet_free(instance, &query->exclude_component_set);
  FREE(instance,                           query->component_count, query->component);
  FREE(instance,                           query->component_count, query->runtime);
  FREE(instance, query->archetype_length                         , query->archetype);
  FREE(instance, query->archetype_length * query->component_count, query->offset_size);
  FREE(instance,                                                1, query);
}

