#ifndef __MAP_H__
#define __MAP_H__

#include <search.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    int value;
} IntIntMap;

typedef struct {
    void *tree;
} IntMap;

#ifdef __cplusplus
extern "C" {
#endif
    void init_map(IntMap *map);
    void insert_map(IntMap *map, int key, int value);
    int get_value(IntMap *map, int key);
#ifdef __cplusplus
}
#endif

#endif

