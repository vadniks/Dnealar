/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "internal.h"
#include "renderer.h"
#include <dnealar/widgets.h>
#include <dnealar/dnealar.h>

bool dlrWidgetsButton(const char* DLR_NONNULL text, int x, int y) {
    int textWidth, textHeight;
    internalTextMetrics(text, &textWidth, &textHeight);

    const int width = textWidth + 10, height = textHeight + 10;

    const bool withinBounds =
        internalMouseX >= x && internalMouseX <= x + width &&
        internalMouseY >= y && internalMouseY <= y + height;

    int r, g, b, a;
    internalDecodeColorChannels(withinBounds ? dlrHoverColor : dlrForegroundColor, &r, &g, &b, &a);

    rendererDrawRectangle(
        (vec2) {(float) x, (float) y},
        (vec2) {(float) width, (float) height},
        1,
        (vec4) {(float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f},
        false
    );

    void* rawTexture = internalTextTextureCreate(text, r, g, b, a);
    DlrTexture* texture = dlrTextureCreate(textWidth, textHeight, internalTextureData(rawTexture));
    rendererDrawTexture(
        texture,
        (vec2) {(float) x + 5.0f, (float) y + 5.0f},
        (vec2) {(float) textWidth, (float) textHeight},
        0.0f,
        (vec4) {1.0f, 1.0f, 1.0f, 1.0f}
    );
    dlrTextureDestroy(texture);
    internalTextureDestroy(rawTexture);

    return false;
}
