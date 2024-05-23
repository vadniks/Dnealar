/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include <dnealar/dnealar.h>
#include <dnealar/texture.h>
#include <stdbool.h>

DLR_EXPORT void dlrPoint(int x, int y, int pointSize, int r, int g, int b, int a);
DLR_EXPORT void dlrLine(int x0, int y0, int x1, int y1, int lineWidth, int r, int g, int b, int a);
DLR_EXPORT void dlrRectangle(int x, int y, int w, int h, int lineWidth, int r, int g, int b, int a, bool fill);
DLR_EXPORT void dlrCircle(int x, int y, int radius, int pointSize, int r, int g, int b, int a, bool fill);
DLR_EXPORT void dlrTexture(const DlrTexture* DLR_NONNULL texture, int x, int y, int w, int h, float rotation, int r, int g, int b, int a);
