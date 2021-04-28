#include "ecs_local.h"

#include <string.h>

alias_ecs_Result alias_ecs_malloc(
    alias_ecs_Instance * instance
  , size_t               size
  , size_t               alignment
  , void *             * out_ptr
) {
  *out_ptr = alias_Closure_call(&instance->memory_allocation_cb, NULL, 0, size, alignment);
  if(*out_ptr == NULL) {
    // TODO make effort to cleanup old archetype blocks
    return ALIAS_ECS_ERROR_OUT_OF_MEMORY;
  }
  memset(*out_ptr, 0, size);
  return ALIAS_ECS_SUCCESS;
}

alias_ecs_Result alias_ecs_realloc(
    alias_ecs_Instance * instance
  , void               * ptr
  , size_t               old_size
  , size_t               new_size
  , size_t               alignment
  , void *             * out_ptr
) {
  *out_ptr = alias_Closure_call(&instance->memory_allocation_cb, ptr, old_size, new_size, alignment);
  if(*out_ptr == NULL) {
    return ALIAS_ECS_ERROR_OUT_OF_MEMORY;
  }
  if(old_size < new_size) {
    memset(((unsigned char *)*out_ptr) + old_size, 0, new_size - old_size);
  }
  return ALIAS_ECS_SUCCESS;
}

void alias_ecs_free(
    alias_ecs_Instance * instance
  , void               * ptr
  , size_t               size
  , size_t               alignment
) {
  if(ptr != NULL && size > 0) {
    alias_Closure_call(&instance->memory_allocation_cb, ptr, size, 0, alignment);
  }
}

// naive qsort
// https://en.wikipedia.org/wiki/Quicksort

#define OPTIMIZED
#define QSORT_LINEAR_SORT_LIMIT 16

static inline void _swap(
    uint8_t * base
  , size_t    size
  , size_t    i
  , size_t    j
) {
  if(i == j) {
    return;
  }

  uint8_t * a = base + size * i;
  uint8_t * b = base + size * j;

  for(size_t i = 0; i < size; i++, a++, b++) {
    uint8_t temp = *a;
    *a = *b;
    *b = temp;
  } while(size-- > 0);
}
#define SWP(I, J) _swap(base, size, I, J)

enum PivotScheme {
  PivotLo,
  PivotHi,
  PivotMid,
  MedianOfThree
};

enum PartitionScheme {
  Lumuto,
  Hoare
};

static int _cmp(
    const uint8_t       * base
  , size_t                size
  , size_t                i
  , size_t                j
  , alias_ecs_CompareCB   cb
) {
  if(i == j) {
    return 0;
  }
  return alias_Closure_call(&cb, base + (size * i), base + (size * j));
}
#define CMP(I, OP, J) (_cmp(base, size, I, J, cb) OP 0)

static inline size_t size_t_min(
    size_t a
  , size_t b
) {
  return a < b ? a : b;
}

static size_t _partition(
    enum PivotScheme       pivot_scheme
  , enum PartitionScheme   partition_scheme
  , uint8_t              * base
  , size_t                 size
  , size_t                 lo
  , size_t                 hi
  , alias_ecs_CompareCB cb
) {
  size_t pivot, mid = lo + (hi - lo)/2;

  switch(pivot_scheme) {
  case PivotLo:
    pivot = lo;
    break;
  case PivotHi:
    pivot = hi;
    break;
  case PivotMid:
    pivot = mid;
    break;
  case MedianOfThree:
    if(CMP(mid, <, lo)) {
      SWP(lo, mid);
    }
    if(CMP(hi, <, lo)) {
      SWP(lo, hi);
    }
    if(CMP(mid, <, hi)) {
      SWP(mid, hi);
    }
    pivot = hi;
    break;
  }

  size_t i, j;

  switch(partition_scheme) {
  case Lumuto:
    if(pivot != hi) {
      SWP(pivot, hi);
      pivot = hi;
    }
    i = lo;
    for(size_t j = lo; j < hi; j++) {
      if(CMP(j, <, pivot)) {
        SWP(i, j);
        i++;
      }
    }
    SWP(i, pivot);
    return i;
  case Hoare:
    i = lo;
    j = hi;
    for(;;) {
      while(CMP(i, <, pivot)) {
        i++;
      }
      while(CMP(j, >, pivot)) {
        j--;
      }
      if(i >= j) {
        return j;
      }
      SWP(i, j);
      pivot = i == pivot ? j :
              j == pivot ? i : pivot;
    }
  }

  // does not reach here
  return 0;
}

#ifndef OPTIMIZED
static void _quicksort(
    uint8_t * base
  , size_t    size
  , size_t    lo
  , size_t    hi
  , alias_ecs_CompareCB cb
) {
  if(lo >= hi) {
    return;
  }
  size_t pivot = _partition(PivotMid, Hoare, base, size, lo, hi, cb);
  _quicksort(base, size, lo, pivot ? pivot - 1 : pivot, cb);
  _quicksort(base, size, pivot + 1, hi, cb);
}
#else
static void _insertion_sort(
    uint8_t * base
  , size_t    size
  , size_t    lo
  , size_t    hi
  , alias_ecs_CompareCB cb
) {
  size_t i = lo + 1;
  while(i <= hi) {
    size_t j = i;
    while(j > 0 && CMP(j - 1, >, j)) {
      SWP(j, j - 1);
      j--;
    }
    i++;
  }
}

static void _quicksort(
    uint8_t             * base
  , size_t                size
  , size_t                lo
  , size_t                hi
  , alias_ecs_CompareCB   cb
) {
again:
  if(lo >= hi) {
    return;
  }

  // optimization: perform linear insertion sort on small sub arrays
  if(hi - lo < QSORT_LINEAR_SORT_LIMIT) {
    _insertion_sort(base, size, lo, hi, cb);
    return;
  }

  size_t pivot = _partition(PivotHi, Lumuto, base, size, lo, hi, cb);
  
  // optimization: sort the smaller subarray first (in the call stack) then go to the top with the other side
  size_t sub[2][2] = { {    lo, pivot ? pivot - 1 : lo }
                     , { pivot + 1,    hi }
                     };
  size_t shortest = (sub[0][1] - sub[0][0] > sub[1][1] - sub[1][0]);
  _quicksort(base, size, sub[shortest][0], sub[shortest][1], cb);
  lo = sub[!shortest][0];
  hi = sub[!shortest][1];
  goto again;
}
#endif

void alias_ecs_quicksort(
    void                * base
  , size_t                num
  , size_t                size
  , alias_ecs_CompareCB   cb
) {
  if(num == 0 || size == 0 || base == NULL) {
    return;
  }
  _quicksort((uint8_t *)base, size, 0, num - 1, cb);
}

// naive bsearch
void * alias_ecs_bsearch(
    const void          * key
  , const void          * base
  , size_t                num
  , size_t                size
  , alias_ecs_CompareCB   cb
) {
  if(key == NULL || base == NULL || num == 0 || size == 0) {
    return NULL;
  }
  const uint8_t * b = (const uint8_t *)base;
  size_t lo = 0;
  size_t hi = num - 1;
  while(lo <= hi && hi != SIZE_MAX) {
    size_t mid = lo + (hi - lo)/2;
    const void * item = b + mid * size;
    int cmp = alias_Closure_call(&cb, key, item);
    if(cmp > 0) {
      lo = mid + 1;
    } else if(cmp < 0) {
      hi = mid - 1;
    } else {
      return (void *)item;
    }
  }
  return NULL;
}

