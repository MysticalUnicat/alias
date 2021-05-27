#ifndef _ALIAS_ECS_LOCAL_H_
#define _ALIAS_ECS_LOCAL_H_

#include "utils_local.h"
#include <alias/ecs.h>

#include <stdlib.h>
#include <stdalign.h>
#include <string.h>

#define UNUSED(X) (void)X
#define sizeof_alignof(X) sizeof(X), alignof(X)

typedef uint32_t alias_ecs_ArchetypeHandle;

#define alias_ecs_Vector(T) struct { uint32_t capacity; uint32_t length; T * data; }

typedef struct alias_ecs_Layer {
  uint32_t dirty : 1;
  uint32_t at_max : 1;
  uint32_t _reserved : 30;
  alias_ecs_Vector(uint32_t) entities;
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
} alias_ecs_Component;

typedef struct alias_ecs_ComponentSet {
  uint32_t count;
  uint32_t * index;
} alias_ecs_ComponentSet;

#define TOTAL_BLOCK_SIZE (1 << 16)
#define BLOCK_DATA_SIZE (TOTAL_BLOCK_SIZE - (sizeof(uint32_t) * 2))

typedef struct alias_ecs_DataBlock {
  uint32_t live_count;
  uint8_t data[BLOCK_DATA_SIZE];
} alias_ecs_DataBlock;

typedef struct alias_ecs_Archetype {
  alias_ecs_ComponentSet components;

  uint32_t * offset_size;

  uint32_t entity_size;
  uint32_t entities_per_block;

  uint32_t next_index;
  alias_ecs_Vector(uint32_t) free_indexes;

  alias_ecs_Vector(alias_ecs_DataBlock *) blocks;
} alias_ecs_Archetype;

// typedef already in ecs.h
struct alias_ecs_Instance {
  alias_MemoryAllocationCallback memory_allocation_cb;

  // generational layers
  struct {
    alias_ecs_Vector(uint32_t) free_indexes;
    uint32_t capacity;
    uint32_t length;
    uint32_t * generation;
    alias_ecs_Layer * data;
  } layer;

  // generational entities
  struct {
    alias_ecs_Vector(uint32_t) free_indexes;
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

  alias_ecs_Vector(alias_ecs_Component) component;
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

  uint32_t * offset_size;
};

// ============================================================================
#define ENTITY_GENERATION(I, E)             (I)->entity.generation[E]
#define ENTITy_LAYER_INDEX(I, E)            (I)->entity.layer_index[E]
#define ENTITY_ARCHETYPE_INDEX(I, E)        (I)->entity.archetype_index[E]
#define ENTITY_ARCHETYPE_CODE(I, E)         (I)->entity.archetype_code[E]
#define ENTITY_ARCHETYPE_BLOCK_INDEX(I, E)  (ENTITY_ARCHETYPE_CODE(I, E) >> 16)
#define ENTITY_ARCHETYPE_BLOCK_OFFSET(I, E) (ENTITY_ARCHETYPE_CODE(I, E) & 0xFFFF)
#define ENTITY_ARCHETYPE_DATA(I, E)         (&(I)->archetype.data[ENTITY_ARCHETYPE_INDEX(I, E)])
#define ENTITY_DATA_BLOCK(I, E)             ENTITY_ARCHETYPE_DATA(I, E)->blocks.data[ENTITY_ARCHETYPE_BLOCK_INDEX(I, E)]
#define ENTITY_DATA_BLOCK_DATA(I, E)        (ENTITY_DATA_BLOCK(I, E)->data)
#define ENTITY_DATA_ENTITY_INDEX(I, E)      ((uint32_t *)ENTITY_DATA_BLOCK_DATA(I, E))[ENTITY_ARCHETYPE_BLOCK_OFFSET(I, E)]

static inline void * alias_ecs_raw_access(
    alias_ecs_Instance * instance
  , uint32_t             archetype_index
  , uint32_t             component_index
  , uint32_t             block_index
  , uint32_t             block_offset
) {
  alias_ecs_Archetype * archetype = &instance->archetype.data[archetype_index];
  alias_ecs_DataBlock * block = archetype->blocks.data[block_index];
  uint32_t offset_size = archetype->offset_size[component_index];
  uint32_t offset = offset_size >> 16;
  uint32_t size = offset_size & 0xFFFF;
  return (void *)(block->data + (uintptr_t)offset + ((uintptr_t)block_offset * size));
}

static inline void * alias_ecs_write(
    alias_ecs_Instance * instance
  , uint32_t             entity_index
  , uint32_t             component_index
) {
  uint32_t archetype_index = ENTITY_ARCHETYPE_INDEX(instance, entity_index);
  uint32_t block_index = ENTITY_ARCHETYPE_BLOCK_INDEX(instance, entity_index);
  uint32_t block_offset = ENTITY_ARCHETYPE_BLOCK_OFFSET(instance, entity_index);
  return alias_ecs_raw_access(instance, archetype_index, component_index, block_index, block_offset);
}

// ============================================================================
#define return_if_ERROR(C) do { alias_ecs_Result __r = C; if(__r < ALIAS_ECS_SUCCESS) return __r; } while(0)
#define return_ERROR_INVALID_ARGUMENT_if(X) do { if(X) { return ALIAS_ECS_ERROR_INVALID_ARGUMENT; } } while(0)
#define ASSERT(X) do { if(!(X)) { return ALIAS_ECS_ERROR_INVALID_ARGUMENT; } } while(0)

#if 1
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
// Vector utility functions and macros

// VoidVector makes some code easier
typedef alias_ecs_Vector(void) alias_ecs_VoidVector;

static inline alias_ecs_Result alias_ecs_VoidVector_set_capacity(
    alias_ecs_Instance *   instance
  , alias_ecs_VoidVector * vv
  , size_t                 s
  , size_t                 a
  , size_t                 new_capacity
) {
  size_t old_capacity = vv->capacity;
  if(old_capacity == new_capacity) {
    return ALIAS_ECS_SUCCESS;
  }
  alias_ecs_Result result = alias_ecs_realloc(instance, vv->data, old_capacity * s, new_capacity * s, a, &vv->data);
  if(result >= ALIAS_ECS_SUCCESS) {
    vv->capacity = new_capacity;
  }
  return result;
}

static inline alias_ecs_Result alias_ecs_VoidVector_space_for(
    alias_ecs_Instance   * instance
  , alias_ecs_VoidVector * vv
  , size_t                 s
  , size_t                 a
  , size_t                 c
) {
  size_t new_capacity = vv->length + c;
  if(new_capacity > vv->capacity) {
    new_capacity += new_capacity >> 1;
    return  alias_ecs_VoidVector_set_capacity(instance, vv, s, a, new_capacity);
  }
  return ALIAS_ECS_SUCCESS;
}

#define alias_ecs_Vector_VoidVector_args(V) (alias_ecs_VoidVector *)(V), sizeof(*(V)->data), alignof(*(V)->data)

#define alias_ecs_Vector_free(I, V)                                                          \
  do {                                                                                       \
    if((V)->data != NULL) {                                                                  \
      alias_ecs_free(I, (V)->data, (V)->capacity * sizeof(*(V)->data), alignof(*(V)->data)); \
    }                                                                                        \
    (V)->length = 0;                                                                         \
    (V)->capacity = 0;                                                                       \
    (V)->data = NULL;                                                                        \
  } while(0)
#define alias_ecs_Vector_pop(V) ((V)->data + (--(V)->length))
#define alias_ecs_Vector_push(V) ((V)->data + ((V)->length++))
#define alias_ecs_Vector_set_capacity(I, V, C) alias_ecs_VoidVector_set_capacity(I, alias_ecs_Vector_VoidVector_args(V), C)
#define alias_ecs_Vector_space_for(I, V, C) alias_ecs_VoidVector_space_for(I, alias_ecs_Vector_VoidVector_args(V), C)
#define alias_ecs_Vector_qsort(V, F) qsort((V)->data, (V)->length, sizeof(*(V)->data), F)
#define alias_ecs_Vector_bsearch(V, F, K) bsearch(K, (V)->data, (V)->length, sizeof(*(V)->data), F)
#define alias_ecs_Vector_remove_at(V, I)                                                         \
  do {                                                                                           \
      uint32_t __i = (I);                                                                        \
      (V)->length--;                                                                             \
      if((V)->length > 0 && (V)->length != __i) {                                                \
        memmove((V)->data + __i, (V)->data + __i + 1, ((V)->length - __i) * sizeof(*(V)->data)); \
      }                                                                                          \
  } while(0)
#define alias_ecs_Vector_swap_pop(V, I)                                     \
  do {                                                                      \
    uint32_t __i = (I);                                                     \
    (V)->length--;                                                          \
    if((V)->length != __i) {                                                \
      memcpy((V)->data + __i, (V)->data + (V)->length, sizeof(*(V)->data)); \
    }                                                                       \
  } while(0)

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

