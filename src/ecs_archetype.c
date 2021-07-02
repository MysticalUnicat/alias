#include "ecs_local.h"

static int _compare_components(
    uint32_t         a_num_components
  , const uint32_t * a_component_indexes
  , uint32_t         b_num_components
  , const uint32_t * b_component_indexes
) {
  if(a_num_components != b_num_components) {
    return (int)a_num_components - (int)b_num_components;
  }
  if(a_num_components > 0) {
    return memcmp(a_component_indexes, b_component_indexes, sizeof(*a_component_indexes) * a_num_components);
  } else {
    return 0;
  }
}

static int _sort(void * ud, const void * ap, const void * bp) {
  alias_ecs_Instance * instance = (alias_ecs_Instance *)ud;
  uint32_t a_index = *(uint32_t *)ap;
  uint32_t b_index = *(uint32_t *)bp;
  alias_ecs_Archetype * a = &instance->archetype.data[a_index];
  alias_ecs_Archetype * b = &instance->archetype.data[b_index];
  return _compare_components(a->components.count, a->components.index, b->components.count, b->components.index);
}

static int _search(void * ud, const void * ap, const void * bp) {
  alias_ecs_Instance * instance = (alias_ecs_Instance *)ud;
  const alias_ecs_ComponentSet * components = (const alias_ecs_ComponentSet *)ap;
  uint32_t archetype_index = *(uint32_t *)bp;
  const alias_ecs_Archetype * archetype = &instance->archetype.data[archetype_index];
  return _compare_components(components->count, components->index, archetype->components.count, archetype->components.index);
}

alias_ecs_Result alias_ecs_resolve_archetype(
    alias_ecs_Instance        * instance
  , alias_ecs_ComponentSet      components
  , alias_ecs_ArchetypeHandle * out_ptr
) {
  return_if_ERROR(alias_ecs_ComponentSet_expand_required(instance, &components));
  
  uint32_t * index_ptr = alias_ecs_bsearch(
      &components
    , instance->archetype.components_index
    , instance->archetype.length
    , sizeof(*instance->archetype.components_index)
    , (alias_ecs_CompareCB) { _search, instance }
  );

  if(index_ptr != NULL) {
    *out_ptr = *index_ptr;
    alias_ecs_ComponentSet_free(instance, &components);
    return ALIAS_ECS_SUCCESS;
  }

  uint32_t archetype_index = instance->archetype.length++;

  if(instance->archetype.length > instance->archetype.capacity) {
    uint32_t old_capacity = instance->archetype.capacity;
    uint32_t new_capacity = instance->archetype.length + (instance->archetype.length >> 1);
    RELOC(instance, old_capacity, new_capacity, instance->archetype.components_index);
    RELOC(instance, old_capacity, new_capacity, instance->archetype.data);
    instance->archetype.capacity = new_capacity;
  }

  alias_ecs_Archetype * archetype = &instance->archetype.data[archetype_index];

  archetype->components = components;

  size_t * sizes = alias_malloc(&instance->memory_cb, sizeof(size_t) * (1 + components.count), alignof(*sizes));

  sizes[0] = sizeof(uint32_t);
  for(uint32_t i = 0; i < components.count; i++) {
    sizes[i + 1] = instance->component.data[components.index[i]].size;
  }

  alias_PagedSOA_initialize(&archetype->paged_soa, &instance->memory_cb, sizeof(uint32_t), 1 + components.count, sizes);

  alias_free(&instance->memory_cb, sizes, sizeof(size_t) * (1 + components.count), alignof(*sizes));

  instance->archetype.components_index[archetype_index] = archetype_index;
  alias_ecs_quicksort(
      instance->archetype.components_index
    , instance->archetype.length
    , sizeof(*instance->archetype.components_index)
    , (alias_ecs_CompareCB) { _sort, instance });

  *out_ptr = archetype_index;

  return ALIAS_ECS_SUCCESS;
}

static alias_ecs_Result _allocate_code(
    alias_ecs_Instance * instance
  , uint32_t             archetype_index
  , uint32_t           * archetype_code
) {
  alias_ecs_Archetype * archetype = &instance->archetype.data[archetype_index];

  uint32_t code;

  if(archetype->free_codes.length > 0) {
    code = *alias_Vector_pop(&archetype->free_codes);
  } else {
    alias_PagedSOA_space_for(&archetype->paged_soa, &instance->memory_cb, 1);
    code = alias_PagedSOA_push(&archetype->paged_soa);
  }

  *(uint32_t *)alias_PagedSOA_page(&archetype->paged_soa, code) += 1;

  *archetype_code = code;

  return ALIAS_ECS_SUCCESS;
}

static alias_ecs_Result _free_code(
    alias_ecs_Instance * instance
  , uint32_t             archetype_index
  , uint32_t             code
) {
  alias_ecs_Archetype * archetype = &instance->archetype.data[archetype_index];

  if(!alias_Vector_space_for(&archetype->free_codes, &instance->memory_cb, 1)) {
    return ALIAS_ECS_ERROR_OUT_OF_MEMORY;
  }
  
  *alias_Vector_push(&archetype->free_codes) = code;

  *(uint32_t *)alias_PagedSOA_page(&archetype->paged_soa, code) -= 1;

  return ALIAS_ECS_SUCCESS;
}

alias_ecs_Result alias_ecs_unset_entity_archetype(
    alias_ecs_Instance * instance
  , uint32_t             entity_index
) {
  uint32_t archetype_index = ENTITY_ARCHETYPE_INDEX(instance, entity_index);
  uint32_t archetype_code = ENTITY_ARCHETYPE_CODE(instance, entity_index);
  
  ENTITY_DATA_ENTITY_INDEX(instance, entity_index) = 0;
  ENTITY_ARCHETYPE_INDEX(instance, entity_index) = 0;
  ENTITY_ARCHETYPE_CODE(instance, entity_index) = 0;

  return _free_code(instance, archetype_index, archetype_code);
}

alias_ecs_Result alias_ecs_set_entity_archetype(
    alias_ecs_Instance * instance
  , uint32_t             entity_index
  , uint32_t             archetype_index
) {
  alias_ecs_Archetype * archetype = &instance->archetype.data[archetype_index];

  if(ENTITY_ARCHETYPE_INDEX(instance, entity_index) == 0) {
    uint32_t code;
    return_if_ERROR(_allocate_code(instance, archetype_index, &code));
    ENTITY_ARCHETYPE_INDEX(instance, entity_index) = archetype_index;
    ENTITY_ARCHETYPE_CODE(instance, entity_index) = code;
    ENTITY_DATA_ENTITY_INDEX(instance, entity_index) = entity_index;
    return ALIAS_ECS_SUCCESS;
  }

  ENTITY_DATA_ENTITY_INDEX(instance, entity_index) = 0;

  uint32_t old_archetype_index = ENTITY_ARCHETYPE_INDEX(instance, entity_index);
  uint32_t old_code = ENTITY_ARCHETYPE_CODE(instance, entity_index);
  alias_ecs_Archetype * old_archetype = &instance->archetype.data[old_archetype_index];
  uint32_t old_block_index = old_code >> 16;
  uint32_t old_block_offset = old_code & 0xFFFF;

  return_if_ERROR(_free_code(instance, old_archetype_index, old_code));

  uint32_t code;
  return_if_ERROR(_allocate_code(instance, archetype_index, &code));
  uint32_t block_index = code >> 16;
  uint32_t block_offset = code & 0xFFFF;
  
  ENTITY_ARCHETYPE_INDEX(instance, entity_index) = archetype_index;
  ENTITY_ARCHETYPE_CODE(instance, entity_index) = code;
  ENTITY_DATA_ENTITY_INDEX(instance, entity_index) = entity_index;

  uint32_t r = 0;
  uint32_t w = 0;

  while(w < archetype->components.count && r < old_archetype->components.count) {
    alias_ecs_ComponentHandle c = archetype->components.index[w];

    while(r < old_archetype->components.count && old_archetype->components.index[r] < c) {
      r++;
    }

    if(r < old_archetype->components.count && old_archetype->components.index[r] == c) {
      void * old_data = alias_ecs_raw_access(instance, old_archetype_index, r, old_block_index, old_block_offset);
      void *     data = alias_ecs_raw_access(instance,     archetype_index, w,     block_index,     block_offset);
      memcpy(data, old_data, archetype->paged_soa.size_offset[w + 1] >> 16);
      
      r++;
    }

    w++;
  }
  
  return ALIAS_ECS_SUCCESS;
}

