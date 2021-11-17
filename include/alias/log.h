// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_LOG_H_
#define _ALIAS_LOG_H_

#include <stdint.h>

enum alias_log_level {
  ALIAS_LOG_ERROR,
  ALIAS_LOG_WARNING,
  ALIAS_LOG_INFO,
  ALIAS_LOG_DEBUG,
  ALIAS_LOG_TRACE
};

void alias_log(enum alias_log_level level, const char * file, uint32_t line, const char * format, ...);

#define ALIAS_ERROR(FORMAT, ...) alias_log(ALIAS_LOG_ERROR, __FILE__, __LINE__, FORMAT, ## __VA_ARGS__)
#define ALIAS_WARNING(FORMAT, ...) alias_log(ALIAS_LOG_WARNING, __FILE__, __LINE__, FORMAT, ## __VA_ARGS__)
#define ALIAS_INFO(FORMAT, ...) alias_log(ALIAS_LOG_INFO, __FILE__, __LINE__, FORMAT, ## __VA_ARGS__)
#define ALIAS_DEBUG(FORMAT, ...) alias_log(ALIAS_LOG_DEBUG, __FILE__, __LINE__, FORMAT, ## __VA_ARGS__)
#define ALIAS_TRACE(FORMAT, ...) alias_log(ALIAS_LOG_TRACE, __FILE__, __LINE__, FORMAT, ## __VA_ARGS__)

#endif
