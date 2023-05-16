#include "shell.h"
/*
 * main - Entry point to the shell
 * @argc: arguements count
 * @argv: arguements values
 * @env: environment vector
 * Return : the process
 */

int main(int argc, char *argv[], char *env[])
{
    int pid;
    ssize_t nread;
    char *line = NULL;
    size_t n = 0;
    char *av[100] = {NULL};
    char *en[] = {NULL};
    list_path *list_of_paths;
    char *input;
    int i = 0;
    list_of_paths = set_all_paths_to_list();
    if (list_of_paths == NULL)
    {
        write(STDERR_FILENO, "ERROR", 5);
        exit(127);
    }

    if (isatty(STDIN_FILENO))
    {
        while (1)
        {
            write(STDOUT_FILENO, "^_* -> ", 7);
            fflush(stdout);
            nread = getline(&line, &n, stdin);
            exit_check(nread, line);

            line[nread - 1] = '\0';

            input = strtok(line, " ");
            i = 0;
            while (input && i < 99)
            {
                av[i] = input;
                input = strtok(NULL, " ");
                i++;
            }
            av[i] = NULL;

            char full_path[1024]; // to construct full path
            list_path *current = list_of_paths;
            int found = 0;
            while (current)
            {
                int len = _strlen(current->path) + _strlen(av[0]) + 2; // to calculate the length of the full path
                if (len > 1024)
                {
                    write(STDERR_FILENO, "ERROR: Path too long\n", 21);
                    break;
                }
                strcpy(full_path, current->path); // to copy path to full_path
                strcat(full_path, "/"); // to add '/' to full_path
                strcat(full_path, av[0]);
                if (access(full_path, X_OK) == 0)
                {
                    found = 1;
                    break;
                }
                current = current->next;
            }

            if (!found)
            {
                write(STDERR_FILENO, argv[0], _strlen(argv[0]));
                write(STDERR_FILENO, ": command not found\n", 20);
                continue;
            }

            pid = fork();

            if (pid == 0)
            {
                execve(full_path, av, en);
                perror("execve");
                exit(EXIT_FAILURE);
            }
            else if (pid > 0)
            {
                wait(NULL);
            }
            else
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
        }
    }


    free_list(list_of_paths);
    free(line);
    return (0);
}