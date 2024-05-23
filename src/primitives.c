/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <dnealar/primitives.h>
#include "renderer.h"

void dlrPoint(int x, int y, int pointSize, int r, int g, int b, int a) {
    rendererDrawPoint((vec2) {(float) x, (float) y}, (float) pointSize, (vec4) {(float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f});
}

void dlrLine(int x0, int y0, int x1, int y1, int lineWidth, int r, int g, int b, int a) {
    rendererDrawLine((vec2) {(float) x0, (float) y0}, (vec2) {(float) x1, (float) y1}, (float) lineWidth, (vec4) {(float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f});
}

void dlrRectangle(int x, int y, int w, int h, int lineWidth, int r, int g, int b, int a, bool fill) {
    rendererDrawRectangle((vec2) {(float) x, (float) y}, (vec2) {(float) w, (float) h}, (float) lineWidth, (vec4) {(float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f}, fill);
}

void dlrCircle(int x, int y, int radius, int pointSize, int r, int g, int b, int a, bool fill) {
    rendererDrawCircle((vec2) {(float) x, (float) y}, radius, (float) pointSize, (vec4) {(float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f}, fill);
}

void dlrTexture(const DlrTexture* DLR_NONNULL texture, int x, int y, int w, int h, float rotation, int r, int g, int b, int a) {
    rendererDrawTexture(texture, (vec2) {(float) x, (float) y}, (vec2) {(float) w, (float) h}, rotation, (vec4) {(float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f});
}
