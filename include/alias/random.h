// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_RANDOM_H_
#define _ALIAS_RANDOM_H_

#include <alias/memory.h>
#include <alias/math.h>

#define ALIAS_RANDOM_BUFFER_SIZE 1024

typedef struct alias_random_State {
  uint8_t * data;
  uint8_t * data_end;
} alias_random_State;

extern alias_random_State alias_random_State_GLOBAL;

alias_random_State * alias_random_new_State(alias_MemoryCB * mcb);
void alias_random_free_State(alias_random_State * state, alias_MemoryCB * mcb);

void alias_random_State_init(alias_random_State * state, const uint8_t * seed, size_t size);
void alias_random_State_fill(alias_random_State * state);

static inline void alias_random_State_read(alias_random_State * state, uint8_t * dst, size_t size) {
  while(size > 0) {
    size_t to_read = alias_min(size, state->data_end - state->data);
    if(to_read == 0) {
      alias_random_State_fill(state);
      to_read = alias_min(size, state->data_end - state->data);
    }
    alias_memory_copy(dst, size, state->data, to_read);
    state->data += to_read;
    size -= to_read;
  }
}

static inline uint32_t alias_random_State_u32(alias_random_State * state) {
  uint32_t x;
  alias_random_State_read(state, (uint8_t *)&x, sizeof(x));
  return x;
}

static inline float alias_random_State_f32_unorm(alias_random_State * state) {
  uint32_t x;
  alias_random_State_read(state, (uint8_t *)&x, sizeof(x));
  return (x >> 9) * 0x1.0p-24;
}

static inline float alias_random_State_f32_snorm(alias_random_State * state) {
  uint32_t x;
  alias_random_State_read(state, (uint8_t *)&x, sizeof(x));
  return (x >> 9) * 0x1.0p-23 - 0.5f;
}

static inline uint64_t alias_random_State_u64(alias_random_State * state) {
  uint64_t x;
  alias_random_State_read(state, (uint8_t *)&x, sizeof(x));
  return x;
}

static inline float alias_random_State_f64_unorm(alias_random_State * state) {
  uint64_t x;
  alias_random_State_read(state, (uint8_t *)&x, sizeof(x));
  return (x >> 11) * 0x1.0p-53;
}

static inline float alias_random_State_f64_snorm(alias_random_State * state) {
  uint64_t x;
  alias_random_State_read(state, (uint8_t *)&x, sizeof(x));
  return (x >> 9) * 0x2.0p-53 - 1.0f;
}

// ====================================================================================================================

static inline uint32_t alias_random_u32(void) { return alias_random_State_u32(&alias_random_State_GLOBAL); }
static inline float alias_random_f32_unorm(void) { return alias_random_State_f32_unorm(&alias_random_State_GLOBAL); }
static inline float alias_random_f32_snorm(void) { return alias_random_State_f32_snorm(&alias_random_State_GLOBAL); }

static inline uint32_t alias_random_u64(void) { return alias_random_State_u64(&alias_random_State_GLOBAL); }
static inline float alias_random_f64_unorm(void) { return alias_random_State_f64_unorm(&alias_random_State_GLOBAL); }
static inline float alias_random_f64_snorm(void) { return alias_random_State_f64_snorm(&alias_random_State_GLOBAL); }

#endif
