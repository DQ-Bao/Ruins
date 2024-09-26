#include "ruins_input.h"
#include "ruins_input_codes.h"
#include <string.h>

void input_prep_next_frame(InputState* state)
{
    memcpy_s(&state->keyboard_previous, sizeof(state->keyboard_previous), &state->keyboard_current,
             sizeof(state->keyboard_current));
    memcpy_s(&state->mouse_previous, sizeof(state->mouse_previous), &state->mouse_current,
             sizeof(state->mouse_current));
    state->mouse_scroll = 0;
}

void input_update_key(InputState* state, KeyCode key, b8 pressed)
{
    if (!state || key == KEY_INVALID) { return; }
    state->keyboard_current.keys[key] = pressed;
}

void input_update_mouse_move(InputState* state, i32 x, i32 y)
{
    if (!state) { return; }
    state->mouse_current.x = x;
    state->mouse_current.y = y;
}

void input_update_mouse_button(InputState* state, MouseButton button, b8 pressed)
{
    if (!state || button == MOUSE_BUTTON_INVALID) { return; }
    state->mouse_current.buttons[button] = pressed;
}

void input_update_mouse_wheel(InputState* state, i32 y)
{
    state->mouse_scroll = y;
}
