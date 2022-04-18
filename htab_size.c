// htab_size.c
// Řešení IJC-DU2, příklad 2), 18.4.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include "htab.h"
#include "htab_internal.h"

size_t htab_size(const htab_t* t) {
    if (t == NULL) {
        return 0;
    }

    return t->size;
}
