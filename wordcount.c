// wordcount.c
// Řešení IJC-DU2, příklad 2), 22.3.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

// Hodnoty byly zvoleny na základě vyzkoušení rozsahu pomocí vlastního scriptu.
// Tyto hodnoty jdou změnit při překladu (-DHTAB_SIZE=xxx ...).
// Velikost HTAB_SIZE tolik neovlivňuje rychlost, důležité je aby se jednalo o
// prvočíslo. Zvolená hodnota vychází z počtu anglických slov v běžné knize.
// Hodnota AVG_LEN_MAX byla zjištěna pomocí scriptu při HTAB_SIZE = 30011,
// na sadě ze zadání "seq 1000000 2000000|shuf".
// V programu není použito htab_erase, tudíž hodnota AVG_LEN_MIN byla zjištěna
// odhadem, důležité je, aby AVG_LEN_MIN * 2 < AVG_LEN_MAX, aby nevznikla oscilace
// při opětovném přidávání a odebírání prvků.

#ifndef HTAB_SIZE
#define HTAB_SIZE 30011
#endif  // HTAB_SIZE

#ifndef AVG_LEN_MIN
#define AVG_LEN_MIN 0.5
#endif  // AVG_LEN_MIN

#ifndef AVG_LEN_MAX
#define AVG_LEN_MAX 1.4
#endif  // AVG_LEN_MAX

#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "io.h"

#define MAX_WORD_LENGTH 128  // 127 + \0

// Custom hashing function
#ifdef HASHTEST
// http://www.cse.yorku.ca/~oz/hash.html - varianta djb2):
size_t htab_hash_function(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
#endif

void print_pair(htab_pair_t* data) {
    printf("%s\t%d\n", data->key, data->value);
}

int main() {
    // Initialize hash table
    htab_t* t = htab_init(HTAB_SIZE);
    if (t == NULL) {
        fprintf(stderr, "Couldn't initialize hash table\n");
        return EXIT_FAILURE;
    }

    // Read words from stdin
    int length = 0;
    while (length != EOF) {
        char key[MAX_WORD_LENGTH] = {0};
        // Read one word
        length = read_word(key, MAX_WORD_LENGTH, stdin);
        if (length == EOF) {
            break;
        }
        // Insert word into hash table
        htab_pair_t* pair = htab_lookup_add(t, key);
        if (pair == NULL) {
            fprintf(stderr, "Couldn't insert word into hash table\n");
            htab_free(t);
            return EXIT_FAILURE;
        }
        pair->value++;
    }

    // Print all items
    htab_for_each(t, print_pair);

    // Free hash table
    htab_free(t);

    return EXIT_SUCCESS;
}
