/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "renderer.h"

struct Renderer {

};

Renderer* DLR_NONNULL rendererCreate(const CompoundShader* DLR_NONNULL shader) {

}

void rendererDestroy(Renderer* DLR_NONNULL renderer) {

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
