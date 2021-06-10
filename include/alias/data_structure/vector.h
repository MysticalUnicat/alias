#ifndef _ALIAS_DATA_STRUCTURE_VECTOR_H_
#define _ALIAS_DATA_STRUCTURE_VECTOR_H_

#include <alias/utils.h>
#include <stdbool.h>

#define alias_Vector(T) struct { uint32_t capacity; uint32_t length; T * data; }

#define alias_Vector_VoidVector_args(V, CB) (alias_VoidVector *)(V), CB, sizeof(*(V)->data), alignof(*(V)->data)

#define alias_Vector_free(V, CB)                                                          \
  do {                                                                                    \
    if((V)->data != NULL) {                                                               \
      alias_free(CB, (V)->data, (V)->capacity * sizeof(*(V)->data), alignof(*(V)->data)); \
    }                                                                                     \
    (V)->length = 0;                                                                      \
    (V)->capacity = 0;                                                                    \
    (V)->data = NULL;                                                                     \
  } while(0)

#define alias_Vector_pop(V) ((V)->data + (--(V)->length))

#define alias_Vector_push(V) ((V)->data + ((V)->length++))

#define alias_Vector_set_capacity(V, CB, C)                                                                                              \
  do {                                                                                                                                   \
    size_t __old_capacity = (V)->capacity;                                                                                               \
    if(__old_capacity != (C)) {                                                                                                          \
      void * new_ptr = alias_realloc(CB, (V)->data, __old_capacity * sizeof(*(V)->data), (C) * sizeof(*(V)->data), alignof(*(V)->data)); \
      if(new_ptr != NULL) {                                                                                                              \
        (V)->data = new_ptr;                                                                                                             \
        (V)->capacity = (C);                                                                                                             \
      }                                                                                                                                  \
    }                                                                                                                                    \
  } while(false)

#define alias_Vector_space_for(V, CB, C)                \
  do {                                                  \
    uint32_t __new_capacity = (V)->length + (C);        \
    if(__new_capacity > (V)->capacity) {                \
      __new_capacity += __new_capacity >> 1;            \
      alias_Vector_set_capacity(V, CB, __new_capacity); \
    }                                                   \
  } while(false)

#define alias_Vector_qsort(V, F) qsort((V)->data, (V)->length, sizeof(*(V)->data), F)

#define alias_Vector_bsearch(V, F, K) bsearch(K, (V)->data, (V)->length, sizeof(*(V)->data), F)

#define alias_Vector_remove_at(V, I)                                                             \
  do {                                                                                           \
      uint32_t __i = (I);                                                                        \
      (V)->length--;                                                                             \
      if((V)->length > 0 && (V)->length != __i) {                                                \
        memmove((V)->data + __i, (V)->data + __i + 1, ((V)->length - __i) * sizeof(*(V)->data)); \
      }                                                                                          \
  } while(0)

#define alias_Vector_swap_pop(V, I)                                         \
  do {                                                                      \
    uint32_t __i = (I);                                                     \
    (V)->length--;                                                          \
    if((V)->length != __i) {                                                \
      memcpy((V)->data + __i, (V)->data + (V)->length, sizeof(*(V)->data)); \
    }                                                                       \
  } while(0)

#endif
