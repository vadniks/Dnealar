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

static const char* const vertexShader =
    "#version 330 core"
    "layout (location = 0) in vec2 pos;"
    "uniform mat4 projection;"
    "void main() {"
    "   gl_Position = projection * model * vec4(pos, 0.0, 1.0);"
    "}";

static const char* const fragmentShader =
    "#version 330 core"
    "out vec4 colorOut;"
    "uniform vec4 color;"
    "void main() {"
    "   colorOut = color;"
    "}";

struct Renderer {
    CompoundShader* shader;
    unsigned vbo, ebo, vao;
};

Renderer* DLR_NONNULL rendererCreate(void) {
    Renderer* renderer = internalMalloc(sizeof *renderer);
    renderer->shader = compoundShaderCreate(vertexShader, fragmentShader);
    glGenBuffers(1, &(renderer->vbo));
    glGenBuffers(1, &(renderer->ebo));
    glGenVertexArrays(1, &((renderer->vao)));
    return renderer;
}

void rendererDestroy(Renderer* DLR_NONNULL renderer) {
    compoundShaderDestroy(renderer->shader);
    glDeleteBuffers(1, &(renderer->vbo));
    glDeleteBuffers(1, &(renderer->ebo));
    glDeleteVertexArrays(1, &((renderer->vao)));
    internalFree(renderer);
}

void rendererDrawPoint(Renderer* DLR_NONNULL renderer, vec2 DLR_NONNULL position) {

}

void rendererDrawLine(Renderer* DLR_NONNULL renderer, vec2 DLR_NONNULL positionStart, vec2 DLR_NONNULL positionEnd) {

}

void rendererDrawRectangle(Renderer* DLR_NONNULL renderer, vec2 DLR_NONNULL position, vec2 DLR_NONNULL dimension, bool filled) {

}

void rendererDrawCircle(Renderer* DLR_NONNULL renderer, vec2 DLR_NONNULL positionCenter, int radius, bool filled) {

}

void rendererDrawTexture(Renderer* DLR_NONNULL renderer, vec2 DLR_NONNULL position, vec2 DLR_NONNULL dimension, const dlrByte* DLR_NONNULL data) {

}
