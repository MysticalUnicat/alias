#include <alias/physics.h>

alias_ecs_Result alias_Physics2DBundle_initialize(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_TransformBundle * transform_bundle) {
  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Physics2DParticle)
    , .num_required_components = 1
    , .required_components = &transform_bundle->Translation2D_component
  }, &bundle->Physics2DParticle_component);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 2
    , .write_components = (alias_ecs_ComponentHandle[]) { 
        transform_bundle->Translation2D_component
      , bundle->Physics2DParticle_component
      }
#if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
    , .num_filters = 1
    , .filters = &(alias_ecs_QueryFilterCreateInfo) {
        .filter = ALIAS_ECS_FILTER_EXCLUDE
      , .component = transform_bundle->Parent2D_component
      }
#endif
  }, &bundle->particle_query);

  return ALIAS_ECS_SUCCESS;
}

// =============================================================================================================================================================
struct _update2d_particles_data {
  alias_R duration;
};

static void _update2d_particles(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  struct _update2d_particles_data * udata = (struct _update2d_particles_data *)ud;
  (void)instance;
  (void)entity;
  alias_R duration = udata->duration;
  alias_Translation2D * translation = (alias_Translation2D *)data[0];
  alias_Physics2DParticle * particle = (alias_Physics2DParticle *)data[1];
  translation->value.x = alias_fma(particle->velocity.x, duration, translation->value.x);
  translation->value.y = alias_fma(particle->velocity.y, duration, translation->value.y);
  alias_Vector2D total_acceleration = {
      .x = alias_fma(particle->accumulated_force.x, particle->inverse_mass, particle->acceleration.x
    , .y = alias_fma(particle->accumulated_force.y, particle->inverse_mass, particle->acceleration.y
    };
}

void alias_physics_update2d_particles(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  struct _update2d_particles_data udata = { .duration = duration };
  alias_ecs_execute_query(instance, bundle->particle_query, (alias_ecs_QueryCB) { _update2d_particles, &udata});
}

// =============================================================================================================================================================

void alias_physics_update2d_serial(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  alias_physics_update2d_particles(instance, bundle, duration);
}

