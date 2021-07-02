#ifndef _ALIAS_DATA_STRUCTURE_SOA_H_
#define _ALIAS_DATA_STRUCTURE_SOA_H_

#include <stdbool.h>
#include <stdalign.h>

#include <alias/memory.h>

typedef struct alias_SOA {
  uint32_t    length;
  uint32_t    capacity;
  uint32_t    num_columns;
  uint32_t  * column_size_alignment;
  uint8_t * * column_data;
} alias_SOA;

static inline bool alias_SOA_initialize(alias_SOA * soa, alias_MemoryCB * mcb, uint32_t num_columns, const size_t * sizes, const size_t * alignments) {
  soa->length = 0;
  soa->capacity = 0;
  soa->num_columns = num_columns;
  soa->column_size_alignment = alias_malloc(mcb, sizeof(*soa->column_size_alignment) * num_columns, alignof(*soa->column_size_alignment));
  if(soa->column_size_alignment == NULL) {
    return false;
  }
  
  soa->column_data = alias_malloc(mcb, sizeof(*soa->column_data) * num_columns, alignof(*soa->column_data));
  if(soa->column_data == NULL) {
    return false;
  }

  for(uint32_t i = 0; i < soa->num_columns; i++) {
    soa->column_size_alignment[i] = (alignments[i] << 16) | sizes[i];
    soa->column_data[i] = NULL;
  }

  return true;
}

static inline void alias_SOA_free(alias_SOA * soa, alias_MemoryCB * mcb) {
  for(uint32_t i = 0; i < soa->num_columns; i++) {
    alias_free(mcb, soa->column_data[i], soa->column_size_alignment[i] & 0xFFFF * soa->capacity, soa->column_size_alignment[i] >> 16);
  }

  alias_free(mcb, soa->column_size_alignment, sizeof(*soa->column_size_alignment) * soa->num_columns, alignof(*soa->column_size_alignment));
  alias_free(mcb, soa->column_data, sizeof(*soa->column_data) * soa->num_columns, alignof(*soa->column_data));

  alias_memory_clear(soa, sizeof(*soa));
}

static inline bool alias_SOA_set_capacity(alias_SOA * soa, alias_MemoryCB * mcb, uint32_t new_capacity) {
  for(uint32_t i = 0; i < soa->num_columns; i++) {
    soa->column_data[i] = alias_realloc(
        mcb
      , soa->column_data[i]
      , soa->capacity * (soa->column_size_alignment[i] & 0xFFFF)
      , new_capacity * (soa->column_size_alignment[i] & 0xFFFF)
      , soa->column_size_alignment[i] >> 16
      );
    if(soa->column_data[i] == NULL) {
      return false;
    }
  }
  return true;
}

static inline bool alias_SOA_space_for(alias_SOA * soa, alias_MemoryCB * mcb, uint32_t count) {
  uint32_t new_capacity = soa->length + count;
  if(new_capacity > soa->capacity) {
    return alias_SOA_set_capacity(soa, mcb, new_capacity);
  }
  return true;
}

static inline uint32_t alias_SOA_push(alias_SOA * soa) {
  return soa->length++;
}

static inline const void * alias_SOA_read(const alias_SOA * soa, uint32_t index, uint32_t column) {
  return index < soa->length ? soa->column_data[column] + index : NULL;
}

static inline void * alias_SOA_write(alias_SOA * soa, uint32_t index, uint32_t column) {
  return index < soa->length ? soa->column_data[column] + index : NULL;
}

#endif
