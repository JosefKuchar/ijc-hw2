// htab_find.c
// Řešení IJC-DU2, příklad 2), 18.4.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include <string.h>
#include "htab.h"
#include "htab_internal.h"

htab_pair_t* htab_find(htab_t* t, htab_key_t key) {
    if (t == NULL || key == NULL) {
        return NULL;
    }

    // Find item bucket
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item* item = t->arr_ptr[index];

    // Find item
    while (item != NULL) {
        // Found the item
        if (strcmp(item->pair.key, key) == 0) {
            return &(item->pair);
        }
        // Update pointer
        item = item->next;
    }

    // Item not found
    return NULL;
}
