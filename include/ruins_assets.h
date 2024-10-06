#pragma once
#include "ruins_render.h"
#include "ruins_string.h"
#define ASSET_TEXTURE_CAPACITY 128
#define ASSET_SPRITE_CAPACITY 512
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
    string  name;
    string  path;
    TileMap map;
} TileMapAsset;

typedef struct
{
    TextureAsset textures[ASSET_TEXTURE_CAPACITY];
    u64          texture_count;
    SpriteAsset  sprites[ASSET_SPRITE_CAPACITY];
    u64          sprite_count;
    TileMapAsset maps[ASSET_TILEMAP_CAPACITY];
    u64          map_count;
} Assets;

extern Assets assets;

Texture asset_get_texture_by_name(string name);
Texture asset_get_texture_by_id(i32 id);
i32     asset_get_texture_id_by_name(string name);
Sprite  asset_get_sprite_by_id(i32 id);
void    asset_load_from_conf(SDL_Renderer* renderer, char* filepath);
void    assets_clean(void);
