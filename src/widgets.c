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

static void drawText(const char* DLR_NONNULL text, int fontSize, int x, int y, int r, int g, int b, int a) {
    void* rawTexture = internalTextTextureCreate(text, fontSize, r, g, b, a);

    int textWidth, textHeight;
    internalTextureMetrics(rawTexture, &textWidth, &textHeight);

    DlrTexture* texture = dlrTextureCreate(textWidth, textHeight, internalTextureData(rawTexture));
    rendererDrawTexture(
        texture,
        (vec2) {(float) x, (float) y},
        (vec2) {(float) textWidth, (float) textHeight},
        0.0f,
        (vec4) {1.0f, 1.0f, 1.0f, 1.0f}
    );
    dlrTextureDestroy(texture);

    internalTextureDestroy(rawTexture);
}

void dlrWidgetsText(const char* DLR_NONNULL text, int fontSize, int x, int y) {
    int r, g, b, a;
    internalDecodeColorChannels(dlrForegroundColor, &r, &g, &b, &a);
    drawText(text, fontSize, x, y, r, g, b, a);
}

void dlrWidgetsTextSize(const char* DLR_NONNULL text, int fontSize, int* DLR_NONNULL width, int* DLR_NONNULL height) {
    internalTextMetrics(text, fontSize, width, height);
}

bool dlrWidgetsButton(const char* DLR_NONNULL text, int fontSize, int x, int y) {
    int textWidth, textHeight;
    internalTextMetrics(text, fontSize, &textWidth, &textHeight);

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

    drawText(text, fontSize, x + 5, y + 5, r, g, b, a);

    bool clicked = withinBounds && internalMouseButtonDown;
    if (clicked)
        internalMouseButtonDown = false;

    return clicked;
}

void dlrWidgetsButtonSize(const char* DLR_NONNULL text, int fontSize, int* DLR_NONNULL width, int* DLR_NONNULL height) {
    internalTextMetrics(text, fontSize, width, height);
    (*width) += 10;
    (*height) += 10;
}

DLR_EXPORT bool dlrWidgetsCheckbox(const char* DLR_NONNULL text, int fontSize, bool checked, bool square, int x, int y) {
    int textWidth, textHeight;
    internalTextMetrics(text, fontSize, &textWidth, &textHeight);

    const int width = textWidth + 5 + textHeight, height = textHeight;

    const bool withinBounds =
        internalMouseX >= x && internalMouseX <= x + width &&
        internalMouseY >= y && internalMouseY <= y + height;

    int r, g, b, a;
    internalDecodeColorChannels(withinBounds ? dlrHoverColor : dlrForegroundColor, &r, &g, &b, &a);

    if (square)
        rendererDrawRectangle(
            (vec2) {(float) x, (float) y},
            (vec2) {(float) textHeight, (float) textHeight},
            1,
            (vec4) {(float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f},
            checked
        );
    else
        rendererDrawCircle(
            (vec2) {(float) x + (float) textHeight / 2.0f, (float) y + (float) textHeight / 2.0f},
            textHeight / 2 - 4,
            1,
            (vec4) {(float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f},
            checked
        );

    drawText(text, fontSize, x + 5 + textHeight, y, r, g, b, a);

    bool clicked = withinBounds && internalMouseButtonDown;
    if (clicked)
        internalMouseButtonDown = false;

    return clicked;
}

DLR_EXPORT void dlrWidgetsCheckboxSize(const char* DLR_NONNULL text, int fontSize, int* DLR_NONNULL width, int* DLR_NONNULL height) {
    internalTextMetrics(text, fontSize, width, height);
    (*width) += 5 + *height;
}
