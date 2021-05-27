#ifndef _ALIAS_TRANSFORM_H_
#define _ALIAS_TRANSFORM_H_

#include <alias/math.h>
#include <alias/ecs.h>

#define ALIAS_TRANSFORM_ENABLE_SCALE 0
#define ALIAS_TRANSFORM_ENABLE_NON_UNIFORM_SCALE (ALIAS_TRANSFORM_ENABLE_SCALE && 0)
#define ALIAS_TRANSFORM_ENABLE_HEIRARCHY 0

typedef struct alias_Translation2D {
  alias_Vector2D value;
} alias_Translation2D;

typedef struct alias_Rotation2D {
  float value;
} alias_Rotation2D;

#if ALIAS_TRANSFORM_ENABLE_SCALE
typedef struct alias_UniformScale2D {
  float value;
} alias_UniformScale2D;
#endif

#if ALIAS_TRANSFORM_ENABLE_NON_UNIFORM_SCALE
typedef struct alias_NonUniformScale2D {
  alias_Vector2D value;
} alias_NonUniformScale2D;
#endif

typedef struct alias_LocalToWorld2D {
  alias_Affine2D value;
} alias_LocalToWorld2D;

typedef struct alias_WorldToLocal2D {
  alias_Affine2D value;
} alias_WorldToLocal2D;

#if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
typedef struct alias_LocalToParent2D {
  alias_Affine2D value;
} alias_LocalToParent2D;

typedef struct alias_Parent2D {
  alias_ecs_EntityHandle value;
} alias_Parent2D;
#endif

typedef struct alias_TransformBundle {
  alias_ecs_ComponentHandle Translation2D_component;
  alias_ecs_ComponentHandle Rotation2D_component;
#if ALIAS_TRANSFORM_ENABLE_SCALE
  alias_ecs_ComponentHandle UniformScale2D_component;
#endif
#if ALIAS_TRANSFORM_ENABLE_NON_UNIFORM_SCALE
  alias_ecs_ComponentHandle NonUniformScale2D_component;
#endif

  alias_ecs_ComponentHandle LocalToWorld2D_component;
  alias_ecs_ComponentHandle WorldToLocal2D_component;

#if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
  alias_ecs_ComponentHandle Parent2D_component;
  alias_ecs_ComponentHandle LocalToParent2D_component;
#endif

  alias_ecs_Query * translation_query;
  alias_ecs_Query * rotation_query;
  alias_ecs_Query * rotation_translation_query;
#if ALIAS_TRANSFORM_ENABLE_SCALE
  alias_ecs_Query * uniform_scale_query;
  alias_ecs_Query * uniform_scale_translation_query;
  alias_ecs_Query * uniform_scale_rotation_query;
  alias_ecs_Query * uniform_scale_rotation_translation_query;
#endif
#if ALIAS_TRANSFORM_ENABLE_NON_UNIFORM_SCALE
  alias_ecs_Query * non_uniform_scale_query;
  alias_ecs_Query * non_uniform_scale_translation_query;
  alias_ecs_Query * non_uniform_scale_rotation_query;
  alias_ecs_Query * non_uniform_scale_rotation_translation_query;
#endif
#if ALIAS_TRANSFORM_ENABLE_HEIRARCHY
  alias_ecs_Query * translation_child_query;
  alias_ecs_Query * rotation_child_query;
  alias_ecs_Query * rotation_translation_child_query;
#if ALIAS_TRANSFORM_ENABLE_SCALE
  alias_ecs_Query * uniform_scale_child_query;
  alias_ecs_Query * uniform_scale_translation_child_query;
  alias_ecs_Query * uniform_scale_rotation_child_query;
  alias_ecs_Query * uniform_scale_rotation_translation_child_query;
#endif
#if ALIAS_TRANSFORM_ENABLE_NON_UNIFORM_SCALE
  alias_ecs_Query * non_uniform_scale_child_query;
  alias_ecs_Query * non_uniform_scale_translation_child_query;
  alias_ecs_Query * non_uniform_scale_rotation_child_query;
  alias_ecs_Query * non_uniform_scale_rotation_translation_child_query;
#endif
  alias_ecs_Query * parent_query;
#endif
  alias_ecs_Query * inverse_query;
} alias_TransformBundle;

alias_ecs_Result alias_TransformBundle_initialize(alias_ecs_Instance * instance, alias_TransformBundle * bundle);

void alias_transform_update2d_serial(alias_ecs_Instance * instance, alias_TransformBundle * bundle);

#endif

