// htab_internal.h
// Řešení IJC-DU2, příklad 2), 22.3.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#ifndef HTAB_INTERNAL_INCLUDED
#define HTAB_INTERNAL_INCLUDED

#include "htab.h"

// Fallback values
#ifndef AVG_LEN_MIN
#define AVG_LEN_MIN 0.5
#endif  // AVG_LEN_MIN

#ifndef AVG_LEN_MAX
#define AVG_LEN_MAX 2.0
#endif  // AVG_LEN_MAX

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item** arr_ptr;
};

struct htab_item {
    struct htab_pair pair;
    struct htab_item* next;
};

#endif  // HTAB_INTERNAL_INCLUDED
