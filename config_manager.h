#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include "list.h"
#include "json_parser.h"

typedef struct Config{
list_t* configuration;
char* gameName;
} Config;

//initialize our config struct
Config* init_config();

//get data from our config json
list_t* load_config();

//return name from config
char* get_name_from_config(Config* config);

void free_config(Config* config);

#endif