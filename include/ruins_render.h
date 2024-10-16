#pragma once
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include "ruins_base.h"
#define TILE_COUNT_WIDTH 40
#define TILE_COUNT_HEIGHT 23
#define MAX_OBJECTS 256
#define MAX_ANIM_FRAMES 256

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
    u32 frame_count;
    u32 sprite_indexes[MAX_ANIM_FRAMES];
    u32 durations_in_frames[MAX_ANIM_FRAMES];

    u32 current_frame;
    u32 frame_cooldown;
} Frames;

typedef struct
{
    u32 tile_size;
    i32 tiles[TILE_COUNT_HEIGHT][TILE_COUNT_WIDTH];
} TileMap;

typedef struct
{
    u32      obj_count;
    b8       has_anim[MAX_OBJECTS];
    SDL_Rect positions[MAX_OBJECTS];
    u32      indexes[MAX_OBJECTS];
} ObjectMap;

typedef struct
{
    f64              rotation_angle;
    SDL_Point        rotation_center;
    u32              scale;
    SDL_RendererFlip flip;
} RenderTransform;

Texture texture_load_png(SDL_Renderer* renderer, char* filepath);
void    texture_free(Texture* texture);
void    anim_frames_reset(Frames* anim);
void    render_sprite(SDL_Renderer* renderer, Sprite* sprite, SDL_Rect dest_rect);
void    render_frames(SDL_Renderer* renderer, Frames* frames, SDL_Rect dest_rect);
void    render_tilemap(SDL_Renderer* renderer, TileMap* map);
void    render_objmap(SDL_Renderer* renderer, ObjectMap* map);
