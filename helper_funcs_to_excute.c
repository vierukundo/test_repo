#include "shell.h"

/*will edit betty soon*/

char **get_av_with_flags(char *line)
{
    char *line_cpy, *token, *cmd;
    char **av;
    int i = 0;
    unsigned int c_count;

    line_cpy = _strdup(line);
    if (line_cpy == NULL)
        return (NULL); /*can't cpy*/

    c_count = char_count(line_cpy);
    av = malloc((c_count + 1) * sizeof(char *));
    token = strtok(line_cpy, " ");
    if (_strcmp("$$", token) == 0)
        token = get_process_id();
    else if (_strcmp("$?", token) == 0)
        token = get_status(0);
    // else if (_strcmp("export", token) == 0)
    //    token = _setenv();
    // else if (_strcmp("export", token) == 0)
    //      token = _unsetenv();
    /* couldn't handle this :') */
    cmd = _strdup(token);
    av[i++] = cmd;
    while (token != NULL)
    {
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            if (_strcmp("$$", token) == 0)
                token = get_process_id();
            else if (_strcmp("$?", token) == 0)
                token = get_status(0);

            cmd = _strdup(token);
            av[i++] = cmd;
        }

    }
    av[i] = NULL;
    free(line_cpy);
    return (av);
}
void exit_check(int nread, char *exit_cmd)
{
    if (nread == EOF)
    {
        write(STDOUT_FILENO, "\n", 1);
        exit(0);
    }
    if (_strcmp(exit_cmd, "exit") == 0)
    {
        exit(0);
    }

    if (_strcmp(exit_cmd, "exit") == 0)
    {
        exit(0);
    }
}

int has_access(char *cmd)
{
    char *path;

    path = _getenv("PATH");
    if (path == NULL)
        return (-1); /*var PATH not exists*/

    return (-1); /*does not have access*/
}

char *_getenv(const char *name)
{
    int i = 0, j = 0;
    extern char **environ;

    if (name == NULL)
        return (NULL);
    while (environ[i])
    {
        j = 0;
        while (environ[i][j] != '=')
        {
            if (environ[i][j] != name[j])
                break;
            if (environ[i][j] == name[j] && (environ[i][j + 1] == '='))
                return (&environ[i][strlen(name) + 1]);
            j++;
        }
        i++;
    }
    return (NULL);
}

unsigned int char_count(char *str)
{
    unsigned int count = 0;

    while (*str != '\0')
    {
        if (*str != ' ' && *(str + 1) == ' ')
            count++;
        str++;
    }
    return (count + 1);
}
