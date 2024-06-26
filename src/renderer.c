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
#include <cglm/affine.h>

struct Renderer {
    CompoundShader* shapeShader;
    CompoundShader* spriteShader;
    unsigned vbo, ebo, vao;
};
typedef struct Renderer Renderer;

static Renderer* DLR_NULLABLE gRenderer = NULL;

static const char* const gShapeVertexShader =
    "#version 330 core\n"
    "layout (location = 0) in vec2 pos;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "   gl_Position = projection * vec4(pos, 0.0, 1.0);\n"
    "}\n";

static const char* const gShapeFragmentShader =
    "#version 330 core\n"
    "out vec4 colorOut;\n"
    "uniform vec4 color;\n"
    "void main() {\n"
    "   colorOut = color;\n"
    "}\n";

static const char* const gSpriteVertexShader =
    "#version 330 core\n"
    "layout (location = 0) in vec4 vertex;\n"
    "out vec2 textureCoords;\n"
    "uniform mat4 model;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "   textureCoords = vertex.zw;\n"
    "   gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);\n"
    "}";

static const char* const gSpriteFragmentShader =
    "#version 330 core\n"
    "in vec2 textureCoords;\n"
    "out vec4 color;\n"
    "uniform sampler2D sprite;\n"
    "uniform vec4 spriteColor;\n"
    "void main() {\n"
    "   color = spriteColor * texture(sprite, textureCoords);\n"
    "}";

void rendererInit(void) {
    gRenderer = internalMalloc(sizeof *gRenderer);
    gRenderer->shapeShader = compoundShaderCreate(gShapeVertexShader, gShapeFragmentShader);
    gRenderer->spriteShader = compoundShaderCreate(gSpriteVertexShader, gSpriteFragmentShader);
    glGenBuffers(1, &(gRenderer->vbo));
    glGenBuffers(1, &(gRenderer->ebo));
    glGenVertexArrays(1, &((gRenderer->vao)));
}

void rendererQuit(void) {
    compoundShaderDestroy(gRenderer->shapeShader);
    compoundShaderDestroy(gRenderer->spriteShader);
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

    compoundShaderUse(gRenderer->shapeShader);
    compoundShaderSetMat4(gRenderer->shapeShader, "projection", internalProjection);
    compoundShaderSetVec4(gRenderer->shapeShader, "color", color);

    glPointSize((float) pointSize);
    glDrawArrays(GL_POINTS, 0, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static void drawPoints(int count, const float* DLR_NONNULL vertices, float pointSize, const vec4 DLR_NONNULL color) {
    glBindVertexArray(gRenderer->vao);

    glBindBuffer(GL_ARRAY_BUFFER, gRenderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, (long) (count * sizeof(float)), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    compoundShaderUse(gRenderer->shapeShader);
    compoundShaderSetMat4(gRenderer->shapeShader, "projection", internalProjection);
    compoundShaderSetVec4(gRenderer->shapeShader, "color", color);

    glPointSize((float) pointSize);
    glDrawArrays(GL_POINTS, 0, count);

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

    compoundShaderUse(gRenderer->shapeShader);
    compoundShaderSetMat4(gRenderer->shapeShader, "projection", internalProjection);
    compoundShaderSetVec4(gRenderer->shapeShader, "color", color);

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

    compoundShaderUse(gRenderer->shapeShader);
    compoundShaderSetMat4(gRenderer->shapeShader, "projection", internalProjection);
    compoundShaderSetVec4(gRenderer->shapeShader, "color", color);

    if (!filled)
        glLineWidth((float) lineWidth);

    glDrawElements(filled ? GL_TRIANGLES : GL_LINES, filled ? 6 : 8, GL_UNSIGNED_INT, (void*) 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static void drawCircle(const vec2 DLR_NONNULL positionCenter, int radius, float pointSize, const vec4 DLR_NONNULL color) {
    const int diameter = (radius * 2);

    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    int count = 0;
    float* vertices = NULL;

    while (x >= y) {
        count += 16;
        vertices = internalRealloc(vertices, count * sizeof(float));
        vertices[count - 16] = positionCenter[0] + (float) x; vertices[count - 15] = positionCenter[1] - (float) y;
        vertices[count - 14] = positionCenter[0] + (float) x; vertices[count - 13] = positionCenter[1] + (float) y;
        vertices[count - 12] = positionCenter[0] - (float) x; vertices[count - 11] = positionCenter[1] - (float) y;
        vertices[count - 10] = positionCenter[0] - (float) x; vertices[count - 9] = positionCenter[1] + (float) y;
        vertices[count - 8] = positionCenter[0] + (float) y; vertices[count - 7] = positionCenter[1] - (float) x;
        vertices[count - 6] = positionCenter[0] + (float) y; vertices[count - 5] = positionCenter[1] + (float) x;
        vertices[count - 4] = positionCenter[0] - (float) y; vertices[count - 3] = positionCenter[1] - (float) x;
        vertices[count - 2] = positionCenter[0] - (float) y; vertices[count - 1] = positionCenter[1] + (float) x;

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

    if (vertices != NULL)
        drawPoints(count, vertices, pointSize, color);
    internalFree(vertices);
}

static void drawFilledCircle(const vec2 DLR_NONNULL position, int radius, float pointSize, const vec4 DLR_NONNULL color) {
    int count = 0;
    float* vertices = NULL;

    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            const int dx = radius - w, dy = radius - h;

            if ((dx * dx + dy * dy) <= (radius * radius)) {
                count += 2;
                vertices = internalRealloc(vertices, count * sizeof(float));
                vertices[count - 2] = position[0] + (float) dx; vertices[count - 1] = position[1] + (float) dy;
            }
        }
    }

    if (vertices != NULL)
        drawPoints(count, vertices, pointSize, color);
    internalFree(vertices);
}

void rendererDrawCircle(const vec2 DLR_NONNULL positionCenter, int radius, float pointSize, const vec4 DLR_NONNULL color, bool filled) { // TODO: optimize
    if (!filled)
        drawCircle(positionCenter, radius, pointSize, color);
    else
        drawFilledCircle(positionCenter, radius, pointSize, color);
}

void rendererDrawTexture(const DlrTexture* DLR_NONNULL texture, const vec2 DLR_NONNULL position, const vec2 DLR_NONNULL size, float rotation, const vec4 DLR_NONNULL color) {
    glBindVertexArray(gRenderer->vao);

    float vertices[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, gRenderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, (vec3) {position[0], position[1], 0.0f});

    glm_translate(model, (vec3) {0.5f * size[0], 0.5f * size[1], 0.0f});
    glm_rotate(model, glm_rad(rotation), (vec3) {0.0f, 0.0f, 1.0f});
    glm_translate(model, (vec3) {-0.5f * size[0], -0.5f * size[1], 0.0f});

    glm_scale(model, (vec3) {size[0], size[1], 1.0f});

    compoundShaderUse(gRenderer->spriteShader);
    compoundShaderSetMat4(gRenderer->spriteShader, "projection", internalProjection);
    compoundShaderSetMat4(gRenderer->spriteShader, "model", model);
    compoundShaderSetVec4(gRenderer->spriteShader, "spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    dlrTextureBind(texture);

    glBindVertexArray(gRenderer->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
