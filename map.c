//
// Created by emmanuel on 9/10/2017.
//

#include <malloc.h>
#include <stdbool.h>
#include "map.h"

struct Map* init_map() {
    return calloc(1, sizeof(struct Map));
}

void put(struct Map* map, int key, void* value) {
    map->elements[key] = value;
}

bool contains(struct Map* map, int key) {
    return map->elements[key] != NULL;
}

void* get(struct Map* map, int pos) {
    return map->elements[pos];
}