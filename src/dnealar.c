/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <dnealar/dnealar.h>
#include "internal.h"

struct DlrContext {
    int todo;
};

void dlrSetMallocFunction(DlrMalloc malloc) {
    *((DlrMalloc*) &internalMalloc) = malloc;
}

void dlrSetReallocFunction(DlrRealloc realloc) {
    *((DlrRealloc*) &internalRealloc) = realloc;
}

void dlrSetFreeFunction(DlrFree free) {
    *((DlrFree*) &internalFree) = free;
}
