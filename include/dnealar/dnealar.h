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

typedef unsigned char dlrByte;

struct DLR_EXPORT DlrContext;
typedef struct DlrContext DlrContext;

typedef void* DLR_NULLABLE (* DLR_NONNULL DlrMalloc)(unsigned long size);
typedef void* DLR_NULLABLE (* DLR_NONNULL DlrRealloc)(void* DLR_NULLABLE memory, unsigned long size);
typedef void (* DLR_NONNULL DlrFree)(void* DLR_NULLABLE memory);

DLR_EXPORT void dlrSetMallocFunction(DlrMalloc malloc);
DLR_EXPORT void dlrSetReallocFunction(DlrRealloc realloc);
DLR_EXPORT void dlrSetFreeFunction(DlrFree free);

DLR_EXPORT void dlrInit(void);
DLR_EXPORT void dlrQuit(void);
DLR_EXPORT void dlrSetViewport(int width, int height);
DLR_EXPORT void dlrUpdateFrame(void);
