#pragma once
#include "ruins_base.h"
#include "ruins_input.h"
#include "ruins_render.h"

typedef struct
{
    Texture layers[5];
} Background;

typedef struct
{
    b8            running;
    SDL_Window*   window;
    SDL_Renderer* renderer;
    InputState    input_state;
    Background    background;
} Game;

void game_startup(Game* game);
void game_update_and_render(Game* game, f32 delta_time);
