#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include <string.h>

typedef struct env_var {
    char* name;
    char* value;
    struct env_var* next;
} EnvVar;

EnvVar* env = NULL;

void add_env_var(line) {
    int *status;[]

    EnvVar* curr_var = _getenv;

    char **lineV = get_av_with_flags(line, *status);

    char command = lineV[0];
    char name = lineV[1];
    char value = lineV[2];



    while (curr_var != NULL) {
        if (strcmp(curr_var->name, name) == 0) {
            // variable already exists, update its value
            free(curr_var->value);
            curr_var->value = strdup(value);
            return;
        }
        curr_var = curr_var->next;
    }
    // variable does not exist, create a new one
    EnvVar* new_var = malloc(sizeof(EnvVar));
    new_var->name = strdup(name);
    new_var->value = strdup(value);
    new_var->next = env;
    env = new_var;
}

void remove_env_var(char* name) {
    EnvVar* curr_var = env;
    EnvVar* prev_var = NULL;

    while (curr_var != NULL) {
        if (strcmp(curr_var->name, name) == 0) {
            if (prev_var == NULL) {
                // removing first node
                env = curr_var->next;
            } else {
                prev_var->next = curr_var->next;
            }
            free(curr_var->name);
            free(curr_var->value);
            free(curr_var);
            return;
        }
        prev_var = curr_var;
        curr_var = curr_var->next;
    }
}
int main(int argc, char* argv[]) {
    if (argc == 3 && strcmp(argv[1], "setenv") == 0) {
        char* name = argv[2];
        char* value = argv[3];
        add_env_var(name, value);
    } else if (argc == 2 && strcmp(argv[1], "unsetenv") == 0) {
        char* name = argv[2];
        remove_env_var(name);
    } else {
        fprintf(stderr,"Invalid syntax. Usage: setenv VARIABLE VALUE or unsetenv VARIABLE\n");
        return 1;
    }

    // use the environment as needed
    char* path = getenv("PATH");
    printf("PATH=%s\n", path);

    // free memory for the environment before exiting
    EnvVar* curr_var = env;
    while (curr_var != NULL) {
        EnvVar* next_var = curr_var->next;
        free(curr_var->name);
        free(curr_var->value);
        free(curr_var);
        curr_var = next_var;
    }

    return 0;
}