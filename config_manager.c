#include "config_manager.h"
#include <string.h>
#include <stdlib.h>

Config* init_config()
{
    Config* config = malloc(sizeof(Config));
    //Handle Malloc Error
    if(config == NULL){
         printf("Failed to allocate Config.\n");
         return NULL;
    }
    config->configuration = load_config();
    config->gameName = get_name_from_config(config);
    return config;
}

list_t* load_config()
{
    list_t* config = read_json_into_objects("assets/config/config.json");
}

char* get_name_from_config(Config* config)
{
    char* game = json_obj_get(config->configuration,"game_name")->value.s;
    char* author = json_obj_get(config->configuration,"author_name")->value.s;
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
    for(int i = 0; i<config->configuration->capacity; i++){
        if(config->configuration->data[i] != NULL){
            free_json(config->configuration->data[i]);
        }
    }
    free_list(config->configuration); 
}