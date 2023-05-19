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
        if (buffer_pos >= buffer_len) {
            buffer_len = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);
            buffer_pos = 0;
        }

        if (buffer_len == 0) {
            if (line_len > 0) {
                line[line_len] = '\0';
                return line;
            }
            return NULL;
        }

        while (buffer_pos < buffer_len) {
            if (buffer[buffer_pos] == '\n') {
                line = (char*)malloc((line_len + 1) * sizeof(char));
                memcpy(line, buffer, line_len * sizeof(char));
                line[line_len] = '\0';

                buffer_pos++;

                return line;
            } else {
                line_len++;
            }
            buffer_pos++;
        }
    }
}
