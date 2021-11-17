// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_ECS_TEST_LOCAL_H_
#define _ALIAS_ECS_TEST_LOCAL_H_

#include <alias/ecs.h>
#include <stdio.h>

struct StubAllocator {
  alias_MemoryCB cb;
  uint32_t num_allocations;
  uint32_t bytes_allocated;
  uint32_t num_frees;
  uint32_t bytes_freed;
  uint32_t fail : 1;
  uint32_t random : 1;
  uint32_t _padding : 30;
};

extern struct StubAllocator g_stub_allocator;

static inline void g_stub_allocator_reset() {
  g_stub_allocator.num_allocations = 0;
  g_stub_allocator.bytes_allocated = 0;
  g_stub_allocator.num_frees = 0;
  g_stub_allocator.bytes_freed = 0;
  g_stub_allocator.fail = 0;
  g_stub_allocator.random = 0;
}

struct Test {
  const char * ident;
  const char * description;
  struct Test * next;
  void (*fn)(int *);
};

extern struct Test * g_tests;

#define TEST(IDENT, DESCRIPTION)               \
  static void IDENT##_fn(int *, const char *); \
  static void IDENT##_fn_0(int * _success) {   \
    IDENT##_fn(_success, #IDENT);              \
  }                                            \
  __attribute__((constructor))                 \
  static void IDENT##_setup(void) {            \
    static struct Test _test;                  \
    _test = (struct Test)                      \
      { .ident = #IDENT                        \
      , .description = DESCRIPTION             \
      , .next = g_tests                        \
      , .fn = IDENT##_fn_0                     \
      };                                       \
    g_tests = &_test;                          \
  }                                            \
  static void IDENT##_fn(int * _success, const char * _test_ident)

#define TEST_EQ(A, B, FMT, ...)                                                      \
  do {                                                                               \
    if((A) != (B)) {                                                                 \
      fprintf(stderr, "%16s:%i - " FMT "\n", _test_ident, __LINE__, ## __VA_ARGS__); \
      *_success = 0;                                                                 \
      return;                                                                        \
    }                                                                                \
  } while(0) 

#define TEST_NE(A, B, FMT, ...)                                                      \
  do {                                                                               \
    if((A) == (B)) {                                                                 \
      fprintf(stderr, "%16s:%i - " FMT "\n", _test_ident, __LINE__, ## __VA_ARGS__); \
      *_success = 0;                                                                 \
      return;                                                                        \
    }                                                                                \
  } while(0) 

#endif // _ALIAS_ECS_TEST_LOCAL_H_

