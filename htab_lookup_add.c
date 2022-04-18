// htab_lookup_add.c
// Řešení IJC-DU2, příklad 2), 18.4.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htab.h"
#include "htab_internal.h"

htab_pair_t* htab_lookup_add(htab_t* t, htab_key_t key) {
    if (t == NULL || key == NULL) {
        return NULL;
    }

    // Look if pair already exists
    htab_pair_t* pair = htab_find(t, key);

    // Return existing pair if found
    if (pair != NULL) {
        return pair;
    }

    // Create new item
    struct htab_item* item = malloc(sizeof(struct htab_item));
    if (item == NULL) {
        return NULL;
    }

    // Initialize item
    item->next = NULL;
    item->pair.key = malloc(strlen(key) + 1);
    if (item->pair.key == NULL) {
        free(item);
        return NULL;
    }
    strcpy((char*)item->pair.key, key);
    item->pair.value = 0;

    // Add to list
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item* target = t->arr_ptr[index];

    // Add to head
    if (target == NULL) {
        t->arr_ptr[index] = item;
    } else {
        // Add to tail
        while (target->next != NULL) {
            target = target->next;
        }
        target->next = item;
    }

    // Update size
    t->size++;

    // Update hash table size
    if (htab_size(t) / (double)htab_bucket_count(t) > AVG_LEN_MAX) {
        htab_resize(t, htab_bucket_count(t) * 2);
    }

    // Return new item
    return &(item->pair);
}
