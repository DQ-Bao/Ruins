#include "render.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_render.h"
#include "app.h"
#include <stdio.h>

void render_texture(Texture* texture, i32 x, i32 y, RenderTransform* transform)
{
    f64       rotation_angle  = !transform ? 0.0 : transform->rotation_angle;
    SDL_Point rotation_center = { 0 };
    rotation_center           = !transform ? rotation_center : transform->rotation_center;
    u32              scale    = !transform ? 1 : transform->scale;
    SDL_RendererFlip flip     = !transform ? SDL_FLIP_NONE : transform->flip;

    SDL_Rect dest = { x, y, texture->width * scale, texture->height * scale };
    SDL_RenderCopyEx(app.renderer, texture->texture, NULL, &dest, rotation_angle, &rotation_center, flip);
}

void render_texture_repeat(Texture* texture, i32 x, i32 y, i32 count_x, i32 count_y, RenderTransform* transform)
{
    f64       rotation_angle  = !transform ? 0.0 : transform->rotation_angle;
    SDL_Point rotation_center = { 0 };
    rotation_center           = !transform ? rotation_center : transform->rotation_center;
    u32              scale    = !transform ? 1 : transform->scale;
    SDL_RendererFlip flip     = !transform ? SDL_FLIP_NONE : transform->flip;

    SDL_Rect dest = { x, y, texture->width * scale, texture->height * scale };
    for (i32 i = 0; i < count_y; i++)
    {
        for (i32 j = 0; j < count_x; j++)
        {
            SDL_RenderCopyEx(app.renderer, texture->texture, NULL, &dest, rotation_angle, &rotation_center, flip);
            dest.x += texture->width;
        }
        dest.y += texture->height;
    }
}

void render_sprite(Sprite* sprite, i32 x, i32 y, RenderTransform* transform)
{
    if (!sprite || !sprite->sheet)
    {
        printf("Sprite not found!\n");
        return;
    }

    f64       rotation_angle  = !transform ? 0.0 : transform->rotation_angle;
    SDL_Point rotation_center = { 0 };
    rotation_center           = !transform ? rotation_center : transform->rotation_center;
    u32              scale    = !transform ? 1 : transform->scale;
    SDL_RendererFlip flip     = !transform ? SDL_FLIP_NONE : transform->flip;

    SDL_Rect src  = { sprite->x, sprite->y, sprite->width, sprite->height };
    SDL_Rect dest = { x, y, sprite->width * scale, sprite->height * scale };
    SDL_RenderCopyEx(app.renderer, sprite->sheet, &src, &dest, rotation_angle, &rotation_center, flip);
}

void render_sprite_repeat(Sprite* sprite, i32 x, i32 y, i32 count_x, i32 count_y, RenderTransform* transform)
{
    if (!sprite || !sprite->sheet) { return; }

    f64       rotation_angle  = !transform ? 0.0 : transform->rotation_angle;
    SDL_Point rotation_center = { 0 };
    rotation_center           = !transform ? rotation_center : transform->rotation_center;
    u32              scale    = !transform ? 1 : transform->scale;
    SDL_RendererFlip flip     = !transform ? SDL_FLIP_NONE : transform->flip;

    SDL_Rect src  = { sprite->x, sprite->y, sprite->width, sprite->height };
    SDL_Rect dest = { x, y, sprite->width * scale, sprite->height * scale };
    for (i32 i = 0; i < count_y; i++)
    {
        for (i32 j = 0; j < count_x; j++)
        {
            SDL_RenderCopyEx(app.renderer, sprite->sheet, &src, &dest, rotation_angle, &rotation_center, flip);
            dest.x += sprite->width;
        }
        dest.y += sprite->height;
    }
}

Texture create_texture(char* filepath, b8 blend)
{
    SDL_Surface* surface = IMG_Load(filepath);
    Texture      texture = { 0 };
    if (!surface)
    {
        printf("Couldn't load texture: %s\n", filepath);
        return texture;
    }
    texture.texture = SDL_CreateTextureFromSurface(app.renderer, surface);
    texture.width   = surface->w;
    texture.height  = surface->h;
    if (blend) { SDL_SetTextureBlendMode(texture.texture, SDL_BLENDMODE_BLEND); }
    SDL_FreeSurface(surface);
    return texture;
}
