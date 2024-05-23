/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "renderer.h"
#include "internal.h"
#include "context.h"
#include "compoundShader.h"
#include <GL/glew.h>

struct Renderer {
    CompoundShader* shader;
    unsigned vbo, ebo, vao;
};
typedef struct Renderer Renderer;

static Renderer* DLR_NULLABLE gRenderer = NULL;

static const char* const gVertexShader =
    "#version 330 core\n"
    "layout (location = 0) in vec2 pos;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "   gl_Position = projection * vec4(pos, 0.0, 1.0);\n"
    "}\n";

static const char* const gFragmentShader =
    "#version 330 core\n"
    "out vec4 colorOut;\n"
    "uniform vec4 color;\n"
    "void main() {\n"
    "   colorOut = color;\n"
    "}\n";

void rendererInit(void) {
    gRenderer = internalMalloc(sizeof *gRenderer);
    gRenderer->shader = compoundShaderCreate(gVertexShader, gFragmentShader);
    glGenBuffers(1, &(gRenderer->vbo));
    glGenBuffers(1, &(gRenderer->ebo));
    glGenVertexArrays(1, &((gRenderer->vao)));
}

void rendererQuit(void) {
    compoundShaderDestroy(gRenderer->shader);
    glDeleteBuffers(1, &(gRenderer->vbo));
    glDeleteBuffers(1, &(gRenderer->ebo));
    glDeleteVertexArrays(1, &((gRenderer->vao)));
    internalFree(gRenderer);
}

void rendererDrawPoint(const vec2 DLR_NONNULL position, float pointSize, const vec4 DLR_NONNULL color) {
    glBindVertexArray(gRenderer->vao);

    const float vertices[] = {
        position[0], position[1]
    };

    glBindBuffer(GL_ARRAY_BUFFER, gRenderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    compoundShaderUse(gRenderer->shader);
    compoundShaderSetMat4(gRenderer->shader, "projection", internalContext->projection);
    compoundShaderSetVec4(gRenderer->shader, "color", color);

    glPointSize((float) pointSize);
    glDrawArrays(GL_POINTS, 0, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void rendererDrawLine(const vec2 DLR_NONNULL positionStart, const vec2 DLR_NONNULL positionEnd, const vec4 DLR_NONNULL color) {

}

void rendererDrawRectangle(const vec2 DLR_NONNULL position, const vec2 DLR_NONNULL dimension, const vec4 DLR_NONNULL color, bool filled) {

}

void rendererDrawCircle(const vec2 DLR_NONNULL positionCenter, int radius, const vec4 DLR_NONNULL color, bool filled) {

}

void rendererDrawTexture(const vec2 DLR_NONNULL position, const vec2 DLR_NONNULL dimension, const dlrByte* DLR_NONNULL data) {

}
