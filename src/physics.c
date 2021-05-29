#include <alias/physics.h>

typedef struct alias_Physics2DLinearSpeed {
  alias_R speed;
  alias_Normal2D direction;
} alias_Physics2DLinearSpeed;

alias_ecs_Result alias_Physics2DBundle_initialize(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_TransformBundle * transform_bundle) {
  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Physics2DLinearMotion)
    , .num_required_components = 1
    , .required_components = &transform_bundle->Translation2D_component
  }, &bundle->Physics2DLinearMotion_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Physics2DLinearMass)
    , .num_required_components = 1
    , .required_components = &bundle->Physics2DLinearMotion_component
  }, &bundle->Physics2DLinearMass_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Physics2DLinearMass)
    , .num_required_components = 1
    , .required_components = &bundle->Physics2DLinearMass_component
  }, &bundle->Physics2DGravity_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Physics2DLinearMass)
    , .num_required_components = 1
    , .required_components = &bundle->Physics2DLinearMass_component
  }, &bundle->Physics2DDrag_component);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 2
    , .write_components = (alias_ecs_ComponentHandle[]) { transform_bundle->Translation2D_component, bundle->Physics2DLinearMotion_component }
#if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
    , .num_filters = 1
    , .filters = &(alias_ecs_QueryFilterCreateInfo) {
        .filter = ALIAS_ECS_FILTER_EXCLUDE
      , .component = transform_bundle->Parent2D_component
      }
#endif
  }, &bundle->integrate_position_query);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 1
    , .write_components = &bundle->Physics2DLinearMass_component
    , .num_read_components = 1
    , .read_components = &bundle->Physics2DGravity_component
#if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
    , .num_filters = 1
    , .filters = &(alias_ecs_QueryFilterCreateInfo) {
        .filter = ALIAS_ECS_FILTER_EXCLUDE
      , .component = transform_bundle->Parent2D_component
      }
#endif
  }, &bundle->gravity_query);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 1
    , .write_components = &bundle->Physics2DLinearMass_component
    , .num_read_components = 2
    , .read_components = (alias_ecs_ComponentHandle[]) { bundle->Physics2DLinearMotion_component, bundle->Physics2DDrag_component }
#if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
    , .num_filters = 1
    , .filters = &(alias_ecs_QueryFilterCreateInfo) {
        .filter = ALIAS_ECS_FILTER_EXCLUDE
      , .component = transform_bundle->Parent2D_component
      }
#endif
  }, &bundle->drag_query);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 2
    , .write_components = (alias_ecs_ComponentHandle[]){ bundle->Physics2DLinearMotion_component, bundle->Physics2DLinearMass_component }
#if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
    , .num_filters = 1
    , .filters = &(alias_ecs_QueryFilterCreateInfo) {
        .filter = ALIAS_ECS_FILTER_EXCLUDE
      , .component = transform_bundle->Parent2D_component
      }
#endif
  }, &bundle->integrate_velocity_query);

  return ALIAS_ECS_SUCCESS;
}

// =============================================================================================================================================================
struct _update_data {
  alias_R t;
  alias_R half_t;
  alias_Vector2D gravity;
};

void _fill_update_data(struct _update_data * data, alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  (void)instance;
  data->t = duration;
  data->half_t = 1.0f / duration;
  data->gravity = bundle->gravity;
}

// =============================================================================================================================================================
static void _update2d_integrate_position(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)instance;
  (void)entity;

  struct _update_data * udata = (struct _update_data *)ud;
  alias_Translation2D * translation = (alias_Translation2D *)data[0];
  alias_Physics2DLinearMotion * motion = (alias_Physics2DLinearMotion *)data[1];

  alias_R scale = udata->t;

  translation->value.x = alias_fma(motion->velocity.x, scale, translation->value.x);
  translation->value.y = alias_fma(motion->velocity.y, scale, translation->value.y);
  motion->velocity.x *= motion->damping;
  motion->velocity.y *= motion->damping;

  motion->speed = alias_Vector2D_length(motion->velocity);
  motion->direction = alias_Vector2D_scale(motion->velocity, motion->speed > 0.0f ? 1.0f / motion->speed : 0.0f);
}

void alias_physics_update2d_integrate_position(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  struct _update_data udata;
  _fill_update_data(&udata, instance, bundle, duration);
  alias_ecs_execute_query(instance, bundle->integrate_position_query, (alias_ecs_QueryCB) { _update2d_integrate_position, &udata });
}

// =============================================================================================================================================================
static void _update2d_apply_gravity(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)instance;
  (void)entity;

  struct _update_data * udata = (struct _update_data *)ud;
  alias_Physics2DLinearMass * mass = (alias_Physics2DLinearMass *)data[0];
  const alias_Physics2DGravity * gravity = (const alias_Physics2DGravity *)data[1];

  alias_R scale = mass->mass * gravity->global_gravity_scale;

  mass->force.x = alias_fma(udata->gravity.x, scale, mass->force.x);
  mass->force.y = alias_fma(udata->gravity.y, scale, mass->force.y);
}

void alias_physics_update2d_apply_gravity(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  struct _update_data udata;
  _fill_update_data(&udata, instance, bundle, duration);
  alias_ecs_execute_query(instance, bundle->gravity_query, (alias_ecs_QueryCB) { _update2d_apply_gravity, &udata });
}

// =============================================================================================================================================================
static void _update2d_apply_drag(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;

  alias_Physics2DLinearMass * mass = (alias_Physics2DLinearMass *)data[0];
  const alias_Physics2DLinearMotion * motion = (const alias_Physics2DLinearMotion *)data[1];
  const alias_Physics2DDrag * drag = (const alias_Physics2DDrag *)data[2];

  alias_R length = alias_Vector2D_length(motion->velocity);
  alias_R scale = -(drag->velocity_drag_coefficient + drag->velocity_squared_drag_coefficient * length);

  mass->force.x = alias_fma(motion->velocity.x, scale, mass->force.x);
  mass->force.y = alias_fma(motion->velocity.y, scale, mass->force.y);
}

void alias_physics_update2d_apply_drag(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  (void)duration;
  alias_ecs_execute_query(instance, bundle->drag_query, (alias_ecs_QueryCB) { _update2d_apply_drag, NULL });
}

// =============================================================================================================================================================
static void _update2d_integrate_velocity(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)instance;
  (void)entity;

  struct _update_data * udata = (struct _update_data *)ud;

  alias_Physics2DLinearMotion * motion = (alias_Physics2DLinearMotion *)data[0];
  alias_Physics2DLinearMass * mass = (alias_Physics2DLinearMass *)data[1];

  alias_R scale = mass->inverse_mass * udata->t;

  motion->velocity.x = alias_fma(mass->force.x, scale, motion->velocity.x);
  motion->velocity.y = alias_fma(mass->force.y, scale, motion->velocity.y);
  mass->force.x = 0.0f;
  mass->force.y = 0.0f;
}

void alias_physics_update2d_integrate_velocity(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  struct _update_data udata;
  _fill_update_data(&udata, instance, bundle, duration);
  alias_ecs_execute_query(instance, bundle->integrate_velocity_query, (alias_ecs_QueryCB) { _update2d_integrate_velocity, &udata });
}

// =============================================================================================================================================================

void alias_physics_update2d_serial_pre_transform(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  alias_physics_update2d_integrate_position(instance, bundle, duration);
}

void alias_physics_update2d_serial_post_transform(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  alias_physics_update2d_apply_gravity(instance, bundle, duration);
  alias_physics_update2d_apply_drag(instance, bundle, duration);
  alias_physics_update2d_integrate_velocity(instance, bundle, duration);
}

