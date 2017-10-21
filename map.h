//
// Created by emmanuel on 9/10/2017.
//

#ifndef CORRECTORORTOGRAFICO_MAP_H
#define CORRECTORORTOGRAFICO_MAP_H

#include <stdint.h>
#include <stdbool.h>

struct Map {
    void *elements[33];//[a:z]+[á:ú]+ñ+ü+' '
};

struct Map* init_map();
void put(struct Map*, int, void*);
void* get(struct Map*, int);
bool contains(struct Map*, int key);


#endif //CORRECTORORTOGRAFICO_MAP_H
