#ifndef _ALIAS_PHYSICS_LOCAL_H_
#define _ALIAS_PHYSICS_LOCAL_H_

#include <alias/physics.h>
#include <alias/data_structure/bvh.h>

typedef struct alias_Physics2DBodyMotion {
  alias_pga2d_Vector forque;
  alias_pga2d_Vector I;
} alias_Physics2DBodyMotion;

#endif
