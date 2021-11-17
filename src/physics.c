// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "physics_local.h"

alias_ecs_Result alias_Physics2DBundle_initialize(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_TransformBundle * transform_bundle) {
  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Physics2DMotion)
    , .num_required_components = 1
    , .required_components = &transform_bundle->Transform2D_component
  }, &bundle->Physics2DMotion_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Physics2DBodyMotion)
    , .num_required_components = 1
    , .required_components = &bundle->Physics2DMotion_component
  }, &bundle->Physics2DBodyMotion_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Physics2DMass)
    , .num_required_components = 1
    , .required_components = &bundle->Physics2DBodyMotion_component
  }, &bundle->Physics2DMass_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Physics2DCircle)
  }, &bundle->Physics2DCircle_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Physics2DRectangle)
  }, &bundle->Physics2DRectangle_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Physics2DGravity)
    , .num_required_components = 1
    , .required_components = &bundle->Physics2DBodyMotion_component
  }, &bundle->Physics2DGravity_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Physics2DDampen)
    , .num_required_components = 1
    , .required_components = &bundle->Physics2DBodyMotion_component
  }, &bundle->Physics2DDampen_component);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 2
    , .write_components = (alias_ecs_ComponentHandle[]) { transform_bundle->Transform2D_component, bundle->Physics2DMotion_component }
    , .num_filters = 1
    , .filters = &(alias_ecs_QueryFilterCreateInfo) {
        .filter = ALIAS_ECS_FILTER_EXCLUDE
      , .component = transform_bundle->Parent2D_component
      }
  }, &bundle->transform_motion_query);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 1
    , .write_components = &bundle->Physics2DBodyMotion_component
    , .num_read_components = 2
    , .read_components = (alias_ecs_ComponentHandle[]) { bundle->Physics2DCircle_component, bundle->Physics2DMass_component }
    , .num_filters = 3
    , .filters = (alias_ecs_QueryFilterCreateInfo[]) {
          { .filter = ALIAS_ECS_FILTER_EXCLUDE
          , .component = transform_bundle->Parent2D_component
          }
        , { .filter = ALIAS_ECS_FILTER_MODIFIED
          , .component = bundle->Physics2DCircle_component
          }
        , { .filter = ALIAS_ECS_FILTER_MODIFIED
          , .component = bundle->Physics2DMass_component
          }
      }
  }, &bundle->circle_mass_query);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 1
    , .write_components = &bundle->Physics2DBodyMotion_component
    , .num_read_components = 2
    , .read_components = (alias_ecs_ComponentHandle[]) { bundle->Physics2DRectangle_component, bundle->Physics2DMass_component }
    , .num_filters = 3
    , .filters = (alias_ecs_QueryFilterCreateInfo[]) {
          { .filter = ALIAS_ECS_FILTER_EXCLUDE
          , .component = transform_bundle->Parent2D_component
          }
        , { .filter = ALIAS_ECS_FILTER_MODIFIED
          , .component = bundle->Physics2DRectangle_component
          }
        , { .filter = ALIAS_ECS_FILTER_MODIFIED
          , .component = bundle->Physics2DMass_component
          }
      }
  }, &bundle->rectangle_mass_query);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 1
    , .write_components = &bundle->Physics2DBodyMotion_component
    , .num_read_components = 2
    , .read_components = (alias_ecs_ComponentHandle[]) { transform_bundle->Transform2D_component, bundle->Physics2DGravity_component }
    , .num_filters = 1
    , .filters = &(alias_ecs_QueryFilterCreateInfo) {
        .filter = ALIAS_ECS_FILTER_EXCLUDE
      , .component = transform_bundle->Parent2D_component
      }
  }, &bundle->force_gravity_query);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 1
    , .write_components = &bundle->Physics2DBodyMotion_component
    , .num_read_components = 2
    , .read_components = (alias_ecs_ComponentHandle[]) { bundle->Physics2DMotion_component, bundle->Physics2DDampen_component }
    , .num_filters = 1
    , .filters = &(alias_ecs_QueryFilterCreateInfo) {
        .filter = ALIAS_ECS_FILTER_EXCLUDE
      , .component = transform_bundle->Parent2D_component
      }
  }, &bundle->force_dampen_query);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 2
    , .write_components = (alias_ecs_ComponentHandle[]) { bundle->Physics2DMotion_component, bundle->Physics2DBodyMotion_component }
    , .num_filters = 1
    , .filters = &(alias_ecs_QueryFilterCreateInfo) {
        .filter = ALIAS_ECS_FILTER_EXCLUDE
      , .component = transform_bundle->Parent2D_component
      }
  }, &bundle->body_motion_query);

  return ALIAS_ECS_SUCCESS;
}

// =============================================================================================================================================================
struct _update_data {
  alias_R t;
  alias_R half_t;
  alias_pga2d_Bivector gravity;
};

void _fill_update_data(struct _update_data * data, alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  (void)instance;
  data->t = duration;
  data->half_t = 1.0f / duration;
  data->gravity = bundle->gravity;
}

// =============================================================================================================================================================
static void _update2d_transform_motion(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)instance;
  (void)entity;

  struct _update_data * udata = (struct _update_data *)ud;
  alias_Transform2D * transform = (alias_Transform2D *)data[0];
  alias_Physics2DMotion * motion = (alias_Physics2DMotion *)data[1];

  // position = sub(position, mul(time_delta / 2, mul(position, velocity)));
  transform->value = alias_pga2d_sub(
      alias_pga2d_m(transform->value)
    , alias_pga2d_mul(
        alias_pga2d_s(udata->t / 2)
      , alias_pga2d_mul_mb(transform->value, motion->value)
      )
    );
}

void alias_physics_update2d_transform_motion(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  struct _update_data udata;
  _fill_update_data(&udata, instance, bundle, duration);
  alias_ecs_execute_query(instance, bundle->transform_motion_query, (alias_ecs_QueryCB) { _update2d_transform_motion, &udata });
}

// =============================================================================================================================================================
static void _update2d_circle_mass(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;

  alias_Physics2DBodyMotion * body = (alias_Physics2DBodyMotion *)data[0];
  const alias_Physics2DCircle * circle = (const alias_Physics2DCircle *)data[1];
  const alias_Physics2DMass * mass = (const alias_Physics2DMass *)data[2];

  alias_R r = circle->radius, x = alias_R_PI * r*r*r*r / 4;
  body->I = alias_pga2d_mul_sv(mass->value, ((alias_pga2d_Vector) { .e0 = 1, .e1 = x, .e2 = x }));
}

void alias_physics_update2d_circle_mass(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->circle_mass_query, (alias_ecs_QueryCB) { _update2d_circle_mass, NULL });
}

// =============================================================================================================================================================
static void _update2d_rectangle_mass(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;

  alias_Physics2DBodyMotion * body = (alias_Physics2DBodyMotion *)data[0];
  const alias_Physics2DRectangle * rectangle = (const alias_Physics2DRectangle *)data[1];
  const alias_Physics2DMass * mass = (const alias_Physics2DMass *)data[2];

  alias_R w = rectangle->width
        , h = rectangle->height;
  body->I = alias_pga2d_mul_sv(mass->value, ((alias_pga2d_Vector) { .e0 = 1, .e1 = (h * w*w*w) / 12, .e2 = (w * h*h*h) / 12 }));
}

void alias_physics_update2d_rectangle_mass(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->rectangle_mass_query, (alias_ecs_QueryCB) { _update2d_rectangle_mass, NULL });
}

// =============================================================================================================================================================
static void _update2d_force_gravity(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)instance;
  (void)entity;

  struct _update_data * udata = (struct _update_data *)ud;

  alias_Physics2DBodyMotion * body = (alias_Physics2DBodyMotion *)data[0];
  const alias_Transform2D * position = (const alias_Transform2D *)data[1];
  const alias_Physics2DGravity * gravity = (const alias_Physics2DGravity *)data[2];

  // gravity = mul(gravity_scale, dual(sandwich(gravity_line, reverse(position))))
  body->forque = alias_pga2d_add(
      alias_pga2d_v(body->forque),
      alias_pga2d_mul(alias_pga2d_s(gravity->value),
                      alias_pga2d_dual(alias_pga2d_grade_2(alias_pga2d_sandwich(
                          alias_pga2d_b(udata->gravity),
                          alias_pga2d_reverse_m(position->value))))));
}

void alias_physics_update2d_force_gravity(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle) {
  struct _update_data udata;
  _fill_update_data(&udata, instance, bundle, 0);
  alias_ecs_execute_query(instance, bundle->force_gravity_query, (alias_ecs_QueryCB) { _update2d_force_gravity, &udata });
}

// =============================================================================================================================================================
static void _update2d_force_dampen(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;

  alias_Physics2DBodyMotion * body = (alias_Physics2DBodyMotion *)data[0];
  const alias_Physics2DMotion * velocity = (const alias_Physics2DMotion *)data[1];
  const alias_Physics2DDampen * dampen = (const alias_Physics2DDampen *)data[2];

  // damping = -0.25 * dual(velocity);
  body->forque = alias_pga2d_sub(
      alias_pga2d_v(body->forque),
      alias_pga2d_mul(
          alias_pga2d_s(dampen->value),
          alias_pga2d_dual_b(velocity->value)));
}

void alias_physics_update2d_force_dampen(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->force_dampen_query, (alias_ecs_QueryCB) { _update2d_force_dampen, NULL });
}

#include <stdio.h>

// =============================================================================================================================================================
static void _update2d_body_motion(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)instance;
  (void)entity;

  struct _update_data * udata = (struct _update_data *)ud;

  alias_Physics2DMotion * motion = (alias_Physics2DMotion *)data[0];
  alias_Physics2DBodyMotion * body = (alias_Physics2DBodyMotion *)data[1];

  alias_pga2d_Bivector velocity = motion->value;
  alias_pga2d_AntiBivector forque = body->forque;

  // velocity = add(velocity, mul(time_delta, dual(sub(forque, commutator_product(dual(velocity), velocity)))));
  alias_pga2d_AntiBivector momentum = alias_pga2d_commutator_product(
      alias_pga2d_dual_b(velocity), alias_pga2d_b(velocity));

  motion->value = alias_pga2d_add(
      alias_pga2d_b(velocity),
      alias_pga2d_mul(
          alias_pga2d_s(udata->t),
          alias_pga2d_dual(alias_pga2d_sub_vv(forque, momentum))));
  
  alias_memory_clear(&body->forque, sizeof(body->forque));
}

void alias_physics_update2d_body_motion(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  struct _update_data udata;
  _fill_update_data(&udata, instance, bundle, duration);
  alias_ecs_execute_query(instance, bundle->body_motion_query, (alias_ecs_QueryCB) { _update2d_body_motion, &udata });
}

// =============================================================================================================================================================

void alias_physics_update2d_serial_pre_transform(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  alias_physics_update2d_transform_motion(instance, bundle, duration);
  alias_physics_update2d_circle_mass(instance, bundle);
  alias_physics_update2d_rectangle_mass(instance, bundle);
}

void alias_physics_update2d_serial_post_transform(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  alias_physics_update2d_force_gravity(instance, bundle);
  alias_physics_update2d_force_dampen(instance, bundle);
  alias_physics_update2d_body_motion(instance, bundle, duration);
}

