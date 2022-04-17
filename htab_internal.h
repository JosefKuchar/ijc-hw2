#ifndef HTAB_INTERNAL_INCLUDED
#define HTAB_INTERNAL_INCLUDED

#include "htab.h"

#define AVG_LEN_MIN 2
#define AVG_LEN_MAX 3

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
