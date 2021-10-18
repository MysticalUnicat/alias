#include <alias/transform.h>
#include <alias/log.h>

#include <math.h>
#include <stdbool.h>

static alias_ecs_Result _construct_query(
    alias_ecs_Instance    * instance
  , alias_TransformBundle * bundle
  , alias_ecs_Query *     * out
  , bool                    child
) {
  alias_ecs_ComponentHandle read_components[6];
  alias_ecs_QueryFilterCreateInfo filters[12];
  alias_ecs_QueryCreateInfo create_info = {
      .num_write_components = 1
    , .write_components = child ? &bundle->LocalToParent2D_component : &bundle->LocalToWorld2D_component
    , .read_components = read_components
    , .filters = filters
  };

  read_components[create_info.num_read_components] = bundle->Transform2D_component;
  create_info.num_read_components++;

  filters[create_info.num_filters].component = bundle->Transform2D_component;
  filters[create_info.num_filters].filter = ALIAS_ECS_FILTER_MODIFIED;
  create_info.num_filters++;

  if(child) {
    filters[create_info.num_filters].component = bundle->Parent2D_component;
    filters[create_info.num_filters].filter = ALIAS_ECS_FILTER_MODIFIED;
    create_info.num_filters++;
  } else {
    filters[create_info.num_filters].component = bundle->Parent2D_component;
    filters[create_info.num_filters].filter = ALIAS_ECS_FILTER_EXCLUDE;
    create_info.num_filters++;
  }
  
  return alias_ecs_create_query(instance, &create_info, out);
}

alias_ecs_Result alias_TransformBundle_initialize(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Transform2D)
  }, &bundle->Transform2D_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
    .size = sizeof(alias_LocalToParent2D)
    , .num_required_components = 1
    , .required_components = &bundle->Transform2D_component
  }, &bundle->LocalToParent2D_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Parent2D)
    , .num_required_components = 1
    , .required_components = &bundle->LocalToParent2D_component
  }, &bundle->Parent2D_component);

  _construct_query(instance, bundle, &bundle->transform_query, false);

  _construct_query(instance, bundle, &bundle->transform_child_query, true);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 1
    , .write_components = &bundle->LocalToWorld2D_component
    , .num_read_components = 2
    , .read_components = (alias_ecs_ComponentHandle[]){ bundle->LocalToParent2D_component, bundle->Parent2D_component }
    , .num_filters = 2
    , .filters = (alias_ecs_QueryFilterCreateInfo[]) { 
        { .component = bundle->LocalToParent2D_component, .filter = ALIAS_ECS_FILTER_MODIFIED }
      , { .component = bundle->Parent2D_component, .filter = ALIAS_ECS_FILTER_MODIFIED }
      }
  }, &bundle->parent_query);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 1
    , .write_components = &bundle->WorldToLocal2D_component
    , .num_read_components = 1
    , .read_components = &bundle->LocalToWorld2D_component
    , .num_filters = 1
    , .filters = &(alias_ecs_QueryFilterCreateInfo) { .component = bundle->LocalToWorld2D_component, .filter = ALIAS_ECS_FILTER_MODIFIED }
  }, &bundle->inverse_query);
  
  return ALIAS_ECS_SUCCESS;  
}

// =============================================================================================================================================================
static void _construct_local_from_transform(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  alias_LocalToWorld2D * local_to_world = (alias_LocalToWorld2D *)data[0];
  const alias_Transform2D * transform = (const alias_Transform2D *)data[1];
  local_to_world->motor = alias_pga2d_motor(transform->orientation, alias_pga2d_direction(transform->position_x, transform->position_y));
  local_to_world->position = alias_pga2d_sandwich_bm(alias_pga2d_point(0, 0), local_to_world->motor);
}

void alias_transform_update2d_construct_local_from_transform(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->transform_query, (alias_ecs_QueryCB) { _construct_local_from_transform, bundle });
}

// =============================================================================================================================================================
static void _construct_parent_from_transform(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  alias_LocalToParent2D * local_to_parent = (alias_LocalToParent2D *)data[0];
  const alias_Transform2D * transform = (const alias_Transform2D *)data[1];
  local_to_parent->value = alias_pga2d_motor(transform->orientation, alias_pga2d_direction(transform->position_x, transform->position_y));
}

void alias_transform_update2d_construct_parent_from_transform(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->transform_child_query, (alias_ecs_QueryCB) { _construct_parent_from_transform, bundle });
}

// =============================================================================================================================================================
static void _construct_local_from_parent(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  const alias_TransformBundle * bundle = (const alias_TransformBundle *)ud;
  (void)entity;
  alias_LocalToWorld2D * local_to_world = (alias_LocalToWorld2D *)data[0];
  const alias_LocalToParent2D * local_to_parent = (alias_LocalToParent2D *)data[1];
  const alias_Parent2D * parent = (alias_Parent2D *)data[2];

  const alias_LocalToWorld2D * parent_local_to_world = NULL;
  alias_ecs_read_entity_component(instance, parent->value, bundle->LocalToWorld2D_component, (const void **)&parent_local_to_world);

  local_to_world->motor = alias_pga2d_mul_mm(parent_local_to_world->motor, local_to_parent->value);
  local_to_world->position = alias_pga2d_sandwich_bm(alias_pga2d_point(0, 0), local_to_world->motor);
}

void alias_transform_update2d_construct_local_from_parent(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->parent_query, (alias_ecs_QueryCB) { _construct_local_from_parent, bundle });
}

// =============================================================================================================================================================
static void _inverse_local(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  alias_WorldToLocal2D * world_to_local = (alias_WorldToLocal2D *)data[0];
  const alias_LocalToWorld2D * local_to_world = (const alias_LocalToWorld2D *)data[1];
  world_to_local->value = alias_pga2d_reverse_m(local_to_world->motor);
}

void alias_transform_update2d_inverse_local(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->inverse_query, (alias_ecs_QueryCB) { _inverse_local, bundle });
}

// =============================================================================================================================================================
void alias_transform_update2d_serial(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_transform_update2d_construct_local_from_transform(instance, bundle);
  alias_transform_update2d_construct_parent_from_transform(instance, bundle);
  alias_transform_update2d_construct_local_from_parent(instance, bundle);
  alias_transform_update2d_inverse_local(instance, bundle);
}

