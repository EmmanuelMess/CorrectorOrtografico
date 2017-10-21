//
// Created by emmanuel
//

#include <string.h>
#include <malloc.h>
#include "wordcreation.h"
#include "trie.h"

#define MAX_WORD_LEN 30

struct Array* first(unsigned char *word, unsigned int len) {
    len++;//because '\0'
    unsigned char **list = malloc((len - 2) * sizeof(char *));
    for (int i = 0; word[i + 1] != '\0'; i++) {
        unsigned char *fabrication = malloc(len * sizeof(char));
        memcpy(fabrication, word, len);
        fabrication[i] = word[i + 1];
        fabrication[i + 1] = word[i];
        list[i] = fabrication;
    }

    return init_array(list, len - 2);
}

struct Array* second(unsigned char *word, unsigned int len) {
    len++;
    unsigned char **list = malloc((len - 2) * 26 * sizeof(char *));
    for (unsigned int i = 1; word[i] != '\0'; i++) {
        for (unsigned char j = 'a'; j <= 'z'; j++) {
            unsigned char *fabrication = malloc(len * sizeof(char));
            memcpy(fabrication, word, i);
            fabrication[i] = j;
            memcpy(fabrication + i + 1, word + i, len - i);
            list[(i - 1) * 26 + (j - 'a')] = fabrication;
        }
    }

    return init_array(list, (len - 2) * 26);
}

struct Array* third(unsigned char *word, unsigned int len) {
    len++;//because '\0'
    unsigned char **list = malloc((len - 1) * sizeof(char*));
    for (unsigned int i = 0; word[i] != '\0'; i++) {
        unsigned char* fabrication = malloc(len*sizeof(char));
        memcpy(fabrication, word, i);
        memcpy(fabrication+i, word+i+1, len-i-1);
        list[i] = fabrication;
    }

    return init_array(list, len-1);
}

struct Array* fourth(unsigned char *word, unsigned int len) {
    len++;//because '\0'
    unsigned char **list = malloc((len - 1) * 26 * sizeof(char*));
    for (int i = 0; word[i] != '\0'; i++) {
        for (unsigned char j = 'a'; j <= 'z'; j++) {
            unsigned char *fabrication = malloc(len * sizeof(char));
            memcpy(fabrication, word, len);
            fabrication[i] = j;
            list[i*26+(j-'a')] = fabrication;
        }
    }

    return init_array(list, (len-1)*26);
}

struct Array *fifth(struct Trie *trie, unsigned char *word, unsigned int len) {
    len++;
    unsigned char **list = malloc((len - 2) * 2 * sizeof(char *));
    unsigned int outLen = 0;
    for (unsigned int i = 1; word[i] != '\0'; i++) {
        unsigned char *fabrication1 = malloc((i+1) * sizeof(char));
        unsigned char *fabrication2 = malloc((len-i) * sizeof(char));
        memcpy(fabrication1, word, i);
        fabrication1[i] = '\0';
        memcpy(fabrication2, word + i, len - i);
        if(check(trie, fabrication1) && check(trie, fabrication2)) {
            list[outLen++] = fabrication1;
            list[outLen++] = fabrication2;
        } else {
            free(fabrication1);
            free(fabrication2);
        }
    }

    return init_array(list, outLen);
}