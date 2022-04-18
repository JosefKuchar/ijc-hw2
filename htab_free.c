// htab_free.c
// Řešení IJC-DU2, příklad 2), 22.3.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include "htab.h"
#include "htab_internal.h"

void htab_free(htab_t* t) {
    if (t == NULL) {
        return;
    }

    // Clear the table
    htab_clear(t);

    // Free the array
    free(t->arr_ptr);

    // Free the table
    free(t);
}
