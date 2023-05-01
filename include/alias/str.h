// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_STR_H_
#define _ALIAS_STR_H_

#include <stdint.h>

#include <alias/memory.h>

typedef const char *alias_str;

alias_str alias_str_clone(alias_MemoryCB *mcb, alias_str s);

alias_str alias_str_format(alias_MemoryCB *mcb, alias_str format, ...);

void alias_str_free(alias_MemoryCB *mcb, alias_str s);

bool alias_str_same(alias_str a, alias_str b);

uintmax_t alias_str_length(alias_str s);
uintmax_t alias_str_size(alias_str s);

#endif