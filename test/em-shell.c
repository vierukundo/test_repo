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
    char *line;
    size_t n = 0;
    char **av;
    char *en[] = {NULL};
    list_path *list_of_paths;
    int x;

    /*
        av = get_av_with_flags("ls -l -f");
    fflush(stdout);
    for (x = 0; x < 3; x++)
    {
        printf("%s\n", av[x]);
        fflush(stdout);
    }

    exit(0);
    */

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
            nread = getline(&line, &n, stdin);
            line[nread - 1] = '\0';
            exit_check(nread, line);

            if (access(line, X_OK) == 0)
                pid = fork();
            else
            {
                write(STDERR_FILENO, argv[0], sizeof(argv[0]));
                write(STDERR_FILENO, ": No such file or directory\n", 28);
            }
            if (pid != 0)
            {
                wait(NULL);
            }
            if (pid == 0)
            {
                printf("im child");
                fflush(stdout);
                execve(line, av, en);
            }
        }
    }

    /*
        TODO FREE
    */
    return (0);
}