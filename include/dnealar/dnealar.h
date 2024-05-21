/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#if !defined(__GNUC__) || !defined(__STDC__) || __STDC_VERSION__ < 201710L // C17
#   error
#endif

#define DLR_EXPORT __attribute__((visibility("default")))

#ifdef __clang__
#   define DLR_NULLABLE _Nullable
#   define DLR_NONNULL _Nonnull
#else
#   define DLR_NULLABLE
#   define DLR_NONNULL
#endif

_Static_assert(sizeof(char) == 1 & sizeof(short) == 2 & sizeof(int) == 4 & sizeof(float) == 4 & sizeof(long) == 8 & sizeof(void*) == 8, "");

struct DLR_EXPORT DlrContext;
typedef struct DlrContext DlrContext;

DLR_EXPORT
void dlrSetMallocFunction(void* DLR_NULLABLE (* DLR_NONNULL malloc)(unsigned long size));

DLR_EXPORT
void dlrSetReallocFunction(void* DLR_NULLABLE (* DLR_NONNULL realloc)(void* DLR_NULLABLE memory, unsigned long size));

DLR_EXPORT
void dlrSetFreeFunction(void (* DLR_NONNULL free)(void* DLR_NULLABLE memory));
