#include <stdlib.h>
#include "htab.h"
#include "htab_internal.h"

htab_pair_t* htab_lookup_add(htab_t* t, htab_key_t key) {
    // Look if item already exists
    htab_pair_t* item = htab_find(t, key);

    // Return existing item if found
    if (item != NULL) {
        return item;
    }

    // Create new item
    item = malloc(sizeof(struct htab_item));
    if (item == NULL) {
        return NULL;
    }
    item->key = key;
    item->value = 0;

    // Add to list
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item* target = t->arr_ptr[index];
    while (target != NULL) {
        if (target->next == NULL) {
            target->next = item;
            break;
        }
        target = target->next;
    }

    // Return new item
    return (htab_pair_t*)item;
}
