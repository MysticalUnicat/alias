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

#endif // _ALIAS_UTILS_H_

