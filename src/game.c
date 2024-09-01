#include "game.h"
#include "SDL2/SDL_render.h"
#include "app.h"
#include "input.h"
#include "render.h"
#include "rmath.h"
#include <stdlib.h>

static Texture create_background(void)
{
    Texture background_1 = create_texture("assets/background_1.png", false);
    Texture background_2 = create_texture("assets/background_2.png", false);
    Texture background_3 = create_texture("assets/background_3.png", false);
    Texture background_4 = create_texture("assets/background_4.png", false);
    Texture background_5 = create_texture("assets/background_5.png", false);

    Texture background = { 0 };
    background.width   = app.window_width;
    background.height  = app.window_height;
    background.texture = SDL_CreateTexture(app.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
                                           background.width, background.height);

    SDL_SetRenderTarget(app.renderer, background.texture);

    SDL_RenderCopy(app.renderer, background_1.texture, NULL, NULL);
    SDL_RenderCopy(app.renderer, background_2.texture, NULL, NULL);
    SDL_RenderCopy(app.renderer, background_3.texture, NULL, NULL);
    SDL_RenderCopy(app.renderer, background_4.texture, NULL, NULL);
    SDL_RenderCopy(app.renderer, background_5.texture, NULL, NULL);

    SDL_DestroyTexture(background_1.texture);
    SDL_DestroyTexture(background_2.texture);
    SDL_DestroyTexture(background_3.texture);
    SDL_DestroyTexture(background_4.texture);
    SDL_DestroyTexture(background_5.texture);

    SDL_SetRenderTarget(app.renderer, NULL);

    return background;
}

static Sprite* get_next_animation_sprite(Animation* animation)
{
    if (!animation) { return NULL; }

    if (animation->curr_frame >= animation->frames_per_sprite)
    {
        animation->curr_frame = 0;
        animation->curr_sprite++;
        if (animation->curr_sprite >= animation->sprite_count) { animation->curr_sprite = 0; }
    }
    animation->curr_frame++;
    return &animation->sprites[animation->curr_sprite];
}

void game_startup(GameState* game)
{
    game->background      = create_background();
    game->platform_sheet  = create_texture("assets/platforms.png", true);
    game->character_sheet = create_texture("assets/warrior.png", true);

    game->ground.sheet  = game->platform_sheet.texture;
    game->ground.width  = 32;
    game->ground.height = 32 * 3;
    game->ground.x      = game->ground.width;
    game->ground.y      = 0;

    i32 period_seconds               = 1;
    game->char_running.sprite_count  = 8;
    game->char_running.sprites       = (Sprite*)malloc(sizeof(Sprite) * game->char_running.sprite_count);
    game->char_running.curr_sprite   = 0;
    game->char_running.curr_frame    = 0;
    game->char_running.period_frames = period_seconds * app.frames_per_second;
    game->char_running.frames_per_sprite =
        div_ceil_i32(game->char_running.period_frames, game->char_running.sprite_count);
    for (i32 i = 0; i < game->char_running.sprite_count; i++)
    {
        game->char_running.sprites[i].sheet  = game->character_sheet.texture;
        game->char_running.sprites[i].width  = 80;
        game->char_running.sprites[i].height = 64;
        game->char_running.sprites[i].x      = i * game->char_running.sprites[i].width;
        game->char_running.sprites[i].y      = game->char_running.sprites[i].height * 2;
    }
}

void game_update_and_render(GameState* game, InputState* input)
{
    Sprite* curr_sprite = get_next_animation_sprite(&game->char_running);

    render_texture(&game->background, 0, 0, NULL);
    render_sprite_repeat(&game->ground, 0, app.window_height - game->ground.height,
                         div_ceil_i32(app.window_width, game->ground.width), 1, NULL);

    RenderTransform character_transform = { 0 };
    character_transform.scale           = 4;
    character_transform.flip            = SDL_FLIP_HORIZONTAL;
    render_sprite(curr_sprite, 100, app.window_height - game->ground.height - curr_sprite->height * 4,
                  &character_transform);
}

void game_shutdown(GameState* game)
{
    SDL_DestroyTexture(game->background.texture);
    SDL_DestroyTexture(game->platform_sheet.texture);
    SDL_DestroyTexture(game->character_sheet.texture);
    free(game->char_running.sprites);
}
