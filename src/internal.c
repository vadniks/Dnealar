/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "internal.h"
#include <stdlib.h>

DlrMalloc internalMallocFunc = NULL;
DlrRealloc internalReallocFunc = NULL;
DlrFree internalFreeFunc = NULL;

void* DLR_NULLABLE internalMalloc(unsigned long size) {
    return internalMallocFunc(size);
}

void* DLR_NULLABLE internalRealloc(void* DLR_NULLABLE memory, unsigned long size) {
    return internalReallocFunc(memory, size);
}

void internalFree(void* DLR_NULLABLE memory) {
    internalFreeFunc(memory);
}

DlrContext* internalContext = NULL;

void internalAssert(bool condition) {
    if (!condition)
        abort();
}
