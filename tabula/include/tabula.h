/* This blank slate is intended to give a reasonable c11 library.
 * Replace functions that are missing in compiler environments out in the wild to normalize application development for
 * Alias.
 *
 * Turns out many projects end up with their own bits of stdlib self implemented. We also require it to be available in
 * the Alias tools for the host to use during compiling the target.
 *
 * generally, for functions and/or header that are found to have undesireable behaviour (like, they are hiding). make a
 * replacement and provide a macro to replace it.
 *
 * When making the replacement do several things; use the modern API (such as bsearch vs bsearch_s from c11); prefer to
 * use the C.UTF-8 locale instead of C; and/or UTF-8 compatible
 *
 * Not sure how to tackle locale, may just enforce these functions are C.UTF-8 and user beware about printing and
 * contained under tabula_locale_*
 *
 */

#ifndef _TABULA_H_
#define _TABULA_H_

#if defined(_MSC_VER)
// issues encountered while using Visual Studio:
//  - restrict keyword

#define restrict __restrict
#elif defined(__MINGW32__)
// issues encountered while using MingW:
//  - printf positional arguments
//  - no <uchar.h>

#define TABULA_HAS_UCHAR 0
#endif

#ifndef TABULA_HAS_UCHAR
#define TABULA_HAS_UCHAR 1
#endif

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if TABULA_HAS_UCHAR
#include <uchar.h>
#else
#include <wchar.h>
#endif

#ifdef TABULA_NO_REPLACEMENT_MACROS
#define TABULA_NO_REPLACEMENT_MACROS 1
#else
#define TABULA_NO_REPLACEMENT_MACROS 0
#endif

#if !TABULA_HAS_UCHAR
typedef uint8_t tabula_char8_t;
typedef uint16_t tabula_char16_t;
typedef uint32_t tabula_char32_t;

#define char8_t tabula_char8_t
#define char16_t tabula_char16_t
#define char32_t tabula_char32_t
#endif

// uchar
size_t tabula_mbrtoc16(char16_t *restrict pc16, const char *restrict s, size_t n, mbstate_t *restrict ps);
size_t tabula_c16rtomb(char *restrict s, char16_t c16, mbstate_t *restrict ps);

size_t tabula_mbrtoc32(char32_t *restrict pc32, const char *restrict s, size_t n, mbstate_t *restrict ps);
size_t tabula_c32rtomb(char *restrict s, char32_t c32, mbstate_t *restrict ps);

#if !TABULA_NO_REPLACEMENT_MACROS || !TABULA_HAS_UCHAR
#define mbrtoc16 tabula_mbrtoc16
#define c16rtomb tabula_c16rtomb
#define mbrtoc32 tabula_mbrtoc32
#define c32rtomb tabula_c32rtomb
#endif

bool tabula_binary_search(const void *key, const void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *, void *ud), void *ud,
                          const void **found, size_t *not_found);
void tabula_qsort(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *, void *ud), void *ud);

static inline void *tabula_bsearch(const void *key, const void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *, void *ud), void *ud) {
  const void *found;
  size_t not_found;
  return tabula_bsearch_index(key, ptr, count, size, comp, ud, &found, &not_found) ? (void *)found : NULL;
}

#if !TABULA_NO_REPLACEMENT_MACROS
#define bsearch tabula_bsearch
#define qsort tabula_qsort
#endif

// format
struct tabula_format_emit_to_string_data {
  uint8_t *string;
  size_t string_size;
  size_t position;
};

#if defined(_MSC_VER)
#define TABULA_FORMAT_DECORATE(FORMAT_INDEX, FIRST_ARGUMENT_INDEX)
#else
#define TABULA_FORMAT_DECORATE(FORMAT_INDEX, FIRST_ARGUMENT_INDEX) __attribute__((format(printf, FORMAT_INDEX, FIRST_ARGUMENT_INDEX)))
#endif

int tabula_vformat(void (*emit)(const uint8_t *ptr, size_t length, void *ud), void *ud, unsigned int limit, const char *format, va_list ap);

TABULA_FORMAT_DECORATE(4, 5)
static inline int tabula_format(void (*emit)(const uint8_t *ptr, size_t length, void *ud), void *ud, unsigned int limit, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = tabula_vformat(emit, ud, limit, format, ap);
  va_end(ap);
  return result;
}

void tabula_format_emit_to_file(const uint8_t *ptr, size_t length, void *ud);
void tabula_format_emit_to_string(const uint8_t *ptr, size_t length, void *ud);
void tabula_format_emit_to_nothing(const uint8_t *ptr, size_t length, void *ud);

// # format null options
enum tabula_format_null {
  TABULA_FORMAT_HASHx_0,
  TABULA_FORMAT_HASHX_0,
  TABULA_FORMAT_PARENTHESIS_null,
  TABULA_FORMAT_PARENTHESIS_NULL,
};

enum tabula_format_null tabula_format_get_ptrnull(void);
void tabula_format_set_ptrnull_from_system(void);
void tabula_format_set_ptrnull(enum tabula_format_null e);

enum tabula_format_null tabula_format_get_strnull(void);
void tabula_format_set_strnull_from_system(void);
void tabula_format_set_strnull(enum tabula_format_null e);

// stdio
static inline int tabula_vprintf(const char *format, va_list ap) { return tabula_vformat(tabula_format_emit_to_file, stdout, (unsigned int)-1, format, ap); }

static inline int tabula_vcprintf(const char *format, va_list ap) { return tabula_vformat(tabula_format_emit_to_nothing, NULL, (unsigned int)-1, format, ap); }

static inline int tabula_vsnprintf(char *string, size_t string_size, unsigned int limit, const char *format, va_list ap) {
  struct tabula_format_emit_to_string_data data = {.string = string, .string_size = string_size, .position = 0};
  int result = tabula_vformat(tabula_format_emit_to_string, &data, limit, format, ap);
  if(string_size > 0) {
    size_t position = data.position >= string_size ? string_size - 1 : data.position;
    if(string_size && position < limit) {
      string[position] = 0;
    }
  }
  return result;
}

static inline int tabula_vsprintf(char *string, size_t string_size, const char *format, va_list ap) {
  return tabula_vsnprintf(string, string_size, (unsigned int)-1, format, ap);
}

static inline int tabula_vasprintf(char **string_ptr, const char *format, va_list ap_) {
  va_list ap;
  va_copy(ap, ap_);
  int result = tabula_vcprintf(format, ap);
  va_end(ap);
  *string_ptr = malloc(result + 1);
  va_copy(ap, ap_);
  result = tabula_vsprintf(*string_ptr, result + 1, format, ap);
  va_end(ap);
  return result;
}

TABULA_FORMAT_DECORATE(4, 5)
static inline int tabula_snprintf(char *string, size_t string_size, unsigned int limit, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = tabula_vsnprintf(string, string_size, limit, format, ap);
  va_end(ap);
  return result;
}

TABULA_FORMAT_DECORATE(3, 4)
static inline int tabula_sprintf(char *string, size_t string_size, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = tabula_vsnprintf(string, string_size, (unsigned int)-1, format, ap);
  va_end(ap);
  return result;
}

TABULA_FORMAT_DECORATE(2, 3)
static inline int tabula_asprintf(char **string_ptr, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = tabula_vasprintf(string_ptr, format, ap);
  va_end(ap);
  return result;
}

TABULA_FORMAT_DECORATE(1, 2)
static inline int tabula_printf(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = tabula_vprintf(format, ap);
  va_end(ap);
  return result;
}

TABULA_FORMAT_DECORATE(1, 2)
static inline int tabula_cprintf(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = tabula_vcprintf(format, ap);
  va_end(ap);
  return result;
}

#if !TABULA_NO_REPLACEMENT_MACROS
#define printf tabula_printf
#define vprintf tabula_vprintf
#define cprintf tabula_cprintf
#define vcprintf tabula_vcprintf
#define sprintf tabula_sprintf
#define vsprintf tabula_vsprintf
#define snprintf tabula_snprintf
#define vsnprintf tabula_vsnprintf
#define asprintf tabula_asprintf
#endif
#endif

#ifdef TABULA_IMPLEMENTATION
#define TABULA_CAT2(A, B) TABULA_CAT2_0(A, B)
#define TABULA_CAT2_0(A, B) TABULA_CAT2_1(A, B)
#define TABULA_CAT2_1(A, B) A##B

bool tabula_binary_search(const void *key, const void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *, void *ud), void *ud,
                          const void **found, size_t *not_found) {
  size_t low = 0;
  size_t high = count;
  size_t middle;
  while(high >= low) {
    middle = (low + high) >> 1;
    const void *test = (uint8_t *)ptr + middle * size;
    int cmp = comp(key, test, ud);
    if(cmp == 0) {
      *found = test;
      return true;
    } else if(cmp > 0) {
      low = middle + 1;
    } else {
      high = middle - 1;
    }
  }
  *not_found = middle;
  return false;
}

static inline void tabula_quicksort_swap(uint8_t *a, uint8_t * b, size_t size) {
  while(size--) {
    uint8_t c = *a;
    *a = *b;
    *b = c;
    a++;
    b++;
  }
}

void tabula_quicksort(uint8_t *low, uint8_t * high, size_t size, int (*comp)(const void *, const void *, void *ud), void *ud) {
  if(low >= high) {
    return;
  }

  size_t count = ((high - low) / size) + 1;

  #define LESS_THAN_EQUAL(I, J) (comp(I, J, ud) <= 0)
  #define SWAP(I, J) tabula_quicksort_swap(I, J, size)
  #define SORT2(I, J) do { \
    if(LESS_THAN_EQUAL(J, I)) { \
      SWAP(I, J); \
    } \
	} while(false)

  SORT2(low, high);
  if(count == 2) {
    return;
  }

  // find mid
  uint8_t * mid = low + ((high - low) / (size << 1)) * size;

  // make sure low < mid
  SORT2(low, mid);

  // if count 3, make sure low < mid < high then return
  if(count == 3) {
    SORT2(mid, high);
    return;
  }

  // start partiion
  // place in this order: low < high < mid (using position high as pivot)
  SORT2(high, mid);
  uint8_t * pivot = low - size;

  for(uint8_t * scan = low; scan < high; scan += size) {
    if(LESS_THAN_EQUAL(scan, high)) {
      pivot += size;
      SWAP(pivot, scan);
    }
  }
  pivot += size;
  SWAP(pivot, high);
  // done partition
   
  tabula_quicksort(         low, pivot - size, size, comp, ud);
  tabula_quicksort(pivot + size,         high, size, comp, ud);

  #undef LESS_THAN_EQUAL
  #undef SWAP
  #undef SORT2
}

void tabula_qsort(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *, void *ud), void *ud) {
  tabula_quicksort((uint8_t *)ptr, (uint8_t *)ptr + (count - 1) * size, size, comp, ud);
}

static inline int tabula_format_is_digit(int c) { return (c >= '0') && (c <= '9') ? (c - '0') + 1 : 0; }

static inline intmax_t tabula_format_atoi(const char *restrict a, const char **restrict out_ptr) {
  intmax_t i = 0;
  intmax_t n = (*a == '-' ? (a++, -1) : *a == '+' ? (a++, 1) : 1);
  int c;
  while((c = tabula_format_is_digit(*a))) {
    i = i * 10 + (c - 1);
    a++;
  }
  if(out_ptr != NULL) {
    *out_ptr = a;
  }
  return n * i;
}

static inline uintmax_t tabula_format_atod(const char *restrict a, const char **restrict out_ptr) {
  uintmax_t i = 0;
  int c;
  while((c = tabula_format_is_digit(*a))) {
    i = i * 10 + (c - 1);
    a++;
  }
  if(out_ptr != NULL) {
    *out_ptr = a;
  }
  return i;
}

// TODO: make lazy atomic for read, seq for write
static enum tabula_format_null tabula_format_ptrnull = TABULA_FORMAT_HASHx_0;
static enum tabula_format_null tabula_format_strnull = TABULA_FORMAT_PARENTHESIS_null;

struct tabula_format_emit_partial {
  const char *ptr;
  unsigned int length;
};

struct tabula_format_emit_partial tabula_null_to_str[] = {[TABULA_FORMAT_HASHx_0] = {"0x0", 3},
                                                          [TABULA_FORMAT_HASHX_0] = {"0X0", 3},
                                                          [TABULA_FORMAT_PARENTHESIS_null] = {"(null)", 6},
                                                          [TABULA_FORMAT_PARENTHESIS_NULL] = {"(NULL)", 6}};

static inline enum tabula_format_null tabula_null_from_str(const char *s, enum tabula_format_null d) {
  if(!strcmp("0x0", s)) {
    return TABULA_FORMAT_HASHx_0;
  } else if(!strcmp("0X0", s)) {
    return TABULA_FORMAT_HASHX_0;
  } else if(!strcmp("(null)", s)) {
    return TABULA_FORMAT_PARENTHESIS_null;
  } else if(!strcmp("(NULL)", s)) {
    return TABULA_FORMAT_PARENTHESIS_NULL;
  }
  return d;
}

enum tabula_format_null tabula_format_get_ptrnull(void) { return tabula_format_ptrnull; }

enum tabula_format_null tabula_format_get_strnull(void) { return tabula_format_strnull; }

#undef snprintf

void tabula_format_set_ptrnull_from_system(void) {
  char buffer[64];
  snprintf(buffer, 64, "%p", NULL);
  tabula_format_ptrnull = tabula_null_from_str(buffer, TABULA_FORMAT_HASHx_0);
}

void tabula_format_set_strnull_from_system(void) {
  char buffer[64];
  snprintf(buffer, 64, "%s", (const char *)NULL);
  tabula_format_strnull = tabula_null_from_str(buffer, TABULA_FORMAT_PARENTHESIS_null);
}

#define snprintf tabula_snprintf

void tabula_format_set_ptrnull(enum tabula_format_null e) { tabula_format_ptrnull = e; }

void tabula_format_set_strnull(enum tabula_format_null e) { tabula_format_strnull = e; }

// format      = placeholder | !'%'
// placeholder = % parameter? flags? width? precision? length? type
// parameter   = digit+ '$'
// flags       = ('-' | '+' | ' ' | '0' | '\'' | '#')*
// width       = digit+
// precision   = '.' digit+
// length      = 'hh' | 'h' | 'l' | 'll' | 'L' | 'z' | 'j' | 't'
// type        = 'd' | 'i' | 'u' | ...
static const int32_t TABULA_FORMAT_UNDEFINED = INT32_MIN;

enum tabula_format_length {
  tabula_format_undefined,
  tabula_format_hh,
  tabula_format_h,
  tabula_format_l,
  tabula_format_ll,
  tabula_format_L,
  tabula_format_z,
  tabula_format_j,
  tabula_format_t
};

enum tabula_format_datatype {
  tabula_format_datatype_unsigned_integer,
  tabula_format_datatype_signed_integer,
  tabula_format_datatype_character,
  tabula_format_datatype_double,
  tabula_format_datatype_pointer,
  tabula_format_datatype_string
};

enum tabula_format_style {
  tabula_format_style_escape = '%',
  tabula_format_style_signed_dec = 'i',
  tabula_format_style_unsigned_oct = 'o',
  tabula_format_style_unsigned_dec = 'u',
  tabula_format_style_unsigned_hex = 'x',
  tabula_format_style_unsigned_HEX = 'X',
  tabula_format_style_float_hex = 'a',
  tabula_format_style_float_HEX = 'A',
  tabula_format_style_float_fixed = 'f',
  tabula_format_style_float_FIXED = 'F',
  tabula_format_style_float_standard = 'e',
  tabula_format_style_float_STANDARD = 'E',
  tabula_format_style_float_auto = 'g',
  tabula_format_style_float_AUTO = 'G'
};

static unsigned int tabula_format_size_table[] = {
    // unsigned integer
    sizeof(int), sizeof(int), sizeof(int), sizeof(long), sizeof(long long), 0, sizeof(size_t), sizeof(intmax_t), sizeof(ptrdiff_t),
    // signed integer
    sizeof(int), sizeof(int), sizeof(int), sizeof(long), sizeof(long long), 0, sizeof(size_t), sizeof(intmax_t), sizeof(ptrdiff_t),
    // character
    sizeof(int), sizeof(int), sizeof(int), sizeof(long), sizeof(long long), 0, sizeof(size_t), sizeof(intmax_t), sizeof(ptrdiff_t),
    // double
    sizeof(double), 0, 0, 0, sizeof(double), sizeof(long double), 0, 0, 0,
    // pointer
    sizeof(void *), 0, 0, 0, 0, 0, 0, 0, 0,
    // string
    sizeof(const char *), 0, 0, 0, 0, 0, 0, 0, 0};

struct tabula_format_placeholder {
  uint8_t flag_minus : 1;
  uint8_t flag_plus : 1;
  uint8_t flag_space : 1;
  uint8_t flag_zero : 1;
  uint8_t flag_apostrophe : 1;
  uint8_t flag_hash : 1;
  uint8_t width_dynamic : 1;
  uint8_t precision_dynamic : 1;
  int32_t parameter;
  int32_t width;
  int32_t precision;
  enum tabula_format_length length;
  enum tabula_format_datatype datatype;
  enum tabula_format_style style;
};

#define TABULA_FORMAT_EMIT_UNSIGNED_INTEGER_BASE(NAME, TYPE, BASE, ALPHA)                                                                                      \
  static char *NAME##_imprecise(char *end, TYPE value) {                                                                                                       \
    do {                                                                                                                                                       \
      TYPE d_value = value % BASE;                                                                                                                             \
      value /= BASE;                                                                                                                                           \
      *--end = ALPHA + d_value;                                                                                                                                \
    } while(value);                                                                                                                                            \
    return end;                                                                                                                                                \
  }                                                                                                                                                            \
  static char *NAME##_precise(char *end, TYPE value, int32_t precision) {                                                                                      \
    while((precision > 0 ? (precision--, 1) : 0) || value) {                                                                                                   \
      TYPE d_value = value % BASE;                                                                                                                             \
      value /= BASE;                                                                                                                                           \
      *--end = ALPHA + d_value;                                                                                                                                \
    }                                                                                                                                                          \
    return end;                                                                                                                                                \
  }                                                                                                                                                            \
  static char *NAME(char *end, TYPE value, int32_t precision) {                                                                                                \
    if(precision == TABULA_FORMAT_UNDEFINED) {                                                                                                                 \
      return NAME##_imprecise(end, value);                                                                                                                     \
    } else {                                                                                                                                                   \
      return NAME##_precise(end, value, precision);                                                                                                            \
    }                                                                                                                                                          \
  }

#define TABULA_FORMAT_EMIT_UNSIGNED_INTEGER(NAME, UNSIGNED_TYPE, SIGNED_TYPE)                                                                                  \
  TABULA_FORMAT_EMIT_UNSIGNED_INTEGER_BASE(NAME##_oct, UNSIGNED_TYPE, 8, '0')                                                                                  \
  TABULA_FORMAT_EMIT_UNSIGNED_INTEGER_BASE(NAME##_dec, UNSIGNED_TYPE, 10, '0')                                                                                 \
  TABULA_FORMAT_EMIT_UNSIGNED_INTEGER_BASE(NAME##_hex, UNSIGNED_TYPE, 16, (d_value < 10 ? '0' : 'a' - 10))                                                     \
  TABULA_FORMAT_EMIT_UNSIGNED_INTEGER_BASE(NAME##_HEX, UNSIGNED_TYPE, 16, (d_value < 10 ? '0' : 'A' - 10))                                                     \
  static char *NAME(char *end, UNSIGNED_TYPE value, int32_t precision, enum tabula_format_style style) {                                                       \
    if(style == tabula_format_style_unsigned_oct) {                                                                                                            \
      return NAME##_oct(end, value, precision);                                                                                                                \
    } else if(style == tabula_format_style_unsigned_dec) {                                                                                                     \
      return NAME##_dec(end, value, precision);                                                                                                                \
    } else if(style == tabula_format_style_unsigned_hex) {                                                                                                     \
      return NAME##_hex(end, value, precision);                                                                                                                \
    } else if(style == tabula_format_style_unsigned_HEX) {                                                                                                     \
      return NAME##_HEX(end, value, precision);                                                                                                                \
    } else {                                                                                                                                                   \
      /* invalid style */                                                                                                                                      \
      assert("tabula_format_emit_intX_unsigned");                                                                                                              \
    }                                                                                                                                                          \
  }                                                                                                                                                            \
  static uint32_t NAME##_prefix_count(UNSIGNED_TYPE value, bool f_hash, enum tabula_format_style style) {                                                      \
    if(style == tabula_format_style_unsigned_oct && f_hash && value) {                                                                                         \
      return 1;                                                                                                                                                \
    } else if((style | ' ') == tabula_format_style_unsigned_hex && f_hash && value) {                                                                          \
      return 2;                                                                                                                                                \
    } else {                                                                                                                                                   \
      return 0;                                                                                                                                                \
    }                                                                                                                                                          \
  }                                                                                                                                                            \
  static char *NAME##_prefix(char *end, UNSIGNED_TYPE value, bool f_hash, enum tabula_format_style style) {                                                    \
    if(style == tabula_format_style_unsigned_oct && f_hash && value) {                                                                                         \
      *--end = '0';                                                                                                                                            \
    } else if(style == tabula_format_style_unsigned_hex && f_hash && value) {                                                                                  \
      *--end = 'x';                                                                                                                                            \
      *--end = '0';                                                                                                                                            \
    } else if(style == tabula_format_style_unsigned_HEX && f_hash && value) {                                                                                  \
      *--end = 'X';                                                                                                                                            \
      *--end = '0';                                                                                                                                            \
    }                                                                                                                                                          \
    return end;                                                                                                                                                \
  }

#define TABULA_FORMAT_EMIT_SIGNED_INTEGER(NAME, UNSIGNED_TYPE, SIGNED_TYPE)                                                                                    \
  TABULA_FORMAT_EMIT_UNSIGNED_INTEGER(NAME##_unsigned, UNSIGNED_TYPE, SIGNED_TYPE)                                                                             \
  static char *NAME(char *end, SIGNED_TYPE value, int32_t precision) {                                                                                         \
    if(value >= 0) {                                                                                                                                           \
      return NAME##_unsigned_dec(end, (UNSIGNED_TYPE)value, precision);                                                                                        \
    } else {                                                                                                                                                   \
      return NAME##_unsigned_dec(end, (UNSIGNED_TYPE)-value, precision);                                                                                       \
    }                                                                                                                                                          \
    return end;                                                                                                                                                \
  }                                                                                                                                                            \
  static uint32_t NAME##_prefix_count(SIGNED_TYPE value, bool f_plus, bool f_space) { return (value < (SIGNED_TYPE)0) || f_plus || f_space ? 1 : 0; }          \
  static char *NAME##_prefix(char *end, SIGNED_TYPE value, bool f_plus, bool f_space) {                                                                        \
    if(value >= 0) {                                                                                                                                           \
      if(f_plus) {                                                                                                                                             \
        *--end = '+';                                                                                                                                          \
      } else if(f_space) {                                                                                                                                     \
        *--end = ' ';                                                                                                                                          \
      }                                                                                                                                                        \
    } else {                                                                                                                                                   \
      *--end = '-';                                                                                                                                            \
    }                                                                                                                                                          \
    return end;                                                                                                                                                \
  }

TABULA_FORMAT_EMIT_SIGNED_INTEGER(tabula_format_emit_int32, uint32_t, int32_t)
TABULA_FORMAT_EMIT_SIGNED_INTEGER(tabula_format_emit_int64, uint64_t, int64_t)

// ============================================================================================================================================================
// detour into dragonbox
typedef struct {
  uint64_t high;
  uint64_t low;
} tabula_db_u128;

#define TABULA_DB_TYPE__SIGNFICAND_BITS__binary64 52
#define TABULA_DB_TYPE__EXPONENT_BITS__binary64 11
#define TABULA_DB_TYPE__MIN_EXPONENT__binary64 -1022
#define TABULA_DB_TYPE__BMAX_EXPONENT__binary64 1023
#define TABULA_DB_TYPE__EXPONENT_BIAS__binary64 -1023
#define TABULA_DB_TYPE__DECIMAL_DIGITS__binary64 17
#define TABULA_DB_TYPE__EXPONENT_BITS_MASK__binary64 ((1 << TABULA_DB_BINARY64_EXPONENT_BITS) - 1)
#define TABULA_DB_TYPE__CACHE_MIN_K__binary64 -292
#define TABULA_DB_TYPE__CACHE_MAX_K__binary64 326
#define TABULA_DB_TYPE__KAPPA__binary64 2

#define TABULA_DB_TYPE_SIGNFICAND_BITS(TYPE) TABULA_CAT2(TABULA_DB_TYPE__SIGNFICAND_BITS__, TYPE)
#define TABULA_DB_TYPE_EXPONENT_BITS(TYPE) TABULA_CAT2(TABULA_DB_TYPE__EXPONENT_BITS__, TYPE)
#define TABULA_DB_TYPE_MIN_EXPONENT(TYPE) TABULA_CAT2(TABULA_DB_TYPE__MIN_EXPONENT__, TYPE)
#define TABULA_DB_TYPE_MAX_EXPONENT(TYPE) TABULA_CAT2(TABULA_DB_TYPE__MAX_EXPONENT__, TYPE)
#define TABULA_DB_TYPE_EXPONENT_BIAS(TYPE) TABULA_CAT2(TABULA_DB_TYPE__EXPONENT_BIAS__, TYPE)
#define TABULA_DB_TYPE_DECIMAL_DIGITS(TYPE) TABULA_CAT2(TABULA_DB_TYPE__DECIMAL_DIGITS__, TYPE)
#define TABULA_DB_TYPE_CACHE_MIN_K(TYPE) TABULA_CAT2(TABULA_DB_TYPE__CACHE_MIN_K__, TYPE)
#define TABULA_DB_TYPE_CACHE_MAX_K(TYPE) TABULA_CAT2(TABULA_DB_TYPE__CACHE_MAX_K__, TYPE)
#define TABULA_DB_TYPE_KAPPA(TYPE) TABULA_CAT2(TABULA_DB_TYPE__KAPPA__, TYPE)

#define TABULA_DB_TYPE_EXPONENT_BITS_MASK(TYPE) ((1 << TABULA_DB_TYPE_EXPONENT_BITS(TYPE)) - 1)

static tabula_db_u128 tabula_db_get_binary64_cache(int k) {
  static const tabula_db_u128 data[] = {
      {0xff77b1fcbebcdc4f, 0x25e8e89c13bb0f7b}, {0x9faacf3df73609b1, 0x77b191618c54e9ad}, {0xc795830d75038c1d, 0xd59df5b9ef6a2418},
      {0xf97ae3d0d2446f25, 0x4b0573286b44ad1e}, {0x9becce62836ac577, 0x4ee367f9430aec33}, {0xc2e801fb244576d5, 0x229c41f793cda740},
      {0xf3a20279ed56d48a, 0x6b43527578c11110}, {0x9845418c345644d6, 0x830a13896b78aaaa}, {0xbe5691ef416bd60c, 0x23cc986bc656d554},
      {0xedec366b11c6cb8f, 0x2cbfbe86b7ec8aa9}, {0x94b3a202eb1c3f39, 0x7bf7d71432f3d6aa}, {0xb9e08a83a5e34f07, 0xdaf5ccd93fb0cc54},
      {0xe858ad248f5c22c9, 0xd1b3400f8f9cff69}, {0x91376c36d99995be, 0x23100809b9c21fa2}, {0xb58547448ffffb2d, 0xabd40a0c2832a78b},
      {0xe2e69915b3fff9f9, 0x16c90c8f323f516d}, {0x8dd01fad907ffc3b, 0xae3da7d97f6792e4}, {0xb1442798f49ffb4a, 0x99cd11cfdf41779d},
      {0xdd95317f31c7fa1d, 0x40405643d711d584}, {0x8a7d3eef7f1cfc52, 0x482835ea666b2573}, {0xad1c8eab5ee43b66, 0xda3243650005eed0},
      {0xd863b256369d4a40, 0x90bed43e40076a83}, {0x873e4f75e2224e68, 0x5a7744a6e804a292}, {0xa90de3535aaae202, 0x711515d0a205cb37},
      {0xd3515c2831559a83, 0x0d5a5b44ca873e04}, {0x8412d9991ed58091, 0xe858790afe9486c3}, {0xa5178fff668ae0b6, 0x626e974dbe39a873},
      {0xce5d73ff402d98e3, 0xfb0a3d212dc81290}, {0x80fa687f881c7f8e, 0x7ce66634bc9d0b9a}, {0xa139029f6a239f72, 0x1c1fffc1ebc44e81},
      {0xc987434744ac874e, 0xa327ffb266b56221}, {0xfbe9141915d7a922, 0x4bf1ff9f0062baa9}, {0x9d71ac8fada6c9b5, 0x6f773fc3603db4aa},
      {0xc4ce17b399107c22, 0xcb550fb4384d21d4}, {0xf6019da07f549b2b, 0x7e2a53a146606a49}, {0x99c102844f94e0fb, 0x2eda7444cbfc426e},
      {0xc0314325637a1939, 0xfa911155fefb5309}, {0xf03d93eebc589f88, 0x793555ab7eba27cb}, {0x96267c7535b763b5, 0x4bc1558b2f3458df},
      {0xbbb01b9283253ca2, 0x9eb1aaedfb016f17}, {0xea9c227723ee8bcb, 0x465e15a979c1cadd}, {0x92a1958a7675175f, 0x0bfacd89ec191eca},
      {0xb749faed14125d36, 0xcef980ec671f667c}, {0xe51c79a85916f484, 0x82b7e12780e7401b}, {0x8f31cc0937ae58d2, 0xd1b2ecb8b0908811},
      {0xb2fe3f0b8599ef07, 0x861fa7e6dcb4aa16}, {0xdfbdcece67006ac9, 0x67a791e093e1d49b}, {0x8bd6a141006042bd, 0xe0c8bb2c5c6d24e1},
      {0xaecc49914078536d, 0x58fae9f773886e19}, {0xda7f5bf590966848, 0xaf39a475506a899f}, {0x888f99797a5e012d, 0x6d8406c952429604},
      {0xaab37fd7d8f58178, 0xc8e5087ba6d33b84}, {0xd5605fcdcf32e1d6, 0xfb1e4a9a90880a65}, {0x855c3be0a17fcd26, 0x5cf2eea09a550680},
      {0xa6b34ad8c9dfc06f, 0xf42faa48c0ea481f}, {0xd0601d8efc57b08b, 0xf13b94daf124da27}, {0x823c12795db6ce57, 0x76c53d08d6b70859},
      {0xa2cb1717b52481ed, 0x54768c4b0c64ca6f}, {0xcb7ddcdda26da268, 0xa9942f5dcf7dfd0a}, {0xfe5d54150b090b02, 0xd3f93b35435d7c4d},
      {0x9efa548d26e5a6e1, 0xc47bc5014a1a6db0}, {0xc6b8e9b0709f109a, 0x359ab6419ca1091c}, {0xf867241c8cc6d4c0, 0xc30163d203c94b63},
      {0x9b407691d7fc44f8, 0x79e0de63425dcf1e}, {0xc21094364dfb5636, 0x985915fc12f542e5}, {0xf294b943e17a2bc4, 0x3e6f5b7b17b2939e},
      {0x979cf3ca6cec5b5a, 0xa705992ceecf9c43}, {0xbd8430bd08277231, 0x50c6ff782a838354}, {0xece53cec4a314ebd, 0xa4f8bf5635246429},
      {0x940f4613ae5ed136, 0x871b7795e136be9a}, {0xb913179899f68584, 0x28e2557b59846e40}, {0xe757dd7ec07426e5, 0x331aeada2fe589d0},
      {0x9096ea6f3848984f, 0x3ff0d2c85def7622}, {0xb4bca50b065abe63, 0x0fed077a756b53aa}, {0xe1ebce4dc7f16dfb, 0xd3e8495912c62895},
      {0x8d3360f09cf6e4bd, 0x64712dd7abbbd95d}, {0xb080392cc4349dec, 0xbd8d794d96aacfb4}, {0xdca04777f541c567, 0xecf0d7a0fc5583a1},
      {0x89e42caaf9491b60, 0xf41686c49db57245}, {0xac5d37d5b79b6239, 0x311c2875c522ced6}, {0xd77485cb25823ac7, 0x7d633293366b828c},
      {0x86a8d39ef77164bc, 0xae5dff9c02033198}, {0xa8530886b54dbdeb, 0xd9f57f830283fdfd}, {0xd267caa862a12d66, 0xd072df63c324fd7c},
      {0x8380dea93da4bc60, 0x4247cb9e59f71e6e}, {0xa46116538d0deb78, 0x52d9be85f074e609}, {0xcd795be870516656, 0x67902e276c921f8c},
      {0x806bd9714632dff6, 0x00ba1cd8a3db53b7}, {0xa086cfcd97bf97f3, 0x80e8a40eccd228a5}, {0xc8a883c0fdaf7df0, 0x6122cd128006b2ce},
      {0xfad2a4b13d1b5d6c, 0x796b805720085f82}, {0x9cc3a6eec6311a63, 0xcbe3303674053bb1}, {0xc3f490aa77bd60fc, 0xbedbfc4411068a9d},
      {0xf4f1b4d515acb93b, 0xee92fb5515482d45}, {0x991711052d8bf3c5, 0x751bdd152d4d1c4b}, {0xbf5cd54678eef0b6, 0xd262d45a78a0635e},
      {0xef340a98172aace4, 0x86fb897116c87c35}, {0x9580869f0e7aac0e, 0xd45d35e6ae3d4da1}, {0xbae0a846d2195712, 0x8974836059cca10a},
      {0xe998d258869facd7, 0x2bd1a438703fc94c}, {0x91ff83775423cc06, 0x7b6306a34627ddd0}, {0xb67f6455292cbf08, 0x1a3bc84c17b1d543},
      {0xe41f3d6a7377eeca, 0x20caba5f1d9e4a94}, {0x8e938662882af53e, 0x547eb47b7282ee9d}, {0xb23867fb2a35b28d, 0xe99e619a4f23aa44},
      {0xdec681f9f4c31f31, 0x6405fa00e2ec94d5}, {0x8b3c113c38f9f37e, 0xde83bc408dd3dd05}, {0xae0b158b4738705e, 0x9624ab50b148d446},
      {0xd98ddaee19068c76, 0x3badd624dd9b0958}, {0x87f8a8d4cfa417c9, 0xe54ca5d70a80e5d7}, {0xa9f6d30a038d1dbc, 0x5e9fcf4ccd211f4d},
      {0xd47487cc8470652b, 0x7647c32000696720}, {0x84c8d4dfd2c63f3b, 0x29ecd9f40041e074}, {0xa5fb0a17c777cf09, 0xf468107100525891},
      {0xcf79cc9db955c2cc, 0x7182148d4066eeb5}, {0x81ac1fe293d599bf, 0xc6f14cd848405531}, {0xa21727db38cb002f, 0xb8ada00e5a506a7d},
      {0xca9cf1d206fdc03b, 0xa6d90811f0e4851d}, {0xfd442e4688bd304a, 0x908f4a166d1da664}, {0x9e4a9cec15763e2e, 0x9a598e4e043287ff},
      {0xc5dd44271ad3cdba, 0x40eff1e1853f29fe}, {0xf7549530e188c128, 0xd12bee59e68ef47d}, {0x9a94dd3e8cf578b9, 0x82bb74f8301958cf},
      {0xc13a148e3032d6e7, 0xe36a52363c1faf02}, {0xf18899b1bc3f8ca1, 0xdc44e6c3cb279ac2}, {0x96f5600f15a7b7e5, 0x29ab103a5ef8c0ba},
      {0xbcb2b812db11a5de, 0x7415d448f6b6f0e8}, {0xebdf661791d60f56, 0x111b495b3464ad22}, {0x936b9fcebb25c995, 0xcab10dd900beec35},
      {0xb84687c269ef3bfb, 0x3d5d514f40eea743}, {0xe65829b3046b0afa, 0x0cb4a5a3112a5113}, {0x8ff71a0fe2c2e6dc, 0x47f0e785eaba72ac},
      {0xb3f4e093db73a093, 0x59ed216765690f57}, {0xe0f218b8d25088b8, 0x306869c13ec3532d}, {0x8c974f7383725573, 0x1e414218c73a13fc},
      {0xafbd2350644eeacf, 0xe5d1929ef90898fb}, {0xdbac6c247d62a583, 0xdf45f746b74abf3a}, {0x894bc396ce5da772, 0x6b8bba8c328eb784},
      {0xab9eb47c81f5114f, 0x066ea92f3f326565}, {0xd686619ba27255a2, 0xc80a537b0efefebe}, {0x8613fd0145877585, 0xbd06742ce95f5f37},
      {0xa798fc4196e952e7, 0x2c48113823b73705}, {0xd17f3b51fca3a7a0, 0xf75a15862ca504c6}, {0x82ef85133de648c4, 0x9a984d73dbe722fc},
      {0xa3ab66580d5fdaf5, 0xc13e60d0d2e0ebbb}, {0xcc963fee10b7d1b3, 0x318df905079926a9}, {0xffbbcfe994e5c61f, 0xfdf17746497f7053},
      {0x9fd561f1fd0f9bd3, 0xfeb6ea8bedefa634}, {0xc7caba6e7c5382c8, 0xfe64a52ee96b8fc1}, {0xf9bd690a1b68637b, 0x3dfdce7aa3c673b1},
      {0x9c1661a651213e2d, 0x06bea10ca65c084f}, {0xc31bfa0fe5698db8, 0x486e494fcff30a63}, {0xf3e2f893dec3f126, 0x5a89dba3c3efccfb},
      {0x986ddb5c6b3a76b7, 0xf89629465a75e01d}, {0xbe89523386091465, 0xf6bbb397f1135824}, {0xee2ba6c0678b597f, 0x746aa07ded582e2d},
      {0x94db483840b717ef, 0xa8c2a44eb4571cdd}, {0xba121a4650e4ddeb, 0x92f34d62616ce414}, {0xe896a0d7e51e1566, 0x77b020baf9c81d18},
      {0x915e2486ef32cd60, 0x0ace1474dc1d122f}, {0xb5b5ada8aaff80b8, 0x0d819992132456bb}, {0xe3231912d5bf60e6, 0x10e1fff697ed6c6a},
      {0x8df5efabc5979c8f, 0xca8d3ffa1ef463c2}, {0xb1736b96b6fd83b3, 0xbd308ff8a6b17cb3}, {0xddd0467c64bce4a0, 0xac7cb3f6d05ddbdf},
      {0x8aa22c0dbef60ee4, 0x6bcdf07a423aa96c}, {0xad4ab7112eb3929d, 0x86c16c98d2c953c7}, {0xd89d64d57a607744, 0xe871c7bf077ba8b8},
      {0x87625f056c7c4a8b, 0x11471cd764ad4973}, {0xa93af6c6c79b5d2d, 0xd598e40d3dd89bd0}, {0xd389b47879823479, 0x4aff1d108d4ec2c4},
      {0x843610cb4bf160cb, 0xcedf722a585139bb}, {0xa54394fe1eedb8fe, 0xc2974eb4ee658829}, {0xce947a3da6a9273e, 0x733d226229feea33},
      {0x811ccc668829b887, 0x0806357d5a3f5260}, {0xa163ff802a3426a8, 0xca07c2dcb0cf26f8}, {0xc9bcff6034c13052, 0xfc89b393dd02f0b6},
      {0xfc2c3f3841f17c67, 0xbbac2078d443ace3}, {0x9d9ba7832936edc0, 0xd54b944b84aa4c0e}, {0xc5029163f384a931, 0x0a9e795e65d4df12},
      {0xf64335bcf065d37d, 0x4d4617b5ff4a16d6}, {0x99ea0196163fa42e, 0x504bced1bf8e4e46}, {0xc06481fb9bcf8d39, 0xe45ec2862f71e1d7},
      {0xf07da27a82c37088, 0x5d767327bb4e5a4d}, {0x964e858c91ba2655, 0x3a6a07f8d510f870}, {0xbbe226efb628afea, 0x890489f70a55368c},
      {0xeadab0aba3b2dbe5, 0x2b45ac74ccea842f}, {0x92c8ae6b464fc96f, 0x3b0b8bc90012929e}, {0xb77ada0617e3bbcb, 0x09ce6ebb40173745},
      {0xe55990879ddcaabd, 0xcc420a6a101d0516}, {0x8f57fa54c2a9eab6, 0x9fa946824a12232e}, {0xb32df8e9f3546564, 0x47939822dc96abfa},
      {0xdff9772470297ebd, 0x59787e2b93bc56f8}, {0x8bfbea76c619ef36, 0x57eb4edb3c55b65b}, {0xaefae51477a06b03, 0xede622920b6b23f2},
      {0xdab99e59958885c4, 0xe95fab368e45ecee}, {0x88b402f7fd75539b, 0x11dbcb0218ebb415}, {0xaae103b5fcd2a881, 0xd652bdc29f26a11a},
      {0xd59944a37c0752a2, 0x4be76d3346f04960}, {0x857fcae62d8493a5, 0x6f70a4400c562ddc}, {0xa6dfbd9fb8e5b88e, 0xcb4ccd500f6bb953},
      {0xd097ad07a71f26b2, 0x7e2000a41346a7a8}, {0x825ecc24c873782f, 0x8ed400668c0c28c9}, {0xa2f67f2dfa90563b, 0x728900802f0f32fb},
      {0xcbb41ef979346bca, 0x4f2b40a03ad2ffba}, {0xfea126b7d78186bc, 0xe2f610c84987bfa9}, {0x9f24b832e6b0f436, 0x0dd9ca7d2df4d7ca},
      {0xc6ede63fa05d3143, 0x91503d1c79720dbc}, {0xf8a95fcf88747d94, 0x75a44c6397ce912b}, {0x9b69dbe1b548ce7c, 0xc986afbe3ee11abb},
      {0xc24452da229b021b, 0xfbe85badce996169}, {0xf2d56790ab41c2a2, 0xfae27299423fb9c4}, {0x97c560ba6b0919a5, 0xdccd879fc967d41b},
      {0xbdb6b8e905cb600f, 0x5400e987bbc1c921}, {0xed246723473e3813, 0x290123e9aab23b69}, {0x9436c0760c86e30b, 0xf9a0b6720aaf6522},
      {0xb94470938fa89bce, 0xf808e40e8d5b3e6a}, {0xe7958cb87392c2c2, 0xb60b1d1230b20e05}, {0x90bd77f3483bb9b9, 0xb1c6f22b5e6f48c3},
      {0xb4ecd5f01a4aa828, 0x1e38aeb6360b1af4}, {0xe2280b6c20dd5232, 0x25c6da63c38de1b1}, {0x8d590723948a535f, 0x579c487e5a38ad0f},
      {0xb0af48ec79ace837, 0x2d835a9df0c6d852}, {0xdcdb1b2798182244, 0xf8e431456cf88e66}, {0x8a08f0f8bf0f156b, 0x1b8e9ecb641b5900},
      {0xac8b2d36eed2dac5, 0xe272467e3d222f40}, {0xd7adf884aa879177, 0x5b0ed81dcc6abb10}, {0x86ccbb52ea94baea, 0x98e947129fc2b4ea},
      {0xa87fea27a539e9a5, 0x3f2398d747b36225}, {0xd29fe4b18e88640e, 0x8eec7f0d19a03aae}, {0x83a3eeeef9153e89, 0x1953cf68300424ad},
      {0xa48ceaaab75a8e2b, 0x5fa8c3423c052dd8}, {0xcdb02555653131b6, 0x3792f412cb06794e}, {0x808e17555f3ebf11, 0xe2bbd88bbee40bd1},
      {0xa0b19d2ab70e6ed6, 0x5b6aceaeae9d0ec5}, {0xc8de047564d20a8b, 0xf245825a5a445276}, {0xfb158592be068d2e, 0xeed6e2f0f0d56713},
      {0x9ced737bb6c4183d, 0x55464dd69685606c}, {0xc428d05aa4751e4c, 0xaa97e14c3c26b887}, {0xf53304714d9265df, 0xd53dd99f4b3066a9},
      {0x993fe2c6d07b7fab, 0xe546a8038efe402a}, {0xbf8fdb78849a5f96, 0xde98520472bdd034}, {0xef73d256a5c0f77c, 0x963e66858f6d4441},
      {0x95a8637627989aad, 0xdde7001379a44aa9}, {0xbb127c53b17ec159, 0x5560c018580d5d53}, {0xe9d71b689dde71af, 0xaab8f01e6e10b4a7},
      {0x9226712162ab070d, 0xcab3961304ca70e9}, {0xb6b00d69bb55c8d1, 0x3d607b97c5fd0d23}, {0xe45c10c42a2b3b05, 0x8cb89a7db77c506b},
      {0x8eb98a7a9a5b04e3, 0x77f3608e92adb243}, {0xb267ed1940f1c61c, 0x55f038b237591ed4}, {0xdf01e85f912e37a3, 0x6b6c46dec52f6689},
      {0x8b61313bbabce2c6, 0x2323ac4b3b3da016}, {0xae397d8aa96c1b77, 0xabec975e0a0d081b}, {0xd9c7dced53c72255, 0x96e7bd358c904a22},
      {0x881cea14545c7575, 0x7e50d64177da2e55}, {0xaa242499697392d2, 0xdde50bd1d5d0b9ea}, {0xd4ad2dbfc3d07787, 0x955e4ec64b44e865},
      {0x84ec3c97da624ab4, 0xbd5af13bef0b113f}, {0xa6274bbdd0fadd61, 0xecb1ad8aeacdd58f}, {0xcfb11ead453994ba, 0x67de18eda5814af3},
      {0x81ceb32c4b43fcf4, 0x80eacf948770ced8}, {0xa2425ff75e14fc31, 0xa1258379a94d028e}, {0xcad2f7f5359a3b3e, 0x096ee45813a04331},
      {0xfd87b5f28300ca0d, 0x8bca9d6e188853fd}, {0x9e74d1b791e07e48, 0x775ea264cf55347e}, {0xc612062576589dda, 0x95364afe032a819e},
      {0xf79687aed3eec551, 0x3a83ddbd83f52205}, {0x9abe14cd44753b52, 0xc4926a9672793543}, {0xc16d9a0095928a27, 0x75b7053c0f178294},
      {0xf1c90080baf72cb1, 0x5324c68b12dd6339}, {0x971da05074da7bee, 0xd3f6fc16ebca5e04}, {0xbce5086492111aea, 0x88f4bb1ca6bcf585},
      {0xec1e4a7db69561a5, 0x2b31e9e3d06c32e6}, {0x9392ee8e921d5d07, 0x3aff322e62439fd0}, {0xb877aa3236a4b449, 0x09befeb9fad487c3},
      {0xe69594bec44de15b, 0x4c2ebe687989a9b4}, {0x901d7cf73ab0acd9, 0x0f9d37014bf60a11}, {0xb424dc35095cd80f, 0x538484c19ef38c95},
      {0xe12e13424bb40e13, 0x2865a5f206b06fba}, {0x8cbccc096f5088cb, 0xf93f87b7442e45d4}, {0xafebff0bcb24aafe, 0xf78f69a51539d749},
      {0xdbe6fecebdedd5be, 0xb573440e5a884d1c}, {0x89705f4136b4a597, 0x31680a88f8953031}, {0xabcc77118461cefc, 0xfdc20d2b36ba7c3e},
      {0xd6bf94d5e57a42bc, 0x3d32907604691b4d}, {0x8637bd05af6c69b5, 0xa63f9a49c2c1b110}, {0xa7c5ac471b478423, 0x0fcf80dc33721d54},
      {0xd1b71758e219652b, 0xd3c36113404ea4a9}, {0x83126e978d4fdf3b, 0x645a1cac083126ea}, {0xa3d70a3d70a3d70a, 0x3d70a3d70a3d70a4},
      {0xcccccccccccccccc, 0xcccccccccccccccd}, {0x8000000000000000, 0x0000000000000000}, {0xa000000000000000, 0x0000000000000000},
      {0xc800000000000000, 0x0000000000000000}, {0xfa00000000000000, 0x0000000000000000}, {0x9c40000000000000, 0x0000000000000000},
      {0xc350000000000000, 0x0000000000000000}, {0xf424000000000000, 0x0000000000000000}, {0x9896800000000000, 0x0000000000000000},
      {0xbebc200000000000, 0x0000000000000000}, {0xee6b280000000000, 0x0000000000000000}, {0x9502f90000000000, 0x0000000000000000},
      {0xba43b74000000000, 0x0000000000000000}, {0xe8d4a51000000000, 0x0000000000000000}, {0x9184e72a00000000, 0x0000000000000000},
      {0xb5e620f480000000, 0x0000000000000000}, {0xe35fa931a0000000, 0x0000000000000000}, {0x8e1bc9bf04000000, 0x0000000000000000},
      {0xb1a2bc2ec5000000, 0x0000000000000000}, {0xde0b6b3a76400000, 0x0000000000000000}, {0x8ac7230489e80000, 0x0000000000000000},
      {0xad78ebc5ac620000, 0x0000000000000000}, {0xd8d726b7177a8000, 0x0000000000000000}, {0x878678326eac9000, 0x0000000000000000},
      {0xa968163f0a57b400, 0x0000000000000000}, {0xd3c21bcecceda100, 0x0000000000000000}, {0x84595161401484a0, 0x0000000000000000},
      {0xa56fa5b99019a5c8, 0x0000000000000000}, {0xcecb8f27f4200f3a, 0x0000000000000000}, {0x813f3978f8940984, 0x4000000000000000},
      {0xa18f07d736b90be5, 0x5000000000000000}, {0xc9f2c9cd04674ede, 0xa400000000000000}, {0xfc6f7c4045812296, 0x4d00000000000000},
      {0x9dc5ada82b70b59d, 0xf020000000000000}, {0xc5371912364ce305, 0x6c28000000000000}, {0xf684df56c3e01bc6, 0xc732000000000000},
      {0x9a130b963a6c115c, 0x3c7f400000000000}, {0xc097ce7bc90715b3, 0x4b9f100000000000}, {0xf0bdc21abb48db20, 0x1e86d40000000000},
      {0x96769950b50d88f4, 0x1314448000000000}, {0xbc143fa4e250eb31, 0x17d955a000000000}, {0xeb194f8e1ae525fd, 0x5dcfab0800000000},
      {0x92efd1b8d0cf37be, 0x5aa1cae500000000}, {0xb7abc627050305ad, 0xf14a3d9e40000000}, {0xe596b7b0c643c719, 0x6d9ccd05d0000000},
      {0x8f7e32ce7bea5c6f, 0xe4820023a2000000}, {0xb35dbf821ae4f38b, 0xdda2802c8a800000}, {0xe0352f62a19e306e, 0xd50b2037ad200000},
      {0x8c213d9da502de45, 0x4526f422cc340000}, {0xaf298d050e4395d6, 0x9670b12b7f410000}, {0xdaf3f04651d47b4c, 0x3c0cdd765f114000},
      {0x88d8762bf324cd0f, 0xa5880a69fb6ac800}, {0xab0e93b6efee0053, 0x8eea0d047a457a00}, {0xd5d238a4abe98068, 0x72a4904598d6d880},
      {0x85a36366eb71f041, 0x47a6da2b7f864750}, {0xa70c3c40a64e6c51, 0x999090b65f67d924}, {0xd0cf4b50cfe20765, 0xfff4b4e3f741cf6d},
      {0x82818f1281ed449f, 0xbff8f10e7a8921a5}, {0xa321f2d7226895c7, 0xaff72d52192b6a0e}, {0xcbea6f8ceb02bb39, 0x9bf4f8a69f764491},
      {0xfee50b7025c36a08, 0x02f236d04753d5b5}, {0x9f4f2726179a2245, 0x01d762422c946591}, {0xc722f0ef9d80aad6, 0x424d3ad2b7b97ef6},
      {0xf8ebad2b84e0d58b, 0xd2e0898765a7deb3}, {0x9b934c3b330c8577, 0x63cc55f49f88eb30}, {0xc2781f49ffcfa6d5, 0x3cbf6b71c76b25fc},
      {0xf316271c7fc3908a, 0x8bef464e3945ef7b}, {0x97edd871cfda3a56, 0x97758bf0e3cbb5ad}, {0xbde94e8e43d0c8ec, 0x3d52eeed1cbea318},
      {0xed63a231d4c4fb27, 0x4ca7aaa863ee4bde}, {0x945e455f24fb1cf8, 0x8fe8caa93e74ef6b}, {0xb975d6b6ee39e436, 0xb3e2fd538e122b45},
      {0xe7d34c64a9c85d44, 0x60dbbca87196b617}, {0x90e40fbeea1d3a4a, 0xbc8955e946fe31ce}, {0xb51d13aea4a488dd, 0x6babab6398bdbe42},
      {0xe264589a4dcdab14, 0xc696963c7eed2dd2}, {0x8d7eb76070a08aec, 0xfc1e1de5cf543ca3}, {0xb0de65388cc8ada8, 0x3b25a55f43294bcc},
      {0xdd15fe86affad912, 0x49ef0eb713f39ebf}, {0x8a2dbf142dfcc7ab, 0x6e3569326c784338}, {0xacb92ed9397bf996, 0x49c2c37f07965405},
      {0xd7e77a8f87daf7fb, 0xdc33745ec97be907}, {0x86f0ac99b4e8dafd, 0x69a028bb3ded71a4}, {0xa8acd7c0222311bc, 0xc40832ea0d68ce0d},
      {0xd2d80db02aabd62b, 0xf50a3fa490c30191}, {0x83c7088e1aab65db, 0x792667c6da79e0fb}, {0xa4b8cab1a1563f52, 0x577001b891185939},
      {0xcde6fd5e09abcf26, 0xed4c0226b55e6f87}, {0x80b05e5ac60b6178, 0x544f8158315b05b5}, {0xa0dc75f1778e39d6, 0x696361ae3db1c722},
      {0xc913936dd571c84c, 0x03bc3a19cd1e38ea}, {0xfb5878494ace3a5f, 0x04ab48a04065c724}, {0x9d174b2dcec0e47b, 0x62eb0d64283f9c77},
      {0xc45d1df942711d9a, 0x3ba5d0bd324f8395}, {0xf5746577930d6500, 0xca8f44ec7ee3647a}, {0x9968bf6abbe85f20, 0x7e998b13cf4e1ecc},
      {0xbfc2ef456ae276e8, 0x9e3fedd8c321a67f}, {0xefb3ab16c59b14a2, 0xc5cfe94ef3ea101f}, {0x95d04aee3b80ece5, 0xbba1f1d158724a13},
      {0xbb445da9ca61281f, 0x2a8a6e45ae8edc98}, {0xea1575143cf97226, 0xf52d09d71a3293be}, {0x924d692ca61be758, 0x593c2626705f9c57},
      {0xb6e0c377cfa2e12e, 0x6f8b2fb00c77836d}, {0xe498f455c38b997a, 0x0b6dfb9c0f956448}, {0x8edf98b59a373fec, 0x4724bd4189bd5ead},
      {0xb2977ee300c50fe7, 0x58edec91ec2cb658}, {0xdf3d5e9bc0f653e1, 0x2f2967b66737e3ee}, {0x8b865b215899f46c, 0xbd79e0d20082ee75},
      {0xae67f1e9aec07187, 0xecd8590680a3aa12}, {0xda01ee641a708de9, 0xe80e6f4820cc9496}, {0x884134fe908658b2, 0x3109058d147fdcde},
      {0xaa51823e34a7eede, 0xbd4b46f0599fd416}, {0xd4e5e2cdc1d1ea96, 0x6c9e18ac7007c91b}, {0x850fadc09923329e, 0x03e2cf6bc604ddb1},
      {0xa6539930bf6bff45, 0x84db8346b786151d}, {0xcfe87f7cef46ff16, 0xe612641865679a64}, {0x81f14fae158c5f6e, 0x4fcb7e8f3f60c07f},
      {0xa26da3999aef7749, 0xe3be5e330f38f09e}, {0xcb090c8001ab551c, 0x5cadf5bfd3072cc6}, {0xfdcb4fa002162a63, 0x73d9732fc7c8f7f7},
      {0x9e9f11c4014dda7e, 0x2867e7fddcdd9afb}, {0xc646d63501a1511d, 0xb281e1fd541501b9}, {0xf7d88bc24209a565, 0x1f225a7ca91a4227},
      {0x9ae757596946075f, 0x3375788de9b06959}, {0xc1a12d2fc3978937, 0x0052d6b1641c83af}, {0xf209787bb47d6b84, 0xc0678c5dbd23a49b},
      {0x9745eb4d50ce6332, 0xf840b7ba963646e1}, {0xbd176620a501fbff, 0xb650e5a93bc3d899}, {0xec5d3fa8ce427aff, 0xa3e51f138ab4cebf},
      {0x93ba47c980e98cdf, 0xc66f336c36b10138}, {0xb8a8d9bbe123f017, 0xb80b0047445d4185}, {0xe6d3102ad96cec1d, 0xa60dc059157491e6},
      {0x9043ea1ac7e41392, 0x87c89837ad68db30}, {0xb454e4a179dd1877, 0x29babe4598c311fc}, {0xe16a1dc9d8545e94, 0xf4296dd6fef3d67b},
      {0x8ce2529e2734bb1d, 0x1899e4a65f58660d}, {0xb01ae745b101e9e4, 0x5ec05dcff72e7f90}, {0xdc21a1171d42645d, 0x76707543f4fa1f74},
      {0x899504ae72497eba, 0x6a06494a791c53a9}, {0xabfa45da0edbde69, 0x0487db9d17636893}, {0xd6f8d7509292d603, 0x45a9d2845d3c42b7},
      {0x865b86925b9bc5c2, 0x0b8a2392ba45a9b3}, {0xa7f26836f282b732, 0x8e6cac7768d7141f}, {0xd1ef0244af2364ff, 0x3207d795430cd927},
      {0x8335616aed761f1f, 0x7f44e6bd49e807b9}, {0xa402b9c5a8d3a6e7, 0x5f16206c9c6209a7}, {0xcd036837130890a1, 0x36dba887c37a8c10},
      {0x802221226be55a64, 0xc2494954da2c978a}, {0xa02aa96b06deb0fd, 0xf2db9baa10b7bd6d}, {0xc83553c5c8965d3d, 0x6f92829494e5acc8},
      {0xfa42a8b73abbf48c, 0xcb772339ba1f17fa}, {0x9c69a97284b578d7, 0xff2a760414536efc}, {0xc38413cf25e2d70d, 0xfef5138519684abb},
      {0xf46518c2ef5b8cd1, 0x7eb258665fc25d6a}, {0x98bf2f79d5993802, 0xef2f773ffbd97a62}, {0xbeeefb584aff8603, 0xaafb550ffacfd8fb},
      {0xeeaaba2e5dbf6784, 0x95ba2a53f983cf39}, {0x952ab45cfa97a0b2, 0xdd945a747bf26184}, {0xba756174393d88df, 0x94f971119aeef9e5},
      {0xe912b9d1478ceb17, 0x7a37cd5601aab85e}, {0x91abb422ccb812ee, 0xac62e055c10ab33b}, {0xb616a12b7fe617aa, 0x577b986b314d600a},
      {0xe39c49765fdf9d94, 0xed5a7e85fda0b80c}, {0x8e41ade9fbebc27d, 0x14588f13be847308}, {0xb1d219647ae6b31c, 0x596eb2d8ae258fc9},
      {0xde469fbd99a05fe3, 0x6fca5f8ed9aef3bc}, {0x8aec23d680043bee, 0x25de7bb9480d5855}, {0xada72ccc20054ae9, 0xaf561aa79a10ae6b},
      {0xd910f7ff28069da4, 0x1b2ba1518094da05}, {0x87aa9aff79042286, 0x90fb44d2f05d0843}, {0xa99541bf57452b28, 0x353a1607ac744a54},
      {0xd3fa922f2d1675f2, 0x42889b8997915ce9}, {0x847c9b5d7c2e09b7, 0x69956135febada12}, {0xa59bc234db398c25, 0x43fab9837e699096},
      {0xcf02b2c21207ef2e, 0x94f967e45e03f4bc}, {0x8161afb94b44f57d, 0x1d1be0eebac278f6}, {0xa1ba1ba79e1632dc, 0x6462d92a69731733},
      {0xca28a291859bbf93, 0x7d7b8f7503cfdcff}, {0xfcb2cb35e702af78, 0x5cda735244c3d43f}, {0x9defbf01b061adab, 0x3a0888136afa64a8},
      {0xc56baec21c7a1916, 0x088aaa1845b8fdd1}, {0xf6c69a72a3989f5b, 0x8aad549e57273d46}, {0x9a3c2087a63f6399, 0x36ac54e2f678864c},
      {0xc0cb28a98fcf3c7f, 0x84576a1bb416a7de}, {0xf0fdf2d3f3c30b9f, 0x656d44a2a11c51d6}, {0x969eb7c47859e743, 0x9f644ae5a4b1b326},
      {0xbc4665b596706114, 0x873d5d9f0dde1fef}, {0xeb57ff22fc0c7959, 0xa90cb506d155a7eb}, {0x9316ff75dd87cbd8, 0x09a7f12442d588f3},
      {0xb7dcbf5354e9bece, 0x0c11ed6d538aeb30}, {0xe5d3ef282a242e81, 0x8f1668c8a86da5fb}, {0x8fa475791a569d10, 0xf96e017d694487bd},
      {0xb38d92d760ec4455, 0x37c981dcc395a9ad}, {0xe070f78d3927556a, 0x85bbe253f47b1418}, {0x8c469ab843b89562, 0x93956d7478ccec8f},
      {0xaf58416654a6babb, 0x387ac8d1970027b3}, {0xdb2e51bfe9d0696a, 0x06997b05fcc0319f}, {0x88fcf317f22241e2, 0x441fece3bdf81f04},
      {0xab3c2fddeeaad25a, 0xd527e81cad7626c4}, {0xd60b3bd56a5586f1, 0x8a71e223d8d3b075}, {0x85c7056562757456, 0xf6872d5667844e4a},
      {0xa738c6bebb12d16c, 0xb428f8ac016561dc}, {0xd106f86e69d785c7, 0xe13336d701beba53}, {0x82a45b450226b39c, 0xecc0024661173474},
      {0xa34d721642b06084, 0x27f002d7f95d0191}, {0xcc20ce9bd35c78a5, 0x31ec038df7b441f5}, {0xff290242c83396ce, 0x7e67047175a15272},
      {0x9f79a169bd203e41, 0x0f0062c6e984d387}, {0xc75809c42c684dd1, 0x52c07b78a3e60869}, {0xf92e0c3537826145, 0xa7709a56ccdf8a83},
      {0x9bbcc7a142b17ccb, 0x88a66076400bb692}, {0xc2abf989935ddbfe, 0x6acff893d00ea436}, {0xf356f7ebf83552fe, 0x0583f6b8c4124d44},
      {0x98165af37b2153de, 0xc3727a337a8b704b}, {0xbe1bf1b059e9a8d6, 0x744f18c0592e4c5d}, {0xeda2ee1c7064130c, 0x1162def06f79df74},
      {0x9485d4d1c63e8be7, 0x8addcb5645ac2ba9}, {0xb9a74a0637ce2ee1, 0x6d953e2bd7173693}, {0xe8111c87c5c1ba99, 0xc8fa8db6ccdd0438},
      {0x910ab1d4db9914a0, 0x1d9c9892400a22a3}, {0xb54d5e4a127f59c8, 0x2503beb6d00cab4c}, {0xe2a0b5dc971f303a, 0x2e44ae64840fd61e},
      {0x8da471a9de737e24, 0x5ceaecfed289e5d3}, {0xb10d8e1456105dad, 0x7425a83e872c5f48}, {0xdd50f1996b947518, 0xd12f124e28f7771a},
      {0x8a5296ffe33cc92f, 0x82bd6b70d99aaa70}, {0xace73cbfdc0bfb7b, 0x636cc64d1001550c}, {0xd8210befd30efa5a, 0x3c47f7e05401aa4f},
      {0x8714a775e3e95c78, 0x65acfaec34810a72}, {0xa8d9d1535ce3b396, 0x7f1839a741a14d0e}, {0xd31045a8341ca07c, 0x1ede48111209a051},
      {0x83ea2b892091e44d, 0x934aed0aab460433}, {0xa4e4b66b68b65d60, 0xf81da84d56178540}, {0xce1de40642e3f4b9, 0x36251260ab9d668f},
      {0x80d2ae83e9ce78f3, 0xc1d72b7c6b42601a}, {0xa1075a24e4421730, 0xb24cf65b8612f820}, {0xc94930ae1d529cfc, 0xdee033f26797b628},
      {0xfb9b7cd9a4a7443c, 0x169840ef017da3b2}, {0x9d412e0806e88aa5, 0x8e1f289560ee864f}, {0xc491798a08a2ad4e, 0xf1a6f2bab92a27e3},
      {0xf5b5d7ec8acb58a2, 0xae10af696774b1dc}, {0x9991a6f3d6bf1765, 0xacca6da1e0a8ef2a}, {0xbff610b0cc6edd3f, 0x17fd090a58d32af4},
      {0xeff394dcff8a948e, 0xddfc4b4cef07f5b1}, {0x95f83d0a1fb69cd9, 0x4abdaf101564f98f}, {0xbb764c4ca7a4440f, 0x9d6d1ad41abe37f2},
      {0xea53df5fd18d5513, 0x84c86189216dc5ee}, {0x92746b9be2f8552c, 0x32fd3cf5b4e49bb5}, {0xb7118682dbb66a77, 0x3fbc8c33221dc2a2},
      {0xe4d5e82392a40515, 0x0fabaf3feaa5334b}, {0x8f05b1163ba6832d, 0x29cb4d87f2a7400f}, {0xb2c71d5bca9023f8, 0x743e20e9ef511013},
      {0xdf78e4b2bd342cf6, 0x914da9246b255417}, {0x8bab8eefb6409c1a, 0x1ad089b6c2f7548f}, {0xae9672aba3d0c320, 0xa184ac2473b529b2},
      {0xda3c0f568cc4f3e8, 0xc9e5d72d90a2741f}, {0x8865899617fb1871, 0x7e2fa67c7a658893}, {0xaa7eebfb9df9de8d, 0xddbb901b98feeab8},
      {0xd51ea6fa85785631, 0x552a74227f3ea566}, {0x8533285c936b35de, 0xd53a88958f872760}, {0xa67ff273b8460356, 0x8a892abaf368f138},
      {0xd01fef10a657842c, 0x2d2b7569b0432d86}, {0x8213f56a67f6b29b, 0x9c3b29620e29fc74}, {0xa298f2c501f45f42, 0x8349f3ba91b47b90},
      {0xcb3f2f7642717713, 0x241c70a936219a74}, {0xfe0efb53d30dd4d7, 0xed238cd383aa0111}, {0x9ec95d1463e8a506, 0xf4363804324a40ab},
      {0xc67bb4597ce2ce48, 0xb143c6053edcd0d6}, {0xf81aa16fdc1b81da, 0xdd94b7868e94050b}, {0x9b10a4e5e9913128, 0xca7cf2b4191c8327},
      {0xc1d4ce1f63f57d72, 0xfd1c2f611f63a3f1}, {0xf24a01a73cf2dccf, 0xbc633b39673c8ced}, {0x976e41088617ca01, 0xd5be0503e085d814},
      {0xbd49d14aa79dbc82, 0x4b2d8644d8a74e19}, {0xec9c459d51852ba2, 0xddf8e7d60ed1219f}, {0x93e1ab8252f33b45, 0xcabb90e5c942b504},
      {0xb8da1662e7b00a17, 0x3d6a751f3b936244}, {0xe7109bfba19c0c9d, 0x0cc512670a783ad5}, {0x906a617d450187e2, 0x27fb2b80668b24c6},
      {0xb484f9dc9641e9da, 0xb1f9f660802dedf7}, {0xe1a63853bbd26451, 0x5e7873f8a0396974}, {0x8d07e33455637eb2, 0xdb0b487b6423e1e9},
      {0xb049dc016abc5e5f, 0x91ce1a9a3d2cda63}, {0xdc5c5301c56b75f7, 0x7641a140cc7810fc}, {0x89b9b3e11b6329ba, 0xa9e904c87fcb0a9e},
      {0xac2820d9623bf429, 0x546345fa9fbdcd45}, {0xd732290fbacaf133, 0xa97c177947ad4096}, {0x867f59a9d4bed6c0, 0x49ed8eabcccc485e},
      {0xa81f301449ee8c70, 0x5c68f256bfff5a75}, {0xd226fc195c6a2f8c, 0x73832eec6fff3112}, {0x83585d8fd9c25db7, 0xc831fd53c5ff7eac},
      {0xa42e74f3d032f525, 0xba3e7ca8b77f5e56}, {0xcd3a1230c43fb26f, 0x28ce1bd2e55f35ec}, {0x80444b5e7aa7cf85, 0x7980d163cf5b81b4},
      {0xa0555e361951c366, 0xd7e105bcc3326220}, {0xc86ab5c39fa63440, 0x8dd9472bf3fefaa8}, {0xfa856334878fc150, 0xb14f98f6f0feb952},
      {0x9c935e00d4b9d8d2, 0x6ed1bf9a569f33d4}, {0xc3b8358109e84f07, 0x0a862f80ec4700c9}, {0xf4a642e14c6262c8, 0xcd27bb612758c0fb},
      {0x98e7e9cccfbd7dbd, 0x8038d51cb897789d}, {0xbf21e44003acdd2c, 0xe0470a63e6bd56c4}, {0xeeea5d5004981478, 0x1858ccfce06cac75},
      {0x95527a5202df0ccb, 0x0f37801e0c43ebc9}, {0xbaa718e68396cffd, 0xd30560258f54e6bb}, {0xe950df20247c83fd, 0x47c6b82ef32a206a},
      {0x91d28b7416cdd27e, 0x4cdc331d57fa5442}, {0xb6472e511c81471d, 0xe0133fe4adf8e953}, {0xe3d8f9e563a198e5, 0x58180fddd97723a7},
      {0x8e679c2f5e44ff8f, 0x570f09eaa7ea7649}, {0xb201833b35d63f73, 0x2cd2cc6551e513db}, {0xde81e40a034bcf4f, 0xf8077f7ea65e58d2},
      {0x8b112e86420f6191, 0xfb04afaf27faf783}, {0xadd57a27d29339f6, 0x79c5db9af1f9b564}, {0xd94ad8b1c7380874, 0x18375281ae7822bd},
      {0x87cec76f1c830548, 0x8f2293910d0b15b6}, {0xa9c2794ae3a3c69a, 0xb2eb3875504ddb23}, {0xd433179d9c8cb841, 0x5fa60692a46151ec},
      {0x849feec281d7f328, 0xdbc7c41ba6bcd334}, {0xa5c7ea73224deff3, 0x12b9b522906c0801}, {0xcf39e50feae16bef, 0xd768226b34870a01},
      {0x81842f29f2cce375, 0xe6a1158300d46641}, {0xa1e53af46f801c53, 0x60495ae3c1097fd1}, {0xca5e89b18b602368, 0x385bb19cb14bdfc5},
      {0xfcf62c1dee382c42, 0x46729e03dd9ed7b6}, {0x9e19db92b4e31ba9, 0x6c07a2c26a8346d2}, {0xc5a05277621be293, 0xc7098b7305241886},
      {0xf70867153aa2db38, 0xb8cbee4fc66d1ea8}};
  return data[k - TABULA_DB_TYPE__CACHE_MIN_K__binary64];
}

#define tabula_db_floor_util(MULTIPLY, SUBTRACT, SHIFT, MIN_EXPONENT, MAX_EXPONENT, e)                                                                         \
  (int)(((int32_t)(e) * (int32_t)(MULTIPLY) - (int32_t)(SUBTRACT)) >> (size_t)(SHIFT))

#define tabula_db_compute_power(OUT, K, TYPE, A)                                                                                                               \
  do {                                                                                                                                                         \
    TYPE a_ = A;                                                                                                                                               \
    OUT = 1;                                                                                                                                                   \
    for(int i = 0; i < K; i++) {                                                                                                                               \
      OUT *= a_;                                                                                                                                               \
    }                                                                                                                                                          \
  } while(false)

#define tabula_db_count_factors(OUT, A, TYPE, N)                                                                                                               \
  do {                                                                                                                                                         \
    TYPE n_ = N;                                                                                                                                               \
    OUT = 0;                                                                                                                                                   \
    while((n_ % A) == 0) {                                                                                                                                     \
      n_ /= A;                                                                                                                                                 \
      OUT++;                                                                                                                                                   \
    }                                                                                                                                                          \
  } while(false)

#define tabula_db_floor_log2(OUT, TYPE, N)                                                                                                                     \
  do {                                                                                                                                                         \
    TYPE n_ = N;                                                                                                                                               \
    OUT = -1;                                                                                                                                                  \
    while(n_ != 0) {                                                                                                                                           \
      ++OUT;                                                                                                                                                   \
      n_ >>= 1;                                                                                                                                                \
    }                                                                                                                                                          \
  } while(false)

#define tabula_db_floor_log10_pow2(e) tabula_db_floor_util(315653, 0, 20, -2620, 2620, e)
#define tabula_db_floor_log2_pow10(e) tabula_db_floor_util(1741647, 0, 19, -1233, 1233, e)
#define tabula_db_floor_log10_pow2_minus_log10_4_over_3(e) tabula_db_floor_util(315653, 0, 20, -2620, 2620, e)
#define tabula_db_floor_log5_pow2(e) tabula_db_floor_util(225799, 0, 19, -1831, 1831, e)
#define tabula_db_floor_log5_pow2_minus_log5_3(e) tabula_db_floor_util(451597, 715764, 20, -3543, 2427, e)

#define tabula_db_mul_u32_u32(OUT, A, B) (OUT = ((A) * (uint64_t)(B)))
#define tabula_db_mul_u64_u64(OUT, A, B)                                                                                                                       \
  do {                                                                                                                                                         \
    uint32_t a_ = (uint32_t)((A) >> 32);                                                                                                                       \
    uint32_t b_ = (uint32_t)(A);                                                                                                                               \
    uint32_t c_ = (uint32_t)((B) >> 32);                                                                                                                       \
    uint32_t d_ = (uint32_t)((B));                                                                                                                             \
    uint64_t ac_, bc_, ad_, bd_;                                                                                                                               \
    tabula_db_mul_u32_u32(ac_, a_, c_);                                                                                                                        \
    tabula_db_mul_u32_u32(bc_, b_, c_);                                                                                                                        \
    tabula_db_mul_u32_u32(ad_, a_, d_);                                                                                                                        \
    tabula_db_mul_u32_u32(bd_, b_, d_);                                                                                                                        \
    uint64_t intermediate_ = (bd_ >> 32) + (uint32_t)(ad_) + (uint32_t)(bc_);                                                                                  \
    OUT.high = ac_ + (intermediate_ >> 32) + (ad_ >> 32) + (bc_ >> 32);                                                                                        \
    OUT.low = (intermediate_ << 32) + (uint32_t)(bd_);                                                                                                         \
  } while(false)
#define tabula_db_mul_u64_u64_upper64(OUT, A, B)                                                                                                               \
  do {                                                                                                                                                         \
    uint32_t a_ = (uint32_t)((A) >> 32);                                                                                                                       \
    uint32_t b_ = (uint32_t)(A);                                                                                                                               \
    uint32_t c_ = (uint32_t)((B) >> 32);                                                                                                                       \
    uint32_t d_ = (uint32_t)((B));                                                                                                                             \
    uint64_t ac_, bc_, ad_, bd_;                                                                                                                               \
    tabula_db_mul_u32_u32(ac_, a_, c_);                                                                                                                        \
    tabula_db_mul_u32_u32(bc_, b_, c_);                                                                                                                        \
    tabula_db_mul_u32_u32(ad_, a_, d_);                                                                                                                        \
    tabula_db_mul_u32_u32(bd_, b_, d_);                                                                                                                        \
    uint64_t intermediate_ = (bd_ >> 32) + (uint32_t)(ad_) + (uint32_t)(bc_);                                                                                  \
    OUT = ac_ + (intermediate_ >> 32) + (ad_ >> 32) + (bc_ >> 32);                                                                                             \
  } while(false)
#define tabula_db_add_u128_u64(OUT, A, B)                                                                                                                      \
  do {                                                                                                                                                         \
    OUT.high = A.high + (A.low + B < A.low ? 1 : 0);                                                                                                           \
    OUT.low = A.low + B;                                                                                                                                       \
  } while(false)
#define tabula_db_mul_u64_u128_upper128(OUT, A, B)                                                                                                             \
  do {                                                                                                                                                         \
    tabula_db_mul_u64_u64(OUT, A, B.high);                                                                                                                     \
    uint64_t tabula_db_mul_u64_u128_upper128_temp_;                                                                                                            \
    tabula_db_mul_u64_u64_upper64(tabula_db_mul_u64_u128_upper128_temp_, A, B.low);                                                                            \
    tabula_db_add_u128_u64(OUT, OUT, tabula_db_mul_u64_u128_upper128_temp_);                                                                                   \
  } while(false)
#define tabula_db_mul_u64_u128_lower128(OUT, A, B)                                                                                                             \
  do {                                                                                                                                                         \
    tabula_db_mul_u64_u64(OUT, A, B.low);                                                                                                                      \
    OUT.high += A * B.high;                                                                                                                                    \
  } while(false)

#define tabula_db_divide_by_pow10(OUT, N, TYPE, MAX, n)                                                                                                        \
  do {                                                                                                                                                         \
    TYPE divisor_;                                                                                                                                             \
    tabula_db_compute_power(divisor_, N, TYPE, 10);                                                                                                            \
    OUT = n / divisor_;                                                                                                                                        \
  } while(false)

#define TABULA_DB_DIVINFO__MAGIC_NUMBER__2 656
#define TABULA_DB_DIVINFO__SHIFT_AMOUNT__2 16

#define tabula_db_check_divisibility_and_divide_by_pow10(OUT1, N, n)                                                                                           \
  do {                                                                                                                                                         \
    static uint32_t magic_number_ = TABULA_CAT2(TABULA_DB_DIVINFO__MAGIC_NUMBER__, N);                                                                         \
    static uint32_t shift_amount_ = TABULA_CAT2(TABULA_DB_DIVINFO__SHIFT_AMOUNT__, N);                                                                         \
    n *= magic_number_;                                                                                                                                        \
    OUT1 = (n & (((uint32_t)1 << shift_amount_) - 1)) < magic_number_;                                                                                         \
    n >>= shift_amount_;                                                                                                                                       \
  } while(false)

#define tabula_db_small_division_by_pow10(N, n) (((n)*TABULA_CAT2(TABULA_DB_DIVINFO__MAGIC_NUMBER__, N)) >> TABULA_CAT2(TABULA_DB_DIVINFO__SHIFT_AMOUNT__, N))

static uint32_t tabula_db_bits_rotr__uint32_t(uint32_t a, uint32_t b) {
  b &= 31;
  return (a >> b) | (a << (32 - b));
}

static uint64_t tabula_db_bits_rotr__uint64_t(uint64_t a, uint64_t b) {
  b &= 63;
  return (a >> b) | (a << (64 - b));
}

static int tabula_db_remove_trailing_zeros__binary64(uint64_t n, uint64_t *out_n) {
  /* ceil(2^90 / 10^8) */
  static uint64_t magic_number_ = 12379400392853802749ull;
  tabula_db_u128 nm_;
  tabula_db_mul_u64_u64(nm_, n, magic_number_);
  int s_;
  if((nm_.high & (((uint64_t)1 << (90 - 64)) - 1)) == 0 && nm_.low < magic_number_) {
    uint32_t q_;
    uint32_t n32_ = (uint32_t)(nm_.high >> (90 - 64));
    uint32_t mod_inv_5_ = 0xCCCCCCCD;
    uint32_t mod_inv_25_ = mod_inv_5_ * mod_inv_5_;
    s_ = 8;
    for(;;) {
      q_ = tabula_db_bits_rotr__uint32_t(n32_ * mod_inv_25_, 2);
      if(q_ <= UINT32_MAX / 100) {
        n32_ = q_;
        s_ += 2;
      } else {
        break;
      }
    }
    q_ = tabula_db_bits_rotr__uint32_t(n32_ * mod_inv_5_, 1);
    if(q_ <= UINT32_MAX / 100) {
      n32_ = q_;
      s_ |= 1;
    }
    *out_n = n32_;
    return s_;
  } else {
    uint64_t mod_inv_5_ = 0xCCCCCCCCCCCCCCCD;
    uint64_t mod_inv_25_ = mod_inv_5_ * mod_inv_5_;
    uint64_t q_;
    s_ = 0;
    for(;;) {
      q_ = tabula_db_bits_rotr__uint64_t(n * mod_inv_25_, 2);
      if(q_ <= UINT64_MAX / 100) {
        n = q_;
        s_ += 2;
      } else {
        break;
      }
    }
    q_ = tabula_db_bits_rotr__uint64_t(n * mod_inv_5_, 1);
    if(q_ <= UINT64_MAX / 100) {
      n = q_;
      s_ |= 1;
    }
    *out_n = n;
    return s_;
  }
}
#define tabula_db_remove_trailing_zeros(OUT, TYPE, N)                                                                                                          \
  do {                                                                                                                                                         \
    OUT = TABULA_CAT2(tabula_db_remove_trailing_zeros__, TYPE)(N, &N);                                                                                         \
  } while(false)

#define tabula_db_compute_mul__binary64(OUT1, OUT2, TYPE, U, CACHE)                                                                                            \
  do {                                                                                                                                                         \
    tabula_db_u128 r_;                                                                                                                                         \
    tabula_db_mul_u64_u128_upper128(r_, U, CACHE);                                                                                                             \
    OUT1 = r_.high;                                                                                                                                            \
    OUT2 = r_.low == 0;                                                                                                                                        \
  } while(false)
#define tabula_db_compute_mul(OUT1, OUT2, TYPE, U, CACHE) TABULA_CAT2(tabula_db_compute_mul__, TYPE)(OUT1, OUT2, TYPE, U, CACHE)

#define tabula_db_compute_delta__binary64(TYPE, CACHE, BETA) ((uint32_t)(CACHE.high >> (128 - 1 - BETA)))
#define tabula_db_compute_delta(TYPE, CACHE, BETA) TABULA_CAT2(tabula_db_compute_delta__, TYPE)(TYPE, CACHE, BETA)

#define tabula_db_compute_mul_parity__binary64(OUT1, OUT2, TYPE, TWO_F, CACHE, BETA)                                                                           \
  do {                                                                                                                                                         \
    tabula_db_u128 r_;                                                                                                                                         \
    tabula_db_mul_u64_u128_lower128(r_, TWO_F, CACHE);                                                                                                         \
    OUT1 = ((r_.high >> (64 - BETA)) & 1) != 0;                                                                                                                \
    OUT2 = ((r_.high << BETA) | (r_.low >> (64 - BETA))) == 0;                                                                                                 \
  } while(false)
#define tabula_db_compute_mul_parity(OUT1, OUT2, TYPE, TWO_F, CACHE, BETA)                                                                                     \
  TABULA_CAT2(tabula_db_compute_mul_parity__, TYPE)(OUT1, OUT2, TYPE, TWO_F, CACHE, BETA)

#define tabula_db_compute_left_endpoint_for_shorter_interval_case__binary64(TYPE, CACHE, BETA)                                                                 \
  (CACHE.high - (CACHE.high >> (TABULA_DB_TYPE_SIGNFICAND_BITS(TYPE) + 2))) >> (128 - TABULA_DB_TYPE_SIGNFICAND_BITS(TYPE) - 1 - BETA)
#define tabula_db_compute_left_endpoint_for_shorter_interval_case(TYPE, CACHE, BETA)                                                                           \
  TABULA_CAT2(tabula_db_compute_left_endpoint_for_shorter_interval_case__, TYPE)                                                                               \
  (TYPE, CACHE, BETA)

#define tabula_db_compute_right_endpoint_for_shorter_interval_case__binary64(TYPE, CACHE, BETA)                                                                \
  (CACHE.high - (CACHE.high >> (TABULA_DB_TYPE_SIGNFICAND_BITS(TYPE) + 1))) >> (128 - TABULA_DB_TYPE_SIGNFICAND_BITS(TYPE) - 1 - BETA)
#define tabula_db_compute_right_endpoint_for_shorter_interval_case(TYPE, CACHE, BETA)                                                                          \
  TABULA_CAT2(tabula_db_compute_right_endpoint_for_shorter_interval_case__, TYPE)                                                                              \
  (TYPE, CACHE, BETA)

#define tabula_db_compute_round_up_for_shorter_interval_case__binary64(TYPE, CACHE, BETA)                                                                      \
  (CACHE.high - (CACHE.high >> (TABULA_DB_TYPE_SIGNFICAND_BITS(TYPE) + 1))) >> (128 - TABULA_DB_TYPE_SIGNFICAND_BITS(TYPE) - 1 - BETA)
#define tabula_db_compute_round_up_for_shorter_interval_case(TYPE, CACHE, BETA)                                                                                \
  TABULA_CAT2(tabula_db_compute_right_endpoint_for_shorter_interval_case__, TYPE)                                                                              \
  (TYPE, CACHE, BETA)

static bool tabula_db_is_right_endpoint_integer_shorter_interval__binary64(int exponent) {
  static int case_shorter_interval_right_endpoint_lower_threshold = 0;
  static int case_shorter_interval_right_endpoint_upper_threshold = 0;
  if(case_shorter_interval_right_endpoint_upper_threshold == 0) {
    int factor, power;
    tabula_db_count_factors(factor, 5, int, ((uint64_t)(1) << (TABULA_DB_TYPE_SIGNFICAND_BITS(binary64) + 2)) - 1);
    factor += 1;
    tabula_db_compute_power(power, factor, int, 10);
    power /= 3;
    tabula_db_floor_log2(case_shorter_interval_right_endpoint_upper_threshold, int, power);
    case_shorter_interval_right_endpoint_upper_threshold += 2;
  }
  return exponent >= case_shorter_interval_right_endpoint_lower_threshold && exponent <= case_shorter_interval_right_endpoint_upper_threshold;
}
#define tabula_db_is_right_endpoint_integer_shorter_interval(TYPE, exponent)                                                                                   \
  TABULA_CAT2(tabula_db_is_right_endpoint_integer_shorter_interval__, TYPE)                                                                                    \
  (exponent)

static bool tabula_db_is_left_endpoint_integer_shorter_interval__binary64(int exponent) {
  static int case_shorter_interval_left_endpoint_lower_threshold = 2;
  static int case_shorter_interval_left_endpoint_upper_threshold = 0;
  if(case_shorter_interval_left_endpoint_upper_threshold == 0) {
    int factor, power;
    tabula_db_count_factors(factor, 5, int, ((uint64_t)(1) << (TABULA_DB_TYPE_SIGNFICAND_BITS(binary64) + 2)) - 1);
    factor += 1;
    tabula_db_compute_power(power, factor, int, 10);
    power /= 3;
    tabula_db_floor_log2(case_shorter_interval_left_endpoint_upper_threshold, int, power);
    case_shorter_interval_left_endpoint_upper_threshold += 2;
  }
  return exponent >= case_shorter_interval_left_endpoint_lower_threshold && exponent <= case_shorter_interval_left_endpoint_upper_threshold;
}
#define tabula_db_is_left_endpoint_integer_shorter_interval(TYPE, exponent)                                                                                    \
  TABULA_CAT2(tabula_db_is_left_endpoint_integer_shorter_interval__, TYPE)                                                                                     \
  (exponent)

static bool tabula_db_is_shorter_interval_tie__binary64(int exponent) {
  static int shorter_interval_tie_lower_threshold = 0;
  static int shorter_interval_tie_upper_threshold = 0;
  if(shorter_interval_tie_lower_threshold == 0) {
    shorter_interval_tie_lower_threshold =
        -tabula_db_floor_log5_pow2_minus_log5_3(TABULA_DB_TYPE_SIGNFICAND_BITS(binary64) + 4) - 2 - TABULA_DB_TYPE_SIGNFICAND_BITS(binary64);
  }
  if(shorter_interval_tie_upper_threshold == 0) {
    shorter_interval_tie_upper_threshold =
        -tabula_db_floor_log5_pow2(TABULA_DB_TYPE_SIGNFICAND_BITS(binary64) + 2) - 2 - TABULA_DB_TYPE_SIGNFICAND_BITS(binary64);
  }
  return exponent >= shorter_interval_tie_lower_threshold && exponent <= shorter_interval_tie_upper_threshold;
}
#define tabula_db_is_shorter_interval_tie(TYPE, exponent) TABULA_CAT2(tabula_db_is_shorter_interval_tie__, TYPE)(exponent)

// TRAILING_ZERO
#define TABULA_DB__TRAILING_ZERO__ON_TRAILING_ZEROS__ignore(TYPE)                                                                                              \
  do {                                                                                                                                                         \
  } while(false)
#define TABULA_DB__TRAILING_ZERO__ON_TRAILING_ZEROS__remove(TYPE)                                                                                              \
  do {                                                                                                                                                         \
    int out_exp;                                                                                                                                               \
    tabula_db_remove_trailing_zeros(out_exp, TYPE, ret_significand);                                                                                           \
    ret_exponent += out_exp;                                                                                                                                   \
  } while(false)

#define TABULA_DB__TRAILING_ZERO_ON_TRAILING_ZEROS(TRAILING_ZERO, TYPE) TABULA_CAT2(TABULA_DB__TRAILING_ZERO__ON_TRAILING_ZEROS__, TRAILING_ZERO)(TYPE)
#define TABULA_DB__TRAILING_ZERO_NO_TRAILING_ZEROS(TRAILING_ZERO, TYPE)                                                                                        \
  do {                                                                                                                                                         \
  } while(false)

// DEC_TO_BIN
#define TABULA_DB__DEC_TO_BIN__TAG__TO_NEAREST 0
#define TABULA_DB__DEC_TO_BIN__TAG__LEFT_CLOSED 1
#define TABULA_DB__DEC_TO_BIN__TAG__RIGHT_CLOSED 2

#define TABULA_DB__DEC_TO_BIN__GET_TAG__nearest_to_even TABULA_DB__DEC_TO_BIN__TAG__TO_NEAREST
#define TABULA_DB__DEC_TO_BIN__SHORT__nearest_to_even closed
#define TABULA_DB__DEC_TO_BIN__NORMAL__nearest_to_even symmetric_boundary((bits_sign_significand % 2) == 0)

#define TABULA_DB__DEC_TO_BIN__GET_TAG__nearest_to_odd TABULA_DB__DEC_TO_BIN__TAG__TO_NEAREST
#define TABULA_DB__DEC_TO_BIN__SHORT__nearest_to_odd open
#define TABULA_DB__DEC_TO_BIN__NORMAL__nearest_to_odd symmetric_boundary((bits_sign_significand % 2) != 0)

#define TABULA_DB__DEC_TO_BIN__GET_TAG__nearest_toward_plus_infinity TABULA_DB__DEC_TO_BIN__TAG__TO_NEAREST
#define TABULA_DB__DEC_TO_BIN__SHORT__nearest_toward_plus_infinity asymmetric_boundary((bits_sign_significand & ((uint64_t)1 << 63)) == 0)
#define TABULA_DB__DEC_TO_BIN__NORMAL__nearest_toward_plus_infinity asymmetric_boundary((bits_sign_significand & ((uint64_t)1 << 63)) == 0)

#define TABULA_DB__DEC_TO_BIN__GET_TAG__nearest_toward_minus_infinity TABULA_DB__DEC_TO_BIN__TAG__TO_NEAREST
#define TABULA_DB__DEC_TO_BIN__SHORT__nearest_toward_minus_infinity asymmetric_boundary((bits_sign_significand & ((uint64_t)1 << 63)) != 0)
#define TABULA_DB__DEC_TO_BIN__NORMAL__nearest_toward_minus_infinity asymmetric_boundary((bits_sign_significand & ((uint64_t)1 << 63)) != 0)

#define TABULA_DB__DEC_TO_BIN__GET_TAG__nearest_toward_zero TABULA_DB__DEC_TO_BIN__TAG__TO_NEAREST
#define TABULA_DB__DEC_TO_BIN__SHORT__nearest_toward_zero right_closed_left_open
#define TABULA_DB__DEC_TO_BIN__NORMAL__nearest_toward_zero right_closed_left_open

#define TABULA_DB__DEC_TO_BIN__GET_TAG__nearest_away_from_zero TABULA_DB__DEC_TO_BIN__TAG__TO_NEAREST
#define TABULA_DB__DEC_TO_BIN__SHORT__nearest_away_from_zero left_closed_right_open
#define TABULA_DB__DEC_TO_BIN__NORMAL__nearest_away_from_zero left_closed_right_open

#define TABULA_DB__DEC_TO_BIN_GET_TAG(DEC_TO_BIN) TABULA_CAT2(TABULA_DB__DEC_TO_BIN__GET_TAG__, DEC_TO_BIN)
#define TABULA_DB__DEC_TO_BIN_SHORT(DEC_TO_BIN) TABULA_CAT2(TABULA_DB__DEC_TO_BIN__SHORT__, DEC_TO_BIN)
#define TABULA_DB__DEC_TO_BIN_NORMAL(DEC_TO_BIN) TABULA_CAT2(TABULA_DB__DEC_TO_BIN__NORMAL__, DEC_TO_BIN)

// INTERVAL
#define TABULA_DB__INTERVAL__IS_SYMMETRIC__symmetric_boundary(IS_CLOSED) true
#define TABULA_DB__INTERVAL__INCLUDE_LEFT__symmetric_boundary(IS_CLOSED) (IS_CLOSED)
#define TABULA_DB__INTERVAL__INCLUDE_RIGHT__symmetric_boundary(IS_CLOSED) (IS_CLOSED)

#define TABULA_DB__INTERVAL__IS_SYMMETRIC__asymmetric_boundary(IS_LEFT_CLOSED) false
#define TABULA_DB__INTERVAL__INCLUDE_LEFT__asymmetric_boundary(IS_LEFT_CLOSED) (IS_LEFT_CLOSED)
#define TABULA_DB__INTERVAL__INCLUDE_RIGHT__asymmetric_boundary(IS_LEFT_CLOSED) (!(IS_LEFT_CLOSED))

#define TABULA_DB__INTERVAL__IS_SYMMETRIC__closed true
#define TABULA_DB__INTERVAL__INCLUDE_LEFT__closed true
#define TABULA_DB__INTERVAL__INCLUDE_RIGHT__closed true

#define TABULA_DB__INTERVAL__IS_SYMMETRIC__open true
#define TABULA_DB__INTERVAL__INCLUDE_LEFT__open false
#define TABULA_DB__INTERVAL__INCLUDE_RIGHT__open false

#define TABULA_DB__INTERVAL__IS_SYMMETRIC__left_closed_right_open false
#define TABULA_DB__INTERVAL__INCLUDE_LEFT__left_closed_right_open true
#define TABULA_DB__INTERVAL__INCLUDE_RIGHT__left_closed_right_open false

#define TABULA_DB__INTERVAL__IS_SYMMETRIC__right_closed_left_open false
#define TABULA_DB__INTERVAL__INCLUDE_LEFT__right_closed_left_open false
#define TABULA_DB__INTERVAL__INCLUDE_RIGHT__right_closed_left_open true

#define TABULA_DB__INTERVAL_IS_SYMMETRIC(INTERVAL) TABULA_CAT2(TABULA_DB__INTERVAL__IS_SYMMETRIC__, INTERVAL)
#define TABULA_DB__INTERVAL_INCLUDE_LEFT(INTERVAL) TABULA_CAT2(TABULA_DB__INTERVAL__INCLUDE_LEFT__, INTERVAL)
#define TABULA_DB__INTERVAL_INCLUDE_RIGHT(INTERVAL) TABULA_CAT2(TABULA_DB__INTERVAL__INCLUDE_RIGHT__, INTERVAL)

// BIN_TO_DEC
#define TABULA_DB__BIN_TO_DEC__TAG__DO_NOT_CARE 0
#define TABULA_DB__BIN_TO_DEC__TAG__TO_EVEN 1
#define TABULA_DB__BIN_TO_DEC__TAG__TO_ODD 2
#define TABULA_DB__BIN_TO_DEC__TAG__AWAY_FROM_ZERO 3
#define TABULA_DB__BIN_TO_DEC__TAG__TOWARD_ZERO 4

#define TABULA_DB__BIN_TO_DEC__GET_TAG__do_not_care TABULA_DB__BIN_TO_DEC__TAG__DO_NOT_CARE
#define TABULA_DB__BIN_TO_DEC__ROUND_DOWN__do_not_care false

#define TABULA_DB__BIN_TO_DEC__GET_TAG__to_even TABULA_DB__BIN_TO_DEC__TAG__TO_EVEN
#define TABULA_DB__BIN_TO_DEC__ROUND_DOWN__to_even ((ret_significand % 2) != 0)

#define TABULA_DB__BIN_TO_DEC__GET_TAG__to_odd TABULA_DB__BIN_TO_DEC__TAG__TO_ODD
#define TABULA_DB__BIN_TO_DEC__ROUND_DOWN__to_odd ((ret_significand % 2) == 0)

#define TABULA_DB__BIN_TO_DEC__GET_TAG__to_odd TABULA_DB__BIN_TO_DEC__TAG__TO_ODD
#define TABULA_DB__BIN_TO_DEC__ROUND_DOWN__to_odd ((ret_significand % 2) == 0)

#define TABULA_DB__BIN_TO_DEC__GET_TAG__away_from_zero TABULA_DB__BIN_TO_DEC__TAG__AWAY_FROM_ZERO
#define TABULA_DB__BIN_TO_DEC__ROUND_DOWN__away_from_zero false

#define TABULA_DB__BIN_TO_DEC__GET_TAG__toward_zero TABULA_DB__BIN_TO_DEC__TAG__AWAY_FROM_ZERO
#define TABULA_DB__BIN_TO_DEC__ROUND_DOWN__toward_zero true

#define TABULA_DB__BIN_TO_DEC_GET_TAG(BIN_TO_DEC) TABULA_CAT2(TABULA_DB__BIN_TO_DEC__GET_TAG__, BIN_TO_DEC)
#define TABULA_DB__BIN_TO_DEC_ROUND_DOWN(BIN_TO_DEC) TABULA_CAT2(TABULA_DB__BIN_TO_DEC__ROUND_DOWN__, BIN_TO_DEC)

// SETTINGS HERE
enum tabula_db_dec_to_bin {
  tabula_db_dec_to_bin__nearest_to_even,
  tabula_db_dec_to_bin__nearest_to_odd,
  tabula_db_dec_to_bin__nearest_toward_plus_infinity,
  tabula_db_dec_to_bin__nearest_toward_minus_infinity,
  tabula_db_dec_to_bin__nearest_toward_zero,
  tabula_db_dec_to_bin__nearest_away_from_zero
};

enum tabula_db_bin_to_dec {
  tabula_db_bin_to_dec__do_not_care,
  tabula_db_bin_to_dec__to_even,
  tabula_db_bin_to_dec__to_odd,
  tabula_db_bin_to_dec__away_from_zero,
  tabula_db_bin_to_dec__toward_zero
};

enum tabula_db_trailing_zero { tabula_db_trailing_zero__ignore, tabula_db_trailing_zero__remove };

#define TABULA_DB_IMPL(NAME, TYPE, DEC_TO_BIN, BIN_TO_DEC, TRAILING_ZERO)                                                                                      \
  static void NAME(double input, uint64_t *result_significand, int *result_exponent) {                                                                         \
    uint64_t bits = *(uint64_t *)&input;                                                                                                                       \
    uint64_t bits_exponent = (bits >> TABULA_DB_TYPE_SIGNFICAND_BITS(TYPE)) & TABULA_DB_TYPE_EXPONENT_BITS_MASK(TYPE);                                         \
    uint64_t bits_sign_significand = bits ^ (bits_exponent << TABULA_DB_TYPE_SIGNFICAND_BITS(TYPE));                                                           \
    uint64_t ret_significand;                                                                                                                                  \
    int ret_exponent;                                                                                                                                          \
    if(TABULA_DB__DEC_TO_BIN_GET_TAG(DEC_TO_BIN) == TABULA_DB__DEC_TO_BIN__TAG__TO_NEAREST) {                                                                  \
      uint64_t two_fc = bits_sign_significand << 1;                                                                                                            \
      int exponent = (int)bits_exponent;                                                                                                                       \
      if(exponent != 0) {                                                                                                                                      \
        exponent += TABULA_DB_TYPE_EXPONENT_BIAS(TYPE) - TABULA_DB_TYPE_SIGNFICAND_BITS(TYPE);                                                                 \
        if(two_fc == 0) {                                                                                                                                      \
          /* Compute k and beta */                                                                                                                             \
          const int minus_k = tabula_db_floor_log10_pow2_minus_log10_4_over_3(exponent);                                                                       \
          const int beta = exponent + tabula_db_floor_log2_pow10(-minus_k);                                                                                    \
          /* Compute xi and zi */                                                                                                                              \
          tabula_db_u128 cache = tabula_db_get_binary64_cache(-minus_k);                                                                                       \
          uint64_t xi = tabula_db_compute_left_endpoint_for_shorter_interval_case(TYPE, cache, beta);                                                          \
          uint64_t zi = tabula_db_compute_right_endpoint_for_shorter_interval_case(TYPE, cache, beta);                                                         \
          /* rounding rules */                                                                                                                                 \
          if(!TABULA_DB__INTERVAL_INCLUDE_RIGHT(TABULA_DB__DEC_TO_BIN_SHORT(DEC_TO_BIN)) &&                                                                    \
             tabula_db_is_right_endpoint_integer_shorter_interval(TYPE, exponent)) {                                                                           \
            zi--;                                                                                                                                              \
          }                                                                                                                                                    \
          if(!TABULA_DB__INTERVAL_INCLUDE_LEFT(TABULA_DB__DEC_TO_BIN_SHORT(DEC_TO_BIN)) &&                                                                     \
             tabula_db_is_left_endpoint_integer_shorter_interval(TYPE, exponent)) {                                                                            \
            xi++;                                                                                                                                              \
          }                                                                                                                                                    \
          /* Try bigger divisor */                                                                                                                             \
          ret_significand = zi / 10;                                                                                                                           \
          if(ret_significand * 10 >= xi) {                                                                                                                     \
            ret_exponent = minus_k + 1;                                                                                                                        \
            TABULA_DB__TRAILING_ZERO_ON_TRAILING_ZEROS(TRAILING_ZERO, TYPE);                                                                                   \
            goto done;                                                                                                                                         \
          }                                                                                                                                                    \
          TABULA_DB__TRAILING_ZERO_NO_TRAILING_ZEROS(TRAILING_ZERO, TYPE);                                                                                     \
          ret_significand = tabula_db_compute_round_up_for_shorter_interval_case(TYPE, cache, beta);                                                           \
          ret_exponent = minus_k;                                                                                                                              \
          if(TABULA_DB__BIN_TO_DEC_ROUND_DOWN(BIN_TO_DEC) && tabula_db_is_shorter_interval_tie(TYPE, exponent)) {                                              \
            ret_significand--;                                                                                                                                 \
          } else if(ret_significand < xi) {                                                                                                                    \
            ret_significand++;                                                                                                                                 \
          }                                                                                                                                                    \
          goto done;                                                                                                                                           \
        }                                                                                                                                                      \
        two_fc |= ((uint64_t)1 << (TABULA_DB_TYPE_SIGNFICAND_BITS(TYPE) + 1));                                                                                 \
      } else {                                                                                                                                                 \
        exponent = TABULA_DB_TYPE_MIN_EXPONENT(TYPE) - TABULA_DB_TYPE_SIGNFICAND_BITS(TYPE);                                                                   \
      }                                                                                                                                                        \
      /* step 1: Schubfach multiplier calculation */                                                                                                           \
      int minus_k = tabula_db_floor_log10_pow2(exponent) - TABULA_DB_TYPE_KAPPA(TYPE);                                                                         \
      tabula_db_u128 cache = tabula_db_get_binary64_cache(-minus_k);                                                                                           \
      int beta = exponent + tabula_db_floor_log2_pow10(-minus_k);                                                                                              \
      uint32_t deltai = tabula_db_compute_delta(TYPE, cache, beta);                                                                                            \
      uint64_t zi;                                                                                                                                             \
      bool is_z_integer;                                                                                                                                       \
      tabula_db_compute_mul(zi, is_z_integer, TYPE, (two_fc | 1) << beta, cache);                                                                              \
      /* Step 2: Try larger divisor; remove trailing zeros if necessary */                                                                                     \
      uint32_t big_divisor;                                                                                                                                    \
      tabula_db_compute_power(big_divisor, TABULA_DB_TYPE_KAPPA(TYPE) + 1, uint32_t, 10);                                                                      \
      uint32_t small_divisor;                                                                                                                                  \
      tabula_db_compute_power(small_divisor, TABULA_DB_TYPE_KAPPA(TYPE), uint32_t, 10);                                                                        \
      ret_significand;                                                                                                                                         \
      tabula_db_divide_by_pow10(ret_significand, TABULA_DB_TYPE_KAPPA(TYPE) + 1, uint64_t,                                                                     \
                                ((uint64_t)1 << (TABULA_DB_TYPE_SIGNFICAND_BITS(TYPE) + 1)) * big_divisor - 1, zi);                                            \
      uint32_t r = (uint32_t)(zi - big_divisor * ret_significand);                                                                                             \
      if(r < deltai) {                                                                                                                                         \
        if(r == 0 && (is_z_integer & !TABULA_DB__INTERVAL_INCLUDE_RIGHT(TABULA_DB__DEC_TO_BIN_NORMAL(DEC_TO_BIN)))) {                                          \
          if(TABULA_DB__BIN_TO_DEC_GET_TAG(BIN_TO_DEC) == TABULA_DB__BIN_TO_DEC__TAG__DO_NOT_CARE) {                                                           \
            ret_significand *= 10;                                                                                                                             \
            ret_exponent = minus_k + TABULA_DB_TYPE_KAPPA(TYPE);                                                                                               \
            ret_significand--;                                                                                                                                 \
            TABULA_DB__TRAILING_ZERO_NO_TRAILING_ZEROS(TRAILING_ZERO, TYPE);                                                                                   \
            goto done;                                                                                                                                         \
          }                                                                                                                                                    \
          ret_significand--;                                                                                                                                   \
          r = big_divisor;                                                                                                                                     \
          goto normal_small;                                                                                                                                   \
        }                                                                                                                                                      \
      } else if(r > deltai) {                                                                                                                                  \
        goto normal_small;                                                                                                                                     \
      } else {                                                                                                                                                 \
        bool xi_parity;                                                                                                                                        \
        bool is_x_integer;                                                                                                                                     \
        uint64_t two_fc_minus_one = two_fc - 1;                                                                                                                \
        tabula_db_compute_mul_parity(xi_parity, is_x_integer, TYPE, two_fc_minus_one, cache, beta);                                                            \
        if(!(xi_parity | (is_x_integer && TABULA_DB__INTERVAL_INCLUDE_LEFT(TABULA_DB__DEC_TO_BIN_NORMAL(DEC_TO_BIN))))) {                                      \
          goto normal_small;                                                                                                                                   \
        }                                                                                                                                                      \
      }                                                                                                                                                        \
      ret_exponent = minus_k + TABULA_DB_TYPE_KAPPA(TYPE) + 1;                                                                                                 \
      TABULA_DB__TRAILING_ZERO_ON_TRAILING_ZEROS(TRAILING_ZERO, TYPE);                                                                                         \
      goto done;                                                                                                                                               \
      /* step 3 : find the significand with the smaller divisor */                                                                                             \
    normal_small:                                                                                                                                              \
      TABULA_DB__TRAILING_ZERO_NO_TRAILING_ZEROS(TRAILING_ZERO, TYPE);                                                                                         \
      ret_significand *= 10;                                                                                                                                   \
      ret_exponent = minus_k + TABULA_DB_TYPE_KAPPA(TYPE);                                                                                                     \
      if(TABULA_DB__BIN_TO_DEC_GET_TAG(BIN_TO_DEC) == TABULA_DB__BIN_TO_DEC__TAG__DO_NOT_CARE) {                                                               \
        if(!TABULA_DB__INTERVAL_INCLUDE_RIGHT(TABULA_DB__DEC_TO_BIN_NORMAL(DEC_TO_BIN))) {                                                                     \
          bool is_divisible;                                                                                                                                   \
          uint32_t r_temp = r;                                                                                                                                 \
          tabula_db_check_divisibility_and_divide_by_pow10(is_divisible, TABULA_DB_TYPE_KAPPA(TYPE), r_temp);                                                  \
          if(is_z_integer && is_divisible) {                                                                                                                   \
            ret_significand += r_temp - 1;                                                                                                                     \
          } else {                                                                                                                                             \
            ret_significand += is_z_integer ? r_temp : r;                                                                                                      \
          }                                                                                                                                                    \
        } else {                                                                                                                                               \
          ret_significand += tabula_db_small_division_by_pow10(TABULA_DB_TYPE_KAPPA(TYPE), r);                                                                 \
        }                                                                                                                                                      \
      } else {                                                                                                                                                 \
        uint32_t dist = r - (deltai / 2) + (small_divisor / 2);                                                                                                \
        bool approx_y_parity = ((dist ^ (small_divisor / 2)) & 1) != 0;                                                                                        \
        bool divisible_by_small_divisor;                                                                                                                       \
        tabula_db_check_divisibility_and_divide_by_pow10(divisible_by_small_divisor, TABULA_DB_TYPE_KAPPA(TYPE), dist);                                        \
        ret_significand += dist;                                                                                                                               \
        if(divisible_by_small_divisor) {                                                                                                                       \
          bool yi_parity;                                                                                                                                      \
          bool is_y_integer;                                                                                                                                   \
          tabula_db_compute_mul_parity(yi_parity, is_y_integer, TYPE, two_fc, cache, beta);                                                                    \
          if(yi_parity != approx_y_parity) {                                                                                                                   \
            ret_significand--;                                                                                                                                 \
          } else if(is_y_integer && TABULA_DB__BIN_TO_DEC_ROUND_DOWN(BIN_TO_DEC)) {                                                                            \
            ret_significand--;                                                                                                                                 \
          }                                                                                                                                                    \
        }                                                                                                                                                      \
      }                                                                                                                                                        \
    } else if(TABULA_DB__DEC_TO_BIN_GET_TAG(DEC_TO_BIN) == TABULA_DB__DEC_TO_BIN__TAG__LEFT_CLOSED) {                                                          \
    } else if(TABULA_DB__DEC_TO_BIN_GET_TAG(DEC_TO_BIN) == TABULA_DB__DEC_TO_BIN__TAG__RIGHT_CLOSED) {                                                         \
    }                                                                                                                                                          \
  done:                                                                                                                                                        \
    *result_significand = ret_significand;                                                                                                                     \
    *result_exponent = ret_exponent;                                                                                                                           \
  }

TABULA_DB_IMPL(tabula_dragonbox_binary64, binary64, nearest_to_even, to_even, remove)
// end of detour into dragonbox
// ============================================================================================================================================================

static char *tabula_format_emit_double(char *end, double value, bool f_hash, int32_t precision, enum tabula_format_style style) {
  char output_case = style - 'A';                     // offset to go from uppercase to expected case
  enum tabula_format_style lower_style = style | ' '; // bit or to go from uppercase to lowercase
  if(isnan(value)) {
    *--end = output_case + 'N';
    *--end = output_case + 'A';
    *--end = output_case + 'N';
  } else if(isinf(value)) {
    *--end = output_case + 'F';
    *--end = output_case + 'N';
    *--end = output_case + 'I';
  } else {
    value = fabs(value);
    if(precision < 0) {
      precision = 6;
    } else if(precision == 0) {
      precision = 1;
    }

    uint64_t significand;
    int exponent;
    tabula_dragonbox_binary64(value, &significand, &exponent);

    // remove zeros
    do {
      uint64_t d_value = significand % 10;
      if(d_value) {
        break;
      }
      significand /= 10;
      exponent++;
    } while(significand && exponent < 0);

    // e form -- raise exponent until significand would be zero
    // only e_exponent is used
    uint64_t e_significand = significand;
    int e_exponent = exponent;
    unsigned int X = 0;
    if(lower_style == tabula_format_style_float_auto || lower_style == tabula_format_style_float_standard) {
      while(e_significand) {
        e_significand /= 10;
        X++;
      }
      X--;
      e_exponent -= X;
    }

    // logic for g/G
    if(lower_style == tabula_format_style_float_auto) {
      if(precision > X) {
        style -= 'g' - 'f';
        precision -= X;
      } else {
        style -= 'g' - 'e';
        precision--;
      }
      lower_style = style | ' ';
    }

    // draw exponent part
    if(lower_style == tabula_format_style_float_standard) {
      end = tabula_format_emit_int32(end, -e_exponent, 2);
      end = tabula_format_emit_int32_prefix(end, -e_exponent, true, false);
      *--end = style;
      exponent = e_exponent;
    }

    bool emitted = false;

    if(-exponent > precision) {
      // the . is too far away for the requested precision, pop some digits
      while(-exponent > precision) {
        significand /= 10;
        exponent++;
      }
    } else if(-exponent < precision) {
      // the . is behind the requested precision, pad with zeros by emitting them. reducing precision
      while(precision > 0 && -exponent < precision) {
        *--end = '0';
        precision--;
      }

      emitted = true;
    }

    // fraction digits to .
    while(significand && exponent < 0) {
      uint64_t d_value = significand % 10;
      significand /= 10;
      exponent++;
      *--end = '0' + d_value;
      emitted = true;
    }

    // fraction digits end
    if(emitted || f_hash) {
      *--end = '.';
    }

    // draw integer part
    end = tabula_format_emit_int64_unsigned_dec_imprecise(end, significand);
  }
  return end;
}
static uint32_t tabula_format_emit_double_prefix_count(double value, bool f_plus, bool f_space) {
  bool negative = value < (double)0;
  return (value < (double)0) || f_plus || f_space ? 1 : 0;
}
static char *tabula_format_emit_double_prefix(char *end, double value, bool f_plus, bool f_space) {
  if(value < (double)0) {
    *--end = '-';
  } else if(f_plus) {
    *--end = '+';
  } else if(f_space) {
    *--end = ' ';
  }
  return end;
}

struct tabula_format_position {
  va_list ap;
  uint8_t size;
};

static const char tabula_format_sixty_spaces[] = "                                                            ";
static const char tabula_format_sixty_zeros[] = "000000000000000000000000000000000000000000000000000000000000";

static inline unsigned int tabula_format_do_emit(void (*emit)(const uint8_t *ptr, size_t length, void *ud), void *ud, unsigned int limit, const uint8_t *ptr,
                                                 unsigned int length, unsigned int have_written) {
  if(have_written < limit) {
    unsigned int emit_length = have_written + length > limit ? limit - have_written : length;
    emit(ptr, emit_length, ud);
  }
  return length;
}

static inline bool tabula_format_parse_placeholder(const char *format, struct tabula_format_placeholder *parsed, const char **end) {
  memset(parsed, 0, sizeof(*parsed));
  parsed->parameter = TABULA_FORMAT_UNDEFINED;
  parsed->width = TABULA_FORMAT_UNDEFINED;
  parsed->precision = TABULA_FORMAT_UNDEFINED;

  const char *param_start = format;
  if(tabula_format_is_digit(*format)) {
    int32_t parameter = (int32_t)tabula_format_atod(format, &format);
    if(*format == '$') {
      format++;
      parsed->parameter = parameter - 1;
    } else {
      format = param_start;
    }
  }

  for(;;) {
    if(*format == '-') {
      parsed->flag_minus = 1;
      format++;
      continue;
    }
    if(*format == '+') {
      parsed->flag_plus = 1;
      format++;
      continue;
    }
    if(*format == ' ') {
      parsed->flag_space = 1;
      format++;
      continue;
    }
    if(*format == '0') {
      parsed->flag_zero = 1;
      format++;
      continue;
    }
    if(*format == '\'') {
      parsed->flag_apostrophe = 1;
      format++;
      continue;
    }
    if(*format == '#') {
      parsed->flag_hash = 1;
      format++;
      continue;
    }
    break;
  }

  if(parsed->parameter == TABULA_FORMAT_UNDEFINED && *format == '*') {
    parsed->width_dynamic = 1;
    parsed->width = 0;
    format++;
  } else if(tabula_format_is_digit(*format)) {
    parsed->width = (int32_t)tabula_format_atoi(format, &format);
  }

  if(*format == '.') {
    format++;
    parsed->flag_zero = 0;
    parsed->precision = 0;
    if(parsed->parameter == TABULA_FORMAT_UNDEFINED && *format == '*') {
      parsed->precision_dynamic = 1;
      format++;
    } else {
      parsed->precision = (int32_t)tabula_format_atoi(format, &format);
    }
  }

  switch(*format) {
  case 'h':
    format++;
    if(*format == 'h') {
      format++;
      parsed->length = tabula_format_hh;
    } else {
      parsed->length = tabula_format_h;
    }
    break;
  case 'l':
    format++;
    if(*format == 'l') {
      format++;
      parsed->length = tabula_format_ll;
    } else {
      parsed->length = tabula_format_l;
    }
    break;
  case 'L':
    format++;
    parsed->length = tabula_format_L;
    break;
  case 'z':
    format++;
    parsed->length = tabula_format_z;
    break;
  case 'j':
    format++;
    parsed->length = tabula_format_j;
    break;
  case 't':
    format++;
    parsed->length = tabula_format_t;
    break;
  }

  parsed->style = *format;
  switch(*format) {
  case 'd':
    parsed->datatype = tabula_format_datatype_signed_integer;
    break;
  case 'i':
    parsed->datatype = tabula_format_datatype_signed_integer;
    break;
  case 'u':
    parsed->datatype = tabula_format_datatype_unsigned_integer;
    break;
  case 'f':
    parsed->datatype = tabula_format_datatype_double;
    break;
  case 'F':
    parsed->datatype = tabula_format_datatype_double;
    break;
  case 'e':
    parsed->datatype = tabula_format_datatype_double;
    break;
  case 'E':
    parsed->datatype = tabula_format_datatype_double;
    break;
  case 'g':
    parsed->datatype = tabula_format_datatype_double;
    break;
  case 'G':
    parsed->datatype = tabula_format_datatype_double;
    break;
  case 'x':
    parsed->datatype = tabula_format_datatype_unsigned_integer;
    break;
  case 'X':
    parsed->datatype = tabula_format_datatype_unsigned_integer;
    break;
  case 'o':
    parsed->datatype = tabula_format_datatype_unsigned_integer;
    break;
  case 's':
    parsed->datatype = tabula_format_datatype_string;
    break;
  case 'c':
    parsed->datatype = tabula_format_datatype_character;
    break;
  case 'p':
    parsed->datatype = tabula_format_datatype_pointer;
    break;
  case 'a':
    parsed->datatype = tabula_format_datatype_double;
    break;
  case 'A':
    parsed->datatype = tabula_format_datatype_double;
    break;
  case '%':
    break;
  default:
    return false;
  }
  *end = format + 1;
  return true;
}

int tabula_vformat(void (*emit)(const uint8_t *ptr, size_t length, void *ud), void *ud, unsigned int limit_, const char *format_, va_list ap) {
  // step 0: parse, if positional step 1 else emit                 ; return
  // step 1: parse, increment max positional count                 ; allocate
  // positional array, step 2 step 2: parse, record size positional array size
  // arra         ; populate positional array data, step 3 step 3: parse, read
  // argument from positional array, emit      ; free positional array, return

  uint8_t emit_buffer[64];
  uint8_t *const emit_buffer_end = emit_buffer + 64;

  int step = 0;
  unsigned int max_positional_argument_index = 0;
  int to_write = 0;

  struct tabula_format_position *positional_array = NULL;

#define TABULA_FORMAT_EMIT(PTR, LENGTH)                                                                                                                        \
  do {                                                                                                                                                         \
    to_write += tabula_format_do_emit(emit, ud, limit, PTR, LENGTH, to_write);                                                                                 \
  } while(0)

  unsigned int limit = limit_ ? limit_ - 1 : 0;

  for(;;) {
    const char *format = format_;

    const char *start = format, *end;
    struct tabula_format_placeholder placeholder;

    while(*format) {
      if(*format == '%') {
        end = format;
        format++;
        if(tabula_format_parse_placeholder(format, &placeholder, &format)) {
          if(end > start && (step == 0 || step == 3)) {
            TABULA_FORMAT_EMIT(start, end - start);
          }
          start = format;
        } else {
          continue;
        }
      } else {
        do {
          format++;
        } while(*format && *format != '%');
        end = format;
        continue;
      }

      if(step == 0) {
        if(placeholder.parameter != TABULA_FORMAT_UNDEFINED) {
          step = 1;
          format_ = end;
        }
      }

      if(step == 1) {
        if(placeholder.parameter == TABULA_FORMAT_UNDEFINED) {
          return 0;
        }
        max_positional_argument_index = placeholder.parameter > max_positional_argument_index ? placeholder.parameter : max_positional_argument_index;
        continue;
      }

      if(step == 2) {
        if(placeholder.parameter == TABULA_FORMAT_UNDEFINED) {
          return 0;
        }
        positional_array[placeholder.parameter].size = tabula_format_size_table[placeholder.datatype * 9 + placeholder.length];
        if(positional_array[placeholder.parameter].size == 0) {
          return 0;
        }
        continue;
      }

      if(step == 3) {
        if(placeholder.parameter == TABULA_FORMAT_UNDEFINED) {
          return 0;
        }
        va_copy(ap, positional_array[placeholder.parameter].ap);
      }

      int i_width = placeholder.width_dynamic ? va_arg(ap, int) : placeholder.width;
      unsigned int width;
      if(i_width < 0) {
        width = -i_width;
        placeholder.flag_minus = 1;
      } else {
        width = i_width;
      }
      int32_t precision = placeholder.precision_dynamic ? va_arg(ap, int) : placeholder.precision;
      const char *pad_characters = placeholder.flag_zero ? tabula_format_sixty_zeros : tabula_format_sixty_spaces;
      uint8_t *emit_ptr = emit_buffer_end;
      unsigned int emit_length;
      unsigned int prefix_length = 0;

      intmax_t i_value;
      uintmax_t u_value;
      double g_value;

      if(placeholder.style == tabula_format_style_escape) {
        TABULA_FORMAT_EMIT("%", 1);
        continue;
      }

      switch(placeholder.datatype) {
      case tabula_format_datatype_unsigned_integer:
        u_value = placeholder.length == tabula_format_hh   ? (unsigned long long int)(unsigned char)va_arg(ap, unsigned int)
                  : placeholder.length == tabula_format_h  ? (unsigned long long int)(unsigned short)va_arg(ap, unsigned int)
                  : placeholder.length == tabula_format_l  ? (unsigned long long int)va_arg(ap, unsigned long)
                  : placeholder.length == tabula_format_ll ? (unsigned long long int)va_arg(ap, unsigned long long)
                  : placeholder.length == tabula_format_z  ? (unsigned long long int)va_arg(ap, size_t)
                  : placeholder.length == tabula_format_j  ? (unsigned long long int)va_arg(ap, intmax_t)
                  : placeholder.length == tabula_format_t  ? (unsigned long long int)va_arg(ap, ptrdiff_t)
                                                           : (unsigned long long int)va_arg(ap, unsigned int);
        emit_ptr = tabula_format_emit_int64_unsigned(emit_ptr, u_value, precision, placeholder.style);
        prefix_length = tabula_format_emit_int64_unsigned_prefix_count(u_value, placeholder.flag_hash, placeholder.style);
        emit_length = emit_buffer_end - emit_ptr;
        break;
      case tabula_format_datatype_signed_integer:
        i_value = placeholder.length == tabula_format_hh   ? (long long int)(char)va_arg(ap, int)
                  : placeholder.length == tabula_format_h  ? (long long int)(short)va_arg(ap, int)
                  : placeholder.length == tabula_format_l  ? (long long int)va_arg(ap, long)
                  : placeholder.length == tabula_format_ll ? (long long int)va_arg(ap, long long)
                  : placeholder.length == tabula_format_z  ? (long long int)va_arg(ap, size_t)
                  : placeholder.length == tabula_format_j  ? (long long int)va_arg(ap, intmax_t)
                  : placeholder.length == tabula_format_t  ? (long long int)va_arg(ap, ptrdiff_t)
                                                           : (long long int)va_arg(ap, int);
        emit_ptr = tabula_format_emit_int64(emit_ptr, i_value, precision);
        prefix_length = tabula_format_emit_int64_prefix_count(i_value, placeholder.flag_plus, placeholder.flag_space);
        emit_length = emit_buffer_end - emit_ptr;
        break;
      case tabula_format_datatype_character: {
        int c = va_arg(ap, int);
        *--emit_ptr = c; // TODO locale
        emit_length = 1;
      } break;
      case tabula_format_datatype_double:
        g_value = placeholder.length == tabula_format_L ? (double)va_arg(ap, long double) : (double)va_arg(ap, double);
        emit_ptr = tabula_format_emit_double(emit_ptr, g_value, placeholder.flag_hash, precision, placeholder.style);
        prefix_length = tabula_format_emit_double_prefix_count(g_value, placeholder.flag_plus, placeholder.flag_space);
        emit_length = emit_buffer_end - emit_ptr;
        break;
      case tabula_format_datatype_pointer: {
        void *value_ptr = va_arg(ap, void *);
        u_value = (uintmax_t)value_ptr;
        if(u_value) {
          emit_ptr = tabula_format_emit_int64_unsigned_hex(emit_ptr, u_value, precision);
          *--emit_ptr = 'x';
          *--emit_ptr = '0';
          emit_length = emit_buffer_end - emit_ptr;
        } else {
          emit_ptr = tabula_null_to_str[tabula_format_ptrnull].ptr;
          emit_length = tabula_null_to_str[tabula_format_ptrnull].length;
        }
      } break;
      case tabula_format_datatype_string: {
        const char *str = va_arg(ap, const char *);
        if(str != NULL) {
          pad_characters = tabula_format_sixty_spaces;
          emit_ptr = str;
          emit_length = strlen(str);
        } else {
          emit_ptr = tabula_null_to_str[tabula_format_strnull].ptr;
          emit_length = tabula_null_to_str[tabula_format_strnull].length;
        }
        if(precision != TABULA_FORMAT_UNDEFINED && emit_length > precision)
          emit_length = precision;
      } break;
      }

      if(width != TABULA_FORMAT_UNDEFINED && width - prefix_length > emit_length) {
        unsigned int pad = width - emit_length - prefix_length;
        if(!placeholder.flag_minus) {
          // draw prefix before zeros
          if(placeholder.flag_zero) {
            char prefix[10];
            char *p = prefix;
            if(placeholder.datatype == tabula_format_datatype_unsigned_integer) {
              p = tabula_format_emit_int64_unsigned_prefix(p, u_value, placeholder.flag_hash, placeholder.style);
            } else if(placeholder.datatype == tabula_format_datatype_signed_integer) {
              p = tabula_format_emit_int64_prefix(p, i_value, placeholder.flag_plus, placeholder.flag_space);
            } else if(placeholder.datatype == tabula_format_datatype_double) {
              p = tabula_format_emit_double_prefix(p, g_value, placeholder.flag_plus, placeholder.flag_plus);
            }
            TABULA_FORMAT_EMIT(p, prefix_length);
          }
          while(pad) {
            unsigned int pl = pad > 60 ? 60 : pad;
            TABULA_FORMAT_EMIT(pad_characters, pl);
            pad -= pl;
          }
        }
        if(placeholder.flag_minus || !placeholder.flag_zero) {
          if(placeholder.datatype == tabula_format_datatype_unsigned_integer) {
            emit_ptr = tabula_format_emit_int64_unsigned_prefix(emit_ptr, u_value, placeholder.flag_hash, placeholder.style);
          } else if(placeholder.datatype == tabula_format_datatype_signed_integer) {
            emit_ptr = tabula_format_emit_int64_prefix(emit_ptr, i_value, placeholder.flag_plus, placeholder.flag_space);
          } else if(placeholder.datatype == tabula_format_datatype_double) {
            emit_ptr = tabula_format_emit_double_prefix(emit_ptr, g_value, placeholder.flag_plus, placeholder.flag_plus);
          }
          emit_length += prefix_length;
        }
        TABULA_FORMAT_EMIT(emit_ptr, emit_length);
        if(placeholder.flag_minus) {
          while(pad) {
            unsigned int pl = pad > 60 ? 60 : pad;
            TABULA_FORMAT_EMIT(tabula_format_sixty_spaces, pl);
            pad -= pl;
          }
        }
      } else {
        if(placeholder.datatype == tabula_format_datatype_unsigned_integer) {
          emit_ptr = tabula_format_emit_int64_unsigned_prefix(emit_ptr, u_value, placeholder.flag_hash, placeholder.style);
        } else if(placeholder.datatype == tabula_format_datatype_signed_integer) {
          emit_ptr = tabula_format_emit_int64_prefix(emit_ptr, i_value, placeholder.flag_plus, placeholder.flag_space);
        } else if(placeholder.datatype == tabula_format_datatype_double) {
          emit_ptr = tabula_format_emit_double_prefix(emit_ptr, g_value, placeholder.flag_plus, placeholder.flag_plus);
        }
        emit_length += prefix_length;
        TABULA_FORMAT_EMIT(emit_ptr, emit_length);
      }
    }

    if(end > start && (step == 0 || step == 3)) {
      TABULA_FORMAT_EMIT(start, end - start);
    }

    if(step == 1) {
      positional_array = malloc(sizeof(*positional_array) * (max_positional_argument_index + 1));
      step = 2;
      continue;
    }

    if(step == 2) {
      for(unsigned int i = 0; i <= max_positional_argument_index; i++) {
        va_copy(positional_array[i].ap, ap);
        if(positional_array[i].size == 1)
          va_arg(ap, int);
        else if(positional_array[i].size == 2)
          va_arg(ap, int);
        else if(positional_array[i].size == 4)
          va_arg(ap, uint32_t);
        else if(positional_array[i].size == 8)
          va_arg(ap, uint64_t);
        else
          return 0;
      }
      step = 3;
      continue;
    }

    if(step == 3) {
      free(positional_array);
    }

    if(limit_) {
      // emit("", 1, ud);
    }

#undef TABULA_FORMAT_EMIT

    return to_write;
  }
}

void tabula_format_emit_to_file(const uint8_t *ptr, size_t length, void *ud) { fwrite(ptr, 1, length, (FILE *)ud); }

void tabula_format_emit_to_string(const uint8_t *ptr, size_t length, void *ud) {
  struct tabula_format_emit_to_string_data *data = (struct tabula_format_emit_to_string_data *)ud;
  size_t position = data->position;
  data->position += length;
  if(position > data->string_size)
    return;
  if(position + length > data->string_size) {
    length = data->string_size - position;
  }
  memcpy(data->string + position, ptr, length);
}

void tabula_format_emit_to_nothing(const uint8_t *ptr, size_t length, void *ud) {}
#endif
