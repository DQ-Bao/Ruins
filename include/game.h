#pragma once
#include "base.h"
#include "input.h"
#include "render.h"

typedef struct
{
    Sprite* sprites;
    i32     sprite_count;
    i32     curr_sprite;
    i32     curr_frame;
    i32     period_frames;
    i32     frames_per_sprite;
} Animation;

typedef struct
{
    Texture   background;
    Texture   platform_sheet;
    Texture   character_sheet;
    Sprite    ground;
    Animation char_running;
} GameState;

void game_startup(GameState* game);
void game_update_and_render(GameState* game, InputState* input);
void game_shutdown(GameState* game);
