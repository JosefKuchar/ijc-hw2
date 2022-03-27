#include <stdlib.h>
#include "htab.h"
#include "htab_internal.h"

void htab_clear(htab_t* t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item* item = t->arr_ptr[i];
        while (item != NULL) {
            struct htab_item* next = item->next;
            free((char*)item->key);
            free(item);
            item = next;
        }
        t->arr_ptr[i] = NULL;
    }
    t->size = 0;
}
