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

DLR_EXPORT void dlrWidgetsText(const char* DLR_NONNULL text, int fontSize, int x, int y);
DLR_EXPORT bool dlrWidgetsButton(const char* DLR_NONNULL text, int fontSize, int x, int y);
