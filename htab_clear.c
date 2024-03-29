// htab_clear.c
// Řešení IJC-DU2, příklad 2), 18.4.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include "htab.h"
#include "htab_internal.h"

void htab_clear(htab_t* t) {
    if (t == NULL) {
        return;
    }

    // Iterate over all buckets
    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item* item = t->arr_ptr[i];
        // Item exists
        while (item != NULL) {
            struct htab_item* next = item->next;

            // Free the item
            free((char*)item->pair.key);
            free(item);

            // Update pointer
            item = next;
        }
        // Clear bucket pointer
        t->arr_ptr[i] = NULL;
    }
    // Clear size
    t->size = 0;
}
