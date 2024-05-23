/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <dnealar/dnealar.h>
#include <dnealar/primitives.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

static void render(void) {
    dlrPoint(100, 100, 5, 255, 255, 255, 255);
    dlrLine(10, 10, 90, 90, 5, 255, 255, 255, 255);
    dlrRectangle(110, 110, 100, 50, 1, 255, 255, 255, 255, true);
    dlrRectangle(220, 170, 100, 50, 1, 255, 255, 255, 255, false);
    dlrCircle(300, 300, 50, 1, 255, 255, 255, 255, false);
    dlrCircle(600, 300, 50, 1, 255, 255, 255, 255, true);
}

static void loop(SDL_Window* window) {
    int width, height;
    SDL_Event event;

    while (true) {
        SDL_GL_GetDrawableSize(window, &width, &height);
        dlrSetViewport(width, height);

        while (SDL_PollEvent(&event) == 1) {
            switch (event.type) {
                case SDL_QUIT:
                    return;
            }
        }

        dlrUpdateFrame(0, 0, 0, 0);
        render();
        SDL_GL_SwapWindow(window);
    }
}

int main(void) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    SDL_version version;
    SDL_GetVersion(&version);
    assert(version.major == 2);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    const int windowMinimalWidth = 16 * 50, windowMinimalHeight = 9 * 50;

    SDL_Window* window = SDL_CreateWindow(
        "Neglest",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowMinimalWidth,
        windowMinimalHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    assert(window != NULL);
    SDL_SetWindowMinimumSize(window, windowMinimalWidth, windowMinimalHeight);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    SDL_GL_SetSwapInterval(1);

    dlrInit(SDL_malloc, SDL_realloc, SDL_free);
    loop(window);
    dlrQuit();

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    assert(SDL_GetNumAllocations() == 0);
    return EXIT_SUCCESS;
}
