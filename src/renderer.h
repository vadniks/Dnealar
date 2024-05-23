/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include <dnealar/dnealar.h>
#include <stdbool.h>
#include <cglm/types.h>

void rendererInit(void);
void rendererQuit(void);
void rendererDrawPoint(const vec2 DLR_NONNULL position, const vec4 DLR_NONNULL color);
void rendererDrawLine(const vec2 DLR_NONNULL positionStart, const vec2 DLR_NONNULL positionEnd, const vec4 DLR_NONNULL color);
void rendererDrawRectangle(const vec2 DLR_NONNULL position, const vec2 DLR_NONNULL dimension, const vec4 DLR_NONNULL color, bool filled);
void rendererDrawCircle(const vec2 DLR_NONNULL positionCenter, int radius, const vec4 DLR_NONNULL color, bool filled);
void rendererDrawTexture(const vec2 DLR_NONNULL position, const vec2 DLR_NONNULL dimension, const dlrByte* DLR_NONNULL data);
