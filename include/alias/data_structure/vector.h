// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_DATA_STRUCTURE_VECTOR_H_
#define _ALIAS_DATA_STRUCTURE_VECTOR_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdalign.h>

#include <alias/memory.h>

#define alias_Vector(T) struct { uint32_t capacity; uint32_t length; T * data; }

#define ALIAS_VECTOR_INIT { 0, 0, NULL }

#define alias_Vector_clear(V) \
  do {                        \
    (V)->length = 0;          \
  } while(0)

#define alias_Vector_init(V) \
  do {                       \
    alias_Vector_clear(V);   \
    (V)->capacity = 0;       \
    (V)->data = NULL;        \
  } while(0)

#define alias_Vector_free(V, CB)                                                          \
  do {                                                                                    \
    if((V)->data != NULL) {                                                               \
      alias_free(CB, (V)->data, (V)->capacity * sizeof(*(V)->data), alignof(*(V)->data)); \
    }                                                                                     \
    alias_Vector_init(V);                                                                 \
  } while(0)

#define alias_Vector_pop(V) ((V)->data + (--(V)->length))

#define alias_Vector_push(V) ((V)->data + ((V)->length++))

#define alias_Vector_set_capacity(V, CB, C)                                                                                                  \
  ( ((C) > (V)->capacity) ?                                                                                                                  \
    (                                                                                                                                        \
     ((V)->data = alias_realloc(CB, (V)->data, (V)->capacity * sizeof(*(V)->data), (C) * sizeof(*(V)->data), alignof(*(V)->data))) != NULL ? \
      ((V)->capacity = (C), true) :                                                                                                          \
      false                                                                                                                                  \
    ) : true                                                                                                                                 \
  )

#define alias_Vector_space_for(V, CB, C) alias_Vector_set_capacity(V, CB, (((V)->length + (C)) + (((V)->length + (C)) >> 1)))

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
