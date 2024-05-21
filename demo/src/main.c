/*
  Dnealar - A simple OpenGL GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <dnealar/dnealar.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main(void) {
    dlrSetMallocFunction(SDL_malloc);
    dlrSetReallocFunction(SDL_realloc);
    dlrSetFreeFunction(SDL_free);
    return EXIT_SUCCESS;
}
