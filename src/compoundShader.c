/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "compoundShader.h"
#include "internal.h"
#include <assert.h>
#include <stddef.h>
#include <GL/glew.h>

struct CompoundShader {
    unsigned programId;
};

CompoundShader* compoundShaderCreate(const char* vertexCode, const char* fragmentCode) {
    CompoundShader* shader = internalMalloc(sizeof *shader);
    int success;

    unsigned vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (const char*[1]) {vertexCode}, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    assert(success == GL_TRUE);

    unsigned fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (const char*[1]) {fragmentCode}, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    assert(success == GL_TRUE);

    shader->programId = glCreateProgram();
    glAttachShader(shader->programId, vertex);
    glAttachShader(shader->programId, fragment);
    glLinkProgram(shader->programId);
    glGetProgramiv(shader->programId, GL_LINK_STATUS, &success);
    assert(success == GL_TRUE);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shader;
}

void compoundShaderDestroy(CompoundShader* shader) {
    glDeleteProgram(shader->programId);
    internalFree(shader);
}

void compoundShaderUse(const CompoundShader* shader) {
    glUseProgram(shader->programId);
}

void compoundShaderSetBool(const CompoundShader* shader, const char* name, bool value) {
    glUniform1i(glGetUniformLocation(shader->programId, name), (int) value);
}

void compoundShaderSetInt(const CompoundShader* shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader->programId, name), value);
}

void compoundShaderSetFloat(const CompoundShader* shader, const char* name, float value) {
    glUniform1f(glGetUniformLocation(shader->programId, name), value);
}

void compoundShaderSetVec2(const CompoundShader* shader, const char* name, const vec2 value) {
    glUniform2f(glGetUniformLocation(shader->programId, name), value[0], value[1]);
}

void compoundShaderSetVec3(const CompoundShader* shader, const char* name, const vec3 value) {
    glUniform3f(glGetUniformLocation(shader->programId, name), value[0], value[1], value[2]);
}

void compoundShaderSetVec4(const CompoundShader* shader, const char* name, const vec4 value) {
    glUniform4f(glGetUniformLocation(shader->programId, name), value[0], value[1], value[2], value[3]);
}

void compoundShaderSetMat3(const CompoundShader* shader, const char* name, const mat3 value) {
    glUniformMatrix3fv(glGetUniformLocation(shader->programId, name), 1, GL_FALSE, &(value[0][0]));
}

void compoundShaderSetMat4(const CompoundShader* shader, const char* name, const mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(shader->programId, name), 1, GL_FALSE, &(value[0][0]));
}
