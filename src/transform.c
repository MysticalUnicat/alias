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
  , bool                    uniform_scale
  , bool                    non_uniform_scale
  , bool                    child
) {
  alias_ecs_ComponentHandle read_components[6];
  alias_ecs_QueryFilterCreateInfo filters[12];
  alias_ecs_QueryCreateInfo create_info = {
      .num_write_components = 1
    , .write_components = &bundle->LocalToWorld2D_component
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

#if ALIAS_TRANSFORM_ENABLE_SCALE
  0 = 0;
#else
  (void)uniform_scale;
#endif

#if ALIAS_TRANSFORM_ENABLE_NON_UNIFORM_SCALE
  0 = 0;
#else
  (void)non_uniform_scale;
#endif

#if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
  if(child) {
    filters[create_info.num_filters].component = bundle->Parent2D_component;
    filters[create_info.num_filters].filter = ALIAS_ECS_FILTER_MODIFIED;
    create_info.num_filters++;
  } else {
    filters[create_info.num_filters].component = bundle->Parent2D_component;
    filters[create_info.num_filters].filter = ALIAS_ECS_FILTER_EXCLUDE;
    create_info.num_filters++;
  }
#else
  (void)child;
#endif
  
  return alias_ecs_create_query(instance, &create_info, out);
}

alias_ecs_Result alias_TransformBundle_initialize(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
    .size = sizeof(alias_WorldToLocal2D)
  }, &bundle->WorldToLocal2D_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_LocalToWorld2D)
    , .num_required_components = 1
    , .required_components = &bundle->WorldToLocal2D_component
  }, &bundle->LocalToWorld2D_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Translation2D)
    , .num_required_components = 1
    , .required_components = &bundle->LocalToWorld2D_component
  }, &bundle->Translation2D_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Rotation2D)
    , .num_required_components = 1
    , .required_components = &bundle->LocalToWorld2D_component
  }, &bundle->Rotation2D_component);

#if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
    .size = sizeof(alias_LocalToParent2D)
  }, &bundle->LocalToParent2D_component);

  alias_ecs_register_component(instance, &(alias_ecs_ComponentCreateInfo) {
      .size = sizeof(alias_Parent2D)
    , .num_required_components = 1
    , .required_components = &bundle->LocalToParent2D_component
  }, &bundle->Parent2D_component);
#endif

  _construct_query(instance, bundle, &bundle->translation_query, true, false, false, false, false);
  _construct_query(instance, bundle, &bundle->rotation_query, false, true, false, false, false);
  _construct_query(instance, bundle, &bundle->rotation_translation_query, true, true, false, false, false);

#if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
  _construct_query(instance, bundle, &bundle->translation_child_query, true, false, false, false, true);
  _construct_query(instance, bundle, &bundle->rotation_child_query, false, true, false, false, true);
  _construct_query(instance, bundle, &bundle->rotation_translation_child_query, true, true, false, false, true);

  alias_ecs_create_query(instance, &(alias_ecs_QueryCreateInfo) {
      .num_write_components = 1
    , .write_components = &bundle->LocalToWorld2D_component
    , .num_read_components = 2
    , .read_components = (alias_ecs_ComponentHandle[]){ bundle->LocalToWorld2D_component, bundle->Parent2D_component }
    , .num_filters = 2
    , .filters = (alias_ecs_QueryFilterCreateInfo[]) { 
        { .component = bundle->LocalToWorld2D_component, .filter = ALIAS_ECS_FILTER_MODIFIED }
      , { .component = bundle->Parent2D_component, .filter = ALIAS_ECS_FILTER_MODIFIED }
      }
  }, &bundle->parent_query);
#endif

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
static void _construct_local_from_translation(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  alias_LocalToWorld2D * local_to_world = (alias_LocalToWorld2D *)data[0];
  const alias_Translation2D * translation = (const alias_Translation2D *)data[1];
  local_to_world->value._11 = 1.0f;
  local_to_world->value._12 = 0.0f;
  local_to_world->value._13 = translation->value.x;
  local_to_world->value._21 = 0.0f;
  local_to_world->value._22 = 1.0f;
  local_to_world->value._23 = translation->value.y;
}

void alias_transform_update2d_construct_local_from_translation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->translation_query, (alias_ecs_QueryCB) { _construct_local_from_translation, bundle });
}

// =============================================================================================================================================================
static void _construct_local_from_rotation(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  alias_LocalToWorld2D * local_to_world = (alias_LocalToWorld2D *)data[0];
  const alias_Rotation2D * rotation = (const alias_Rotation2D *)data[1];
  const float angle = rotation->value;
  const float s = sin(angle);
  const float c = cos(angle);
  local_to_world->value._11 = c;
  local_to_world->value._12 = -s;
  local_to_world->value._13 = 0.0f;
  local_to_world->value._21 = s;
  local_to_world->value._22 = c;
  local_to_world->value._23 = 0.0f;
}

void alias_transform_update2d_construct_local_from_rotation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->rotation_query, (alias_ecs_QueryCB) { _construct_local_from_rotation, bundle });
}

// =============================================================================================================================================================
static void _construct_local_from_rotation_translation(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  alias_LocalToWorld2D * local_to_world = (alias_LocalToWorld2D *)data[0];
  const alias_Translation2D * translation = (const alias_Translation2D *)data[1];
  const alias_Rotation2D * rotation = (const alias_Rotation2D *)data[2];
  const float angle = rotation->value;
  const float s = sin(angle);
  const float c = cos(angle);
  local_to_world->value._11 = c;
  local_to_world->value._12 = -s;
  local_to_world->value._13 = translation->value.x;
  local_to_world->value._21 = s;
  local_to_world->value._22 = c;
  local_to_world->value._23 = translation->value.y;
}

void alias_transform_update2d_construct_local_from_rotation_translation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->rotation_translation_query, (alias_ecs_QueryCB) { _construct_local_from_rotation_translation, bundle });
}

// =============================================================================================================================================================
#if ALIAS_TRANSFORM_ENABLE_SCALE
void alias_transform_update2d_construct_local_from_uniform_scale(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}

void alias_transform_update2d_construct_local_from_uniform_scale_translation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}

void alias_transform_update2d_construct_local_from_uniform_scale_rotation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}

void alias_transform_update2d_construct_local_from_uniform_scale_rotation_translation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}
#endif
#if ALIAS_TRANSFORM_ENABLE_NON_UNIFORM_SCALE
void alias_transform_update2d_construct_local_from_non_uniform_scale(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}

void alias_transform_update2d_construct_local_from_non_uniform_scale_translation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}

void alias_transform_update2d_construct_local_from_non_uniform_scale_rotation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}

void alias_transform_update2d_construct_local_from_non_uniform_scale_rotation_translation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}
#endif

#if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
// =============================================================================================================================================================
static void _construct_parent_from_translation(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  alias_LocalToWorld2D * local_to_world = (alias_LocalToWorld2D *)data[0];
  const alias_Translation2D * translation = (const alias_Translation2D *)data[1];
  local_to_world->value._11 = 1.0f;
  local_to_world->value._12 = 0.0f;
  local_to_world->value._13 = translation->value.x;
  local_to_world->value._21 = 0.0f;
  local_to_world->value._22 = 1.0f;
  local_to_world->value._23 = translation->value.y;
}

void alias_transform_update2d_construct_parent_from_translation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->translation_child_query, (alias_ecs_QueryCB) { _construct_parent_from_translation, bundle });
}

// =============================================================================================================================================================
static void _construct_parent_from_rotation(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  alias_LocalToParent2D * local_to_parent = (alias_LocalToParent2D *)data[0];
  const alias_Rotation2D * rotation = (const alias_Rotation2D *)data[1];
  const float angle = rotation->value;
  const float s = sin(angle);
  const float c = cos(angle);
  local_to_parent->value._11 = c;
  local_to_parent->value._12 = -s;
  local_to_parent->value._13 = 0.0f;
  local_to_parent->value._21 = s;
  local_to_parent->value._22 = c;
  local_to_parent->value._23 = 0.0f;
}

void alias_transform_update2d_construct_parent_from_rotation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->rotation_child_query, (alias_ecs_QueryCB) { _construct_parent_from_rotation, bundle });
}

// =============================================================================================================================================================
static void _construct_parent_from_rotation_translation(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  alias_LocalToParent2D * local_to_parent = (alias_LocalToParent2D *)data[0];
  const alias_Translation2D * translation = (const alias_Translation2D *)data[1];
  const alias_Rotation2D * rotation = (const alias_Rotation2D *)data[2];
  const float angle = rotation->value;
  const float s = sin(angle);
  const float c = cos(angle);
  local_to_parent->value._11 = c;
  local_to_parent->value._12 = -s;
  local_to_parent->value._13 = translation->value.x;
  local_to_parent->value._21 = s;
  local_to_parent->value._22 = c;
  local_to_parent->value._23 = translation->value.y;
}

void alias_transform_update2d_construct_parent_from_rotation_translation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->rotation_translation_child_query, (alias_ecs_QueryCB) { _construct_parent_from_rotation_translation, bundle });
}

#if ALIAS_TRANSFORM_ENABLE_SCALE
void alias_transform_update2d_construct_parent_from_uniform_scale(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}

void alias_transform_update2d_construct_parent_from_uniform_scale_translation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}

void alias_transform_update2d_construct_parent_from_uniform_scale_rotation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}

void alias_transform_update2d_construct_parent_from_uniform_scale_rotation_translation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}
#endif
#if ALIAS_TRANSFORM_ENABLE_NON_UNIFORM_SCALE
void alias_transform_update2d_construct_parent_from_non_uniform_scale(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}

void alias_transform_update2d_construct_parent_from_non_uniform_scale_translation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}

void alias_transform_update2d_construct_parent_from_non_uniform_scale_rotation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}

void alias_transform_update2d_construct_parent_from_non_uniform_scale_rotation_translation(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
}
#endif
// =============================================================================================================================================================
static void _construct_local_from_parent(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  const alias_TransformBundle * bundle = (const alias_TransformBundle *)ud;
  (void)entity;
  alias_LocalToWorld2D * local_to_world = (alias_LocalToWorld2D *)data[0];
  const alias_LocalToParent2D * local_to_parent = (alias_LocalToParent2D *)data[1];
  const alias_Parent2D * parent = (alias_Parent2D *)data[2];

  const alias_LocalToWorld2D * parent_local_to_world = NULL;
  alias_ecs_read_entity_component(instance, parent->value, bundle->LocalToWorld2D_component, (const void **)&parent_local_to_world);

  local_to_world->value = alias_multiply_Affine2D_Affine2D(parent_local_to_world->value, local_to_parent->value);
}

void alias_transform_update2d_construct_local_from_parent(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->parent_query, (alias_ecs_QueryCB) { _construct_local_from_parent, bundle });
}
#endif

// =============================================================================================================================================================
static void _inverse_local(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data) {
  (void)ud;
  (void)instance;
  (void)entity;
  alias_WorldToLocal2D * world_to_local = (alias_WorldToLocal2D *)data[0];
  const alias_LocalToWorld2D * local_to_world = (const alias_LocalToWorld2D *)data[1];
  world_to_local->value = alias_Affine2D_inverse(local_to_world->value);
}

void alias_transform_update2d_inverse_local(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_ecs_execute_query(instance, bundle->inverse_query, (alias_ecs_QueryCB) { _inverse_local, bundle });
}

// =============================================================================================================================================================
void alias_transform_update2d_serial(alias_ecs_Instance * instance, alias_TransformBundle * bundle) {
  alias_transform_update2d_construct_local_from_translation(instance, bundle);
  alias_transform_update2d_construct_local_from_rotation(instance, bundle);
  alias_transform_update2d_construct_local_from_rotation_translation(instance, bundle);
  #if ALIAS_TRANSFORM_ENABLE_SCALE
  alias_transform_update2d_construct_local_from_uniform_scale(instance, bundle);
  alias_transform_update2d_construct_local_from_uniform_scale_translation(instance, bundle);
  alias_transform_update2d_construct_local_from_uniform_scale_rotation(instance, bundle);
  alias_transform_update2d_construct_local_from_uniform_scale_rotation_translation(instance, bundle);
  #endif
  #if ALIAS_TRANSFORM_ENABLE_NON_UNIFORM_SCALE
  alias_transform_update2d_construct_local_from_non_uniform_scale(instance, bundle);
  alias_transform_update2d_construct_local_from_non_uniform_scale_translation(instance, bundle);
  alias_transform_update2d_construct_local_from_non_uniform_scale_rotation(instance, bundle);
  alias_transform_update2d_construct_local_from_non_uniform_scale_rotation_translation(instance, bundle);
  #endif

  #if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
  alias_transform_update2d_construct_parent_from_translation(instance, bundle);
  alias_transform_update2d_construct_parent_from_rotation(instance, bundle);
  alias_transform_update2d_construct_parent_from_rotation_translation(instance, bundle);
  #if ALIAS_TRANSFORM_ENABLE_SCALE
  alias_transform_update2d_construct_parent_from_uniform_scale(instance, bundle);
  alias_transform_update2d_construct_parent_from_uniform_scale_translation(instance, bundle);
  alias_transform_update2d_construct_parent_from_uniform_scale_rotation(instance, bundle);
  alias_transform_update2d_construct_parent_from_uniform_scale_rotation_translation(instance, bundle);
  #endif
  #if ALIAS_TRANSFORM_ENABLE_NON_UNIFORM_SCALE
  alias_transform_update2d_construct_parent_from_non_uniform_scale(instance, bundle);
  alias_transform_update2d_construct_parent_from_non_uniform_scale_translation(instance, bundle);
  alias_transform_update2d_construct_parent_from_non_uniform_scale_rotation(instance, bundle);
  alias_transform_update2d_construct_parent_from_non_uniform_scale_rotation_translation(instance, bundle);
  #endif
  alias_transform_update2d_construct_local_from_parent(instance, bundle);
  #endif
  alias_transform_update2d_inverse_local(instance, bundle);
}

