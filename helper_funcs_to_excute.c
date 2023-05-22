#include "shell.h"

/*will edit betty soon*/
/**
 * get_av_with_flags - .
 * @line: .
 * @status: .
 * Return: .
 */

char **get_av_with_flags(char *line, int status)
{
	char *line_cpy, *token, *cmd;
	char **av;
	int i = 0;
	unsigned int c_count;

	handle_comments(line);
	/*handle_semicolons(line);*/
	line_cpy = _strdup(line);
	if (line_cpy == NULL)
		return (NULL); /*can't cpy*/

	c_count = char_count(line_cpy, ' ');
	av = malloc((c_count + 1) * sizeof(char *));
	token = strtok(line_cpy, TOK_D);
	if (_strcmp("$$", token) == 0)
		cmd = get_process_id();
	else if (_strcmp("$?", token) == 0)
		cmd = get_status(status);
	else
		cmd = _strdup(token);
	av[i++] = cmd;
	while (token != NULL)
	{
		token = strtok(NULL, TOK_D);
		if (token != NULL)
		{
			if (_strcmp("$$", token) == 0)
				cmd = get_process_id();
			else if (_strcmp("$?", token) == 0)
				cmd = get_status(status);
			else
				cmd = _strdup(token);
			av[i++] = cmd;
		}

	}
	av[i] = NULL;
	free(line_cpy);
	return (av);
}
/**
 * exit_check - .
 * @nread: .
 * @exit_cmd: .
 * Return: void
 */
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

/**
 * _getenv - .
 * @name: .
 * Return: .
 */

char *_getenv(const char *name)
{
	int i = 0, j = 0;

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

/**
 * char_count - .
 * @str: .
 * @c: .
 * Return: .
 */

unsigned int char_count(char *str, char c)
{
	unsigned int count = 0;

	while (*str != '\0')
	{
		if (*str != c && *(str + 1) == c)
			count++;
		str++;
	}
	return (count + 1);
}
