#ifndef __UUID_MAP_H__
#define __UUID_MAP_H__

#include <search.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>
#include "../common/common.h"

typedef struct {
    uuid_t key;
    Client value;
} UuidClient;

typedef struct {
    UuidClient map[0x0F];
    int size;
} UuidMap;

#ifdef __cplusplus
extern "C" {
#endif
    void init_uuid_map(UuidMap *map);
    void insert_uuid_map(UuidMap *map, uuid_t key, Client value);
    Client *get_uuid_value(UuidMap *map, uuid_t key);
#ifdef __cplusplus
}
#endif

#endif

