#include "config_manager.h"
#include <string.h>
#include <stdlib.h>

Config* init_config(){
    Config* config = malloc(sizeof(Config));
    //Handle Malloc Error
    if(config == NULL){
         printf("Failed to allocate Config Manager.\n");
         return NULL;
    }
    config->configJSON = read_json_into_objects("assets/config/config.json");
    config->gameName = get_name_from_config(config);
    return config;
}

char* get_name_from_config(Config* config){
    char* game = json_obj_get(config->configJSON,"game_name")->value.s;
    char* author = json_obj_get(config->configJSON,"author_name")->value.s;
    int size = strlen(game) + strlen(author) + 4; //4 = " by "
    char name[size];
    strcat(name,game);
    strcat(name, " by ");
    strcat(name,author);
    char* game_name = strdup(name);
    return game_name;
}

void free_config(Config* config){
    free(config->gameName);
    for(int i = 0; i<config->configJSON->capacity; i++){
        if(config->configJSON->data[i] != NULL){
            free_json(config->configJSON->data[i]);
        }
    }
    free_list(config->configJSON); 
    free(config);
}