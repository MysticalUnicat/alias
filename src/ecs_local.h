// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_ECS_LOCAL_H_
#define _ALIAS_ECS_LOCAL_H_

#include <alias/ecs.h>
#include <alias/data_structure/vector.h>
#include <alias/data_structure/paged_soa.h>

#include <stdlib.h>
#include <stdalign.h>
#include <string.h>

#define UNUSED(X) (void)X
#define sizeof_alignof(X) sizeof(X), alignof(X)

typedef uint32_t alias_ecs_ArchetypeHandle;

typedef struct alias_ecs_Layer {
  uint32_t dirty : 1;
  uint32_t at_max : 1;
  uint32_t _reserved : 30;
  alias_Vector(uint32_t) entities;
} alias_ecs_Layer;

typedef struct alias_ecs_Component {
  union {
    struct {
      uint32_t non_null : 1;
      uint32_t _flags_unused : 31;
    };
    uint32_t flags;
  };
  uint32_t size;
  uint32_t num_required_components;
  const alias_ecs_ComponentHandle * required_components;
  alias_ecs_ComponentInitCB init;
  alias_ecs_ComponentCleanupCB cleanup;
} alias_ecs_Component;

typedef struct alias_ecs_ComponentSet {
  uint32_t count;
  uint32_t * index;
} alias_ecs_ComponentSet;

#define TOTAL_BLOCK_SIZE (1 << 16)
#define BLOCK_DATA_SIZE (TOTAL_BLOCK_SIZE - (sizeof(uint32_t) * 2))

typedef struct alias_ecs_Archetype {
  alias_ecs_ComponentSet components;
  uint32_t               any_init : 1;
  uint32_t               any_cleanup : 1;
  uint32_t               _reserved : 30;
  alias_Vector(uint32_t) free_codes;
  alias_PagedSOA         paged_soa;
} alias_ecs_Archetype;

// typedef already in ecs.h
struct alias_ecs_Instance {
  alias_MemoryCB memory_cb;

  // generational layers
  struct {
    alias_Vector(uint32_t) free_indexes;
    uint32_t capacity;
    uint32_t length;
    uint32_t * generation;
    alias_ecs_Layer * data;
  } layer;

  // generational entities
  struct {
    alias_Vector(uint32_t) free_indexes;
    uint32_t capacity;
    uint32_t length;
    uint32_t * generation;
    uint32_t * layer_index;
    uint32_t * archetype_index;
    uint32_t * archetype_code;
  } entity;

  // archetypes are 'sorted' by component sets
  // created as needed
  struct {
    uint32_t capacity;
    uint32_t length;
    uint32_t * components_index;
    alias_ecs_Archetype * data;
  } archetype;

  alias_Vector(alias_ecs_Component) component;
};

struct alias_ecs_Query {
  alias_ecs_ComponentSet component_set;
  uint32_t last_archetype_tested;

  alias_ecs_ComponentSet require_component_set;
  alias_ecs_ComponentSet exclude_component_set;

  uint32_t component_count;

  uint32_t first_component_read;

  alias_ecs_ComponentHandle * component;
  uint8_t ** runtime;

  uint32_t archetype_capacity;
  uint32_t archetype_length;

  alias_ecs_ArchetypeHandle * archetype;

  uint32_t * size_offset;
};

// ============================================================================
#define ENTITY_GENERATION(I, E)             (I)->entity.generation[E]
#define ENTITy_LAYER_INDEX(I, E)            (I)->entity.layer_index[E]
#define ENTITY_ARCHETYPE_INDEX(I, E)        (I)->entity.archetype_index[E]
#define ENTITY_ARCHETYPE_CODE(I, E)         (I)->entity.archetype_code[E]
#define ENTITY_ARCHETYPE_CODE_PAGE(I, E)    (ENTITY_ARCHETYPE_CODE(I, E) >> 16)
#define ENTITY_ARCHETYPE_CODE_INDEX(I, E)   (ENTITY_ARCHETYPE_CODE(I, E) & 0xFFFF)
#define ENTITY_ARCHETYPE_DATA(I, E)         (&(I)->archetype.data[ENTITY_ARCHETYPE_INDEX(I, E)])
#define ENTITY_DATA_BLOCK(I, E)             ENTITY_ARCHETYPE_DATA(I, E)->paged_soa.pages[ENTITY_ARCHETYPE_CODE_PAGE(I, E)]
#define ENTITY_DATA_BLOCK_DATA(I, E)        ((void *)(ENTITY_DATA_BLOCK(I, E) + sizeof(uint32_t)))
#define ENTITY_DATA_ENTITY_INDEX(I, E)      ((uint32_t *)ENTITY_DATA_BLOCK_DATA(I, E))[ENTITY_ARCHETYPE_CODE_INDEX(I, E)]

static inline alias_ecs_EntityHandle alias_ecs_construct_entity_handle(uint32_t generation, uint32_t index) {
  return ((uint64_t)generation << 32) | (uint64_t)index;
}

static inline alias_ecs_EntityHandle alias_ecs_construct_entity_handle_index_only(alias_ecs_Instance * instance, uint32_t index) {
  return alias_ecs_construct_entity_handle(ENTITY_GENERATION(instance, index), index);
}

static inline void * alias_ecs_raw_access(
    alias_ecs_Instance * instance
  , uint32_t             archetype_index
  , uint32_t             component_index
  , uint32_t             page
  , uint32_t             index
) {
  alias_ecs_Archetype * archetype = &instance->archetype.data[archetype_index];
  uint32_t size, offset;
  alias_PagedSOA_decode_column(&archetype->paged_soa, component_index + 1, &size, &offset);
  return alias_PagedSOA_raw_write(&archetype->paged_soa, page, index, size, offset);
}

static inline void * alias_ecs_write(
    alias_ecs_Instance * instance
  , uint32_t             entity_index
  , uint32_t             component_index
) {
  uint32_t archetype_index = ENTITY_ARCHETYPE_INDEX(instance, entity_index);
  uint32_t page = ENTITY_ARCHETYPE_CODE_PAGE(instance, entity_index);
  uint32_t index = ENTITY_ARCHETYPE_CODE_INDEX(instance, entity_index);
  return alias_ecs_raw_access(instance, archetype_index, component_index, page, index);
}

// ============================================================================
#define return_if_ERROR(C) do { alias_ecs_Result __r = C; if(__r < ALIAS_ECS_SUCCESS) return __r; } while(0)
#define return_ERROR_INVALID_ARGUMENT_if(X) do { if(X) { return ALIAS_ECS_ERROR_INVALID_ARGUMENT; } } while(0)
#define ASSERT(X) do { if(!(X)) { return ALIAS_ECS_ERROR_INVALID_ARGUMENT; } } while(0)

#if 0
int printf(const char *, ...);
#define TRACE(F, ...) printf("%s:%i - " F "\n", __FILE__, __LINE__, ## __VA_ARGS__)
#else
#define TRACE(F, ...)
#endif

// ============================================================================
// memory.c
alias_ecs_Result alias_ecs_malloc(
    alias_ecs_Instance * instance
  , size_t               size
  , size_t               alignment
  , void *             * out_ptr
);

alias_ecs_Result alias_ecs_realloc(
    alias_ecs_Instance * instance
  , void               * ptr
  , size_t               old_size
  , size_t               new_size
  , size_t               alignment
  , void *             * out_ptr
);

void alias_ecs_free(
    alias_ecs_Instance * instance
  , void               * ptr
  , size_t               size
  , size_t               alignment
);

typedef int (*alias_ecs_CompareFn)(void *, const void *, const void *);
typedef alias_Closure(alias_ecs_CompareFn) alias_ecs_CompareCB;

void alias_ecs_quicksort(
    void                * base
  , size_t                num
  , size_t                size
  , alias_ecs_CompareCB   cb
);

void * alias_ecs_bsearch(
    const void          * key
  , const void          * base
  , size_t                num
  , size_t                size
  , alias_ecs_CompareCB   cb
);

#define ALLOC(I, C, P)          return_if_ERROR(alias_ecs_malloc(I, (C) * sizeof_alignof(*P), (void **)&P))
#define RELOC(I, oldC, newC, P) return_if_ERROR(alias_ecs_realloc(I, P, (oldC) * sizeof(*P), (newC) * sizeof_alignof(*P), (void **)&P))
#define FREE(I, C, P)           alias_ecs_free(I, (void *)P, (C) * sizeof_alignof(*P))

// ============================================================================
// component.c
alias_ecs_Result alias_ecs_init_component(alias_ecs_Instance * instance, uint32_t entity_index, uint32_t archetype_index, uint32_t component_index);
alias_ecs_Result alias_ecs_init_components(alias_ecs_Instance * instance, uint32_t entity_index, uint32_t archetype_index);
alias_ecs_Result alias_ecs_cleanup_component(alias_ecs_Instance * instance, uint32_t entity_index, uint32_t archetype_index, uint32_t component_index);
alias_ecs_Result alias_ecs_cleanup_components(alias_ecs_Instance * instance, uint32_t entity_index, uint32_t archetype_index);

alias_ecs_Result alias_ecs_ComponentSet_init(
    alias_ecs_Instance              * instance
  , alias_ecs_ComponentSet          * set
  , uint32_t                          count
  , const alias_ecs_ComponentHandle * components
);

alias_ecs_Result alias_ecs_ComponentSet_add(
    alias_ecs_Instance           * instance
  , alias_ecs_ComponentSet       * dst
  , const alias_ecs_ComponentSet * src
  , alias_ecs_ComponentHandle      component
);

alias_ecs_Result alias_ecs_ComponentSet_remove(
    alias_ecs_Instance * instance
  , alias_ecs_ComponentSet * dst
  , const alias_ecs_ComponentSet * src
  , alias_ecs_ComponentHandle component
);

uint32_t alias_ecs_ComponentSet_order_of(
    const alias_ecs_ComponentSet * set
  , alias_ecs_ComponentHandle component
);

int alias_ecs_ComponentSet_contains(
    const alias_ecs_ComponentSet * set
  , alias_ecs_ComponentHandle      component
);

int alias_ecs_ComponentSet_is_subset(
    const alias_ecs_ComponentSet * a
  , const alias_ecs_ComponentSet * b
);

int alias_ecs_ComponentSet_intersects(
    const alias_ecs_ComponentSet * a
  , const alias_ecs_ComponentSet * b
);

alias_ecs_Result alias_ecs_ComponentSet_expand_required(
    alias_ecs_Instance     * instance
  , alias_ecs_ComponentSet * set
);

void alias_ecs_ComponentSet_free(
    alias_ecs_Instance *     instance
  , alias_ecs_ComponentSet * set
);

// ============================================================================
// layer.c
alias_ecs_Result alias_ecs_validate_layer_handle(
    const alias_ecs_Instance * instance
  , alias_ecs_LayerHandle      layer
  , uint32_t                 * index_ptr
);

alias_ecs_Result alias_ecs_set_entity_layer(
    alias_ecs_Instance * instance
  , uint32_t             entity_index
  , uint32_t             layer_index
);

void alias_ecs_unset_entity_layer(
    alias_ecs_Instance * instance
  , uint32_t             entity_index
);

// ============================================================================
// entity.c
alias_ecs_Result alias_ecs_validate_entity_handle(
    const alias_ecs_Instance * instance
  , alias_ecs_EntityHandle     entity
  , uint32_t                 * index_ptr
);

alias_ecs_Result alias_ecs_create_entity(
    alias_ecs_Instance     * instance
  , alias_ecs_EntityHandle * entity_ptr
);

alias_ecs_Result alias_ecs_free_entity(
    alias_ecs_Instance * instance
  , uint32_t             entity_id
);

// ============================================================================
// archetype.c
alias_ecs_Result alias_ecs_resolve_archetype(
    alias_ecs_Instance        * instance
  , alias_ecs_ComponentSet      components
  , alias_ecs_ArchetypeHandle * out_ptr
);

alias_ecs_Result alias_ecs_unset_entity_archetype(
    alias_ecs_Instance * instance
  , uint32_t             entity_index
);

alias_ecs_Result alias_ecs_set_entity_archetype(
    alias_ecs_Instance * instance
  , uint32_t             entity_index
  , uint32_t             archetype_index
);

#endif

