#ifndef _ALIAS_PHYSICS_LOCAL_H_
#define _ALIAS_PHYSICS_LOCAL_H_

#include <alias/physics.h>
#include <alias/data_structure/bvh.h>

typedef struct alias_Physics2DBodyMotion {
  alias_pga2d_Bivector force;
  alias_pga2d_Bivector linear_force;
  alias_pga2d_Bivector area_of_moment_of_ineria;
} alias_Physics2DBodyMotion;

#endif
