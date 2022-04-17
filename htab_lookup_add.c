#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "htab_internal.h"

htab_pair_t* htab_lookup_add(htab_t* t, htab_key_t key) {
    // Look if pair already exists
    htab_pair_t* pair = htab_find(t, key);

    // Return existing pair if found
    if (pair != NULL) {
        free((char*)key);
        return pair;
    }

    // Create new item
    struct htab_item* item = malloc(sizeof(struct htab_item));
    if (item == NULL) {
        return NULL;
    }

    // Initialize item
    item->next = NULL;
    item->pair.key = key;
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
    if (htab_size(t) / htab_bucket_count(t) > AVG_LEN_MAX) {
        htab_resize(t, htab_bucket_count(t) * 2);
    }

    // Return new item
    return &(item->pair);
}
