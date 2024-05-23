/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "renderer.h"
#include "internal.h"
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

void rendererDrawPoint(vec2 DLR_NONNULL position) {

}

void rendererDrawLine(vec2 DLR_NONNULL positionStart, vec2 DLR_NONNULL positionEnd) {

}

void rendererDrawRectangle(vec2 DLR_NONNULL position, vec2 DLR_NONNULL dimension, bool filled) {

}

void rendererDrawCircle(vec2 DLR_NONNULL positionCenter, int radius, bool filled) {

}

void rendererDrawTexture(vec2 DLR_NONNULL position, vec2 DLR_NONNULL dimension, const dlrByte* DLR_NONNULL data) {

}
