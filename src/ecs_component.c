#include "ecs_local.h"

alias_ecs_Result alias_ecs_register_component(
    alias_ecs_Instance                  * instance
  , const alias_ecs_ComponentCreateInfo * create_info
  , alias_ecs_ComponentHandle           * component_ptr
) {
  return_ERROR_INVALID_ARGUMENT_if(instance == NULL);
  return_ERROR_INVALID_ARGUMENT_if(create_info == NULL);
  return_ERROR_INVALID_ARGUMENT_if(component_ptr == NULL);
  return_ERROR_INVALID_ARGUMENT_if(create_info->size == 0);
  return_ERROR_INVALID_ARGUMENT_if(create_info->num_required_components > 0 && create_info->required_components == NULL);

  for(uint32_t i = 0; i < create_info->num_required_components; i++) {
    return_ERROR_INVALID_ARGUMENT_if(create_info->required_components[i] >= instance->component.length);
  }

  alias_ecs_ComponentHandle * required_components = NULL;

  if(create_info->num_required_components > 0) {
    ALLOC(instance, create_info->num_required_components, required_components);
    memcpy(required_components, create_info->required_components, create_info->num_required_components * sizeof(*required_components));
  }

  struct alias_ecs_Component component_data =
    { .flags = create_info->flags
    , .size = create_info->size
    , .num_required_components = create_info->num_required_components
    , .required_components = required_components
  };

  alias_Vector_space_for(&instance->component, &instance->memory_allocation_cb, 1);

  *component_ptr = instance->component.length;

  *alias_Vector_push(&instance->component) = component_data;

  return ALIAS_ECS_SUCCESS;
}

static int _compar_component_index(const void * ap, const void * bp) {
  uint32_t a = *(uint32_t *)ap;
  uint32_t b = *(uint32_t *)bp;
  return a - b;
}

alias_ecs_Result alias_ecs_ComponentSet_init_0(
    alias_ecs_Instance     * instance
  , alias_ecs_ComponentSet * set
  , uint32_t                 a_count
  , const uint32_t         * a_component_indexes
  , uint32_t                 b_count
  , const uint32_t         * b_component_indexes
) {
  set->count = a_count + b_count;
  set->index = NULL;
  if(set->count == 0) {
    return ALIAS_ECS_SUCCESS;
  }
  ALLOC(instance, set->count, set->index);
  if(a_count > 0) {
    memcpy(set->index, a_component_indexes, a_count * sizeof(*set->index));
  }
  if(b_count > 0) {
    memcpy(set->index + a_count, b_component_indexes, b_count * sizeof(*set->index));
  }
  qsort(set->index, set->count, sizeof(*set->index), _compar_component_index);
  return ALIAS_ECS_SUCCESS;
}

alias_ecs_Result alias_ecs_ComponentSet_init(
    alias_ecs_Instance              * instance
  , alias_ecs_ComponentSet          * set
  , uint32_t                          count
  , const alias_ecs_ComponentHandle * components
) {
  // if aeComponent ever changes, need to translate to the indexes
  return alias_ecs_ComponentSet_init_0(instance, set, count, components, 0, NULL);
}

alias_ecs_Result alias_ecs_ComponentSet_add(
    alias_ecs_Instance           * instance
  , alias_ecs_ComponentSet       * dst
  , const alias_ecs_ComponentSet * src
  , alias_ecs_ComponentHandle      component
) {
  // if aeComponent ever changes, need to translate to the indexes
  return alias_ecs_ComponentSet_init_0(instance, dst, src->count, src->index, 1, &component);
}

alias_ecs_Result alias_ecs_ComponentSet_remove(
    alias_ecs_Instance           * instance
  , alias_ecs_ComponentSet       * dst
  , const alias_ecs_ComponentSet * src
  , alias_ecs_ComponentHandle      component
) {
  // if aeComponent ever changes, need to translate to the indexes
  uint32_t order = alias_ecs_ComponentSet_order_of(src, component);
  if(order == UINT32_MAX) {
    return alias_ecs_ComponentSet_init_0(instance, dst, src->count, src->index, 0, NULL);
  } else {
    return alias_ecs_ComponentSet_init_0(instance, dst, order, src->index, src->count - order - 1, src->index + order + 1);
  }
}

uint32_t alias_ecs_ComponentSet_order_of(
    const alias_ecs_ComponentSet * set
  , alias_ecs_ComponentHandle      component
) {
  // if aeComponent ever changes, need to translate to the indexes
  uint32_t * p = bsearch(&component, set->index, set->count, sizeof(*set->index), _compar_component_index);
  if(p == NULL) {
    return UINT32_MAX;
  }
  return (uint32_t)(p - set->index);
}

int alias_ecs_ComponentSet_contains(
    const struct alias_ecs_ComponentSet * set
  , alias_ecs_ComponentHandle             component
) {
  return alias_ecs_ComponentSet_order_of(set, component) != UINT32_MAX;
}

int alias_ecs_ComponentSet_is_subset(
    const alias_ecs_ComponentSet * set
  , const alias_ecs_ComponentSet * subset
) {
  for(uint32_t s = 0, ss = 0; ss < subset->count; ++ss) {
    while(s < set->count && set->index[s] < subset->index[ss]) s++;
    if(s >= set->count) {
      return 0;
    }
    if(subset->index[ss] != set->index[s]) {
      return 0;
    }
  }
  return 1;
}

int alias_ecs_ComponentSet_intersects(
    const alias_ecs_ComponentSet * aset
  , const alias_ecs_ComponentSet * bset
) {
  uint32_t
      ai = 0
    , bi = 0
    ;
  for(; ai < aset->count; ai++) {
    while(bi < bset->count && bset->index[bi] < aset->index[ai]) bi++;
    if(bi >= bset->count) {
      return 0;
    }
    if(bset->index[bi] == aset->index[ai]) {
      return 1;
    }
  }
  return 0;
}

alias_ecs_Result alias_ecs_ComponentSet_expand_required(
    alias_ecs_Instance     * instance
  , alias_ecs_ComponentSet * set
) {
  top:
    
  for(uint32_t i = 0; i < set->count; i++) {
    alias_ecs_ComponentHandle c = set->index[i];
    
    if(instance->component.data[c].num_required_components > 0) {
      for(uint32_t j = 0; j < instance->component.data[c].num_required_components; j++) {
        alias_ecs_ComponentHandle r = instance->component.data[c].required_components[j];
        
        if(!alias_ecs_ComponentSet_contains(set, r)) {
          alias_ecs_ComponentSet new_set;
          return_if_ERROR(alias_ecs_ComponentSet_add(instance, &new_set, set, r));
          alias_ecs_ComponentSet_free(instance, set);
          *set = new_set;
          goto top;
        }
      }
    }
  }

  return ALIAS_ECS_SUCCESS;
}

void alias_ecs_ComponentSet_free(
    alias_ecs_Instance     * instance
  , alias_ecs_ComponentSet * set
) {
  if(set->index != NULL) {
    FREE(instance, set->count, set->index);
  }
}

