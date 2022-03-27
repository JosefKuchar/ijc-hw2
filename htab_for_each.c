#include "htab.h"
#include "htab_internal.h"

void htab_for_each(const htab_t* t, void (*f)(htab_pair_t* data)) {
    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item* item = t->arr_ptr[i];
        while (item != NULL) {
            struct htab_item* next = item->next;
            f((htab_pair_t*)item);
            item = next;
        }
        t->arr_ptr[i] = NULL;
    }
}
