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

