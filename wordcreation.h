//
// Created by emmanuel on 14/10/2017.
//

#ifndef CORRECTORORTOGRAFICO_WORDCREATION_H
#define CORRECTORORTOGRAFICO_WORDCREATION_H

#include "trie.h"
#include <stdbool.h>
#include "array.h"

struct Array* first(unsigned char *, unsigned int);
struct Array* second(unsigned char *, unsigned int);
struct Array* third(unsigned char *, unsigned int);
struct Array* fourth(unsigned char *, unsigned int);
struct Array *fifth(struct Trie *, unsigned char *, unsigned int);
#endif //CORRECTORORTOGRAFICO_WORDCREATION_H
