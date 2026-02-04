#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "list.h"
#include "json_parser.h"

typedef void* (*AssetLoadFn)(const char* path);

typedef struct {
    const char* name;
    int id;
} NameMap;

//generic asset loader
void load_asset_table(
    void** asset_table,
    int asset_count,
    const NameMap* map,
    list_t* json,
    AssetLoadFn loader,
    const char* asset_type_name
);

//verifies that asset is in NameMap
int lookup_id(const NameMap* map, int count, const char* name);

#endif