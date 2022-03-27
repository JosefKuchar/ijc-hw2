#include <stdlib.h>
#include "htab.h"
#include "htab_internal.h"

void htab_resize(htab_t* t, size_t newn) {
    // Allocate new array
    struct htab_item** new_arr = malloc(newn * sizeof(struct htab_item*));
    if (new_arr == NULL) {
        return;  // Nothing happens
    }

    // Initialize new array
    for (size_t i = 0; i < newn; i++) {
        new_arr[i] = NULL;
    }

    // Rehash old items into new array
    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item* item = t->arr_ptr[i];
        while (item != NULL) {
            struct htab_item* next = item->next;
            size_t index = htab_hash_function(item->key) % newn;
            // new_arr[index]

            item = next;
        }
        t->arr_ptr[i] = NULL;
    }

    // Free old array
    free(t->arr_ptr);

    // Update array pointer and size inside table
    t->arr_ptr = new_arr;
    t->arr_size = newn;
}
