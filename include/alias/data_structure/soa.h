#ifndef _ALIAS_DATA_STRUCTURE_SOA_H_
#define _ALIAS_DATA_STRUCTURE_SOA_H_

#include <stdint.h>
#include <stdalign.h>
#include <alias/utils.h>

#ifndef ALIAS_SOA_PAGE_SIZE
#define ALIAS_SOA_PAGE_SIZE (1 << 16)
#endif

// per-page structure of arrays
typedef struct alias_SOA {
  uint16_t   num_columns;
  uint16_t   rows_per_page;
  uint32_t   num_rows;
  uint32_t * columns;
  uint8_t ** pages;
} alias_SOA;

static inline void alias_SOA_create(alias_SOA * soa, alias_MemoryAllocationCallback * cb, uint16_t num_columns, size_t * column_sizes, size_t header_size) {
  soa->num_columns = num_columns;
  soa->columns = alias_calloc(cb, num_columns, sizeof(*soa->columns), alignof(*soa->columns));

  size_t row_size = 0;
  for(uint16_t i = 0; i < num_columns; i++) {
    row_size += column_sizes[i];
  }

  size_t page_data_size = (1 << 16) - header_size;
  soa->rows_per_page = page_data_size / row_size;

  uint32_t offset = header_size;
  for(uint16_t i = 0; i < num_columns; i++) {
    soa->columns[i] = (offset << 16) | column_sizes[i];
    offset += column_sizes[i];
  }

  soa->num_rows = 0;
  soa->pages = NULL;
}

static inline uint32_t alias_SOA_allocate(alias_SOA * soa, alias_MemoryAllocationCallback * cb) {
  uint32_t row = soa->num_rows++;

  uint32_t cur_num_pages = row / soa->rows_per_page;
  uint32_t new_num_pages = soa->num_rows / soa->rows_per_page;

  if(new_num_pages > cur_num_pages) {
    soa->pages = alias_realloc(cb, soa->pages, cur_num_pages * sizeof(*soa->pages), new_num_pages * sizeof(*soa->pages), alignof(*soa->pages));
    soa->pages[cur_num_pages] = alias_malloc(cb, ALIAS_SOA_PAGE_SIZE, ALIAS_SOA_PAGE_SIZE);
  }

  uint32_t page = cur_num_pages;
  uint32_t index = row % soa->rows_per_page;

  return (page << 16) | index;
}

static inline const void * alias_SOA_read(alias_SOA * soa, uint32_t code, uint16_t column) {
  uint32_t col = soa->columns[column];
  return soa->pages[code >> 16] + ((col >> 16) + (col & 0xFFFF) * (code & 0xFFFF));
}

static inline void * alias_SOA_write(alias_SOA * soa, uint32_t code, uint16_t column) {
  uint32_t col = soa->columns[column];
  return soa->pages[code >> 16] + ((col >> 16) + (col & 0xFFFF) * (code & 0xFFFF));
}

#endif
