/* replacement of a few functions that are not so great on windows CRT
 * 
 * an attempt to normalize behavior, breaking api to have additional safety
 * 
 * a nice confortable white t-shirt.
 * 
 * general:
 *  - Normalize: UTF-8 support by default
 *
 * printf family:
 *  - Behavior:  microsoft vs posix.
 *  - Behavior:  mingw sometimes uses an older version of microsoft CRT.
 *  - Normalize: may be minor differences that effect text matching and types (why we need PRI macros)
 *  - Normalize: missing asprintf in many places
 *  - Safety:    sprintf and snprintf do not bounds check the destination buffer
 * 
 */

#ifndef _TABULA_H_
#define _TABULA_H_

#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <uchar.h>
// atoi
intmax_t tabula_atoi(const char * restrict in, const char ** restrict out_ptr);
uintmax_t tabula_atou(const char * restrict in, const char ** restrict out_ptr);

#ifndef TABULA_NO_REPLACEMENT_MACROS
#define atoi tabula_atoi
#define atou tabula_atou
#endif

// format
struct tabula_format_emit_to_string_data {
  uint8_t * string;
  size_t string_size;
  size_t position;
};

#define TABULA_FORMAT_DECORATE(FORMAT_INDEX, FIRST_ARGUMENT_INDEX) __attribute__ ((format(printf, FORMAT_INDEX, FIRST_ARGUMENT_INDEX)))

int tabula_format(void (* emit)(const uint8_t * ptr, size_t length, void * ud), void * ud, unsigned int limit, const char * format, va_list ap);

void tabula_format_emit_to_file(const uint8_t * ptr, size_t length, void * ud);
void tabula_format_emit_to_string(const uint8_t * ptr, size_t length, void * ud);
void tabula_format_emit_to_nothing(const uint8_t * ptr, size_t length, void * ud);

// # format null options
enum tabula_format_null {
  TABULA_FORMAT_HASHx_0,
  TABULA_FORMAT_HASHX_0,
  TABULA_FORMAT_PARENTHESIS_null,
  TABULA_FORMAT_PARENTHESIS_NULL,
};

enum tabula_format_null tabula_format_get_ptrnull(void);
void                    tabula_format_set_ptrnull_from_system(void);
void                    tabula_format_set_ptrnull(enum tabula_format_null e);

enum tabula_format_null tabula_format_get_strnull(void);
void                    tabula_format_set_strnull_from_system(void);
void                    tabula_format_set_strnull(enum tabula_format_null e);

// # replacement functions
intmax_t tabula_atoi(const char * restrict in, const char ** restrict out_ptr);
uintmax_t tabula_atou(const char * restrict in, const char ** restrict out_ptr);

// stdio
static inline int tabula_vprintf(const char * format, va_list ap) {
  return tabula_format(tabula_format_emit_to_file, stdout, (unsigned int)-1, format, ap);
}

static inline int tabula_vcprintf(const char * format, va_list ap) {
  return tabula_format(tabula_format_emit_to_nothing, NULL, (unsigned int)-1, format, ap);
}

static inline int tabula_vsnprintf(char * string, size_t string_size, unsigned int limit, const char * format, va_list ap) {
  struct tabula_format_emit_to_string_data data = {
    .string = string,
    .string_size = string_size,
    .position = 0
  };
  return tabula_format(tabula_format_emit_to_string, &data, limit, format, ap);
}

static inline int tabula_vsprintf(char * string, size_t string_size, const char * format, va_list ap) {
  return tabula_vsnprintf(string, string_size, (unsigned int)-1, format, ap);
}

static inline int tabula_vasprintf(char ** string_ptr, const char * format, va_list ap_) {
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
static inline int tabula_snprintf(char * string, size_t string_size, unsigned int limit, const char * format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = tabula_vsnprintf(string, string_size, limit, format, ap);
  va_end(ap);
  return result;
}

TABULA_FORMAT_DECORATE(3, 4)
static inline int tabula_sprintf(char * string, size_t string_size, const char * format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = tabula_vsnprintf(string, string_size, (unsigned int)-1, format, ap);
  va_end(ap);
  return result;
}

TABULA_FORMAT_DECORATE(2, 3)
static inline int tabula_asprintf(char ** string_ptr, const char * format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = tabula_vasprintf(string_ptr, format, ap);
  va_end(ap);
  return result;
}

TABULA_FORMAT_DECORATE(1, 2)
static inline int tabula_printf(const char * format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = tabula_vprintf(format, ap);
  va_end(ap);
  return result;
}

TABULA_FORMAT_DECORATE(1, 2)
static inline int tabula_cprintf(const char * format, ...) {
  va_list ap;
  va_start(ap, format);
  int result = tabula_vcprintf(format, ap);
  va_end(ap);
  return result;
}

#ifndef TABULA_NO_REPLACEMENT_MACROS
#define printf    tabula_printf
#define vprintf   tabula_vprintf
#define cprintf   tabula_cprintf
#define vcprintf  tabula_vcprintf
#define sprintf   tabula_sprintf
#define vsprintf  tabula_vsprintf
#define snprintf  tabula_snprintf
#define vsnprintf tabula_vsnprintf
#define asprintf  tabula_asprintf
#endif

#endif

#ifdef TABULA_IMPLEMENTATION
// atoi
static inline int tabula_is_digit(int c) {
  return (c >= '0') && (c <= '9') ? (c - '0') + 1 : 0;
}

intmax_t tabula_atoi(const char * restrict in, const char ** restrict out_ptr) {
  intmax_t i = 0;
  intmax_t n = (*in == '-' ? (in++, -1) : *in == '+' ? (in++, 1) : 1);
  int c;
  while((c = tabula_is_digit(*in))) {
    i = i * 10 + (c - 1);
    in++;
  }
  if(out_ptr != NULL) {
    *out_ptr = in;
  }
  return n * i;
}

// atoi


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
static unsigned int TABULA_FORMAT_UNDEFINED = (unsigned int)-1;
static unsigned int TABULA_FORMAT_DYNAMIC = (unsigned int)-2;

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
  tabula_format_datatype_integer,
  tabula_format_datatype_character,
  tabula_format_datatype_double,
  tabula_format_datatype_pointer,
  tabula_format_datatype_string
};

static unsigned int tabula_format_size_table[] = {
    // integer
    sizeof(int), sizeof(char), sizeof(short), sizeof(long), sizeof(long long), 0, sizeof(size_t), sizeof(intmax_t),
    sizeof(ptrdiff_t),
    // character
    sizeof(int), sizeof(char), sizeof(short), sizeof(long), sizeof(long long), 0, sizeof(size_t), sizeof(intmax_t),
    sizeof(ptrdiff_t),
    // double
    sizeof(double), 0, 0, 0, sizeof(double), sizeof(long double), 0, 0, 0,
    // pointer
    sizeof(void *), 0, 0, 0, 0, 0, 0, 0, 0,
    // string
    sizeof(const char *), 0, 0, 0, 0, 0, 0, 0, 0};

struct tabula_format_placeholder {
  unsigned int parameter;
  uint8_t flag_minus : 1;
  uint8_t flag_plus : 1;
  uint8_t flag_space : 1;
  uint8_t flag_zero : 1;
  uint8_t flag_apostrophe : 1;
  uint8_t flag_hash : 1;
  uint8_t type_unsigned : 1;
  uint8_t flag_unused : 1;
  unsigned int width;
  unsigned int precision;
  enum tabula_format_length length;
  uint8_t type_uppercase : 1;
  uint8_t type_double_fixed : 1;
  uint8_t type_double_standard : 1;
  uint8_t type_base : 5; // 8 10 16
  enum tabula_format_datatype datatype;
};

static inline const char *tabula_format_parse_placeholder(const char *format,
                                                          struct tabula_format_placeholder *parsed) {
  memset(parsed, 0, sizeof(*parsed));
  parsed->parameter = TABULA_FORMAT_UNDEFINED;
  parsed->width = TABULA_FORMAT_UNDEFINED;
  parsed->precision = TABULA_FORMAT_UNDEFINED;

  const char *param_start = format;
  if(isdigit(*format)) {
    unsigned int parameter = tabula_atoi(format, &format) - 1;
    if(*format == '$') {
      format++;
      parsed->parameter = parameter;
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
    parsed->width = TABULA_FORMAT_DYNAMIC;
    format++;
  } else if(isdigit(*format)) {
    parsed->width = tabula_atoi(format, &format);
  }

  if(*format == '.') {
    format++;
    if(parsed->parameter == TABULA_FORMAT_UNDEFINED && *format == '*') {
      parsed->precision = TABULA_FORMAT_DYNAMIC;
      format++;
    } else {
      parsed->precision = tabula_atoi(format, &format);
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

  parsed->type_base = 10;
  switch(*format) {
  case 'd':
    parsed->datatype = tabula_format_datatype_integer;
    break;
  case 'i':
    parsed->datatype = tabula_format_datatype_integer;
    break;
  case 'u':
    parsed->datatype = tabula_format_datatype_integer;
    parsed->type_unsigned = 1;
    break;
  case 'f':
    parsed->datatype = tabula_format_datatype_double;
    parsed->type_double_fixed = 1;
    break;
  case 'F':
    parsed->datatype = tabula_format_datatype_double;
    parsed->type_double_fixed = 1;
    parsed->type_uppercase = 1;
    break;
  case 'e':
    parsed->datatype = tabula_format_datatype_double;
    parsed->type_double_standard = 1;
    break;
  case 'E':
    parsed->datatype = tabula_format_datatype_double;
    parsed->type_double_standard = 1;
    parsed->type_uppercase = 1;
    break;
  case 'g':
    parsed->datatype = tabula_format_datatype_double;
    break;
  case 'G':
    parsed->datatype = tabula_format_datatype_double;
    parsed->type_uppercase = 1;
    break;
  case 'x':
    parsed->datatype = tabula_format_datatype_integer;
    parsed->type_base = 16;
    parsed->type_unsigned = 1;
    break;
  case 'X':
    parsed->datatype = tabula_format_datatype_integer;
    parsed->type_base = 16;
    parsed->type_unsigned = 1;
    parsed->type_uppercase = 1;
    break;
  case 'o':
    parsed->datatype = tabula_format_datatype_integer;
    parsed->type_base = 8;
    parsed->type_unsigned = 1;
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
    parsed->type_base = 16;
    break;
  case 'A':
    parsed->datatype = tabula_format_datatype_double;
    parsed->type_base = 16;
    parsed->type_uppercase = 1;
    break;
  }

  return format + 1;
}

struct tabula_format_position {
  va_list ap;
  uint8_t size;
};

static const char tabula_format_sixty_spaces[] = "                                                            ";
static const char tabula_format_sixty_zeros[] = "000000000000000000000000000000000000000000000000000000000000";

static inline unsigned int tabula_format_do_emit(void (*emit)(const uint8_t *ptr, size_t length, void *ud), void *ud,
                                                 unsigned int limit, const uint8_t *ptr, unsigned int length,
                                                 unsigned int have_written) {
  if(have_written < limit) {
    unsigned int emit_length = have_written + length > limit ? limit - have_written : length;
    emit(ptr, emit_length, ud);
  }
  return length;
}

int tabula_format(void (* emit)(const uint8_t * ptr, size_t length, void * ud), void * ud, unsigned int limit_, const char * format_, va_list ap) {
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

#define TABULA_FORMAT_EMIT(PTR, LENGTH)                                                                                              \
  do {                                                                                                                 \
    to_write += tabula_format_do_emit(emit, ud, limit, PTR, LENGTH, to_write);                                         \
  } while(0)

  unsigned int limit = limit_ ? limit_ - 1 : 0;

  for(;;) {
    const char *format = format_;

    while(*format) {
      if(*format != '%') {
        const char *start = format++;
        while(*format && *format != '%') {
          format++;
        }
        if(step == 0 || step == 3) {
          TABULA_FORMAT_EMIT(start, format - start);
        }
        continue;
      } else {
        format++;
      }

      if(*format == '%') {
        format++;
        TABULA_FORMAT_EMIT("%", 1);
        continue;
      }

      struct tabula_format_placeholder placeholder;
      const char *format_preparse = format - 1;
      format = tabula_format_parse_placeholder(format, &placeholder);

      if(step == 0) {
        if(placeholder.parameter != TABULA_FORMAT_UNDEFINED) {
          step = 1;
          format_ = format_preparse;
        }
      }

      if(step == 1) {
        if(placeholder.parameter == TABULA_FORMAT_UNDEFINED) {
          return 0;
        }
        max_positional_argument_index = placeholder.parameter > max_positional_argument_index
                                            ? placeholder.parameter
                                            : max_positional_argument_index;
        continue;
      }

      if(step == 2) {
        if(placeholder.parameter == TABULA_FORMAT_UNDEFINED) {
          return 0;
        }
        positional_array[placeholder.parameter].size =
            tabula_format_size_table[placeholder.datatype * 9 + placeholder.length];
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

      unsigned int width = placeholder.width == TABULA_FORMAT_DYNAMIC ? va_arg(ap, unsigned int) : placeholder.width;
      unsigned int precision =
          placeholder.precision == TABULA_FORMAT_DYNAMIC ? va_arg(ap, unsigned int) : placeholder.precision;
      const char *pad_characters = placeholder.flag_zero ? tabula_format_sixty_zeros : tabula_format_sixty_spaces;
      const uint8_t *emit_ptr;
      unsigned int emit_length;
      switch(placeholder.datatype) {
      case tabula_format_datatype_integer: {
        unsigned long long int value;
        bool negative = false;
        if(placeholder.type_unsigned) {
          value =
              placeholder.length == tabula_format_hh  ? (unsigned long long int)(unsigned char)va_arg(ap, unsigned int)
              : placeholder.length == tabula_format_h ? (unsigned long long int)(unsigned short)va_arg(ap, unsigned int)
              : placeholder.length == tabula_format_l ? (unsigned long long int)va_arg(ap, unsigned long)
              : placeholder.length == tabula_format_ll ? (unsigned long long int)va_arg(ap, unsigned long long)
              : placeholder.length == tabula_format_z  ? (unsigned long long int)va_arg(ap, size_t)
              : placeholder.length == tabula_format_j  ? (unsigned long long int)va_arg(ap, intmax_t)
              : placeholder.length == tabula_format_t  ? (unsigned long long int)va_arg(ap, ptrdiff_t)
                                                       : (unsigned long long int)va_arg(ap, unsigned int);
        } else {
          long long int i_value = placeholder.length == tabula_format_hh   ? (long long int)(char)va_arg(ap, int)
                                  : placeholder.length == tabula_format_h  ? (long long int)(short)va_arg(ap, int)
                                  : placeholder.length == tabula_format_l  ? (long long int)va_arg(ap, long)
                                  : placeholder.length == tabula_format_ll ? (long long int)va_arg(ap, long long)
                                  : placeholder.length == tabula_format_z  ? (long long int)va_arg(ap, size_t)
                                  : placeholder.length == tabula_format_j  ? (long long int)va_arg(ap, intmax_t)
                                  : placeholder.length == tabula_format_t  ? (long long int)va_arg(ap, ptrdiff_t)
                                                                           : (long long int)va_arg(ap, int);
          negative = i_value < 0;
          value = negative ? 0 - i_value : i_value;
        }
        uint8_t *b = emit_buffer_end;
        long long int base = placeholder.type_base;
        char alpha = (placeholder.type_uppercase ? 'A' : 'a') - 10;
        unsigned long long original_value = value;
        if(precision != TABULA_FORMAT_UNDEFINED) {
          unsigned int p = precision;
          while(p--) {
            unsigned int d_value = value % base;
            value /= base;
            *--b = d_value + (d_value < 10 ? '0' : alpha);
          }
        } else {
          do {
            unsigned int d_value = value % base;
            value /= base;
            *--b = d_value + (d_value < 10 ? '0' : alpha);
          } while(value);
        }
        if(!placeholder.type_unsigned) {
          if(negative) {
            *--b = '-';
          } else if(placeholder.flag_plus) {
            *--b = '+';
          } else if(placeholder.flag_space) {
            *--b = ' ';
          }
        }
        if(placeholder.flag_hash && original_value) {
          if(base == 16) {
            *--b = placeholder.type_uppercase ? 'X' : 'x';
          }
          if(base != 10) {
            *--b = '0';
          }
        }
        emit_ptr = b;
        emit_length = emit_buffer_end - b;
      } break;
      case tabula_format_datatype_character: {
        int c = va_arg(ap, int);
        uint8_t *b = emit_buffer_end;
        *--b = c; // TODO locale
        emit_ptr = b;
        emit_length = 1;
      } break;
      case tabula_format_datatype_double: {
      } break;
      case tabula_format_datatype_pointer: {
        void *value_ptr = va_arg(ap, void *);
        unsigned long long value = (unsigned long long)value_ptr;
        uint8_t *b = emit_buffer_end;
        long long int base = 16;
        char alpha = 'a' - 10;
        if(value) {
          if(precision != TABULA_FORMAT_UNDEFINED) {
            unsigned int p = precision;
            while(p--) {
              unsigned int d_value = value % base;
              value /= base;
              *--b = d_value + (d_value < 10 ? '0' : alpha);
            }
          } else {
            do {
              unsigned int d_value = value % base;
              value /= base;
              *--b = d_value + (d_value < 10 ? '0' : alpha);
            } while(value);
          }
          *--b = 'x';
          *--b = '0';
          emit_ptr = b;
          emit_length = emit_buffer_end - b;
        } else {
          emit_ptr = tabula_null_to_str[tabula_format_ptrnull].ptr;
          emit_length = tabula_null_to_str[tabula_format_ptrnull].length;
          if(precision != TABULA_FORMAT_UNDEFINED && emit_length > precision)
            emit_length = precision;
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

      if(width != TABULA_FORMAT_UNDEFINED && width > emit_length) {
        unsigned int pad = width - emit_length;
        if(!placeholder.flag_minus) {
          while(pad) {
            unsigned int pl = pad > 60 ? 60 : pad;
            TABULA_FORMAT_EMIT(pad_characters, pl);
            pad -= pl;
          }
        }
        TABULA_FORMAT_EMIT(emit_ptr, emit_length);
        if(placeholder.flag_minus) {
          while(pad) {
            unsigned int pl = pad > 60 ? 60 : pad;
            TABULA_FORMAT_EMIT(pad_characters, pl);
            pad -= pl;
          }
        }
      } else {
        TABULA_FORMAT_EMIT(emit_ptr, emit_length);
      }
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
      //emit("", 1, ud);
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
