#include "ruins_assets.h"
#include "SDL2/SDL_render.h"
#include "ruins_base.h"
#include "ruins_containers.h"
#include "ruins_math.h"
#include "ruins_parser.h"
#include "ruins_render.h"
#include "ruins_string.h"
#include "tmx/tmx.h"

Assets assets = { 0 };

Texture* asset_get_texture_by_name(char* name)
{
    for (u64 i = 0; i < assets.texture_count; i++)
    {
        if (string_equals(assets.textures[i].name, string_from_cstr(name))) { return &assets.textures[i].texture; }
    }
    return NULL;
}

Texture* asset_get_texture_by_id(u32 id)
{
    if (id >= assets.texture_count) { return NULL; }
    return &assets.textures[id].texture;
}

u32 asset_find_or_add_texture(char* texture_name, SDL_Renderer* renderer, char* texture_path)
{
    for (u32 i = 0; i < assets.texture_count; i++)
    {
        if (string_equals(assets.textures[i].name, string_from_cstr(texture_name))) { return i; }
    }
    assets.textures[assets.texture_count].name    = string_copy(string_from_cstr(texture_name));
    assets.textures[assets.texture_count].path    = string_copy(string_from_cstr(texture_path));
    assets.textures[assets.texture_count].texture = texture_load_png(renderer, texture_path);
    return assets.texture_count++;
}

Sprite* asset_get_sprite_by_id(u32 id)
{
    if (id >= assets.sprite_count) { return NULL; }
    return &assets.sprites[id].sprite;
}

u32 asset_find_or_add_sprite(i32 x, i32 y, i32 width, i32 height, i32 texture_index)
{
    for (u32 i = 0; i < assets.sprite_count; i++)
    {
        if (assets.sprites[i].sprite.src_rect.x == x && assets.sprites[i].sprite.src_rect.y == y &&
            assets.sprites[i].sprite.src_rect.w == width && assets.sprites[i].sprite.src_rect.h == height &&
            assets.sprites[i].sprite.texture_index == texture_index)
        {
            return i;
        }
    }
    assets.sprites[assets.sprite_count].sprite.src_rect.x    = x;
    assets.sprites[assets.sprite_count].sprite.src_rect.y    = y;
    assets.sprites[assets.sprite_count].sprite.src_rect.w    = width;
    assets.sprites[assets.sprite_count].sprite.src_rect.h    = height;
    assets.sprites[assets.sprite_count].sprite.texture_index = texture_index;
    return assets.sprite_count++;
}

Frames* asset_get_frames_by_id(u32 id)
{
    if (id >= assets.frames_count) { return NULL; }
    return &assets.frames_list[id].frames;
}

static void load_texture(SDL_Renderer* renderer, string name, string path)
{
    TextureAsset asset = { 0 };
    asset.name         = string_copy(name);
    asset.path         = string_copy(path);
    asset.texture      = texture_load_png(renderer, asset.path.data);

    assets.textures[assets.texture_count++] = asset;
}

static void load_map(SDL_Renderer* renderer, string name, string path)
{
    tmx_map* map = tmx_load(path.data);
    if (!map)
    {
        rwarn("Can not load map %s: %s", name.data, path.data);
        return;
    }
    assets.maps[assets.map_count].name                   = string_copy(name);
    assets.maps[assets.map_count].path                   = string_copy(path);
    assets.maps[assets.map_count].platform_map.tile_size = map->tile_width;

    tmx_layer* layer = map->ly_head;
    while (layer)
    {
        if (layer->type == L_LAYER && layer->visible != 0)
        {
            for (u32 row = 0; row < map->height; row++)
            {
                for (u32 col = 0; col < map->width; col++)
                {
                    u32 cell = layer->content.gids[row * map->width + col];
                    u32 gid  = cell & TMX_FLIP_BITS_REMOVAL;

                    tmx_tile* tile = map->tiles[gid];
                    if (tile)
                    {
                        u32 texture_id =
                            asset_find_or_add_texture(tile->tileset->name, renderer, tile->tileset->image->source);
                        u32 sprite_id =
                            asset_find_or_add_sprite(tile->ul_x, tile->ul_y, tile->width, tile->height, texture_id);
                        assets.maps[assets.map_count].platform_map.tiles[row][col] = sprite_id;
                    }
                    else { assets.maps[assets.map_count].platform_map.tiles[row][col] = -1; }
                }
            }
        }
        else if (layer->type == L_OBJGR && layer->visible != 0)
        {
            tmx_object* obj = layer->content.objgr->head;

            u32 obj_cnt = 0;
            while (obj)
            {
                if (obj->obj_type == OT_TILE && obj->visible != 0)
                {
                    u32       gid  = obj->content.gid & TMX_FLIP_BITS_REMOVAL;
                    tmx_tile* tile = map->tiles[gid];
                    if (tile)
                    {
                        u32 texture_id =
                            asset_find_or_add_texture(tile->tileset->name, renderer, tile->tileset->image->source);
                        if (tile->animation_len > 0)
                        {
                            tmx_properties* props = tile->properties;
                            tmx_property*   prop  = tmx_get_property(props, "anim_name");
                            if (prop && prop->type == PT_STRING)
                            {
                                assets.frames_list[assets.frames_count].name =
                                    string_copy(string_from_cstr(prop->value.string));
                                Frames* frames      = &assets.frames_list[assets.frames_count].frames;
                                frames->frame_count = tile->animation_len;
                                for (u32 i = 0; i < tile->animation_len; i++)
                                {
                                    tmx_anim_frame frame      = tile->animation[i];
                                    tmx_tile       anim_tile  = tile->tileset->tiles[frame.tile_id];
                                    frames->sprite_indexes[i] = asset_find_or_add_sprite(
                                        anim_tile.ul_x, anim_tile.ul_y, anim_tile.width, anim_tile.height, texture_id);
                                    frames->durations_in_frames[i] = div_ceil_u32(GAME_FPS * frame.duration, 1000);
                                }
                                frames->current_frame  = 0;
                                frames->frame_cooldown = frames->durations_in_frames[0];
                                u32 anim_id            = assets.frames_count++;

                                assets.maps[assets.map_count].object_map.has_anim[obj_cnt]    = true;
                                assets.maps[assets.map_count].object_map.positions[obj_cnt].x = (i32)obj->x;
                                assets.maps[assets.map_count].object_map.positions[obj_cnt].y =
                                    (i32)(obj->y - obj->height);
                                assets.maps[assets.map_count].object_map.positions[obj_cnt].w = (i32)obj->width;
                                assets.maps[assets.map_count].object_map.positions[obj_cnt].h = (i32)obj->height;
                                assets.maps[assets.map_count].object_map.indexes[obj_cnt]     = anim_id;
                                obj_cnt++;
                                obj = obj->next;
                                continue;
                            }
                        }
                        assets.maps[assets.map_count].object_map.has_anim[obj_cnt]    = false;
                        assets.maps[assets.map_count].object_map.positions[obj_cnt].x = (i32)obj->x;
                        assets.maps[assets.map_count].object_map.positions[obj_cnt].y = (i32)(obj->y - obj->height);
                        assets.maps[assets.map_count].object_map.positions[obj_cnt].w = (i32)obj->width;
                        assets.maps[assets.map_count].object_map.positions[obj_cnt].h = (i32)obj->height;
                        assets.maps[assets.map_count].object_map.indexes[obj_cnt] =
                            asset_find_or_add_sprite(tile->ul_x, tile->ul_y, tile->width, tile->height, texture_id);
                        obj_cnt++;
                    }
                }
                obj = obj->next;
            }
            assets.maps[assets.map_count].object_map.obj_count = obj_cnt;
        }
        layer = layer->next;
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
        else if (string_equals_cstr(config->type, "tilemap")) { load_map(renderer, config->name, config->value); }
        string_free(&config->name);
        string_free(&config->type);
        string_free(&config->value);
    }
    darray_destroy(&configs);
    string_free(&content);
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
