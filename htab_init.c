// htab_init.c
// Řešení IJC-DU2, příklad 2), 18.4.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include "htab.h"
#include "htab_internal.h"

htab_t* htab_init(size_t n) {
    // Allocate memory for the table
    htab_t* t = malloc(sizeof(htab_t));
    if (t == NULL) {
        return NULL;
    }

    // Allocate memory for the array
    t->arr_ptr = malloc(n * sizeof(struct htab_item*));
    if (t->arr_ptr == NULL) {
        free(t);
        return NULL;
    }

    // Initialize everything
    for (size_t i = 0; i < n; i++) {
        t->arr_ptr[i] = NULL;
    }
    t->arr_size = n;
    t->size = 0;

    return t;
}
