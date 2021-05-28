#include <alias/physics.h>

alias_ecs_Result alias_Physics2DBundle_initialize(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_TransformBundle * transform_bundle) {
  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Physics2DParticle)
    , .num_required_components = 1
    , .required_components = &transform_bundle->Translation2D_component
  }, &bundle->Physics2DParticle_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Physics2DMass)
    , .num_required_components = 1
    , .required_components = &bundle->Physics2DParticle_component
  }, &bundle->Physics2DMass_component);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 1
    , .write_components = &transform_bundle->Translation2D_component
    , .num_read_components = 1
    , .read_components = &bundle->Physics2DParticle_component
#if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
    , .num_filters = 1
    , .filters = &(alias_ecs_QueryFilterCreateInfo) {
        .filter = ALIAS_ECS_FILTER_EXCLUDE
      , .component = transform_bundle->Parent2D_component
      }
#endif
  }, &bundle->particle_query);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 1
    , .write_components = &bundle->Physics2DParticle_component
    , .num_read_components = 1
    , .read_components = &bundle->Physics2DMass_component
#if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
    , .num_filters = 1
    , .filters = (alias_ecs_QueryFilterCreateInfo[]) {
        { .filter = ALIAS_ECS_FILTER_EXCLUDE
        , .component = transform_bundle->Parent2D_component
        }
      }
#endif
  }, &bundle->particle_mass_query);

  return ALIAS_ECS_SUCCESS;
}

// =============================================================================================================================================================
struct _update2d_particles_data {
  alias_R t;
};

static void _update2d_particles(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)instance;
  (void)entity;

  struct _update2d_particles_data * udata = (struct _update2d_particles_data *)ud;
  alias_R t = udata->t;

  alias_Translation2D * translation = (alias_Translation2D *)data[0];
  const alias_Physics2DParticle * particle = (const alias_Physics2DParticle *)data[1];

  translation->value.x = alias_fma(particle->velocity.x, t, translation->value.x);
  translation->value.y = alias_fma(particle->velocity.y, t, translation->value.y);
}

void alias_physics_update2d_particles(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  struct _update2d_particles_data udata = { .t = duration };
  alias_ecs_execute_query(instance, bundle->particle_query, (alias_ecs_QueryCB) { _update2d_particles, &udata });
}

// =============================================================================================================================================================
struct _update2d_particles_mass_data {
  alias_R t;
  alias_R half_t;
};

static void _update2d_particles_mass(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)instance;
  (void)entity;

  struct _update2d_particles_mass_data * udata = (struct _update2d_particles_mass_data *)ud;
  alias_R t = udata->t;
  alias_R half_t = udata->half_t;

  alias_Physics2DParticle * particle = (alias_Physics2DParticle *)data[0];
  alias_Physics2DMass * mass = (alias_Physics2DMass *)data[1];

  alias_Vector2D total_acceleration = {
      .x = alias_fma(mass->accumulated_force.x, mass->inverse, particle->acceleration.x)
    , .y = alias_fma(mass->accumulated_force.y, mass->inverse, particle->acceleration.y)
    };
  alias_R damping_pow_t = alias_pow(particle->damping, t);
  particle->velocity.x = alias_fma(total_acceleration.x, half_t, particle->velocity.x) * damping_pow_t;
  particle->velocity.y = alias_fma(total_acceleration.y, half_t, particle->velocity.y) * damping_pow_t;

  mass->accumulated_force.x = 0.0f;
  mass->accumulated_force.y = 0.0f;
}

void alias_physics_update2d_particles_mass(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  struct _update2d_particles_mass_data udata = { .t = duration, .half_t = duration / 2.0f };
  alias_ecs_execute_query(instance, bundle->particle_query, (alias_ecs_QueryCB) { _update2d_particles, &udata });
}

// =============================================================================================================================================================

void alias_physics_update2d_serial(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  // TODO events
  alias_physics_update2d_particles(instance, bundle, duration);
}

