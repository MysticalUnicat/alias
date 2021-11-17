// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_MEMORY_H_
#define _ALIAS_MEMORY_H_

#include <stdbool.h>

#include <alias/utils.h>

#ifndef ALIAS_MEMORY_C11_CONSTRAINTS
#define ALIAS_MEMORY_C11_CONSTRAINTS 0
#endif

typedef enum alias_memory_Format {
  alias_memory_Format_Unknown,

  alias_memory_Format_Uint8,
  alias_memory_Format_Uint16,
  alias_memory_Format_Uint32,
  alias_memory_Format_Uint64,

  alias_memory_Format_Sint8,
  alias_memory_Format_Sint16,
  alias_memory_Format_Sint32,
  alias_memory_Format_Sint64,

  alias_memory_Format_Unorm8,
  alias_memory_Format_Unorm16,

  alias_memory_Format_Snorm8,
  alias_memory_Format_Snorm16,

  alias_memory_Format_Uscaled8,
  alias_memory_Format_Uscaled16,

  alias_memory_Format_Sscaled8,
  alias_memory_Format_Sscaled16,

  alias_memory_Format_Urgb8,

  alias_memory_Format_Float16,
  alias_memory_Format_Float32,
  alias_memory_Format_Float64,

  alias_memory_Format_COUNT
} alias_memory_Format;

ALIAS_DECLARE_CLOSURE(alias_MemoryCB, void *, void * ptr, size_t old_size, size_t new_size, size_t alignment)

typedef struct alias_memory_Buffer {
  void * pointer;
  uintptr_t size;
} alias_memory_Buffer;

typedef struct alias_memory_SubBuffer {
  void * pointer;
  uint32_t count;
  uint32_t stride;
  alias_memory_Format type_format;
  uint32_t type_length;
} alias_memory_SubBuffer;

static inline alias_memory_SubBuffer alias_memory_SubBuffer_from_Buffer(
    alias_memory_Buffer buffer
  , size_t buffer_offset
  , size_t buffer_limit
  , uint32_t stride
  , alias_memory_Format type_format
  , uint32_t type_length
) {
  return (alias_memory_SubBuffer) {
      .pointer = (void *)((uint8_t *)buffer.pointer + buffer_offset)
    , .count = (buffer.size - buffer_limit) / stride
    , .stride = stride
    , .type_format = type_format
    , .type_length = type_length
  };
}

void alias_memory_SubBuffer_copy_from_SubBuffer(alias_memory_SubBuffer * dst, const alias_memory_SubBuffer * src, uint32_t count);

int alias_memory_SubBuffer_write(alias_memory_SubBuffer * dst, uint32_t index, uint32_t count, alias_memory_Format format, uint32_t src_stride, const void * src);
int alias_memory_SubBuffer_read(const alias_memory_SubBuffer * src, uint32_t index, uint32_t count, alias_memory_Format format, uint32_t dst_stride, void * dst);

static inline void * alias_malloc(alias_MemoryCB * cb, size_t size, size_t alignment) {
  return alias_Closure_call(cb, NULL, 0, size, alignment);
}

static inline void * alias_realloc(alias_MemoryCB * cb, void * ptr, size_t old_size, size_t new_size, size_t alignment) {
  return alias_Closure_call(cb, ptr, old_size, new_size, alignment);
}

static inline void alias_free(alias_MemoryCB * cb, void * ptr, size_t size, size_t alignment) {
  alias_Closure_call(cb, ptr, size, 0, alignment);
}

static inline void * alias__default_MemoryCB_fn(void * ud, void * ptr, size_t old_size, size_t new_size, size_t alignment) {
  extern void free(void *);
  extern void * realloc(void *, size_t);
  
  (void)(ud);
  (void)(old_size);
  (void)(alignment);

  if(new_size == 0) {
    free(ptr);
    return NULL;
  } else {
    return realloc(ptr, new_size);
  }
}

static inline alias_MemoryCB * alias_default_MemoryCB(void) {
  static alias_MemoryCB _ = { alias__default_MemoryCB_fn, NULL };
  return &_;
}

static inline bool alias_memory_set(void * dest, size_t dest_size, int ch, size_t count) {
  #if defined(__STDC_LIB_EXT1__) && ALIAS_MEMORY_C11_CONSTRAINTS
  extern int memset_s(void *, size_t, int, size_t);
  return memset_s(dest, dest_size, ch, count) == 0;
  #else
  extern void * memset(void *, int, size_t);
  (void)dest_size;
  memset(dest, ch, count);
  return true;
  #endif
}

static inline bool alias_memory_clear(void * dest, size_t dest_size) {
  return alias_memory_set(dest, dest_size, 0, dest_size);
}

static inline bool alias_memory_copy(void * dest, size_t dest_size, const void * src, size_t count) {
  #if defined(__STDC_LIB_EXT1__) && ALIAS_MEMORY_C11_CONSTRAINTS
  extern int memcpy_s(void *, size_t, const void *, size_t);
  return memcpy_s(dest, dest_size, src, count) == 0;
  #else
  extern void * memcpy(void *, const void *, size_t);
  (void)dest_size;
  memcpy(dest, src, count);
  return true;
  #endif
}

static inline bool alias_memory_move(void * dest, size_t dest_size, const void * src, size_t count) {
  #if defined(__STDC_LIB_EXT1__) && ALIAS_MEMORY_C11_CONSTRAINTS
  extern int memmove_s(void *, size_t, const void *, size_t);
  return memmove_s(dest, dest_size, src, count) == 0;
  #else
  extern void * memmove(void *, const void *, size_t);
  (void)dest_size;
  memmove(dest, src, count);
  return true;
  #endif
}

static inline void * alias_memory_clone(alias_MemoryCB * mcb, const void * src, size_t size, size_t alignment) {
  void * ptr = alias_malloc(mcb, size, alignment);
  if(ptr != NULL) {
    alias_memory_copy(ptr, size, src, size);
  }
  return ptr;
}

#endif
