#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 4095
#define BUFFER_SIZE (MAX_LINE + 2)  // +2 for \n and \0

/**
 * @brief Check if line is too long and skip the rest of the line if it is
 *
 * @param c Circular buffer
 * @param index Index in the circular buffer
 * @param stream Stream to read from
 */
void check_line(char (*c)[BUFFER_SIZE], size_t index, FILE* stream) {
    static bool too_long_found = false;
    if (strlen(c[index]) == BUFFER_SIZE - 1 && c[index][BUFFER_SIZE - 2] != '\n') {
        // Print error only for first time
        if (!too_long_found) {
            fprintf(stderr, "Line too long\n");
            too_long_found = true;
        }
        // Add \n to the end of line
        c[index][BUFFER_SIZE - 2] = '\n';
        // Skip the rest of line
        while (fgetc(stream) != '\n' && !feof(stream))
            ;
    }
}

/**
 * @brief Check if file was correctly opened
 *
 * @param stream File stream
 */
bool check_file_stream(FILE* stream) {
    if (stream == NULL) {
        fprintf(stderr, "Couldn't open file\n");
        return false;
    }
    return true;
}

/**
 * @brief Parse line count from string argument
 *
 * @param arg Argument to parse
 * @param lines Parsed line count
 */
bool parse_line_count(char* arg, size_t* lines) {
    char* end;
    long long count = strtoll(arg, &end, 10);
    if (end == arg || *end != '\0' || arg[0] == '+' || count < 0LL) {
        fprintf(stderr, "Invalid line count\n");
        return false;
    }
    *lines = count;
    return true;
}

/**
 * @brief Parse arguments
 *
 * @param argc Number of arguments
 * @param argv Arguments
 * @param stream Stream to read from
 * @param lines Number of lines to print
 */
bool arg_parse(int argc, char* argv[], FILE** stream, size_t* lines) {
    switch (argc) {
        // No arguments
        case 1:
            *stream = stdin;
            return true;
        // Only file as argument
        case 2:
            *stream = fopen(argv[1], "r");
            return check_file_stream(*stream);
        // Only line count as argument
        case 3:
            *stream = stdin;
            if (strcmp(argv[1], "-n") == 0) {
                return parse_line_count(argv[2], lines);
            }
            fprintf(stderr, "Invalid arguments\n");
            return false;
        // File and line count as arguments
        case 4:
            // File as last argument
            if (strcmp(argv[1], "-n") == 0) {
                *stream = fopen(argv[3], "r");
                return check_file_stream(*stream) && parse_line_count(argv[2], lines);
            }
            // File as first argument
            if (strcmp(argv[2], "-n") == 0) {
                *stream = fopen(argv[1], "r");
                return check_file_stream(*stream) && parse_line_count(argv[3], lines);
            }
            fprintf(stderr, "Invalid arguments\n");
            return false;
    }

    fprintf(stderr, "Invalid number of arguments\n");
    return false;
}

int main(int argc, char* argv[]) {
    size_t lines = 10;
    FILE* stream = NULL;
    if (!arg_parse(argc, argv, &stream, &lines)) {
        return EXIT_FAILURE;
    }

    if (lines == 0) {
        fclose(stream);
        return EXIT_SUCCESS;
    }

    // Construct cyclic buffer
    char(*buf)[BUFFER_SIZE] = malloc(BUFFER_SIZE * lines);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(stream);
        return EXIT_FAILURE;
    }
    size_t index = 0;
    size_t lines_read = 0;
    while (fgets(buf[index], BUFFER_SIZE, stream) != NULL) {
        check_line(buf, index, stream);

        // Update counters
        lines_read++;
        index++;
        index %= lines;
    }

    // When file is smaller than -n (or 10)
    if (lines_read < lines) {
        index = 0;
    }

    // Print content of cyclic buffer (max last n lines)
    for (size_t i = 0; i < lines && i < lines_read; i++) {
        printf("%s", buf[(index + i) % lines]);
    }

    // Free everything
    free(buf);
    fclose(stream);

    return EXIT_SUCCESS;
}
