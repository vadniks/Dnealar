/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include <dnealar/dnealar.h>

struct DLR_EXPORT DlrTexture;
typedef struct DlrTexture DlrTexture;

DLR_EXPORT DlrTexture* DLR_NONNULL dlrTextureCreate(int width, int height, const dlrByte* DLR_NONNULL data);
DLR_EXPORT void dlrTextureDestroy(DlrTexture* DLR_NONNULL texture);
DLR_EXPORT void dlrTextureBind(const DlrTexture* DLR_NONNULL texture);
DLR_EXPORT int dlrTextureWidth(const DlrTexture* DLR_NONNULL texture);
DLR_EXPORT int dlrTextureHeight(const DlrTexture* DLR_NONNULL texture);
