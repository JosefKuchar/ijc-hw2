#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 4096

/**
 * TODO
 * Warning on line overflow
 *
 */

int main(int argc, char* argv[]) {
    int lines = 10;

    if (argc < 2 || argc > 4) {
        fprintf(stderr, "Invalid number of arguments\n");
    }

    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "File not found\n");
        return 1;
    }

    // Construct cyclic buffer
    char(*c)[MAX_LINE] = malloc(MAX_LINE * lines);
    size_t index = 0;
    while (fgets(c[index], MAX_LINE, fp) != NULL) {
        index++;
        index %= lines;
    }

    // Print content of cyclic buffer (last n lines)
    for (int i = 0; i < lines; i++) {
        printf("%s", c[(index + i) % lines]);
    }

    // Free everything
    free(c);
    fclose(fp);

    return 0;
}
