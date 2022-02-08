// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_TRANSFORM_H_
#define _ALIAS_TRANSFORM_H_

#include <alias/math.h>
#include <alias/ecs.h>

typedef struct alias_Translation2D {
  alias_pga2d_Direction value;
} alias_Translation2D;

typedef struct alias_Rotation2D {
  alias_R value;
} alias_Rotation2D;

typedef struct alias_Transform2D {
  union {
    alias_pga2d_Motor value;
    alias_pga2d_Motor M;
  };
} alias_Transform2D;

typedef struct alias_LocalToWorld2D {
  alias_pga2d_Motor motor;

  alias_pga2d_Point position;
  alias_R orientation;
} alias_LocalToWorld2D;

typedef struct alias_Parent2D {
  alias_ecs_EntityHandle value;
} alias_Parent2D;

typedef struct alias_TransformBundle {
  alias_ecs_ComponentHandle Translation2D_component;
  alias_ecs_ComponentHandle Rotation2D_component;
  alias_ecs_ComponentHandle Transform2D_component;

  alias_ecs_ComponentHandle LocalToWorld2D_component;

  alias_ecs_ComponentHandle Parent2D_component;

  alias_ecs_Query * translation_query;
  alias_ecs_Query * rotation_query;
  alias_ecs_Query * translation_rotation_query;
  alias_ecs_Query * parent_world_query;
  alias_ecs_Query * child_world_query;
} alias_TransformBundle;

alias_ecs_Result alias_TransformBundle_initialize(alias_ecs_Instance * instance, alias_TransformBundle * bundle);

void alias_transform_update2d_serial(alias_ecs_Instance * instance, alias_TransformBundle * bundle);

#endif

