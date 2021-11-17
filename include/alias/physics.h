// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_PHYSICS_H_
#define _ALIAS_PHYSICS_H_

#include <alias/math.h>
#include <alias/transform.h>
#include <alias/ecs.h>

#ifndef ALIAS_PHYSICS_2D_MAX_POLYGON_POINTS
#define ALIAS_PHYSICS_2D_MAX_POLYGON_POINTS 32
#endif

#if 0
(d - 1)-vectors
forque   - join line through the contact point - F = .P
momentum - sum of join lines                   - P = |F

dual
F = A*, F = m*a, t = m*rXF
P = V*, P = m*v, L = I*w

2-vectors
acceleration - meet line through the motion center - A = .V
velocity     - sum of meet lines                   - V = |A
position     - motor (2k-refl)                     - M = |V

.V* = F - !V X V
.M = -(M * V)

P = I[B]
momentum P - join line - (d-1)-vector
inertia I[] - duality map
rate B - hyperline 2-vector

(e12, e01, e02)
[ 0 m 0 ]
[ 0 0 m ]
[ I 0 0 ]

changes meet lines to join lines

force(position, velocity) {
   gravity = dual(sandwich(state.gravity_line, reverse(position)))
   damping = -0.25 * dual(velocity);
   hooke = spring_strength * sandwich(world_point, reverse(position)) & body_point
   return gravity + damping + hooke;
}
differential_function(position, velocity, out_position, acceleration) {
  out_position = -(position * velocity)
  acceleration = dual(force(position, velocity) - dual(velocity) X velocity)
}
update(position, velocity, time_delta) {
  out_position, acceleration = differential_function(position, velocity);
  position += out_position * time_delta;
  velocity += acceleration * time_delta;
}

transform:
  position

physics_motion:
  velocity

physics_body_motion:
  forque
  properties

phase1 {
  position = sub(position, mul(time_delta, mul(position, velocity)));
}

force_gravity {
  forque = add(forque, dual(sandwich(gravity_line, reverse(position))));
}

force_damping {
  forque = sub(forque, mul(damping_strength, dual(velocity)));
}

force_hooke {
  forque = add(forque, mul(spring_strength, sandwich(external_point_in_world_space, reverse(position)) & own_point_in_body_space));
}

body_to_inertia_space(i, x) element_mul(dual(x), i)
inertia_to_body_space(i, x) dual(element_div(x, i))

phase2 {
  //velocity = add(velocity, mul(time_delta, inertia_to_body_space(inertia, forque - commutator_product(body_to_inertia_space(inertia, velocity), velocity))));
  velocity = add(velocity, mul(time_delta, dual(forque - commutator_product(dual(velocity), velocity))));
  forque = 0;
}
#endif

// an Entity without linear motion is not movable (static)
typedef struct alias_Physics2DMotion {
  alias_pga2d_Bivector value;
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

typedef struct alias_Physics2DGravity {
  alias_R value;
} alias_Physics2DGravity;

typedef struct alias_Physics2DDampen {
  alias_R value;
} alias_Physics2DDampen;

typedef struct alias_Physics2DBodyMotion {
  alias_pga2d_AntiBivector forque;
  alias_pga2d_AntiBivector I;
} alias_Physics2DBodyMotion;

typedef struct alias_Physics2DBundle {
  alias_TransformBundle * transform_bundle;

  // not sure what this means but i remember this from the talk:
  // this is a force line. a join of two points
  // I am assuming this can be used to create a force line by joining origin point with a point at the strength desired
  alias_pga2d_Bivector gravity;

  alias_ecs_EntityHandle bvh_root;

  alias_ecs_ComponentHandle Physics2DMotion_component;
  alias_ecs_ComponentHandle Physics2DMass_component; // requires alias_Physics2DBodyMotion
  //alias_ecs_ComponentHandle Physics2DCollision_component; // requires alias_Physics2DBodyCollision
  alias_ecs_ComponentHandle Physics2DCircle_component; // effects Mass and Collision components, not required by either
  alias_ecs_ComponentHandle Physics2DRectangle_component;

  alias_ecs_ComponentHandle Physics2DGravity_component;
  alias_ecs_ComponentHandle Physics2DDampen_component;

  alias_ecs_ComponentHandle Physics2DBodyMotion_component; // requires alias_Physics2DMotion
  //alias_ecs_ComponentHandle Physics2DBodyCollision_component;

  alias_ecs_Query * transform_motion_query;
  alias_ecs_Query * circle_mass_query;
  alias_ecs_Query * rectangle_mass_query;
  //alias_ecs_Query * circle_collision_query;
  //alias_ecs_Query * rectangle_collision_query;
  //alias_ecs_Query * bvh_build_query;
  //alias_ecs_Query * bvh_test_query;
  alias_ecs_Query * force_gravity_query;
  alias_ecs_Query * force_dampen_query;
  alias_ecs_Query * body_motion_query;
} alias_Physics2DBundle;

alias_ecs_Result alias_Physics2DBundle_initialize(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_TransformBundle * transform_bundle);
void alias_physics_update2d_serial_pre_transform(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration);
void alias_physics_update2d_serial_post_transform(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration);

#endif
