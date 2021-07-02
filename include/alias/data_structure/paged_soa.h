#ifndef _ALIAS_DATA_STRUCTURE_PAGED_SOA_H_
#define _ALIAS_DATA_STRUCTURE_PAGED_SOA_H_

#include <stdbool.h>
#include <stdalign.h>

#include <alias/memory.h>

#define ALIAS_PAGED_SOA_PAGE_SIZE (1 << 16)
#define ALIAS_PAGED_SOA_PAGE_ALIGNMENT 16

typedef struct alias_PagedSOA {
  uint32_t    length;
  uint32_t    num_columns;
  uint32_t    rows_per_page;
  uint32_t  * size_offset;
  uint32_t    num_pages;
  uint8_t * * pages;
} alias_PagedSOA;

static inline bool alias_PagedSOA_initialize(alias_PagedSOA * soa, alias_MemoryCB * mcb, uint32_t prefix_size, uint32_t num_columns, const size_t * sizes) {
  soa->length = 0;
  soa->num_pages = 0;
  soa->num_columns = num_columns;
  soa->size_offset = alias_malloc(mcb, sizeof(*soa->size_offset) * num_columns, alignof(*soa->size_offset));
  if(soa->size_offset == NULL) {
    return false;
  }
  
  soa->pages = NULL;

  uint32_t row_size = 0;
  for(uint32_t i = 0; i < soa->num_columns; i++) {
    row_size += sizes[i];
  }

  soa->rows_per_page = (ALIAS_PAGED_SOA_PAGE_SIZE - prefix_size) / row_size;

  uint32_t offset = prefix_size;

  for(uint32_t i = 0; i < soa->num_columns; i++) {
    soa->size_offset[i] = (sizes[i] << 16) | offset;
    offset += sizes[i] * soa->rows_per_page;
  }

  return true;
}

static inline void alias_PagedSOA_free(alias_PagedSOA * soa, alias_MemoryCB * mcb) {
  alias_free(mcb, soa->size_offset, sizeof(*soa->size_offset) * soa->num_columns, alignof(*soa->size_offset));
  for(uint32_t i = 0; i < soa->num_pages; i++) {
    alias_free(mcb, soa->pages[i], ALIAS_PAGED_SOA_PAGE_SIZE, ALIAS_PAGED_SOA_PAGE_ALIGNMENT);
  }
  alias_free(mcb, soa->pages, sizeof(*soa->pages) * soa->num_pages, alignof(*soa->pages));
  alias_memory_clear(soa, sizeof(*soa));
}

static inline bool alias_PagedSOA_set_capacity(alias_PagedSOA * soa, alias_MemoryCB * mcb, uint32_t new_capacity) {
  uint32_t new_num_pages = (new_capacity + soa->rows_per_page - 1) / soa->rows_per_page;
  if(new_num_pages > soa->num_pages) {
    soa->pages = alias_realloc(mcb, soa->pages, sizeof(*soa->pages) * soa->num_pages, sizeof(*soa->pages) * new_num_pages, alignof(*soa->pages));
    while(soa->num_pages < new_num_pages) {
      uint8_t * page = alias_malloc(mcb, ALIAS_PAGED_SOA_PAGE_SIZE, ALIAS_PAGED_SOA_PAGE_ALIGNMENT);
      alias_memory_clear(page, soa->size_offset[0] & 0xFFFF);
      soa->pages[soa->num_pages++] = page;
    }
    soa->num_pages = new_num_pages;
  }
  return true;
}

static inline bool alias_PagedSOA_space_for(alias_PagedSOA * soa, alias_MemoryCB * mcb, uint32_t count) {
  uint32_t new_num_pages = (soa->length + count + soa->rows_per_page - 1) / soa->rows_per_page;
  if(new_num_pages > soa->num_pages) {
    return alias_PagedSOA_set_capacity(soa, mcb, new_num_pages);
  }
  return true;
}

static inline uint32_t alias_PagedSOA_push(alias_PagedSOA * soa) {
  uint32_t row = soa->length++;
  uint32_t page = row / soa->rows_per_page;
  uint32_t index = row % soa->rows_per_page;
  return (page << 16) | index;
}

static inline void * alias_PagedSOA_page(const alias_PagedSOA * soa, uint32_t code) {
  uint32_t page = code >> 16;
  return soa->pages[page];
}

static inline void alias_PagedSOA_decode_code(const alias_PagedSOA * soa, uint32_t code, uint32_t * page, uint32_t * index) {
  (void)soa;
  *page = code >> 16;
  *index = code & 0xFFFF;
}

static inline void alias_PagedSOA_decode_column(const alias_PagedSOA * soa, uint32_t column, uint32_t * size, uint32_t * offset) {
  *size = soa->size_offset[column] >> 16;
  *offset = soa->size_offset[column] & 0xFFFF;
}

static inline const void * alias_PagedSOA_raw_read(const alias_PagedSOA * soa, uint32_t page, uint32_t index, uint32_t size, uint32_t offset) {
  return soa->pages[page] + (offset + size * index);
}

static inline const void * alias_PagedSOA_read(const alias_PagedSOA * soa, uint32_t code, uint32_t column) {
  uint32_t page, index, size, offset;
  alias_PagedSOA_decode_code(soa, code, &page, &index);
  alias_PagedSOA_decode_column(soa, column, &size, &offset);
  return alias_PagedSOA_raw_read(soa, page, index, size, offset);
}

static inline void * alias_PagedSOA_raw_write(alias_PagedSOA * soa, uint32_t page, uint32_t index, uint32_t size, uint32_t offset) {
  return soa->pages[page] + (offset + size * index);
}

static inline void * alias_PagedSOA_write(alias_PagedSOA * soa, uint32_t code, uint32_t column) {
  uint32_t page, index, size, offset;
  alias_PagedSOA_decode_code(soa, code, &page, &index);
  alias_PagedSOA_decode_column(soa, column, &size, &offset);
  return alias_PagedSOA_raw_write(soa, page, index, size, offset);
}

#endif
