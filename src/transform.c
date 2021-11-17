// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <alias/transform.h>
#include <alias/log.h>

#include <math.h>
#include <stdbool.h>

static alias_ecs_Result _construct_query(
    alias_ecs_Instance    * instance
  , alias_TransformBundle * bundle
  , alias_ecs_Query *     * out
  , bool                    translation
  , bool                    rotation
) {
  alias_ecs_ComponentHandle read_components[3];
  alias_ecs_QueryFilterCreateInfo filters[3];
  alias_ecs_QueryCreateInfo create_info = {
      .num_write_components = 1
    , .write_components = &bundle->Transform2D_component
    , .read_components = read_components
    , .filters = filters
  };

  if(translation) {
    read_components[create_info.num_read_components] = bundle->Translation2D_component;
    create_info.num_read_components++;

    filters[create_info.num_filters].component = bundle->Translation2D_component;
    filters[create_info.num_filters].filter = ALIAS_ECS_FILTER_MODIFIED;
    create_info.num_filters++;
  } else {
    filters[create_info.num_filters].component = bundle->Translation2D_component;
    filters[create_info.num_filters].filter = ALIAS_ECS_FILTER_EXCLUDE;
    create_info.num_filters++;
  }

  if(rotation) {
    read_components[create_info.num_read_components] = bundle->Rotation2D_component;
    create_info.num_read_components++;

    filters[create_info.num_filters].component = bundle->Rotation2D_component;
    filters[create_info.num_filters].filter = ALIAS_ECS_FILTER_MODIFIED;
    create_info.num_filters++;
  } else {
    filters[create_info.num_filters].component = bundle->Rotation2D_component;
    filters[create_info.num_filters].filter = ALIAS_ECS_FILTER_EXCLUDE;
    create_info.num_filters++;
  }
  
  return alias_ecs_create_query(instance, &create_info, out);
}

alias_ecs_Result alias_TransformBundle_initialize(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_LocalToWorld2D)
  }, &bundle->LocalToWorld2D_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Transform2D)
    , .num_required_components = 1
    , .required_components = &bundle->LocalToWorld2D_component
  }, &bundle->Transform2D_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Translation2D)
    , .num_required_components = 1
    , .required_components = &bundle->Transform2D_component
  }, &bundle->Translation2D_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Rotation2D)
    , .num_required_components = 1
    , .required_components = &bundle->Transform2D_component
  }, &bundle->Rotation2D_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Parent2D)
  }, &bundle->Parent2D_component);

  _construct_query(instance, bundle, &bundle->translation_query, true, false);
  _construct_query(instance, bundle, &bundle->rotation_query, false, true);
  _construct_query(instance, bundle, &bundle->translation_rotation_query, true, true);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 1
    , .write_components = &bundle->LocalToWorld2D_component
    , .num_read_components = 1
    , .read_components = &bundle->Transform2D_component
    , .num_filters = 2
    , .filters = (alias_ecs_QueryFilterCreateInfo[]) { 
        { .component = bundle->Transform2D_component, .filter = ALIAS_ECS_FILTER_MODIFIED }
      , { .component = bundle->Parent2D_component, .filter = ALIAS_ECS_FILTER_EXCLUDE }
      }
  }, &bundle->parent_world_query);
  
  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 1
    , .write_components = &bundle->LocalToWorld2D_component
    , .num_read_components = 2
    , .read_components = (alias_ecs_ComponentHandle[]) { bundle->Transform2D_component, bundle->Parent2D_component }
    , .num_filters = 2
    , .filters = (alias_ecs_QueryFilterCreateInfo[]) { 
        { .component = bundle->Transform2D_component, .filter = ALIAS_ECS_FILTER_MODIFIED }
      , { .component = bundle->Parent2D_component, .filter = ALIAS_ECS_FILTER_MODIFIED }
      }
  }, &bundle->child_world_query);
  
  return ALIAS_ECS_SUCCESS;  
}

// =============================================================================================================================================================
static void _update2d_translation(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  alias_Transform2D * transform = (alias_Transform2D *)data[0];
  const alias_Translation2D * translation = (const alias_Translation2D *)data[1];
  transform->value = alias_pga2d_translator(1, translation->value);
}

void alias_transform_update2d_translation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->translation_query, (alias_ecs_QueryCB) { _update2d_translation, bundle });
}

// =============================================================================================================================================================
static void _update2d_rotation(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  alias_Transform2D * transform = (alias_Transform2D *)data[0];
  const alias_Rotation2D * rotation = (const alias_Rotation2D *)data[1];
  transform->value = alias_pga2d_rotor(rotation->value);
}

void alias_transform_update2d_rotation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->translation_rotation_query, (alias_ecs_QueryCB) { _update2d_rotation, bundle });
}

// =============================================================================================================================================================
static void _update2d_translation_rotation(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  alias_Transform2D * transform = (alias_Transform2D *)data[0];
  const alias_Translation2D * translation = (const alias_Translation2D *)data[1];
  const alias_Rotation2D * rotation = (const alias_Rotation2D *)data[2];
  transform->value = alias_pga2d_motor(rotation->value, translation->value);
}

void alias_transform_update2d_translation_rotation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->translation_rotation_query, (alias_ecs_QueryCB) { _update2d_translation_rotation, bundle });
}

// =============================================================================================================================================================
static void _update2d_parent_world(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  alias_LocalToWorld2D * local_to_world = (alias_LocalToWorld2D *)data[0];
  const alias_Transform2D * transform = (const alias_Transform2D *)data[1];
  local_to_world->motor = transform->value;
  local_to_world->position = alias_pga2d_sandwich_bm(alias_pga2d_point(0, 0), local_to_world->motor);
  local_to_world->orientation = asinf(local_to_world->motor.e12) * 2;
}

void alias_transform_update2d_parent_world(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->parent_world_query, (alias_ecs_QueryCB) { _update2d_parent_world, bundle });
}

// =============================================================================================================================================================
static void _update2d_child_world(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)instance;
  (void)entity;
  alias_LocalToWorld2D * local_to_world = (alias_LocalToWorld2D *)data[0];
  const alias_Transform2D * transform = (const alias_Transform2D *)data[1];
  const alias_Parent2D * parent = (alias_Parent2D *)data[2];

  alias_TransformBundle * bundle = (alias_TransformBundle *)ud;
  const alias_LocalToWorld2D * parent_local_to_world = NULL;
  alias_ecs_read_entity_component(instance, parent->value, bundle->LocalToWorld2D_component, (const void **)&parent_local_to_world);
  
  local_to_world->motor = alias_pga2d_mul_mm(parent_local_to_world->motor, transform->value);
  local_to_world->position = alias_pga2d_sandwich_bm(alias_pga2d_point(0, 0), local_to_world->motor);
  local_to_world->orientation = asinf(local_to_world->motor.e12) * 2;
}

void alias_transform_update2d_child_world(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->child_world_query, (alias_ecs_QueryCB) { _update2d_child_world, bundle });
}

// =============================================================================================================================================================
void alias_transform_update2d_serial(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_transform_update2d_translation(instance, bundle);
  alias_transform_update2d_rotation(instance, bundle);
  alias_transform_update2d_translation_rotation(instance, bundle);
  alias_transform_update2d_parent_world(instance, bundle);
  alias_transform_update2d_child_world(instance, bundle);
}

