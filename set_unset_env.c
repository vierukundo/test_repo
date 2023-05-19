#include "shell.h"

int _setenv(const char *name, const char *value, int overwrite)
{
    extern char **environ;
    char *env_var, *new_env_var, **new_environ;
    int i = 0, n_len, v_len ;

    /* Checkthe env var exists or not */
    env_var = _getenv(name);
    if (env_var != NULL && !overwrite)
        return 0;
     n_len = _strlen(name);
     v_len = _strlen(value);


    new_env_var = malloc(n_len + v_len + 2);
    if (new_env_var == NULL)
        return -1;

    /* Copy the name and value to the new_env_var */
    _strcpy(new_env_var, name);
    _strcat(new_env_var, "=");
    _strcat(new_env_var, value);

    int num_env_vars = 0;
    while (environ[num_env_vars] != NULL)
        num_env_vars++;

    new_environ = malloc((num_env_vars + 2) * sizeof(char *));
    if (new_environ == NULL)
        return -1;

        _strcpy(new_environ, environ);

    /* Add the new environment variable to the new environment  */
    new_environ[i] = new_env_var;
    new_environ[i+1] = NULL;

    environ = new_environ;

    return 0;
}

int _unsetenv(const char *name)
{
    extern char **environ;
    char **new_environ;
    int i = 0, x = 0, k = 0;
    int name_len = strlen(name);

    /* find index of the env_var to remove */
    while (environ[i])
    {
        /* Compare name to the env_var */
        x = 0;
        while (environ[i][x] != '\0' && environ[i][x] != '=')
        {
            if (environ[i][x] != name[x])
                break;
            x++;
        }

        /* the name matches and followed by = it's found */
        if (x == name_len && environ[i][x] == '=')
            break;

        i++;
    }

    /* If the environment variable was not found return success 0 */
    if (environ[i] == NULL)
        return 0;

    /* size of the new environment */
    int num_env_vars = 0;
    while (environ[num_env_vars] != NULL)
        num_env_vars++;

    new_environ = malloc(num_env_vars * sizeof(char *));
    if (new_environ == NULL)
        return -1;

    /* Copy the old environment array into the new environment array, excluding the variable to remove */
    /*CHATGPT*/
    for (x = 0, k = 0; x < num_env_vars; x++)
    {
        if (x != i)
        {
            new_environ[k] = environ[x];
            k++;
        }
    }
    new_environ[k] = NULL;

    environ = new_environ;

    return 0;
}