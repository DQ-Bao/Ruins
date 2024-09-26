#pragma once
#include "ruins_base.h"
#include "ruins_input_codes.h"

typedef struct
{
    b8 keys[KEY_MAX];
} KeyboardState;

typedef struct
{
    i32 x;
    i32 y;
    b8  buttons[MOUSE_BUTTON_MAX];
} MouseState;

typedef struct
{
    KeyboardState keyboard_current;
    KeyboardState keyboard_previous;
    MouseState    mouse_current;
    MouseState    mouse_previous;
    i32           mouse_scroll;
} InputState;

void input_prep_next_frame(InputState* state);
void input_update_key(InputState* state, KeyCode key, b8 pressed);
void input_update_mouse_move(InputState* state, i32 x, i32 y);
void input_update_mouse_button(InputState* state, MouseButton button, b8 pressed);
void input_update_mouse_wheel(InputState* state, i32 y);
