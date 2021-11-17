// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <alias/transform.h>
//#include <alias/physics.h>

enum {
    Binding_Left
  , Binding_Right
  , Binding_Escape
  , Binding_Enter
  , Binding_Pause
};

enum {
    Action_Left
  , Action_Right
  , Action_Pause
  , Action_Restart
  , Action_Exit
};

typedef void (* alias_State_function)(void *);

typedef struct alias_State {
  alias_State_function begin;
  alias_State_function pause;
  alias_State_function unpause;
  alias_State_function end;
  alias_State_function update;
  alias_State_function background;
  void * user_data;
  struct alias_State * previous;
} alias_State;

static inline void alias_push_state(alias_State ** state_machine, alias_State * new_state) {
  if(*state_machine != NULL && (*state_machine)->pause != NULL) {
    (*state_machine)->pause((*state_machine)->user_data);
  }
  new_state->previous = *state_machine;
  *state_machine = new_state;
  if(new_state->begin != NULL) {
    new_state->begin(new_state->user_data);
  }
}

static inline void alias_pop_state(alias_State ** state_machine) {
  if(*state_machine == NULL) {
    return;
  }
  if((*state_machine)->end != NULL) {
    (*state_machine)->end((*state_machine)->user_data);
  }
  *state_machine = (*state_machine)->previous;
  if((*state_machine) != NULL && (*state_machine)->unpause != NULL) {
    (*state_machine)->unpause((*state_machine)->user_data);
  }
}

static inline void alias_update_state(alias_State ** state_machine) {
  alias_State * current = *state_machine;
  if(current->update != NULL) {
    current->update(current->user_data);
  }
  if(current != NULL) {
    current = current->previous;
  }
  while(current != NULL) {
    if(current->background != NULL) {
      current->background(current->user_data);
    }
    current = current->previous;
  }
}

// =============================================================================================================================================================
// =============================================================================================================================================================

alias_TransformBundle g_transform_bundle;
//alias_Physics2DBundle g_physics_2d_bundle;
alias_State * g_state_machine = NULL;

// =============================================================================================================================================================
static inline void _paused_begin(void * ud) {
  (void)ud;
}
static inline void _paused_update(void * ud) {
  (void)ud;
}
static inline void _paused_end(void * ud) {
  (void)ud;
}
static alias_State Paused = {
    .begin  = _paused_begin
  , .update = _paused_update
  , .end    = _paused_end
};
// =============================================================================================================================================================
int main(int argc, char * argv []) {
  (void)argc;
  (void)argv;
  alias_push_state(&g_state_machine, &Paused);
  alias_update_state(&g_state_machine);
}
