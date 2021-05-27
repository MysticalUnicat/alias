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

void alias_Physics2DBundle_update2d_serial(alias_ecs_Instance * instance, alias_Physics2DBundle * bundle, alias_R duration) {

}

