// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_CPP_PROBE_H_
#define _ALIAS_CPP_PROBE_H_

#define ALIAS_CPP_PROBE(...) ~, 1

#define ALIAS_CPP_IS_PROBE(...) ALIAS_CPP_IS_PROBE_(__VA_ARGS__, 0, 0)
#define ALIAS_CPP_IS_PROBE_(X, Y, ...) Y

#endif
