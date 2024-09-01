#pragma once
#include "SDL2/SDL_render.h"
#include "base.h"

typedef struct
{
    SDL_Texture* texture;
    i32          width;
    i32          height;
} Texture;

typedef struct
{
    SDL_Texture* sheet;
    i32          x;
    i32          y;
    i32          width;
    i32          height;
} Sprite;

typedef struct
{
    f64              rotation_angle;
    SDL_Point        rotation_center;
    u32              scale;
    SDL_RendererFlip flip;
} RenderTransform;

Texture create_texture(char* filepath, b8 blend);
void    render_texture(Texture* texture, i32 x, i32 y, RenderTransform* transform);
void    render_texture_repeat(Texture* texture, i32 x, i32 y, i32 count_x, i32 count_y, RenderTransform* transform);
void    render_sprite(Sprite* sprite, i32 x, i32 y, RenderTransform* transform);
void    render_sprite_repeat(Sprite* sprite, i32 x, i32 y, i32 count_x, i32 count_y, RenderTransform* transform);
