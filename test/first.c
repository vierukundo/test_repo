#include "shell.h"

void print_prompt();

int main(int argc, char *argv[], char *env[])
{

    char *input;
    size_t n;
    ssize_t x;
    char *enV[] = {NULL};
    char *argV[] = {"ls", NULL};
    char *path;
    pid_t pid;
    if (isatty(STDIN_FILENO))
    {

        while (1)
        {
            print_prompt();
            x = getline(&input, &n, stdin);

            path = input;
            path[x - 1] = '\0';
            if (x == -1)
                break;

            pid = fork();
            if (pid == -1)
                perror("ERROR");
            else if (pid == 0)
                {
            if ((execve(path, argV, enV)) == -1)
                perror("Failed");
                }
            else
                printf("HEREE");

                wait(NULL);
        }
    }
    return (0);
}

void print_prompt()
{

    char *user;
    char *name;
    char *cwd;
    char *prom = "=> ";

    user = getenv("USER");
    if (user)
        printf("%s@", user);
    name = getenv("NAME");
    if (name)
        printf("%s:", name);
    cwd = getenv("PWD");
    if (cwd)
        printf("%s%s", cwd, prom);
}