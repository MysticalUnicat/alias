// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

