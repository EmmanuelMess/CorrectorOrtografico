//
// Created by emmanuel on 17/10/2017.
//

#ifndef CORRECTORORTOGRAFICO_ARRAY_H
#define CORRECTORORTOGRAFICO_ARRAY_H
struct Array {
    void* data;
    unsigned int length;
};

struct Array* init_array(void*, unsigned int);
#endif //CORRECTORORTOGRAFICO_ARRAY_H
