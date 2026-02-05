#include "graphics_manager.h"
#include <assert.h>

Graphics* init_graphics(SDL_Renderer* ren){
    Graphics* graphics = malloc(sizeof(Graphics));
    //Handle Malloc Error
    if(graphics == NULL){
         printf("Failed to allocate Graphics Manager.\n");
         return NULL;
    }
    graphics->graphicsJSON = read_json_into_objects("assets/config/graphics.json");
    load_graphics(graphics, ren);

    return graphics;
}

void load_graphics(Graphics* graphics, SDL_Renderer* ren){
    list_t* sprites = json_list_get(graphics->graphicsJSON,"sprites");

    load_asset_table((void**)graphics->sprites,NUM_SPRITES,sprite_map,sprites,load_graphics_asset,ren,"sprite");

    list_t* images = json_list_get(graphics->graphicsJSON,"images");

    load_asset_table((void**)graphics->images,NUM_IMAGES,image_map,images,load_graphics_asset,ren,"image");

    list_t* backgrounds = json_list_get(graphics->graphicsJSON,"backgrounds");

    load_asset_table((void**)graphics->backgrounds,NUM_BACKGROUNDS,background_map,backgrounds,load_graphics_asset,ren,"background");
}

void* load_graphics_asset(const char* path, void* ctx){

    SDL_Renderer* renderer = (SDL_Renderer*)ctx;

    SDL_Texture* tex = IMG_LoadTexture(renderer, path);
    if (!tex) {
        printf("Failed to load texture %s: %s\n",
               path, IMG_GetError());
    }
    return tex;
}

void free_graphics(Graphics* graphics){
    
    //free sprites
    for(int s = 0; s<NUM_SPRITES; s++){
        if(graphics->sprites[s]){
            SDL_DestroyTexture(graphics->sprites[s]);
            graphics->sprites[s] = NULL;
        }
    }

    //free images
    for(int i = 0; i<NUM_IMAGES; i++){
        if(graphics->images[i]){
            SDL_DestroyTexture(graphics->images[i]);
            graphics->images[i] = NULL;
        }
    }

    //free backgrounds
    for(int b = 0; b<NUM_BACKGROUNDS; b++){
        if(graphics->backgrounds[b]){
            SDL_DestroyTexture(graphics->backgrounds[b]);
            graphics->backgrounds[b] = NULL;
        }
    }

    //free list and json
    for(int j = 0; j<graphics->graphicsJSON->capacity; j++){
        if(graphics->graphicsJSON->data[j] != NULL){
            free_json(graphics->graphicsJSON->data[j]);
        }
    }

    free_list(graphics->graphicsJSON);

    free(graphics);
}