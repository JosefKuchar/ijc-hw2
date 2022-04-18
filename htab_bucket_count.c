// htab_bucket_count.c
// Řešení IJC-DU2, příklad 2), 22.3.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include "htab.h"
#include "htab_internal.h"

size_t htab_bucket_count(const htab_t* t) {
    if (t == NULL) {
        return 0;
    }

    return t->arr_size;
}
