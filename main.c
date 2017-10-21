#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "trie.h"
#include "wordcreation.h"
#include "array.h"

#define WARRANT "CorrectorOrtografico creado por Emmanuel Messulam\n"

#define MAX_WORD_LEN 30
#define DEBUG false

bool acceptedchars(unsigned char c) {
    switch (c) {
        case 160:
        case 130:
        case 161:
        case 162:
        case 163:
        case 164://ñ
        case 129://ü
            return true;
        default:
            return c >= 'a' && c <= 'z';
    }
}

/**
 * windows-1252 to ASCII
 */
unsigned char convert(unsigned char c) {
    switch (c) {
        case 225:
            return 160;
        case 233:
            return 130;
        case 237:
            return 161;
        case 243:
            return 162;
        case 250:
            return 163;
        case 241:
            return 164;//ñ
        case 252:
            return 129;//ü

        default:
            return c;
    }
}

/**
 * ASCII to windows-1252
 */
unsigned char deconvert(unsigned char c) {
    switch (c) {
        case 160:
            return 225;
        case 130:
            return 233;
        case 161:
            return 237;
        case 162:
            return 243;
        case 163:
            return 250;
        case 164:
            return 241;//ñ
        case 129:
            return 252;//ü

        default:
            return c;
    }
}

struct Trie* read_dictionary(char *dic) {
    FILE *fp = fopen(dic, "r");
    if (fp == NULL) return NULL;

    int data;
    unsigned char *line = malloc(MAX_WORD_LEN+1);
    unsigned int len = 0;
    bool ignore = false;
    struct Trie* trie = init_trie();

    while ((data = fgetc(fp)) != EOF) {
        unsigned char c = convert((unsigned char) data);
        if(c != '\n' && c != '\0' && c != '\r') {
            if(ignore) continue;
            if(!acceptedchars(c)) {
                ignore = true;
                continue;
            }
            line[len] = c;
            len++;
        } else if (!ignore){
            line[len] = '\0';
            add(trie, line);
            len = 0;
        } else {
            ignore = false;
        }
    }

    if (!ignore){
        line[len] = '\0';
        add(trie, line);
    }

    fclose(fp);
    return trie;
}

struct Array* read_file(char *file) {
    FILE *fp = fopen(file, "r");
    if (fp == NULL) return NULL;

    struct Array** lines = NULL;
    unsigned int lineslen = 0;

    int data;
    unsigned char *line = malloc(MAX_WORD_LEN+1);
    unsigned int len = 0;
    bool ignore = false;

    while ((data = fgetc(fp)) != EOF) {
        unsigned char c = convert((unsigned char) data);
        if(c != '\n' && c != '\0' && c != '\r' && c != ' ' && c != '.' && c != ',' && c != ';') {
            if(ignore) continue;
            if(!acceptedchars(c)) {
                ignore = true;
                continue;
            }
            line[len] = c;
            len++;
        } else if (!ignore && len != 0){
            line[len] = '\0';
            if(lineslen%25 == 0) lines = realloc(lines, (lineslen+25)*sizeof(char*));
            lines[lineslen++] = init_array(line, len);

            line = malloc(MAX_WORD_LEN+1);
            len = 0;
        } else {
            ignore = false;
        }
    }

    if(!ignore) {
        line[len] = '\0';
        lines = realloc(lines, (lineslen + 1) * sizeof(char *));
        lines[lineslen++] = init_array(line, len);
    }

    fclose(fp);

    struct Array *r = malloc(sizeof(struct Array));
    r->data = lines;
    r->length = lineslen;

    return r;
}


void printcorrect(FILE *f, struct Trie* trie, struct Array* words, bool alreadyChecked) {
    unsigned char** array = words->data;
    for(int i = 0; i < words->length; i++) {
        if (alreadyChecked || check(trie, array[i])) {
            if(f != NULL) fprintf(f, "%s\n", array[i]);
            else printf("%s\n", array[i]);
        }
    }
}

int main(int argc, char* argv[]) {
    printf(WARRANT);

    char *dicfile, *outfile = NULL, *checkfile;

    if(DEBUG) {
        #ifdef _WIN32
            dicfile = "..\\data\\es-ES.dic";
            checkfile = "..\\data\\texto.txt";
            outfile = "..\\data\\textoCorreccion.txt";
        #else
            dicfile = "../data/es-ES.dic";
            checkfile = "../data/texto.txt";
            outfile = "../data/textoCorreccion.txt";
        #endif
    } else {
        if(argc < 2 || argc > 4) {
            printf("La sintaxis correcta es:\n\tCorrectorOrtografico <entrada> [salida] [diccionario]\n");
            return 0;
        }

        checkfile = argv[1];
        if(argc >= 3) outfile = argv[2];
        if(argc >= 4) dicfile = argv[3];
        #ifdef _WIN32
            else dicfile = "..\\data\\es-ES.dic";
        #else
            else dicfile = "../data/es-ES.dic";
        #endif
    }

    unsigned char *string = malloc(400);
    printf("Cargando...");
    struct Trie* trie = read_dictionary(dicfile);
    FILE *fout = fopen(outfile, "w");
    if((trie == NULL || fout == NULL) && !DEBUG)  {
        printf("Fallo!");
        return 0;
    }

    struct Array* lines = read_file(checkfile);
    struct Array** linesArray = lines->data;

    printf("Terminado\n");

    for(int i = 0; i < lines->length; i++) {
        unsigned char* line = linesArray[i]->data;
        unsigned int len = linesArray[i]->length;
        if(!check(trie, line)) {
            if(fout != NULL) {
                fprintf(fout, "'");
                for(int j = 0; line[j] != '\0'; j++) fputc(deconvert(line[j]), fout);
                fprintf(fout, "':\n");
            } else printf("'%s':\n", line);

            printcorrect(fout, trie, first(line, len), false);
            printcorrect(fout, trie, second(line, len), false);
            printcorrect(fout, trie, third(line, len), false);
            printcorrect(fout, trie, fourth(line, len), false);
            printcorrect(fout, trie, fifth(trie, line, len), true);
        }
    }

    if(fout != NULL) fclose(fout);
}
