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
  alias_pga2d_Direction gravity;
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

  alias_pga2d_Bivector b = alias_pga2d_mul_bb(transform->bivector, motion->velocity);
  transform->bivector = alias_pga2d_lerp_b(transform->bivector, b, udata->t);
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
  body->area_of_moment_of_ineria = alias_pga2d_mul_sb(mass->value, ((alias_pga2d_Bivector) { .e01 = x, .e02 = x, .e12 = 1 }));
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
  body->area_of_moment_of_ineria = alias_pga2d_mul_sb(mass->value, ((alias_pga2d_Bivector) { .e01 = (h * w*w*w) / 12, .e02 = (w * h*h*h) / 12, .e12 = 1 }));
}

void alias_physics_update2d_rectangle_mass(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->rectangle_mass_query, (alias_ecs_QueryCB) { _update2d_rectangle_mass, NULL });
}

// =============================================================================================================================================================
static void _update2d_body_motion(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)instance;
  (void)entity;

  struct _update_data * udata = (struct _update_data *)ud;

  alias_Physics2DMotion * motion = (alias_Physics2DMotion *)data[0];
  alias_Physics2DBodyMotion * body = (alias_Physics2DBodyMotion *)data[1];

  alias_pga2d_Bivector I = body->area_of_moment_of_ineria;

  alias_pga2d_Bivector a = alias_pga2d_add(alias_pga2d_commutator_product_bb(body->force, I), alias_pga2d_b(body->linear_force));

  alias_pga2d_Bivector b = alias_pga2d_mul_bb(motion->velocity, a);
  motion->velocity = alias_pga2d_lerp_b(motion->velocity, b, udata->t);

  alias_memory_clear(&body->force, sizeof(body->force));
  alias_memory_clear(&body->linear_force, sizeof(body->linear_force));
}

void alias_physics_update2d_body_motion(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  struct _update_data udata;
  _fill_update_data(&udata, instance, bundle, duration);
  alias_ecs_execute_query(instance, bundle->integrate_velocity_query, (alias_ecs_QueryCB) { _update2d_body_motion, &udata });
}

// =============================================================================================================================================================

void alias_physics_update2d_serial_pre_transform(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  alias_physics_update2d_transform_motion(instance, bundle, duration);
  alias_physics_update2d_circle_mass(instance, bundle);
  alias_physics_update2d_rectangle_mass(instance, bundle);
}

void alias_physics_update2d_serial_post_transform(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  alias_physics_update2d_body_motion(instance, bundle, duration);
}

