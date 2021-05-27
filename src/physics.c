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

}

void alias_physics_update2d_particles(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  alias_ecs_execute_query(instance, bundle->particle_query, (alias_ecs_QueryCB) { _construct_local_from_translation, bundle });
}

// =============================================================================================================================================================

void alias_physics_update2d_serial(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {
  alias_physics_update2d_particles(instance, bundle, duration);
}

