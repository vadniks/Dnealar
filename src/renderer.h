/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include "compoundShader.h"
#include <dnealar/dnealar.h>
#include <stdbool.h>
#include <cglm/types.h>

struct Renderer;
typedef struct Renderer Renderer;

Renderer* DLR_NONNULL rendererCreate(const CompoundShader* shader);
void rendererDestroy(Renderer* DLR_NONNULL renderer);
void rendererDrawPoint(Renderer* DLR_NONNULL renderer, vec2 position);
void rendererDrawLine(Renderer* DLR_NONNULL renderer, vec2 positionStart, vec2 positionEnd);
void rendererDrawRectangle(Renderer* DLR_NONNULL renderer, vec2 position, vec2 dimension, bool filled);
void rendererDrawCircle(Renderer* DLR_NONNULL renderer, vec2 positionCenter, int radius, bool filled);
void rendererDrawTexture(Renderer* DLR_NONNULL renderer, vec2 position, vec2 dimension, const dlrByte* data);