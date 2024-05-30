/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <dnealar/dnealar.h>
#include <stdbool.h>
#include <cglm/types.h>

// assume const:
extern DlrMalloc internalMalloc;
extern DlrRealloc internalRealloc;
extern DlrFree internalFree;

// assume const:
extern DlrTextTextureCreate internalTextTextureCreate;
extern DlrTextureDestroy internalTextureDestroy;
extern DlrTextureMetrics internalTextureMetrics;
extern DlrTextureData internalTextureData;

// assume const:
extern DlrTextMetrics internalTextMetrics;

// assume const:
extern mat4 internalProjection;

// assume const:
extern int internalMouseX, internalMouseY;
// assume non-const:
extern bool internalMouseButtonDown;

extern const void* DLR_NULLABLE internalActiveField;
extern int internalNextGlyph;
extern bool internalKeyboardInputting;
extern bool internalKeyboardInputErasing;

void internalAssert(bool condition);
void internalDecodeColorChannels(int color, int* DLR_NONNULL r, int* DLR_NONNULL g, int* DLR_NONNULL b, int* DLR_NONNULL a);
