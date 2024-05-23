/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <dnealar/primitives.h>
#include "renderer.h"

void dlrPoint(int x, int y, int size, int r, int g, int b, int a) {
    rendererDrawPoint((vec2) {(float) x, (float) y}, (float) size, (vec4) {(float) r, (float) g, (float) b, (float) a});
}

void dlrLine(int x0, int y0, int x1, int y1, int size, int r, int g, int b, int a) {
    rendererDrawLine((vec2) {(float) x0, (float) y0}, (vec2) {(float) x1, (float) y1}, (float) size, (vec4) {(float) r, (float) g, (float) b, (float) a});
}

void dlrRectangle(int x, int y, int w, int h, int size, int r, int g, int b, int a, bool fill) {
    rendererDrawRectangle((vec2) {(float) x, (float) y}, (vec2) {(float) w, (float) h}, (float) size, (vec4) {(float) r, (float) g, (float) b, (float) a}, fill);
}

void dlrCircle(int x, int y, int radius, int r, int g, int b, int a, bool fill) {

}

void dlrTexture(int x, int y, int w, int h, const dlrByte* DLR_NONNULL data) {

}
