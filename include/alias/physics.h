#ifndef _ALIAS_PHYSICS_H_
#define _ALIAS_PHYSICS_H_

#include <alias/math.h>
#include <alias/transform.h>
#include <alias/ecs.h>

typedef struct alias_AABB2D {
  alias_Vector2D min;
  alias_Vector2D max;
} alias_AABB2D;

static inline alias_AABB2D alias_AABB2D_union(alias_AABB2D a, alias_AABB2D b) {
  return (alias_AABB2D) {
      .min.x = alias_min(a.min.x, b.min.x)
    , .min.y = alias_min(a.min.y, b.min.y)
    , .max.x = alias_max(a.max.x, b.max.x)
    , .max.y = alias_max(a.max.y, b.max.y)
  };
}

// an Entity without linear motion is not movable (static)
typedef struct alias_Physics2DLinearMotion {
  alias_Vector2D velocity;
  alias_R damping; // required to be between 0.0 inclusive and 1.0 exclusive
} alias_Physics2DLinearMotion;

// an Entity without mass is not movable by physics (kinematic)
typedef struct alias_Physics2DLinearMass {
  alias_Vector2D force;
  alias_R mass; // required to be over 0.0
  alias_R inverse_mass;
} alias_Physics2DLinearMass;

#if 0
typedef struct alias_Physics2DRotationalMotion {
  alias_R velocity;
  alias_R damping; // required to be between 0.0 inclusive and 1.0 exclusive
} alias_Physics2DRotationalMotion;

// an Entity with this and Physics2DLinearMass is a rigid body, as collision entities apply force to 
typedef struct alias_Physics2DRotationalMass {
  alias_Point2D center_of_mass;

  alias_R torque;
  alias_R inertia; // required to be over 0.0
  alias_R inverse_inertia;
} alias_Physics2DRotationalMass;
#endif

typedef struct alias_Physics2DGravity {
  alias_R global_gravity_scale;
} alias_Physics2DGravity;

typedef struct alias_Physics2DDrag {
  alias_R velocity_drag_coefficient;
  alias_R velocity_squared_drag_coefficient;
} alias_Physics2DDrag;

typedef struct alias_Physics2DBundle {
  alias_TransformBundle * transform_bundle;

  alias_Vector2D gravity;

  alias_ecs_ComponentHandle Physics2DLinearMotion_component;
  alias_ecs_ComponentHandle Physics2DLinearMass_component;
  #if 0
  alias_ecs_ComponentHandle Physics2DRotationalMotion_component;
  alias_ecs_ComponentHandle Physics2DRotationalMass_component;
  #endif

  // internal cached data
  alias_ecs_ComponentHandle Physics2DLinearSpeed_component;

  // force generators
  alias_ecs_ComponentHandle Physics2DGravity_component;
  alias_ecs_ComponentHandle Physics2DDrag_component;

  alias_ecs_Query * integrate_position_query;
  alias_ecs_Query * cache_linear_speed_query;
  alias_ecs_Query * gravity_query;
  alias_ecs_Query * drag_query;
  alias_ecs_Query * integrate_velocity_query;
} alias_Physics2DBundle;

alias_ecs_Result alias_Physics2DBundle_initialize(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_TransformBundle * transform_bundle);
void alias_physics_update2d_serial_pre_transform(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration);
void alias_physics_update2d_serial_post_transform(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration);

// Translation2D += Physics2DLinearMotion.velocity * t
// Physics2DLinearMotion.velocity *= Physics2DLinearMotion.damping
// 
// <transform>
// 
// Physics2DLinearMass.force += <global gravity> * Phsyics2DGravity.global_gravity_scale
// 
// Physics2DLinearMass.force += v := Physics2DLinearMotion.velocity; m := mag(Physics2DLinearMotion.velocity); -v * (k1 + k2 * m)
// 
// Physics2DLinearMotion.velocity = () + Physics2DLinearMass.force * Physics2DLinearMass.inverse_mass * t
// Physics2DLinearMass.force = 0

#endif
