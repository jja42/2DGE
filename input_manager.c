#include "input_manager.h"

Input* init_input(){
    Input* input = malloc(sizeof(Input));
    //Handle Malloc Error
    if(input == NULL){
         printf("Failed to allocate Input Manager.\n");
         return NULL;
    }
    input->inputJSON = read_json_into_objects("assets/config/input.json");
    bind_inputs(input);
    return input;
}

void bind_inputs(Input* input){
    list_t* buttons = json_list_get(input->inputJSON,"buttons");
    
    input->input_bindings[ACTION_JUMP] = scancode_from_string(json_obj_get(buttons,"jump")->value.s);

    input->input_bindings[ACTION_SHOOT] = scancode_from_string(json_obj_get(buttons,"shoot")->value.s);

    input->input_bindings[ACTION_MOVE_UP] = scancode_from_string(json_obj_get(buttons,"move_up")->value.s);
    
    input->input_bindings[ACTION_MOVE_DOWN] = scancode_from_string(json_obj_get(buttons,"move_down")->value.s);

    input->input_bindings[ACTION_MOVE_LEFT] = scancode_from_string(json_obj_get(buttons,"move_left")->value.s);

    input->input_bindings[ACTION_MOVE_RIGHT] = scancode_from_string(json_obj_get(buttons,"move_right")->value.s);
}

SDL_Scancode scancode_from_string(const char* s) {
    SDL_Keycode keycode = SDL_GetKeyFromName(s);
    if (keycode == SDLK_UNKNOWN) {
        return SDL_SCANCODE_UNKNOWN;
    }
    return SDL_GetScancodeFromKey(keycode);
}

void free_input(Input* input)
{
    for(int i = 0; i<input->inputJSON->capacity; i++){
        if(input->inputJSON->data[i] != NULL){
            free_json(input->inputJSON->data[i]);
        }
    }
    free_list(input->inputJSON); 
    free(input);
}
