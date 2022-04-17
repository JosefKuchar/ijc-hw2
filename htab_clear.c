#include <stdlib.h>
#include "htab.h"
#include "htab_internal.h"

void htab_clear(htab_t* t) {
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
