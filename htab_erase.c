#include <stdlib.h>
#include "htab.h"
#include "htab_internal.h"

bool htab_erase(htab_t* t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item* item = t->arr_ptr[index];
    struct htab_item* prev = NULL;
    while (item != NULL) {
        if (item->key == key) {
            if (prev == NULL) {
                t->arr_ptr[index] = item->next;
            } else {
                prev->next = item->next;
            }
            free((char*)item->key);
            free(item);
            return true;
        }
        prev = item;
        item = item->next;
    }
    return false;
}
