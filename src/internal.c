/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "internal.h"
#include <stdlib.h>

const DlrMalloc internalMalloc = NULL; //malloc;
const DlrRealloc internalRealloc = NULL; //realloc;
const DlrFree internalFree = NULL; //free;

void internalAssert(bool condition) {
    if (!condition)
        abort();
}
