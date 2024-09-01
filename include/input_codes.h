#pragma once
#include "base.h"
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>

typedef enum
{
    KEY_UNKNOWN,

    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,

    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,

    KEY_ENTER,
    KEY_ESCAPE,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_SPACE,

    KEY_LCTRL,
    KEY_LSHIFT,
    KEY_LALT,
    KEY_RCTRL,
    KEY_RSHIFT,
    KEY_RALT,

    KEY_MAX,
    KEY_INVALID = KEY_MAX
} KeyCode;

typedef enum
{
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_SIDE_X,
    MOUSE_BUTTON_SIDE_Y,
    MOUSE_BUTTON_MAX,
    MOUSE_BUTTON_INVALID = MOUSE_BUTTON_MAX
} MouseButton;

static inline KeyCode system_key_code(SDL_Scancode code)
{
    switch (code)
    {
    case SDL_SCANCODE_UNKNOWN:
        return KEY_UNKNOWN;
    case SDL_SCANCODE_A:
        return KEY_A;
    case SDL_SCANCODE_B:
        return KEY_B;
    case SDL_SCANCODE_C:
        return KEY_D;
    case SDL_SCANCODE_E:
        return KEY_E;
    case SDL_SCANCODE_F:
        return KEY_F;
    case SDL_SCANCODE_G:
        return KEY_G;
    case SDL_SCANCODE_H:
        return KEY_H;
    case SDL_SCANCODE_I:
        return KEY_I;
    case SDL_SCANCODE_J:
        return KEY_J;
    case SDL_SCANCODE_K:
        return KEY_K;
    case SDL_SCANCODE_L:
        return KEY_L;
    case SDL_SCANCODE_M:
        return KEY_M;
    case SDL_SCANCODE_N:
        return KEY_N;
    case SDL_SCANCODE_O:
        return KEY_O;
    case SDL_SCANCODE_P:
        return KEY_P;
    case SDL_SCANCODE_Q:
        return KEY_Q;
    case SDL_SCANCODE_R:
        return KEY_R;
    case SDL_SCANCODE_S:
        return KEY_S;
    case SDL_SCANCODE_T:
        return KEY_T;
    case SDL_SCANCODE_U:
        return KEY_U;
    case SDL_SCANCODE_V:
        return KEY_V;
    case SDL_SCANCODE_W:
        return KEY_W;
    case SDL_SCANCODE_X:
        return KEY_X;
    case SDL_SCANCODE_Y:
        return KEY_Y;
    case SDL_SCANCODE_Z:
        return KEY_Z;
    case SDL_SCANCODE_1:
        return KEY_1;
    case SDL_SCANCODE_2:
        return KEY_2;
    case SDL_SCANCODE_3:
        return KEY_3;
    case SDL_SCANCODE_4:
        return KEY_4;
    case SDL_SCANCODE_5:
        return KEY_5;
    case SDL_SCANCODE_6:
        return KEY_6;
    case SDL_SCANCODE_7:
        return KEY_7;
    case SDL_SCANCODE_8:
        return KEY_8;
    case SDL_SCANCODE_9:
        return KEY_9;
    case SDL_SCANCODE_0:
        return KEY_0;
    case SDL_SCANCODE_RETURN:
        return KEY_ENTER;
    case SDL_SCANCODE_ESCAPE:
        return KEY_ESCAPE;
    case SDL_SCANCODE_BACKSPACE:
        return KEY_BACKSPACE;
    case SDL_SCANCODE_TAB:
        return KEY_TAB;
    case SDL_SCANCODE_SPACE:
        return KEY_SPACE;
    case SDL_SCANCODE_LCTRL:
        return KEY_LCTRL;
    case SDL_SCANCODE_LSHIFT:
        return KEY_LSHIFT;
    case SDL_SCANCODE_LALT:
        return KEY_LALT;
    case SDL_SCANCODE_RCTRL:
        return KEY_RCTRL;
    case SDL_SCANCODE_RSHIFT:
        return KEY_RSHIFT;
    case SDL_SCANCODE_RALT:
        return KEY_RALT;
    default:
        Assert("Invalid key\n");
    }
    return KEY_INVALID;
}

static inline MouseButton system_mouse_code(u8 sdl_button)
{
    switch (sdl_button)
    {
    case SDL_BUTTON_LEFT:
        return MOUSE_BUTTON_LEFT;
    case SDL_BUTTON_RIGHT:
        return MOUSE_BUTTON_RIGHT;
    case SDL_BUTTON_MIDDLE:
        return MOUSE_BUTTON_MIDDLE;
    case SDL_BUTTON_X1:
        return MOUSE_BUTTON_SIDE_X;
    case SDL_BUTTON_X2:
        return MOUSE_BUTTON_SIDE_Y;
    default:
        Assert("Invalid button\n");
    }
    return MOUSE_BUTTON_INVALID;
}
