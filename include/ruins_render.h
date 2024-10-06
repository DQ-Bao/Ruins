#pragma once
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include "ruins_base.h"
#define TILE_COUNT_WIDTH 40
#define TILE_COUNT_HEIGHT 23
#define TILE_SIZE 32
#define TILEMAP_MAX_TILES 2048

typedef struct
{
    SDL_Surface* surface;
    SDL_Texture* texture;
} Texture;

typedef struct
{
    SDL_Rect src_rect;
    i32      texture_index;
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
    u32 tile_size;
    i32 tiles[TILE_COUNT_HEIGHT][TILE_COUNT_WIDTH];
} TileMap;

typedef struct
{
    f64              rotation_angle;
    SDL_Point        rotation_center;
    u32              scale;
    SDL_RendererFlip flip;
} RenderTransform;

Texture texture_load_png(SDL_Renderer* renderer, char* filepath);
void    texture_free(Texture* texture);
void    render_tilemap(SDL_Renderer* renderer, TileMap* map);
