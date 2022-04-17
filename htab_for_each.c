#include "htab.h"
#include "htab_internal.h"

void htab_for_each(const htab_t* t, void (*f)(htab_pair_t* data)) {
    if (t == NULL || f == NULL) {
        return;
    }

    // Iterate over all buckets
    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item* item = t->arr_ptr[i];
        // Item exists
        while (item != NULL) {
            // Call supplied function
            f(&(item->pair));

            // Update pointer
            item = item->next;
        }
    }
}
