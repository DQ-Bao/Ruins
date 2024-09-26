#pragma once
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include "ruins_base.h"

typedef struct
{
    SDL_Surface* surface;
    SDL_Texture* texture;
} Texture;

typedef struct
{
    SDL_Rect src_rect;
    u64      texture_index;
} Sprite;

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
    f64              rotation_angle;
    SDL_Point        rotation_center;
    u32              scale;
    SDL_RendererFlip flip;
} RenderTransform;

Texture texture_load_png(SDL_Renderer* renderer, char* filepath);
void    render_texture(Texture* texture, i32 x, i32 y, RenderTransform* transform);
void    render_texture_repeat(Texture* texture, i32 x, i32 y, i32 count_x, i32 count_y, RenderTransform* transform);
void    render_sprite(Sprite* sprite, i32 x, i32 y, RenderTransform* transform);
void    render_sprite_repeat(Sprite* sprite, i32 x, i32 y, i32 count_x, i32 count_y, RenderTransform* transform);
