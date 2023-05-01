#include <tabula.h>

#include <alias/str.h>

alias_str alias_str_clone(alias_MemoryCB *mcb, alias_str s) {
  uintmax_t l = strlen(s);
  return alias_memory_clone(mcb, s, l + 1, 1);
}

alias_str alias_str_format(alias_MemoryCB *mcb, alias_str format, ...) {
  va_list ap1, ap2;
  va_start(ap1, format);
  va_copy(ap2, ap1);
  int length = tabula_vcprintf(format, ap1);
  char *result = alias_malloc(mcb, length + 1, 1);
  tabula_snprintf(result, length, length, format, ap2);
  return result;
}

void alias_str_free(alias_MemoryCB *mcb, alias_str s) { alias_free(mcb, (void *)s, strlen(s) + 1, 1); }

bool alias_str_same(alias_str a, alias_str b) { return strcmp(a, b) == 0; }

uintmax_t alias_str_length(alias_str s) { return strlen(s); }

uintmax_t alias_str_size(alias_str s) { return strlen(s); }