#include <alias/memory.h>

#include <stdalign.h>

#include "shishua.h"

#define BUFFER_SIZE (128 * 128)

typedef struct alias_random_State {
  uint8_t * data;
  uint8_t * data_end;

  uint8_t buffer[BUFFER_SIZE];

  prng_state shishua;
} alias_random_State;

alias_random_State alias_random_State_GLOBAL;

alias_random_State * alias_random_new_State(alias_MemoryCB * mcb) {
  alias_random_State * state = (alias_random_State *)alias_malloc(mcb, sizeof(*state), alignof(*state));
  state->data = state->data_end = state->buffer + BUFFER_SIZE;
  return state;
}

void alias_random_free_State(alias_random_State * state, alias_MemoryCB * mcb) {
  alias_free(mcb, state, sizeof(*state), alignof(*state));
}

void alias_random_State_init(alias_random_State * state, const uint8_t * seed, size_t size) {
  uint64_t shishua_seed[4] = { 0x5fdf8657e5a42a09, 0xf7bf07ff84b5ff76, 0x2f249c219735e5ca, 0x82c1d52a2b5efca5 };
  uint8_t * shishua_seed_bytes = (uint8_t *)&shishua_seed[0];
  for(size_t i = 0; i < size; i++) {
    shishua_seed_bytes[i & 31] ^= seed[i];
  }
  prng_init(&state->shishua, shishua_seed);
  state->data = state->data_end = state->buffer + BUFFER_SIZE;
}

void alias_random_State_fill(alias_random_State * state) {
  prng_gen(&state->shishua, state->buffer, BUFFER_SIZE);
  state->data = state->buffer;
  state->data_end = state->buffer + BUFFER_SIZE;
}

#include <time.h>

static __attribute__((constructor)) void _init_GLOBAL(void) {
  time_t t;
  time(&t);
  alias_random_State_init(&alias_random_State_GLOBAL, (uint8_t *)&t, sizeof(t));
}

