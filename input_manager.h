#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "list.h"
#include "json_parser.h"
#include <SDL2/SDL.h>

typedef enum {
    ACTION_JUMP,
    ACTION_SHOOT,
    ACTION_MOVE_UP,
    ACTION_MOVE_DOWN,
    ACTION_MOVE_LEFT,
    ACTION_MOVE_RIGHT,
    NUM_ACTIONS
} Action;

typedef struct Input{
list_t* inputJSON;
SDL_Scancode input_bindings[NUM_ACTIONS];
} Input;

//get scancode from parsed json string in input config
SDL_Scancode scancode_from_string(const char* s);

//Initialize Input from JSON
Input* init_input();

//assign bindings from json to scancodes
void bind_inputs(Input* input);

//frees list and json
void free_input(Input* input);

#endif