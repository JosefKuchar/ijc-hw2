// wordcount.c
// Řešení IJC-DU2, příklad 2), 22.3.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "io.h"

#define HTAB_SIZE 4
#define MAX_WORD_LENGTH 128

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
