#ifndef GRAPHICS_MANAGER_H
#define GRAPHICS_MANAGER_H

#include "list.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "asset_manager.h"

typedef enum {
    SPRITE_PLAYER_IDLE,
    SPRITE_PLAYER_RUN,
    SPRITE_PLAYER_PROJECTILE,
    SPRITE_ENEMY,
    SPRITE_ENEMY_PROJECTILE,
    SPRITE_PLATFORM,
    NUM_SPRITES
} SpriteID;

typedef enum {
    IMAGE_BANNER,
    NUM_IMAGES
} ImageID;

typedef enum {
    BACKGROUND_MAIN,
    NUM_BACKGROUNDS
} BackgroundID;

static const NameMap sprite_map[] = {
    { "player_idle", SPRITE_PLAYER_IDLE },
    { "player_run", SPRITE_PLAYER_RUN },
    { "player_projectile", SPRITE_PLAYER_PROJECTILE},
    { "enemy", SPRITE_ENEMY },
    { "enemy_projectile", SPRITE_ENEMY_PROJECTILE},
    { "platform", SPRITE_PLATFORM}
};

static const NameMap image_map[] = {
    { "banner", IMAGE_BANNER},
};

static const NameMap background_map[] = {
    { "main_background", BACKGROUND_MAIN},
};

typedef struct Graphics{
    list_t* graphicsJSON;
    SDL_Texture* sprites[NUM_SPRITES];
    SDL_Texture* images[NUM_IMAGES];
    SDL_Texture* backgrounds[NUM_BACKGROUNDS];
} Graphics;

//initialize graphics from JSON
Graphics* init_graphics(SDL_Renderer* ren);

//load graphics files
void load_graphics(Graphics* graphics, SDL_Renderer* ren);

//define asset load for graphics
void* load_graphics_asset(const char* path, void* ctx);

//free json, list, sprites, images and backgrounds
void free_graphics(Graphics* graphics);

#endif