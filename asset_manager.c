#include "asset_manager.h"
#include <string.h>

void load_asset_table(
    void** asset_table,
    int asset_count,
    const NameMap* map,
    list_t* json,
    AssetLoadFn loader,
    const char* asset_type_name
) {
    for (int i = 0; i < json->capacity; i++) {
        JsonObj* obj = json->data[i];
        if (!obj) continue;

        const char* name = obj->key;
        const char* path = obj->value.s;

        int id = lookup_id(map, asset_count, name);
        if (id < 0) {
            printf("Unknown %s: %s\n", asset_type_name, name);
            continue;
        }

        asset_table[id] = loader(path);
        if (!asset_table[id]) {
            printf("Failed to load %s '%s' (%s)\n",
                asset_type_name, name, path);
        }
    }
}

int lookup_id(const NameMap* map, int count, const char* name) {
    for (int i = 0; i < count; i++)
        if (strcmp(map[i].name, name) == 0)
            return map[i].id;
    return -1;
}

