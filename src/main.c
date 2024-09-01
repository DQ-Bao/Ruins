#include "app.h"
#include "base.h"
#include "game.h"
#include "input.h"
#include "input_codes.h"
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

App app = { 0 };

static b8 app_init(App* app)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
    {
        printf("SDL image could not initialize! SDL_ERROR: %s\n", IMG_GetError());
        return false;
    }
    if (TTF_Init() != 0)
    {
        printf("SDL ttf could not initialize! SDL_ERROR: %s\n", TTF_GetError());
        return false;
    }
    app->window = SDL_CreateWindow("Ruins", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, app->window_width,
                                   app->window_height, SDL_WINDOW_SHOWN);
    if (app->window == NULL)
    {
        printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
    if (app->renderer == NULL)
    {
        printf("Renderer could not be created! SDL_ERROR: %s\n", SDL_GetError());
        SDL_DestroyWindow(app->window);
        return false;
    }

    app->running = true;
    return true;
}

static void app_on_event(App* app, InputState* input)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            app->running = false;
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            process_key(input, system_key_code(event.key.keysym.scancode), event.key.state == SDL_PRESSED);
        }
        break;
        case SDL_MOUSEMOTION:
        {
            process_mouse_move(input, event.motion.x, event.motion.y);
        }
        break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            process_mouse_button(input, system_mouse_code(event.button.button), event.button.state == SDL_PRESSED);
        }
        break;
        case SDL_MOUSEWHEEL:
        {
            process_mouse_wheel(input, event.wheel.y);
        }
        break;
        default:
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    app.window_width  = 1280;
    app.window_height = 720;
    if (!app_init(&app))
    {
        printf("App initialization failed!\n");
        return 0;
    }
    app.frames_per_second = 60;
    f32 seconds_per_frame = 1.0f / (f32)app.frames_per_second;

    GameState game = { 0 };
    game_startup(&game);

    InputState input = { 0 };

    while (app.running)
    {
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
        SDL_RenderClear(app.renderer);

        app_on_event(&app, &input);

        game_update_and_render(&game, &input);
        input_update(&input);

        SDL_RenderPresent(app.renderer);

        SDL_Delay(seconds_per_frame * 1000);
    }
    game_shutdown(&game);
    for (i32 i = 0; i < 32; i++)
    {
        TTF_CloseFont(app.fonts[i]);
    }
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    return 0;
}
