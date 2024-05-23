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

void rendererDrawLine(const vec2 DLR_NONNULL positionStart, const vec2 DLR_NONNULL positionEnd, float lineWidth, const vec4 DLR_NONNULL color) {
    glBindVertexArray(gRenderer->vao);

    const float vertices[] = {
        positionStart[0], positionStart[1],
        positionEnd[0], positionEnd[1]
    };

    glBindBuffer(GL_ARRAY_BUFFER, gRenderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    compoundShaderUse(gRenderer->shader);
    compoundShaderSetMat4(gRenderer->shader, "projection", internalContext->projection);
    compoundShaderSetVec4(gRenderer->shader, "color", color);

    glLineWidth((float) lineWidth);
    glDrawArrays(GL_LINES, 0, 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void rendererDrawRectangle(const vec2 DLR_NONNULL position, const vec2 DLR_NONNULL dimension, float lineWidth, const vec4 DLR_NONNULL color, bool filled) {
    glBindVertexArray(gRenderer->vao);

    const float vertices[] = {
        position[0] + dimension[0], position[1],
        position[0] + dimension[0], position[1] + dimension[1],
        position[0], position[1] + dimension[1],
        position[0], position[1]
    };

    glBindBuffer(GL_ARRAY_BUFFER, gRenderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    const unsigned indicesFilled[] = {
        0, 1, 3,
        1, 2, 3
    };

    const unsigned indicesUnfilled[] = {
        0, 1, 2, 3,
        1, 2, 0, 3
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gRenderer->ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        filled ? sizeof(indicesFilled) : sizeof(indicesUnfilled),
        filled ? indicesFilled : indicesUnfilled,
        GL_DYNAMIC_DRAW
    );

    compoundShaderUse(gRenderer->shader);
    compoundShaderSetMat4(gRenderer->shader, "projection", internalContext->projection);
    compoundShaderSetVec4(gRenderer->shader, "color", color);

    if (!filled)
        glLineWidth((float) lineWidth);

    glDrawElements(filled ? GL_TRIANGLES : GL_LINES, filled ? 6 : 8, GL_UNSIGNED_INT, (void*) 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static void drawCircle(const vec2 DLR_NONNULL positionCenter, int radius, float pointSize, const vec4 DLR_NONNULL color) {
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y) {
        rendererDrawPoint((vec2) {positionCenter[0] + (float) x, positionCenter[1] - (float) y}, pointSize, color);
        rendererDrawPoint((vec2) {positionCenter[0] + (float) x, positionCenter[1] + (float) y}, pointSize, color);
        rendererDrawPoint((vec2) {positionCenter[0] - (float) x, positionCenter[1] - (float) y}, pointSize, color);
        rendererDrawPoint((vec2) {positionCenter[0] - (float) x, positionCenter[1] + (float) y}, pointSize, color);
        rendererDrawPoint((vec2) {positionCenter[0] + (float) y, positionCenter[1] - (float) x}, pointSize, color);
        rendererDrawPoint((vec2) {positionCenter[0] + (float) y, positionCenter[1] + (float) x}, pointSize, color);
        rendererDrawPoint((vec2) {positionCenter[0] - (float) y, positionCenter[1] - (float) x}, pointSize, color);
        rendererDrawPoint((vec2) {positionCenter[0] - (float) y, positionCenter[1] + (float) x}, pointSize, color);

        if (error <= 0) {
            y++;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            x--;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void rendererDrawCircle(const vec2 DLR_NONNULL positionCenter, int radius, float pointSize, const vec4 DLR_NONNULL color, bool filled) {
    if (!filled) {
        drawCircle(positionCenter, radius, pointSize, color);
        return;
    }

    for (int i = radius; i >= 0; i--)
        drawCircle(positionCenter, i, 1, color);
}

void rendererDrawTexture(const vec2 DLR_NONNULL position, const vec2 DLR_NONNULL dimension, const dlrByte* DLR_NONNULL data) { // TODO: add a Texture module & struct

}
