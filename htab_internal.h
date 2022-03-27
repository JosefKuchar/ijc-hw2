#ifndef HTAB_INTERNAL_INCLUDED
#define HTAB_INTERNAL_INCLUDED

#include "htab.h"

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item** arr_ptr;
};

struct htab_item {
    htab_key_t key;
    htab_value_t value;
    struct htab_item* next;
};

#endif  // HTAB_INTERNAL_INCLUDED
