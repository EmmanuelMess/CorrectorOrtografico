//
// Created by emmanuel on 17/10/2017.
//

#include <malloc.h>
#include "array.h"

struct Array* init_array(void* d, unsigned int l) {
    struct Array *r = malloc(sizeof(struct Array));
    r->data = d;
    r->length = l;
    return r;
}