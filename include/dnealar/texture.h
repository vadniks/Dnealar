/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include "dnealar.h"

struct Texture;
typedef struct Texture Texture;

Texture* DLR_NONNULL textureCreate(int width, int height, const dlrByte* DLR_NONNULL data);
void textureDestroy(Texture* DLR_NONNULL texture);
void textureBind(const Texture* DLR_NONNULL texture);
int textureWidth(const Texture* DLR_NONNULL texture);
int textureHeight(const Texture* DLR_NONNULL texture);
