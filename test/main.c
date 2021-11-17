// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "local.h"

#include <stdlib.h>
#include <getopt.h>
#include <string.h>

static void * _stub_allocator(void * ud, void * ptr, size_t old_size, size_t new_size, size_t alignment) {
  (void)ud;
  (void)alignment;
  if(g_stub_allocator.fail) {
    return NULL;
  }
  if(new_size == 0) {
    free(ptr);
    g_stub_allocator.num_frees++;
    g_stub_allocator.bytes_freed += old_size;
    return NULL;
  }
  void * result = realloc(ptr, new_size);
  g_stub_allocator.num_allocations += ptr == NULL;
  g_stub_allocator.bytes_allocated += new_size;
  g_stub_allocator.bytes_allocated -= old_size;
  return result;
}

struct StubAllocator g_stub_allocator = {
    .cb = { _stub_allocator, &g_stub_allocator }
  , .num_allocations = 0
  , .bytes_allocated = 0
  , .num_frees = 0
  , .bytes_freed = 0
  , .fail = 0
  , .random = 0
  };

struct Test * g_tests = NULL;

void _run(int * result, struct Test * test) {
  int success = 1;

  g_stub_allocator_reset();
  
  test->fn(&success);

  if(success == 0) {
    fprintf(stdout, "ERR - %s\n", test->ident);
    *result = 1;
  } else if(g_stub_allocator.num_allocations != g_stub_allocator.num_frees || g_stub_allocator.bytes_allocated != g_stub_allocator.bytes_freed) {
    fprintf(
        stdout
      , "MEM - %s, %ia %if %iba %ibf\n"
      , test->ident
      , g_stub_allocator.num_allocations
      , g_stub_allocator.num_frees
      , g_stub_allocator.bytes_allocated
      , g_stub_allocator.bytes_freed
      );
    *result = 1;
  } else {
    fprintf(stdout, " OK - %s\n", test->ident);
  }
}

void _run_by_ident(int * result, const char * ident) {
  struct Test * test = g_tests;
  while(test != NULL) {
    if(strcmp(test->ident, ident) == 0) {
      _run(result, test);
      return;
    }
    test = test->next;
  }
  fprintf(stderr, "Test %s not found\n", ident);
  *result = 1;
}

void _run_all(int * result, int fail_fast) {
  struct Test * test = g_tests;
  while(test != NULL) {
    _run(result, test);
    if(*result && fail_fast) {
      return;
    }
    test = test->next;
  }
}

int main(int argc, char * argv []) {
  int fail_fast = 0;
  
  struct option long_options[] = {
    {"fail-fast",       no_argument, &fail_fast,   1},
    {     "test", required_argument,          0, 't'},
    {          0,                 0,          0,   0}
  };

  int result = 0;
  int ran_tests = 0;

  for(;;) {
    int option_index = 0;
    int c = getopt_long(argc, argv, "f", long_options, &option_index);
    if(c == -1) {
      break;
    }
    switch(c) {
    case 0:
      if(long_options[option_index].flag != NULL) {
        break;
      }
      break;
    case 't':
      _run_by_ident(&result, optarg);
      ran_tests = 1;
      break;
    }
  }

  if(!ran_tests) {
    _run_all(&result, fail_fast);
  }

  return result;
}

