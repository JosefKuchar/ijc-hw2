#include "htab.h"
#include "htab_internal.h"

size_t htab_bucket_count(const htab_t* t) {
    return t->arr_size;
}
