#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include "list.h"
#include "json_parser.h"

typedef struct Config{
list_t* configJSON;
char* gameName;
} Config;

//initialize Config from JSON
Config* init_config();

//return name from config
char* get_name_from_config(Config* config);

//frees list, json and gameName
void free_config(Config* config);

#endif