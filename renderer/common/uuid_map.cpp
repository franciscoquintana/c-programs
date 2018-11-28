#include "uuid_map.h"

void init_uuid_map(UuidMap *map) {
    map->size = 0;
}

void insert_uuid_map(UuidMap *map, uuid_t key, Client value) {
    Client *client = get_uuid_value(map, key);
    if(client == NULL) {
        UuidClient uuidclient;
        memcpy(uuidclient.key, key, sizeof(uuid_t));
        uuidclient.value = value;

        //map->map =  (UuidClient *) realloc(map->map, ++map->size * sizeof(UuidClient));
        map->map[map->size - 1] = uuidclient;
    }
    else {
        memcpy(client, &value, sizeof(Client));
    }
}

Client *get_uuid_value(UuidMap *map, uuid_t key) {
    for(int c = 0; c < map->size; c++) {
        if(uuid_compare(map->map[c].key, key) == 0)
          return &map->map[c].value;
    }
    return NULL;
}
