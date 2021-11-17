// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_RUNTIME_METRICS_H_
#define _ALIAS_RUNTIME_METRICS_H_

#include <stdint.h>

typedef struct alias_RuntimeMetrics {
  uint32_t       capacity;
  uint32_t       length;
  const char * * name;
  uint32_t     * sort;
  int64_t      * total;
  int64_t      * accum;
} alias_RuntimeMetrics;

void alias_RuntimeMetrics_initialize(alias_RuntimeMetrics * metrics);
void alias_RuntimeMetrics_update(alias_RuntimeMetrics * metrics);
uint32_t alias_RuntimeMetrics_register(alias_RuntimeMetrics * metrics, const char * name);
void alias_RuntimeMetrics_submit(alias_RuntimeMetrics * metrics, uint32_t metric, int64_t value);
const char * alias_RuntimeMetrics_get_name(alias_RuntimeMetrics * metrics, uint32_t metric);
int64_t alias_RuntimeMetrics_get_total(alias_RuntimeMetrics * metrics, uint32_t metric);
int64_t alias_RuntimeMetrics_get_accum(alias_RuntimeMetrics * metrics, uint32_t metric);

#endif

