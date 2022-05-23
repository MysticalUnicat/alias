// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_STACKLESS_H_
#define _ALIAS_STACKLESS_H_

#include <alias/cpp/cat.h>

#include <stdbool.h>
#include <stdint.h>

typedef enum alias_stackless_State {
  alias_stackless_State_Running,
  alias_stackless_State_Waiting,
  alias_stackless_State_Yielded,
  alias_stackless_State_Exited,
  alias_stackless_State_Ended
} alias_stackless_State;

typedef struct alias_stackless_Context {
  void                  * init;
  void                  * target;
  alias_stackless_State state;
} alias_stackless_Context;

#define ALIAS__STACKLESS_SET \
ALIAS_CPP_CAT(stackless_target_, __LINE__): \
  stackless_context->target = &&ALIAS_CPP_CAT(stackless_target_, __LINE__);

#define ALIAS_STACKLESS_FUNCTION(NAME) void NAME (alias_stackless_Context * stackless_context)

#define ALIAS_STACKLESS_BEGIN \
  do { \
    stackless_context->state = alias_stackless_State_Running; \
    if(stackless_context->target != NULL) goto *stackless_context->target; \
  } while(0)

#define ALIAS_STACKLESS_END \
  do { \
    ALIAS__STACKLESS_SET \
    stackless_context->state = alias_stackless_State_Ended; \
    return; \
  } while(0)

#define alias_stackless_exit() \
  do { \
    ALIAS__STACKLESS_SET \
    stackless_context->state = alias_stackless_State_Exited; \
    return; \
  } while(0)

#define alias_stackless_yield() \
  do { \
    stackless_context->state = alias_stackless_State_Yielded; \
    ALIAS__STACKLESS_SET \
    if(stackless_context->state == alias_stackless_State_Yielded) { \
      return; \
    } \
  } while(0)

#endif
