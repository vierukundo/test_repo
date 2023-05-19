#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char* _getline() {
    static char buffer[BUFFER_SIZE];
    static int buffer_pos = 0;
    static int buffer_len = 0;

    char* line = NULL;
    int line_len = 0;

    while (1) {
        // If buffer is empty, refill it from stdin
        if (buffer_pos >= buffer_len) {
            buffer_len = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);
            buffer_pos = 0;
        }

        // If EOF reached or error occurred, return NULL
        if (buffer_len == 0) {
            if (line_len > 0) {
                line[line_len] = '\0';
                return line;
            }
            return NULL;
        }

        // Scan buffer for newline character
        while (buffer_pos < buffer_len) {
            if (buffer[buffer_pos] == '\n') {
                // Allocate memory for line and copy characters
                line = (char*)malloc((line_len + 1) * sizeof(char));
                memcpy(line, buffer, line_len * sizeof(char));
                line[line_len] = '\0';

                // Move buffer_pos to next character after newline
                buffer_pos++;

                return line;
            } else {
                // Append character to line
                line_len++;
            }
            buffer_pos++;
        }
    }
}

#include <stdio.h>

int main() {
    char* line;

    while ((line = _getline()) != NULL) {
        printf("%s\n", line);
        free(line);
    }

    return 0;
}