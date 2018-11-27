#include "uuid_map.h"

void init_map(UuidMap *map) {
    map->tree = NULL;
}

int compar_entry_map(const void *l, const void *r) {
    const UuidIntMap *lm = (UuidIntMap *) l;
    const UuidIntMap *lr = (UuidIntMap *) r;
    return lm->key - lr-> key;
}

void insert_map(UuidMap *map, uuid_t key, int value) {
    UuidIntMap *uuidmap = (UuidIntMap * ) malloc(sizeof(UuidMap));
    memcpy(uuidmap->key, key, sizeof(uuid_t));
    uuidmap->value = value;

    UuidIntMap *result = *(UuidIntMap **) tsearch(uuidmap, &map->tree, compar_entry_map);
    if(result != uuidmap) {
        result->value = value;
        free(uuidmap);
    }
}

int get_value(UuidMap *map, uuid_t key) {
    UuidIntMap uuidmap;
    memcpy(uuidmap.key, key, sizeof(uuid_t));

    void *r = tfind(&uuidmap, &(map->tree), compar_entry_map);

    if(r == NULL)
        return 0;

    UuidIntMap result = **(UuidIntMap **) r;

    return result.value;
}
