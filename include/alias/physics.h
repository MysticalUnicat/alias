#ifndef _ALIAS_PHYSICS_H_
#define _ALIAS_PHYSICS_H_

#include <alias/math.h>
#include <alias/transform.h>
#include <alias/ecs.h>

typedef struct alias_Physics2DParticle {
  alias_Vector2D velocity;
  alias_Vector2D acceleration;

  alias_R damping;

  alias_R inverse_mass;
} alias_Physics2DParticle;

typedef struct alias_Physics2DBundle {
  alias_TransformBundle * transform_bundle;

  alias_ecs_ComponentHandle Physics2DParticle_component;

  alias_ecs_Query * particle_query;
} alias_Physics2DBundle;



#endif

