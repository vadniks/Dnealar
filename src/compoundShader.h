/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include <stdbool.h>
#include <cglm/types.h>

struct CompoundShader;
typedef struct CompoundShader CompoundShader;

CompoundShader* compoundShaderCreate(const char* vertexCode, const char* fragmentCode);
void compoundShaderDestroy(CompoundShader* shader);
void compoundShaderUse(const CompoundShader* shader);
void compoundShaderSetBool(const CompoundShader* shader, const char* name, bool value);
void compoundShaderSetInt(const CompoundShader* shader, const char* name, int value);
void compoundShaderSetFloat(const CompoundShader* shader, const char* name, float value);
void compoundShaderSetVec2(const CompoundShader* shader, const char* name, const vec2 value);
void compoundShaderSetVec3(const CompoundShader* shader, const char* name, const vec3 value);
void compoundShaderSetVec4(const CompoundShader* shader, const char* name, const vec4 value);
void compoundShaderSetMat3(const CompoundShader* shader, const char* name, const mat3 value);
void compoundShaderSetMat4(const CompoundShader* shader, const char* name, const mat4 value);
