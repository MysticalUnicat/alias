#ifndef _ALIAS_MEMORY_H_
#define _ALIAS_MEMORY_H_

#include <stdbool.h>

#include <alias/utils.h>

#ifndef ALIAS_MEMORY_C11_CONSTRAINTS
#define ALIAS_MEMORY_C11_CONSTRAINTS 0
#endif

ALIAS_DECLARE_CLOSURE(alias_MemoryCB, void *, void * ptr, size_t old_size, size_t new_size, size_t alignment)

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

#endif
