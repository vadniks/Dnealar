/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "internal.h"
#include "context.h"
#include "renderer.h"
#include <dnealar/dnealar.h>
#include <GL/glew.h>
#include <cglm/cam.h>

void dlrInit(DlrMalloc malloc, DlrRealloc realloc, DlrFree free) {
    glewExperimental = GL_TRUE;
    internalAssert(glewInit() == GLEW_OK);

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    internalMallocFunc = malloc;
    internalReallocFunc = realloc;
    internalFreeFunc = free;

    internalContext = internalMalloc(sizeof(DlrContext));
    rendererInit();
}

void dlrQuit(void) {
    rendererQuit();
    internalFree(internalContext);
}

void dlrSetViewport(int width, int height) {
    glViewport(0, 0, width, height);
    glm_ortho(0.0f, (float) width, (float) height, 0.0f, -1.0f, 1.0f, internalContext->projection);
}

void dlrUpdateFrame(int r, int g, int b, int a) {
    glClearColor((float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
