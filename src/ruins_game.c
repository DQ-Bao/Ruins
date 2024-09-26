#include "ruins_game.h"
#include "SDL2/SDL_render.h"
#include "ruins_asset_defines.h"
#include "ruins_assets.h"
#include "ruins_render.h"
#include <stdio.h>
#include <stdlib.h>

static void render_background(SDL_Renderer* renderer, Background* background)
{
    SDL_RenderCopy(renderer, background->layers[0].texture, NULL, NULL);
    SDL_RenderCopy(renderer, background->layers[1].texture, NULL, NULL);
    SDL_RenderCopy(renderer, background->layers[2].texture, NULL, NULL);
    SDL_RenderCopy(renderer, background->layers[3].texture, NULL, NULL);
    SDL_RenderCopy(renderer, background->layers[4].texture, NULL, NULL);
}

void game_startup(Game* game)
{
    game->background.layers[0] = assets.textures[BACKGROUND_1_TEXTURE_INDEX].texture;
    game->background.layers[1] = assets.textures[BACKGROUND_2_TEXTURE_INDEX].texture;
    game->background.layers[2] = assets.textures[BACKGROUND_3_TEXTURE_INDEX].texture;
    game->background.layers[3] = assets.textures[BACKGROUND_4_TEXTURE_INDEX].texture;
    game->background.layers[4] = assets.textures[BACKGROUND_5_TEXTURE_INDEX].texture;
}

void game_update_and_render(Game* game, f32 delta_time)
{
    render_background(game->renderer, &game->background);
}