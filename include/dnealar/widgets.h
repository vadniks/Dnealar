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

struct DlrWidgetsFieldState;
typedef struct DlrWidgetsFieldState DlrWidgetsFieldState;

DLR_EXPORT void dlrWidgetsText(const char* DLR_NONNULL text, int fontSize, int x, int y);
DLR_EXPORT void dlrWidgetsTextSize(const char* DLR_NONNULL text, int fontSize, int* DLR_NONNULL width, int* DLR_NONNULL height);

DLR_EXPORT bool dlrWidgetsButton(const char* DLR_NONNULL text, int fontSize, int x, int y);
DLR_EXPORT void dlrWidgetsButtonSize(const char* DLR_NONNULL text, int fontSize, int* DLR_NONNULL width, int* DLR_NONNULL height);

DLR_EXPORT bool dlrWidgetsCheckbox(const char* DLR_NONNULL text, int fontSize, bool checked, bool square, int x, int y); // true - square, false - circle
DLR_EXPORT void dlrWidgetsCheckboxSize(const char* DLR_NONNULL text, int fontSize, int* DLR_NONNULL width, int* DLR_NONNULL height);

DLR_EXPORT void dlrWidgetsInfiniteProgressBar(int millisSinceStart, int fontSize, int x, int y);
DLR_EXPORT void dlrWidgetsInfiniteProgressBarSize(int fontSize, int* DLR_NONNULL x, int* DLR_NONNULL y);

DLR_EXPORT DlrWidgetsFieldState* DLR_NONNULL dlrWidgetsFieldStateCreate(void);
DLR_EXPORT void dlrWidgetsFieldStateDestroy(DlrWidgetsFieldState* DLR_NONNULL state);
DLR_EXPORT char* DLR_NULLABLE dlrWidgetsFieldStateText(DlrWidgetsFieldState* DLR_NONNULL state);
DLR_EXPORT void dlrWidgetsField(DlrWidgetsFieldState* DLR_NONNULL state, int fontSize, bool password, int x, int y, int width);
DLR_EXPORT void dlrWidgetsFieldSize(DlrWidgetsFieldState* DLR_NONNULL state, int fontSize, int* DLR_NONNULL width, int* DLR_NONNULL height);

// TODO: text wrap widget
