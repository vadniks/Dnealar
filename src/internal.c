/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "internal.h"
#include <stdlib.h>

DlrMalloc internalMalloc = NULL;
DlrRealloc internalRealloc = NULL;
DlrFree internalFree = NULL;

DlrTextTextureCreate internalTextTextureCreate = NULL;
DlrTextureDestroy internalTextureDestroy = NULL;
DlrTextureMetrics internalTextureMetrics = NULL;
DlrTextureData internalTextureData = NULL;

DlrTextMetrics internalTextMetrics = NULL;

mat4 internalProjection = {0};

int internalMouseX = 0, internalMouseY = 0;
bool internalMouseButtonDown = false;

void internalAssert(bool condition) {
    if (!condition)
        abort();
}

void internalDecodeColorChannels(int color, int* DLR_NONNULL r, int* DLR_NONNULL g, int* DLR_NONNULL b, int* DLR_NONNULL a) {
    const int probe = 0x12345678;
    internalAssert(*((dlrByte*) &probe) == 0x78);

    *r = (color >> 0) & 0xff;
    *g = (color >> 8) & 0xff;
    *b = (color >> 16) & 0xff;
    *a = (color >> 24) & 0xff;
}
