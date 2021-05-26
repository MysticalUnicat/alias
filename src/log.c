#include <alias/log.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void alias_log(enum alias_log_level level, const char * file, uint32_t line, const char * format, ...) {
  const char * last_slash = strrchr(file, '/');
  
  printf("%c %s %4i - ", (char[]){ 'E', 'W', 'I', 'D', 'T' }[level], last_slash + 1, line);
  
  va_list ap;
  va_start(ap, format);
  vprintf(format, ap);
  va_end(ap);

  puts("");
}

