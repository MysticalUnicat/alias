#ifndef _ALIAS_PHYSICS_H_
#define _ALIAS_PHYSICS_H_

#include <alias/math.h>
#include <alias/transform.h>
#include <alias/ecs.h>

typedef struct alias_Physics2DParticle {
  alias_Vector2D velocity;
  alias_Vector2D acceleration;

  alias_Vector2D accumulated_force;

  alias_R damping;
  alias_R mass;
} alias_Physics2DParticle;

typedef struct alias_Physics2DBundle {
  alias_TransformBundle * transform_bundle;

  alias_ecs_ComponentHandle Physics2DParticle_component;

  alias_ecs_Query * particle_query;
} alias_Physics2DBundle;

alias_ecs_Result alias_Physics2DBundle_initialize(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_TransformBundle * transform_bundle);
void alias_physics_update2d_serial(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration);

#endif

