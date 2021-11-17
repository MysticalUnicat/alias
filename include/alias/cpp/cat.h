// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_CPP_CAT_H_
#define _ALIAS_CPP_CAT_H_

#define ALIAS_CPP_CAT(A, ...) ALIAS_CPP_CAT_(A, __VA_ARGS__)
#define ALIAS_CPP_CAT_(A, ...) A ## __VA_ARGS__

#define ALIAS_CPP_CAT3(A, B, ...) ALIAS_CPP_CAT3_(A, B, __VA_ARGS__)
#define ALIAS_CPP_CAT3_(A, B, ...) A ## B ## __VA_ARGS__

#define ALIAS_CPP_CAT4(A, B, C, ...) ALIAS_CPP_CAT4_(A, B, C, __VA_ARGS__)
#define ALIAS_CPP_CAT4_(A, B, C, ...) A ## B ## C ## __VA_ARGS__

#define ALIAS_CPP_CAT5(A, B, C, D, ...) ALIAS_CPP_CAT5_(A, B, C, D, __VA_ARGS__)
#define ALIAS_CPP_CAT5_(A, B, C, D, ...) A ## B ## C ## D ## __VA_ARGS__

#define ALIAS_CPP_CAT6(A, B, C, D, E, ...) ALIAS_CPP_CAT6_(A, B, C, D, E, __VA_ARGS__)
#define ALIAS_CPP_CAT6_(A, B, C, D, E, ...) A ## B ## C ## D ## E ## __VA_ARGS__

#endif
