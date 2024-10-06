#include "ruins_assets.h"
#include "SDL2/SDL_render.h"
#include "ruins_base.h"
#include "ruins_containers.h"
#include "ruins_parser.h"
#include "ruins_render.h"
#include "ruins_string.h"
#include <string.h>

Assets assets = { 0 };

Texture asset_get_texture_by_name(string name)
{
    Texture texture = { 0 };
    for (u64 i = 0; i < assets.texture_count; i++)
    {
        if (string_equals(assets.textures[i].name, name)) { return assets.textures[i].texture; }
    }
    return texture;
}

Texture asset_get_texture_by_id(i32 id)
{
    return assets.textures[id].texture;
}

i32 asset_get_texture_id_by_name(string name)
{
    for (u64 i = 0; i < assets.texture_count; i++)
    {
        if (string_equals(assets.textures[i].name, name)) { return i; }
    }
    return -1;
}

Sprite asset_get_sprite_by_id(i32 id)
{
    return assets.sprites[id].sprite;
}

static void load_texture(SDL_Renderer* renderer, string name, string path)
{
    TextureAsset asset = { 0 };
    asset.name         = string_copy(name);
    asset.path         = string_copy(path);
    asset.texture      = texture_load_png(renderer, asset.path.data);

    assets.textures[assets.texture_count++] = asset;
}

static void load_map(string name, string path)
{
    string conf = file_read_to_string(path.data);

    i32 texture_index = -1;
    while (conf.count > 0)
    {
        string line = string_cut_by_delim(&conf, '\n');
        if (line.count == 0)
        {
            string_free(&line);
            continue;
        }
        string_trim(&line);
        string var = string_cut_by_delim(&line, '=');
        string_trim(&var);
        string_trim(&line);

        if (string_equals_cstr(var, "texture")) { texture_index = asset_get_texture_id_by_name(line); }
        else if (texture_index >= 0 && string_equals_cstr(var, "data"))
        {
            Texture texture = asset_get_texture_by_id(texture_index);

            assets.maps[assets.map_count].name          = name;
            assets.maps[assets.map_count].path          = path;
            assets.maps[assets.map_count].map.tile_size = TILE_SIZE;

            i32 tile_id_set[TILEMAP_MAX_TILES] = { 0 }; // NOTE: 512 is the max number of tiles in a tileset
            memset(tile_id_set, -1, TILEMAP_MAX_TILES * sizeof(i32));
            for (u32 i = 0; line.count > 0; i++)
            {
                i32 tile_id = string_to_i32(string_cut_by_delim(&line, ',')) - 1;
                u64 row     = i / TILE_COUNT_WIDTH;
                u64 col     = i % TILE_COUNT_WIDTH;
                if (tile_id < 0)
                {
                    assets.maps[assets.map_count].map.tiles[row][col] = -1;
                    continue;
                }
                if (tile_id_set[tile_id] == -1)
                {
                    assets.sprites[assets.sprite_count].sprite.texture_index = texture_index;
                    assets.sprites[assets.sprite_count].sprite.src_rect.x =
                        (tile_id % (texture.surface->w / TILE_SIZE)) * TILE_SIZE;
                    assets.sprites[assets.sprite_count].sprite.src_rect.y =
                        (tile_id / (texture.surface->w / TILE_SIZE)) * TILE_SIZE;
                    assets.sprites[assets.sprite_count].sprite.src_rect.w = TILE_SIZE;
                    assets.sprites[assets.sprite_count].sprite.src_rect.h = TILE_SIZE;

                    tile_id_set[tile_id] = assets.sprite_count;
                    assets.sprite_count++;
                }
                assets.maps[assets.map_count].map.tiles[row][col] = tile_id_set[tile_id];
            }
            assets.map_count++;
        }
        string_free(&line);
    }
}

void asset_load_from_conf(SDL_Renderer* renderer, char* filepath)
{
    string content = file_read_to_string(filepath);
    if (content.count <= 0 || !content.data) { rwarn("Can not read from file: %s", filepath); }

    DynamicArray configs = parse_assets_config(content);
    for (u64 i = 0; i < configs.count; i++)
    {
        AssetConfig* config = darray_get(AssetConfig, &configs, i);
        if (string_equals_cstr(config->type, "texture")) { load_texture(renderer, config->name, config->value); }
        else if (string_equals_cstr(config->type, "tilemap")) { load_map(config->name, config->value); }
        string_free(&config->name);
        string_free(&config->type);
        string_free(&config->value);
    }
    darray_destroy(&configs);
}

void assets_clean(void)
{
    for (u64 i = 0; i < assets.texture_count; i++)
    {
        string_free(&assets.textures[i].name);
        string_free(&assets.textures[i].path);
        texture_free(&assets.textures[i].texture);
    }
}
