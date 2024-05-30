/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <dnealar/dnealar.h>
#include <dnealar/primitives.h>
#include <dnealar/widgets.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

enum FontSize {
    FONT_SIZE_DEFAULT = 16
};

static TTF_Font* gFont = NULL;

static void render(void) {
    dlrWidgetsText("Text", FONT_SIZE_DEFAULT, 0, 0);

    if (dlrWidgetsButton("Button", FONT_SIZE_DEFAULT, 50, 0))
        SDL_Log("button clicked");

    static bool clicked = false;
    if (dlrWidgetsCheckbox("Checkbox", FONT_SIZE_DEFAULT, clicked, false, 150, 0))
        clicked = !clicked;

    dlrWidgetsInfiniteProgressBar((int) SDL_GetTicks(), FONT_SIZE_DEFAULT, 300, 0);

//    dlrPrimitivesPoint(100, 100, 5, 255, 255, 255, 255);
//    dlrPrimitivesLine(10, 10, 90, 90, 5, 255, 255, 255, 255);
//    dlrPrimitivesRectangle(110, 110, 100, 50, 1, 255, 255, 255, 255, true);
//    dlrPrimitivesRectangle(220, 170, 100, 50, 5, 255, 255, 255, 255, false);
//    dlrPrimitivesCircle(300, 300, 50, 5, 255, 255, 255, 255, false);
//    dlrPrimitivesCircle(600, 300, 50, 1, 255, 255, 255, 255, true);
//
//    SDL_Surface* surface = TTF_RenderUTF8_Blended(gFont, "Hello World!", (SDL_Color) {255, 255, 255, 255});
//    SDL_Surface* xSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
//    SDL_FreeSurface(surface);
//    assert(xSurface != NULL);
//    DlrTexture* texture = dlrTextureCreate(xSurface->w, xSurface->h, xSurface->pixels);
//    SDL_FreeSurface(xSurface);
//    dlrPrimitivesTexture(texture, 500, 0, dlrTextureWidth(texture), dlrTextureHeight(texture), 0.0f, 255, 255, 255, 255);
//    dlrTextureDestroy(texture);

    SDL_Delay(1000 / 60);
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
                case SDL_MOUSEMOTION:
                    dlrUpdateMousePosition(event.motion.x, event.motion.y);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    dlrUpdateMouseButtonState(true);
                    break;
                case SDL_MOUSEBUTTONUP:
                    dlrUpdateMouseButtonState(false);
                    break;
            }
        }

        dlrUpdateFrame();
        render();
        SDL_GL_SwapWindow(window);
    }
}

static void* DLR_NONNULL textTextureCreate(const char* DLR_NONNULL text, int fontSize, int r, int g, int b, int a) {
    assert(fontSize == FONT_SIZE_DEFAULT);

    SDL_Surface* surface = TTF_RenderUTF8_Blended(gFont, text, (SDL_Color) {r, g, b, a});
    assert(surface != NULL);

    SDL_Surface* xSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
    assert(xSurface != NULL);

    SDL_FreeSurface(surface);
    return xSurface;
}

static void textureDestroy(void* DLR_NONNULL texture) {
    SDL_FreeSurface(texture);
}

static void textureMetrics(void* DLR_NONNULL texture, int* DLR_NONNULL width, int* DLR_NONNULL height) {
    *width = ((SDL_Surface*) texture)->w;
    *height = ((SDL_Surface*) texture)->h;
}

static void* DLR_NONNULL textureData(void* DLR_NONNULL texture) {
    return ((SDL_Surface*) texture)->pixels;
}

static void textMetrics(const char* DLR_NONNULL text, int fontSize, int* DLR_NONNULL width, int* DLR_NONNULL height) {
    assert(fontSize == FONT_SIZE_DEFAULT);
    TTF_SizeUTF8(gFont, text, width, height);
}

int main(void) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();
    gFont = TTF_OpenFont("res/RobotoMono.ttf", 16);

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
        "Dnealar",
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

    dlrInit(
        SDL_malloc,
        SDL_realloc,
        SDL_free,
        textTextureCreate,
        textureDestroy,
        textureMetrics,
        textureData,
        textMetrics
    );
    loop(window);
    dlrQuit();

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);

    TTF_CloseFont(gFont);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    assert(SDL_GetNumAllocations() == 0);
    return EXIT_SUCCESS;
}
