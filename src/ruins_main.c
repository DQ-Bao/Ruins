#include "SDL2/SDL_error.h"
#include "ruins_assets.h"
#include "ruins_base.h"
#include "ruins_game.h"
#include "ruins_input.h"
#include "ruins_input_codes.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static b8 app_init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        rerror("SDL Error: %s", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
    {
        rerror("SDL Error: %s", IMG_GetError());
        return false;
    }
    if (TTF_Init() != 0)
    {
        rerror("SDL Error: %s", TTF_GetError());
        return false;
    }
    return true;
}

static void app_capture_events(Game* game)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            game->running = false;
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            input_update_key(&game->input_state, system_key_code(event.key.keysym.scancode),
                             event.key.state == SDL_PRESSED);
        }
        break;
        case SDL_MOUSEMOTION:
        {
            input_update_mouse_move(&game->input_state, event.motion.x, event.motion.y);
        }
        break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            input_update_mouse_button(&game->input_state, system_mouse_code(event.button.button),
                                      event.button.state == SDL_PRESSED);
        }
        break;
        case SDL_MOUSEWHEEL:
        {
            input_update_mouse_wheel(&game->input_state, event.wheel.y);
        }
        break;
        default:
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    if (!app_init())
    {
        rerror("App initialization failed");
        return 0;
    }
    SDL_Window* window = SDL_CreateWindow("Ruins", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        rerror("Window couldn't be created! SDL Error: %s", SDL_GetError());
        return 0;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        rerror("Renderer couldn't be created! SDL_ERROR: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        return 0;
    }

    f32 delta_time = 1.0f / (f32)GAME_FPS;

    asset_load_from_conf(renderer, "assets.conf");

    Game* game     = (Game*)malloc(sizeof(Game));
    game->window   = window;
    game->renderer = renderer;
    game->running  = true;

    game_startup(game);

    while (game->running)
    {
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
        SDL_RenderClear(game->renderer);

        app_capture_events(game);

        game_update_and_render(game, delta_time);
        input_prep_next_frame(&game->input_state);

        SDL_RenderPresent(game->renderer);

        SDL_Delay(delta_time * 1000);
    }
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    free(game);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    return 0;
}
