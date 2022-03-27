#include "htab.h"
#include "htab_internal.h"

htab_pair_t* htab_find(htab_t* t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item* item = t->arr_ptr[index];
    while (item != NULL) {
        if (item->key == key) {
            return (htab_pair_t*)item;
        }
        item = item->next;
    }
    return NULL;
}
