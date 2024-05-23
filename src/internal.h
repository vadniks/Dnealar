/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <dnealar/dnealar.h>
#include <stdbool.h>

// assume const:
extern DlrMalloc internalMallocFunc;
extern DlrRealloc internalReallocFunc;
extern DlrFree internalFreeFunc;

void* DLR_NULLABLE internalMalloc(unsigned long size);
void* DLR_NULLABLE internalRealloc(void* DLR_NULLABLE memory, unsigned long size);
void internalFree(void* DLR_NULLABLE memory);

extern DlrContext* DLR_NONNULL internalContext;

void internalAssert(bool condition);
