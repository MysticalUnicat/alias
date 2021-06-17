#ifndef _ALIAS_MEMORY_H_
#define _ALIAS_MEMORY_H_

#include <alias/utils.h>

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

static const alias_MemoryCB alias_default_MemoryCB = { alias__default_MemoryCB_fn, NULL };  

#endif
