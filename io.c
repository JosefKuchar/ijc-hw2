// io.c
// Řešení IJC-DU2, příklad 2), 18.4.2022
// Autor: Josef Kuchař, FIT
// Přeloženo: gcc 9.3.0

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

int read_word(char* s, int max, FILE* f) {
    static bool too_long_found = false;
    bool overflow = true;
    int c = 0;  // Current character
    int i = 0;  // Current position in string

    // Skip all whitespaces before word
    while (isspace(c = fgetc(f)) && c != EOF)
        ;

    // Check if stream didn't reach EOF
    if (c == EOF) {
        return EOF;
    }

    // Write first character
    s[0] = c;

    // Read word
    for (i = 1; i < max; i++) {
        // Read next character
        c = fgetc(f);
        // Check if word ended
        if (c == EOF || isspace(c)) {
            overflow = false;
            break;
        }
        // Write character to our buffer
        s[i] = c;
    }
    // Write null terminator
    s[i] = '\0';

    // Check if word is too long
    if (!too_long_found && overflow) {
        fprintf(stderr, "Word too long\n");
        too_long_found = true;
    }

    // Skip rest
    if (overflow) {
        while (!isspace(c = fgetc(f)) && c != EOF)
            ;
    }

    return i;
}
