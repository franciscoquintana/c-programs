#ifndef __UUID_MAP_H__
#define __UUID_MAP_H__

#include <search.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>


typedef struct {
    uuid_t key;
    int value;
} UuidIntMap;

typedef struct {
    void *tree;
} UuidMap;

#ifdef __cplusplus
extern "C" {
#endif
    void init_map(UuidMap *map);
    void insert_map(UuidMap *map, uuid_t key, int value);
    int get_value(UuidMap *map, uuid_t key);
#ifdef __cplusplus
}
#endif

#endif

