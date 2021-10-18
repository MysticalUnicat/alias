#ifndef _ALIAS_PHYSICS_H_
#define _ALIAS_PHYSICS_H_

#include <alias/math.h>
#include <alias/transform.h>
#include <alias/ecs.h>

#ifndef ALIAS_PHYSICS_2D_MAX_POLYGON_POINTS
#define ALIAS_PHYSICS_2D_MAX_POLYGON_POINTS 32
#endif

// an Entity without linear motion is not movable (static)
typedef struct alias_Physics2DMotion {
  alias_pga2d_Bivector velocity;
} alias_Physics2DMotion;

// an Entity without mass is not movable by physics (kinematic)
typedef struct alias_Physics2DMass {
  alias_R value;
} alias_Physics2DMass;

typedef struct alias_Physics2DCollision {
  uint32_t mask;
} alias_Physics2DCollision;

typedef struct alias_Physics2DCircle {
  alias_R radius;
} alias_Physics2DCircle;

typedef struct alias_Physics2DRectangle {
  alias_R width;
  alias_R height;
} alias_Physics2DRectangle;

typedef struct alias_Physics2DBundle {
  alias_TransformBundle * transform_bundle;

  alias_pga2d_Direction gravity;

  alias_ecs_EntityHandle bvh_root;

  alias_ecs_ComponentHandle Physics2DMotion_component;
  alias_ecs_ComponentHandle Physics2DMass_component; // requires alias_Physics2DBodyMotion
  //alias_ecs_ComponentHandle Physics2DCollision_component; // requires alias_Physics2DBodyCollision
  alias_ecs_ComponentHandle Physics2DCircle_component; // effects Mass and Collision components, not required by either
  alias_ecs_ComponentHandle Physics2DRectangle_component;

  alias_ecs_ComponentHandle Physics2DBodyMotion_component; // requires alias_Physics2DMotion
  //alias_ecs_ComponentHandle Physics2DBodyCollision_component;

  alias_ecs_Query * transform_motion_query;
  alias_ecs_Query * circle_mass_query;
  alias_ecs_Query * rectangle_mass_query;
  //alias_ecs_Query * circle_collision_query;
  //alias_ecs_Query * rectangle_collision_query;
  //alias_ecs_Query * bvh_build_query;
  //alias_ecs_Query * bvh_test_query;
  //alias_ecs_Query * forces_queries;
  alias_ecs_Query * body_motion_query;
} alias_Physics2DBundle;

alias_ecs_Result alias_Physics2DBundle_initialize(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_TransformBundle * transform_bundle);
void alias_physics_update2d_serial_pre_transform(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration);
void alias_physics_update2d_serial_post_transform(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration);

#endif
