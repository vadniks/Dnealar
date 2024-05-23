/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "internal.h"
#include <dnealar/dnealar.h>
#include <GL/glew.h>

void dlrSetMallocFunction(DlrMalloc malloc) {
    *((DlrMalloc*) &internalMalloc) = malloc;
}

void dlrSetReallocFunction(DlrRealloc realloc) {
    *((DlrRealloc*) &internalRealloc) = realloc;
}

void dlrSetFreeFunction(DlrFree free) {
    *((DlrFree*) &internalFree) = free;
}

void dlrInit(void) {
    glewExperimental = GL_TRUE;
    internalAssert(glewInit() == GLEW_OK);

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void dlrQuit(void) {

}

void dlrSetViewport(int width, int height) {
    glViewport(0, 0, width, height);
}

void dlrUpdateFrame(int r, int g, int b, int a) {
    glClearColor((float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
