#pragma once
#include "base.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct
{
    b8            running;
    u32           frames_per_second;
    i32           window_width;
    i32           window_height;
    SDL_Window*   window;
    SDL_Renderer* renderer;
    TTF_Font*     fonts[32];
} App;

extern App app;
