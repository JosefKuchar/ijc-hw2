// htab_erase.c
// Řešení IJC-DU2, příklad 2), 18.4.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include <stdlib.h>
#include <string.h>
#include "htab.h"
#include "htab_internal.h"

bool htab_erase(htab_t* t, htab_key_t key) {
    if (t == NULL || key == NULL) {
        return false;
    }

    // Find item bucket
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item* item = t->arr_ptr[index];
    struct htab_item* prev = NULL;

    // Find item
    while (item != NULL) {
        // Found the item
        if (strcmp(item->pair.key, key) == 0) {
            // If item is first then update head
            if (prev == NULL) {
                t->arr_ptr[index] = item->next;
            } else {
                prev->next = item->next;
            }

            // Free item
            free((char*)item->pair.key);
            free(item);

            // Update size
            t->size--;

            return true;
        }
        // Update pointers
        prev = item;
        item = item->next;
    }

    // Update hash table size
    if (htab_size(t) / (double)htab_bucket_count(t) < AVG_LEN_MIN) {
        htab_resize(t, htab_bucket_count(t) / 2);
    }

    // Item not found
    return false;
}
