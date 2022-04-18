// htab_hash_function.c
// Řešení IJC-DU2, příklad 2), 18.4.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include <stdint.h>
#include <stdlib.h>

// http://www.cse.yorku.ca/~oz/hash.html - varianta sdbm):
size_t htab_hash_function(const char* str) {
    uint32_t h = 0;  // musí mít 32 bitů
    const unsigned char* p;
    for (p = (const unsigned char*)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}
