#include "ruins_render.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include "ruins_assets.h"
#include "ruins_base.h"

Texture texture_load_png(SDL_Renderer* renderer, char* filepath)
{
    Texture texture = { 0 };
    texture.surface = IMG_Load(filepath);
    if (!texture.surface) { return texture; }
    texture.texture = SDL_CreateTextureFromSurface(renderer, texture.surface);
    return texture;
}

void texture_free(Texture* texture)
{
    if (!texture) { return; }
    SDL_DestroyTexture(texture->texture);
    SDL_FreeSurface(texture->surface);
}

void render_tilemap(SDL_Renderer* renderer, TileMap* map)
{
    if (!map || map->tile_size == 0) { return; }
    for (u32 row = 0; row < TILE_COUNT_HEIGHT; row++)
    {
        for (u32 col = 0; col < TILE_COUNT_WIDTH; col++)
        {
            if (map->tiles[row][col] >= 0)
            {
                Sprite*  sprite  = asset_get_sprite_by_id(map->tiles[row][col]);
                Texture* texture = asset_get_texture_by_id(sprite->texture_index);
                SDL_Rect dest    = { 0 };
                dest.x           = col * map->tile_size;
                dest.y           = row * map->tile_size;
                dest.w           = map->tile_size;
                dest.h           = map->tile_size;
                SDL_RenderCopy(renderer, texture->texture, &sprite->src_rect, &dest);
            }
        }
    }
}

void render_sprite(SDL_Renderer* renderer, Sprite* sprite, SDL_Rect dest_rect)
{
    if (!sprite) { return; }
    Texture* texture = asset_get_texture_by_id(sprite->texture_index);
    SDL_RenderCopy(renderer, texture->texture, &sprite->src_rect, &dest_rect);
}

static void anim_frames_update(Frames* frames)
{
    if (!frames) { return; }
    if (frames->frame_cooldown > 0)
    {
        frames->frame_cooldown--;
        return;
    }
    frames->current_frame  = (frames->current_frame + 1) % frames->frame_count;
    frames->frame_cooldown = frames->durations_in_frames[frames->current_frame];
}

void anim_frames_reset(Frames* frames)
{
    frames->current_frame  = 0;
    frames->frame_cooldown = frames->durations_in_frames[frames->current_frame];
}

void render_frames(SDL_Renderer* renderer, Frames* frames, SDL_Rect dest_rect)
{
    if (!frames) { return; }
    anim_frames_update(frames);
    Sprite* sprite = asset_get_sprite_by_id(frames->sprite_indexes[frames->current_frame]);
    render_sprite(renderer, sprite, dest_rect);
}

void render_objmap(SDL_Renderer* renderer, ObjectMap* map)
{
    if (!map || map->obj_count == 0) { return; }
    for (u32 i = 0; i < map->obj_count; i++)
    {
        if (map->has_anim[i])
        {
            Frames* frames = asset_get_frames_by_id(map->indexes[i]);
            render_frames(renderer, frames, map->positions[i]);
        }
        else
        {
            Sprite* sprite = asset_get_sprite_by_id(map->indexes[i]);
            render_sprite(renderer, sprite, map->positions[i]);
        }
    }
}
