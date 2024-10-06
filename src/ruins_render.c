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
                Sprite   sprite  = asset_get_sprite_by_id(map->tiles[row][col]);
                Texture  texture = asset_get_texture_by_id(sprite.texture_index);
                SDL_Rect dest    = { 0 };
                dest.x           = col * map->tile_size;
                dest.y           = row * map->tile_size;
                dest.w           = map->tile_size;
                dest.h           = map->tile_size;
                SDL_RenderCopy(renderer, texture.texture, &sprite.src_rect, &dest);
            }
        }
    }
}
