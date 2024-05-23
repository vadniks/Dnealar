/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "internal.h"
#include <stdlib.h>

DlrMalloc internalMalloc = NULL;
DlrRealloc internalRealloc = NULL;
DlrFree internalFree = NULL;

DlrTextTextureCreate internalTextTextureCreate = NULL;
DlrTextureDestroy internalTextureDestroy = NULL;
DlrTextureMetrics internalTextureMetrics = NULL;
DlrTextureData internalTextureData = NULL;

DlrContext* DLR_NONNULL internalContext = NULL;

DlrTextMetrics internalTextMetrics = NULL;

void internalAssert(bool condition) {
    if (!condition)
        abort();
}
