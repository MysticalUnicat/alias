#ifndef _ALIAS_CPP_PROBE_H_
#define _ALIAS_CPP_PROBE_H_

#define ALIAS_CPP_PROBE(...) ~, 1

#define ALIAS_CPP_IS_PROBE(...) ALIAS_CPP_IS_PROBE_(__VA_ARGS__, 0, 0)
#define ALIAS_CPP_IS_PROBE_(X, Y, ...) Y

#endif
