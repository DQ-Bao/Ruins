#include "ruins_render.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_render.h"
#include "ruins_base.h"

Texture texture_load_png(SDL_Renderer* renderer, char* filepath)
{
    Texture texture = { 0 };
    texture.surface = IMG_Load(filepath);
    if (!texture.surface) { return texture; }
    texture.texture = SDL_CreateTextureFromSurface(renderer, texture.surface);
    return texture;
}

void render_texture(Texture* texture, i32 x, i32 y, RenderTransform* transform)
{
    unimplemented("");
}

void render_texture_repeat(Texture* texture, i32 x, i32 y, i32 count_x, i32 count_y, RenderTransform* transform)
{
    unimplemented("");
}

void render_sprite(Sprite* sprite, i32 x, i32 y, RenderTransform* transform)
{
    unimplemented("");
}

void render_sprite_repeat(Sprite* sprite, i32 x, i32 y, i32 count_x, i32 count_y, RenderTransform* transform)
{
    unimplemented("");
}
