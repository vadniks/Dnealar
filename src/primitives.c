/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <dnealar/primitives.h>
#include "renderer.h"

void dlrPoint(int x, int y, int r, int g, int b, int a) {
    rendererDrawPoint((vec2) {(float) x, (float) y}, (vec4) {(float) r, (float) g, (float) b, (float) a});
}

void dlrLine(int x0, int y0, int x1, int y1, int r, int g, int b, int a) {

}

void dlrRectangle(int x, int y, int w, int h, int r, int g, int b, int a, bool fill) {

}

void dlrCircle(int x, int y, int radius, int r, int g, int b, int a, bool fill) {

}

void dlrTexture(int x, int y, int w, int h, const dlrByte* DLR_NONNULL data) {

}
