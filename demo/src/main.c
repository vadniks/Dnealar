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

static const int WIDGETS_PER_LIST_PAGE = 8, TOTAL_WIDGETS_IN_LIST = WIDGETS_PER_LIST_PAGE * 3 + 3;

static TTF_Font* gFont = NULL;
static DlrWidgetsFieldState* gFieldState1 = NULL;
static DlrWidgetsFieldState* gFieldState2 = NULL;
static DlrWidgetsFieldState* gFieldState3 = NULL;
static int gListOffset = 0;
static SDL_Window* gWindow = NULL;

static void listButtonClicked(int which) {
    char message[10];
    assert(SDL_snprintf(message, sizeof message, "Button %d", which) <= (int) sizeof message);
    assert(SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "List button clicked", message, gWindow) == 0);
}

static void renderWidgets(void) {
    dlrWidgetsText("Text", FONT_SIZE_DEFAULT, 0, 0);

    if (dlrWidgetsButton("Button", FONT_SIZE_DEFAULT, 50, 0))
        SDL_Log("button clicked");

    static bool clicked = false;
    if (dlrWidgetsCheckbox("Checkbox", FONT_SIZE_DEFAULT, clicked, false, 150, 0))
        clicked = !clicked;

    dlrWidgetsInfiniteProgressBar((int) SDL_GetTicks(), FONT_SIZE_DEFAULT, 300, 0);

    dlrWidgetsField(gFieldState1, FONT_SIZE_DEFAULT, false, 0, 100, 150);
    dlrWidgetsField(gFieldState2, FONT_SIZE_DEFAULT, true, 160, 100, 150);

    dlrWidgetsWrappedField(gFieldState3, FONT_SIZE_DEFAULT, 0, 200, 150, 70);

    // aka list widget:

    dlrPrimitivesRectangle(425, 10, 350, 400, 1, 255, 255, 255, 255, false);

    for (int i = 0; i < WIDGETS_PER_LIST_PAGE; i++) {
        if (i + gListOffset >= TOTAL_WIDGETS_IN_LIST) break;

        char title[10];
        assert(SDL_snprintf(title, sizeof title, "Item %d", gListOffset + i) <= (int) sizeof title);
        dlrWidgetsText(title, FONT_SIZE_DEFAULT, 425, 10 + i * 50);

        dlrWidgetsText("Subtitle", FONT_SIZE_DEFAULT, 425, 30 + i * 50);

        char button[10];
        assert(SDL_snprintf(button, sizeof button, "Click %d", gListOffset + i) <= (int) sizeof button);
        if (dlrWidgetsButton(button, FONT_SIZE_DEFAULT, 425 + 260, 20 + i * 50))
            listButtonClicked(gListOffset + i);

        dlrPrimitivesLine(425, 10 + i * 50, 425 + 350, 10 + i * 50, 1, 200, 200, 200, 200);
    }
}

static void renderPrimitives(void) {
    dlrPrimitivesPoint(100, 100, 5, 255, 255, 255, 255);
    dlrPrimitivesLine(10, 10, 90, 90, 5, 255, 255, 255, 255);
    dlrPrimitivesRectangle(110, 110, 100, 50, 1, 255, 255, 255, 255, true);
    dlrPrimitivesRectangle(220, 170, 100, 50, 5, 255, 255, 255, 255, false);
    dlrPrimitivesCircle(300, 300, 50, 5, 255, 255, 255, 255, false);
    dlrPrimitivesCircle(600, 300, 50, 1, 255, 255, 255, 255, true);

    SDL_Surface* surface = TTF_RenderUTF8_Blended(gFont, "Hello World!", (SDL_Color) {255, 255, 255, 255});
    SDL_Surface* xSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(surface);
    assert(xSurface != NULL);
    DlrTexture* texture = dlrTextureCreate(xSurface->w, xSurface->h, xSurface->pixels);
    SDL_FreeSurface(xSurface);
    dlrPrimitivesTexture(texture, 500, 0, dlrTextureWidth(texture), dlrTextureHeight(texture), 0.0f, 255, 255, 255, 255);
    dlrTextureDestroy(texture);
}

static void render(void) {
#if true
    renderWidgets();
#else
    renderPrimitives();
#endif
    SDL_Delay(1000 / 60);
}

static void loop(void) {
    int width, height;
    SDL_Event event;

    gFieldState1 = dlrWidgetsFieldStateCreate();
    gFieldState2 = dlrWidgetsFieldStateCreate();
    gFieldState3 = dlrWidgetsFieldStateCreate();

    while (true) {
        SDL_GL_GetDrawableSize(gWindow, &width, &height);
        dlrSetViewport(width, height);

        while (SDL_PollEvent(&event) == 1) {
            switch (event.type) {
                case SDL_QUIT:
                    goto end;
                case SDL_MOUSEMOTION:
                    dlrUpdateMousePosition(event.motion.x, event.motion.y);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    dlrUpdateMouseButtonState(true);
                    break;
                case SDL_MOUSEBUTTONUP:
                    dlrUpdateMouseButtonState(false);
                    break;
                case SDL_KEYDOWN:
                    dlrKeyDown(event.key.keysym.sym == SDLK_BACKSPACE);
                    break;
                case SDL_KEYUP:
                    dlrKeyUp();
                    break;
                case SDL_TEXTINPUT:
                    dlrTextInput(event.text.text);
                    break;
                case SDL_MOUSEWHEEL:
                    if (event.wheel.y > 0) {
                        if (gListOffset > 0)
                            gListOffset -= 1;
                    } else {
                        if (gListOffset + 1 < TOTAL_WIDGETS_IN_LIST)
                            gListOffset += 1;
                    }
                    break;
            }
        }

        dlrUpdateFrame();
        render();
        SDL_GL_SwapWindow(gWindow);
    }
    end:

    {
        char* text1 = dlrWidgetsFieldStateText(gFieldState1);
        char* text2 = dlrWidgetsFieldStateText(gFieldState2);
        char* text3 = dlrWidgetsFieldStateText(gFieldState3);

        SDL_Log("|%s| |%s| |%s|", text1, text2, text3);

        SDL_free(text1);
        SDL_free(text2);
        SDL_free(text3);
    }

    dlrWidgetsFieldStateDestroy(gFieldState1);
    dlrWidgetsFieldStateDestroy(gFieldState2);
    dlrWidgetsFieldStateDestroy(gFieldState3);
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

static void* DLR_NONNULL wrappedTextTextureCreate(const char* DLR_NONNULL text, int width, int fontSize, int r, int g, int b, int a) {
    assert(fontSize == FONT_SIZE_DEFAULT);

    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(gFont, text, (SDL_Color) {r, g, b, a}, width);
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

    gWindow = SDL_CreateWindow(
        "Dnealar",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowMinimalWidth,
        windowMinimalHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    assert(gWindow != NULL);
    SDL_SetWindowMinimumSize(gWindow, windowMinimalWidth, windowMinimalHeight);

    SDL_GLContext glContext = SDL_GL_CreateContext(gWindow);

    SDL_GL_SetSwapInterval(1);

    dlrInit(
        SDL_malloc,
        SDL_realloc,
        SDL_free,
        textTextureCreate,
        wrappedTextTextureCreate,
        textureDestroy,
        textureMetrics,
        textureData,
        textMetrics
    );
    loop();
    dlrQuit();

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(gWindow);

    TTF_CloseFont(gFont);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    assert(SDL_GetNumAllocations() == 0);
    return EXIT_SUCCESS;
}
