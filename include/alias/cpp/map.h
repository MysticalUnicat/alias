// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_CPP_MAP_H_
#define _ALIAS_CPP_MAP_H_

#include <alias/cpp/cat.h>
#include <alias/cpp/defer_eval.h>
#include <alias/cpp/probe.h>
#include <alias/cpp/boolean.h>
#include <alias/cpp/option.h>
#include <alias/cpp/arguments.h>

#define ALIAS_CPP_MAP(F, X, ...) \
  F(X) \
  ALIAS_CPP_IFF( \
    ALIAS_CPP_OPTION_IS_SOME(ALIAS_CPP_FIRST(__VA_ARGS__)) \
  )( \
      ALIAS_CPP_DEFER_2(ALIAS_CPP_MAP_ID)()(F, __VA_ARGS__) \
    , /* do nothing */ \
  )
#define ALIAS_CPP_MAP_ID() ALIAS_CPP_MAP

#define ALIAS_CPP_FILTER_MAP(P, F, X, ...) \
  ALIAS_CPP_IFF(P(X))(F(X),) \
  ALIAS_CPP_IFF( \
    ALIAS_CPP_OPTION_IS_SOME(ALIAS_CPP_FIRST(__VA_ARGS__)) \
  )( \
      ALIAS_CPP_DEFER_2(ALIAS_CPP_FILTER_MAP_ID)()(P, F, __VA_ARGS__) \
    , /* do nothing */ \
  )
#define ALIAS_CPP_FILTER_MAP_ID() ALIAS_CPP_FILTER_MAP

#endif
