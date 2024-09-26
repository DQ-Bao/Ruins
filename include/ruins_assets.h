#pragma once
#include "ruins_render.h"
#include "ruins_string.h"
#define ASSET_TEXTURE_CAPACITY 128

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
    TextureAsset textures[ASSET_TEXTURE_CAPACITY];
    u64          texture_count;
} Assets;

extern Assets assets;

Texture asset_get_texture_by_name(string name);
Texture asset_get_texture_by_id(i32 id);
void    asset_load_from_conf(SDL_Renderer* renderer, char* filepath);
