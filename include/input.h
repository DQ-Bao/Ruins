#pragma once
#include "base.h"
#include "input_codes.h"

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

void input_update(InputState* state);
void process_key(InputState* state, KeyCode key, b8 pressed);
void process_mouse_move(InputState* state, i32 x, i32 y);
void process_mouse_button(InputState* state, MouseButton button, b8 pressed);
void process_mouse_wheel(InputState* state, i32 y);
