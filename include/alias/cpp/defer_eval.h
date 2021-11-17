// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_CPP_DEFER_EVAL_H_
#define _ALIAS_CPP_DEFER_EVAL_H_

#define ALIAS_CPP_EVAL ALIAS_CPP_EVAL_0
#define ALIAS_CPP_EVAL_0(...) ALIAS_CPP_EVAL_1(ALIAS_CPP_EVAL_1(ALIAS_CPP_EVAL_1(ALIAS_CPP_EVAL_1(__VA_ARGS__))))
#define ALIAS_CPP_EVAL_1(...) ALIAS_CPP_EVAL_2(ALIAS_CPP_EVAL_2(ALIAS_CPP_EVAL_2(ALIAS_CPP_EVAL_2(__VA_ARGS__))))
#define ALIAS_CPP_EVAL_2(...) ALIAS_CPP_EVAL_3(ALIAS_CPP_EVAL_3(ALIAS_CPP_EVAL_3(ALIAS_CPP_EVAL_3(__VA_ARGS__))))
#define ALIAS_CPP_EVAL_3(...) __VA_ARGS__

#define ALIAS_CPP_EMPTY()
#define ALIAS_CPP_DEFER_1(X) X ALIAS_CPP_EMPTY()
#define ALIAS_CPP_DEFER_2(X) X ALIAS_CPP_EMPTY ALIAS_CPP_EMPTY()()
#define ALIAS_CPP_DEFER_3(X) X ALIAS_CPP_EMPTY ALIAS_CPP_EMPTY ALIAS_CPP_EMPTY()()()

#endif
