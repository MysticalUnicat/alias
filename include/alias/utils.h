#ifndef _ALIAS_UTILS_H_
#define _ALIAS_UTILS_H_

#include <stdint.h>
#include <stddef.h>

#define alias_Closure(FN_T) struct { FN_T fn; void * ud; }
#define alias_Closure_call(C, ...) (C)->fn((C)->ud, ## __VA_ARGS__)
#define alias_Closure_is_empty(C) ((C)->fn == NULL)
#define ALIAS_DECLARE_CLOSURE(NAME, RESULT_TYPE, ...) \
  typedef RESULT_TYPE (* NAME##_function_type)(void *, ## __VA_ARGS__); \
  typedef alias_Closure(NAME##_function_type) NAME;
  
ALIAS_DECLARE_CLOSURE(alias_MemoryAllocationCallback, void *, void * ptr, size_t old_size, size_t new_size, size_t alignment)

static inline void * alias__system_allocator_function(void * ud, void * ptr, size_t old_size, size_t new_size, size_t alignment) {
  extern void * aligned_alloc(size_t alignemnt, size_t size);
  extern void * realloc(void * ptr, size_t size);
  extern void free(void * ptr);
  (void)ud;
  return
    (old_size == 0 && new_size > 0) ? aligned_alloc(alignment, new_size) :
    (new_size == 0)                 ? (free(ptr), NULL)                  :
    (old_size != new_size)          ? realloc(ptr, new_size)             :
                                      ptr;
}

static alias_MemoryAllocationCallback alias_system_allocator = { alias__system_allocator_function, NULL };

static inline void * alias_malloc(alias_MemoryAllocationCallback * cb, size_t size, size_t alignment) {
  cb = cb == NULL ? &alias_system_allocator : cb;
  return alias_Closure_call(cb, NULL, 0, size, alignment);
}

static inline void * alias_malloc_clear(alias_MemoryAllocationCallback * cb, size_t size, size_t alignment) {
  extern void * memset(void *, int, size_t);
  void * p = alias_malloc(cb, size, alignment);
  if(p != NULL) {
    memset(p, 0, size);
  }
  return p;
}

static inline void * alias_calloc(alias_MemoryAllocationCallback * cb, size_t count, size_t size, size_t alignment) {
  return alias_malloc_clear(cb, count * size, alignment);
}

static inline void * alias_realloc(alias_MemoryAllocationCallback * cb, void * ptr, size_t old_size, size_t new_size, size_t alignment) {
  cb = cb == NULL ? &alias_system_allocator : cb;
  return alias_Closure_call(cb, ptr, old_size, new_size, alignment);
}

static inline void * alias_free(alias_MemoryAllocationCallback * cb, void * ptr, size_t old_size, size_t alignment) {
  cb = cb == NULL ? &alias_system_allocator : cb;
  return alias_Closure_call(cb, ptr, old_size, 0, alignment);
}

#endif
