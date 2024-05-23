/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "texture.h"
#include "internal.h"
#include <GL/glew.h>

struct Texture {
    unsigned id;
    int width, height;
};

Texture* DLR_NONNULL textureCreate(int width, int height, const dlrByte* DLR_NONNULL data) {
    Texture* texture = internalMalloc(sizeof *texture);
    texture->id = 0;
    texture->width = width;
    texture->height = height;

    glGenTextures(1, &(texture->id));
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void textureDestroy(Texture* DLR_NONNULL texture) {
    glDeleteTextures(1, &(texture->id));
    internalFree(texture);
}

void textureBind(const Texture* DLR_NONNULL texture) {
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

int textureWidth(const Texture* DLR_NONNULL texture) {
    return texture->width;
}

int textureHeight(const Texture* DLR_NONNULL texture) {
    return texture->height;
}
