#ifndef UI_ELEM_H
#define UI_ELEM_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game_manager.h"

typedef void (*OnClick)(Game* game);

typedef enum FONT{
ARIAL
} FONT;

typedef enum {
BLUE,
GREEN,
RED,
GOLD
}Color;

typedef struct TextPanel{
    int x_pos;
    int y_pos;
    int width;
    int height;
    char* text;
    SDL_Texture* text_texture;
    SDL_Rect text_rect;
    Color border_color;
} TextPanel;

typedef struct Button{
TextPanel* panel;
OnClick on_click;
} Button;

//Will call game_manager's exit function. 
void exit_button_func(Game* game);

//Will display a popup
void open_info_button_func(Game* game);

//Wil close the popup
void close_info_button_func(Game* game);

//Create a new button and set it up
Button* init_button(TextPanel* t, OnClick click_function);

//Frees Button Data
void free_button(entity_s *ent);

//Creates a new Text Panel
TextPanel* init_text_panel(int x, int y, int w, int h, char* text, FONT font_name, Game* game, Color border_color);

//Renders a Text Panel to the Screen
void render_text_panel(SDL_Renderer* renderer, TextPanel* text_panel);

//Frees Text Panel Data
void free_text_panel(entity_s *ent);
#endif