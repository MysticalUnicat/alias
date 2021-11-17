// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_CPP_ARGUMENTS_H_
#define _ALIAS_CPP_ARGUMENTS_H_

#include <alias/cpp/defer_eval.h>
#include <alias/cpp/probe.h>
#include <alias/cpp/option.h>

#define ALIAS_CPP_PRIMITIVE_1st(A, ...) A
#define ALIAS_CPP_PRIMITIVE_2nd(A, B, ...) B
#define ALIAS_CPP_PRIMITIVE_3rd(A, B, C, ...) C

// get the first argument, hopefully it catches a lot of things, returns None() or Some(X)
#define ALIAS_CPP_FIRST(...) ALIAS_CPP_FIRST_(~, ## __VA_ARGS__, ALIAS_CPP_PROBE)
#define ALIAS_CPP_FIRST_(X, Y, ...) ALIAS_CPP_Some_IFF(ALIAS_CPP_BNOT(ALIAS_CPP_IS_PROBE(Y())))(Y)

#define ALIAS_CPP_UNWRAP(X) ALIA_CPP_DEFER_1(ALIAS_CPP_ALL) X

#endif
