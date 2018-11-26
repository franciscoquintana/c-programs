#include "map.h"

void init_map(IntMap *map) {
    map->tree = NULL;
}

int compar_entry_map(const void *l, const void *r) {
    const IntIntMap *lm = (IntIntMap *) l;
    const IntIntMap *lr = (IntIntMap *) r;
    return lm->key - lr-> key;
}

void insert_map(IntMap *map, int key, int value) {
    IntIntMap *intMap = (IntIntMap * ) malloc(sizeof(IntIntMap));
    intMap->key = key;
    intMap->value = value;

    IntIntMap *result = *(IntIntMap **) tsearch(intMap, &map->tree, compar_entry_map);
    if(result != intMap) {
        result->value = value;
        free(intMap);
    }
}

int get_value(IntMap *map, int key) {
    IntIntMap intMap;
    intMap.key = key;

    void *r = tfind(&intMap, &(map->tree), compar_entry_map);

    if(r == NULL)
        return 0;

    IntIntMap result = **(IntIntMap **) r;

    return result.value;
}
