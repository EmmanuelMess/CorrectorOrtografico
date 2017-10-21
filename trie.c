//
// Created by emmanuel on 10/10/2017.
//

#include <stdlib.h>
#include "trie.h"
#include "map.h"

struct Trie* init_trie() {
    struct Trie* trie = calloc(1, sizeof(struct Trie));
    trie->map = init_map();
    return trie;
}

static unsigned char reassign(unsigned char c) {
    switch (c) {
        case 164:
            return 26;
        case 160:
            return 27;
        case 130:
            return 28;
        case 161:
            return 29;
        case 162:
            return 30;
        case 163:
            return 31;
        case 129:
            return 32;
        case ' ':
            return 33;
        default:
            return c - 'a';
    }
}

static bool isterminator(char c) {
    return c == '\n' || c == '\0' || c == '\r';
}

struct Trie* getchild(struct Trie* trie, unsigned char pos) {
    return get(trie->map, reassign(pos));
}

void add(struct Trie* trie, unsigned char* word) {
    if (isterminator(word[0])) {
        trie->isEnd = true;
    } else {
        struct Trie *child = getchild(trie, word[0]);

        if (child == NULL) {
            put(trie->map, reassign(word[0]), init_trie());
            child = getchild(trie, word[0]);
        }

        add(child, word + 1);
    }
}

bool check(struct Trie* trie, unsigned char* word) {
    if(isterminator(word[0])) {
        return trie->isEnd;
    } else {
        struct Trie *next = getchild(trie, word[0]);

        if(next == NULL) return false;
        else return check(next, word+1);
    }
}