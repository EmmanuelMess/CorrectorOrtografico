//
// Created by emmanuel on 10/10/2017.
//

#ifndef CORRECTORORTOGRAFICO_TRIE_H
#define CORRECTORORTOGRAFICO_TRIE_H
#include <stdbool.h>

struct Trie {
    struct Map* map;
    bool isEnd;
};

struct Trie* init_trie();
void add(struct Trie*, unsigned char* word);
bool check(struct Trie*, unsigned char* word);

#endif //CORRECTORORTOGRAFICO_TRIE_H
