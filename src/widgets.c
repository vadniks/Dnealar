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
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef enum {
    INFINITE_PROGRESS_BAR_STATE_A = 150,
    INFINITE_PROGRESS_BAR_STATE_B = 300,
    INFINITE_PROGRESS_BAR_STATE_C = 450,
    INFINITE_PROGRESS_BAR_STATE_D = 600,
    INFINITE_PROGRESS_BAR_STATE_E = 750,
    INFINITE_PROGRESS_BAR_STATE_F = 1000
} InfiniteProgressBarState;

struct DlrWidgetsFieldState {
    int* DLR_NULLABLE glyphs;
    int length;
};

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

bool dlrWidgetsCheckbox(const char* DLR_NONNULL text, int fontSize, bool checked, bool square, int x, int y) {
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

void dlrWidgetsCheckboxSize(const char* DLR_NONNULL text, int fontSize, int* DLR_NONNULL width, int* DLR_NONNULL height) {
    internalTextMetrics(text, fontSize, width, height);
    (*width) += 5 + *height;
}

void dlrWidgetsInfiniteProgressBar(int millisSinceStart, int fontSize, int x, int y) {
    const int interval = millisSinceStart % INFINITE_PROGRESS_BAR_STATE_F;

    const char* string;
    if (INFINITE_PROGRESS_BAR_STATE_A >= interval)
        string = "==----------";
    else if (INFINITE_PROGRESS_BAR_STATE_B >= interval)
        string = "--==--------";
    else if (INFINITE_PROGRESS_BAR_STATE_C >= interval)
        string = "----==------";
    else if (INFINITE_PROGRESS_BAR_STATE_D >= interval)
        string = "------==----";
    else if (INFINITE_PROGRESS_BAR_STATE_E >= interval)
        string = "--------==--";
    else if (INFINITE_PROGRESS_BAR_STATE_F >= interval)
        string = "----------==";

    int r, g, b, a;
    internalDecodeColorChannels(dlrForegroundColor, &r, &g, &b, &a);

    drawText(string, fontSize, x, y, r, g, b, a);
}

void dlrWidgetsInfiniteProgressBarSize(int fontSize, int* DLR_NONNULL x, int* DLR_NONNULL y) {
    internalTextMetrics("==----------", fontSize, x, y);
}

DlrWidgetsFieldState* DLR_NONNULL dlrWidgetsFieldStateCreate(void) {
    DlrWidgetsFieldState* state = internalMalloc(sizeof *state);
    state->glyphs = NULL;
    state->length = 0;
    return state;
}

void dlrWidgetsFieldStateDestroy(DlrWidgetsFieldState* DLR_NONNULL state) {
    internalFree(state->glyphs);
    internalFree(state);
}

char* DLR_NULLABLE dlrWidgetsFieldStateText(DlrWidgetsFieldState* DLR_NONNULL state) {
    if (state->length == 0)
        return NULL;

    char* text = NULL;
    int textLength = 0;
    for (int i = 0; i < state->length; i++) {
        const char* const glyphBytes = (char*) &(state->glyphs[i]);

        for (int j = 0; j < (int) sizeof(int); j++) {
            if (glyphBytes[j] == 0) break;
            text = internalRealloc(text, ++textLength);
            internalAssert(text != NULL);
            text[textLength - 1] = glyphBytes[j];
        }
    }

    text = internalRealloc(text, ++textLength);
    text[textLength - 1] = 0;

    return text;
}

void dlrWidgetsField(DlrWidgetsFieldState* DLR_NONNULL state, int fontSize, bool password, int x, int y, int width) {
    char* DLR_NULLABLE const text = dlrWidgetsFieldStateText(state);

    int textWidth, textHeight;
    if (text != NULL)
        internalTextMetrics(text, fontSize, &textWidth, &textHeight);
    else {
        internalTextMetrics("W", fontSize, &textWidth, &textHeight);
        textWidth = 0;
    }

    const bool active = internalActiveField == state;
    if (active) {

        if (internalKeyboardInputErasing && state->length > 0) {
            internalKeyboardInputErasing = false;

            if (state->length > 1)
                state->glyphs = internalRealloc(state->glyphs, --(state->length) * sizeof(int));
            else {
                internalFree(state->glyphs);
                state->glyphs = NULL;
                state->length = 0;
            }
        }

        if (internalKeyboardInputting && textWidth < width) {
            internalKeyboardInputting = false;
            state->glyphs = internalRealloc(state->glyphs, ++(state->length) * sizeof(int));
            internalAssert(state->glyphs != NULL);
            state->glyphs[state->length - 1] = internalNextGlyph;
        }
    }

    int r, g, b, a;
    internalDecodeColorChannels(dlrForegroundColor, &r, &g, &b, &a);

    if (text != NULL) {
        const int passwordTextSize = (int) strlen(text);
        char passwordText[passwordTextSize + 1];
        memset(passwordText, '*', passwordTextSize);
        passwordText[passwordTextSize] = 0;

        drawText(password ? passwordText : text, fontSize, x, y, r, g, b, a);
    }

    internalFree(text);

    const int height = textHeight + 5;

    const bool withinBounds =
        internalMouseX >= x && internalMouseX <= x + width &&
        internalMouseY >= y && internalMouseY <= y + height + 1;

    if (withinBounds && internalMouseButtonDown) {
        internalMouseButtonDown = false;
        internalActiveField = state;
    }

    internalDecodeColorChannels(
        withinBounds ? dlrHoverColor : active ? dlrForegroundColor : dlrPassiveColor,
        &r, &g, &b, &a
    );

    rendererDrawLine(
        (vec2) {(float) x, (float) y + (float) textHeight + 5},
        (vec2) {(float) x + (float) width, (float) y + (float) textHeight + 5},
        1,
        (vec4) {(float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f}
    );
}

void dlrWidgetsFieldSize(DlrWidgetsFieldState* DLR_NONNULL state, int fontSize, int* DLR_NONNULL width, int* DLR_NONNULL height) {
    char* text = dlrWidgetsFieldStateText(state);
    internalTextMetrics(text, fontSize, width, height);
    internalFree(text);
    *height += 5 + 1;
}
