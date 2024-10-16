#pragma once
#include "ruins_render.h"
#include "ruins_string.h"
#define ASSET_TEXTURE_CAPACITY 128
#define ASSET_SPRITE_CAPACITY 512
#define ASSET_FRAMES_CAPACITY 512
#define ASSET_TILEMAP_CAPACITY 128

typedef struct
{
    string  name;
    string  path;
    Texture texture;
} TextureAsset;

typedef struct
{
    string name;
    string path;
    Sprite sprite;
} SpriteAsset;

typedef struct
{
    string name;
    string path;
    Frames frames;
} FramesAsset;

typedef struct
{
    string    name;
    string    path;
    TileMap   platform_map;
    ObjectMap object_map;
} MapAsset;

typedef struct
{
    u64          texture_count;
    TextureAsset textures[ASSET_TEXTURE_CAPACITY];

    u64         sprite_count;
    SpriteAsset sprites[ASSET_SPRITE_CAPACITY];

    u64         frames_count;
    FramesAsset frames_list[ASSET_FRAMES_CAPACITY];

    u64      map_count;
    MapAsset maps[ASSET_TILEMAP_CAPACITY];
} Assets;

extern Assets assets;

Texture* asset_get_texture_by_name(char* name);
Texture* asset_get_texture_by_id(u32 id);
u32      asset_find_or_add_texture(char* texture_name, SDL_Renderer* renderer, char* texture_path);

Sprite* asset_get_sprite_by_id(u32 id);
u32     asset_find_or_add_sprite(i32 x, i32 y, i32 width, i32 height, i32 texture_index);

Frames* asset_get_frames_by_id(u32 id);

void asset_load_from_conf(SDL_Renderer* renderer, char* filepath);
void assets_clean(void);
