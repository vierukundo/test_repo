#include "shell.h"
/**
 * handle_comments - .
 * @line: .
 * Return: void
 */
void handle_comments(char *line)
{
	int len = _strlen(line);
	int x = 0;
	int _strating = 0;

	for (x = 0; x < len; x++)
	{
		if (line[x] == ' ')
		{
			_strating = 0;
		}
		else if (line[x] == '#')
		{
			if (!_strating)
			{
				line[x] = '\0';
				break;
			}
		}
		/*
		 * this else handles the mid
		 */
		else
		{
			_strating = 1;
		}
	}
}

/**
 * _cd - .
 * @line_vector: .
 * Return: .
 */
int _cd(char *line_vector[])
{
	char cwd[PATH_MAX];

		if (line_vector[1] == NULL)
		{
			chdir(_getenv("HOME"));
			return (1);
		}
		else if (_strcmp(line_vector[1], "-") == 0)
		{
			chdir(_getenv("OLDPWD"));
		}
		else
			chdir(line_vector[1]);

	if (chdir(line_vector[1]) == -1)
	{
		char *msg = _strcat(line_vector[1], ": no such directory\n");

		write(STDOUT_FILENO, msg, strlen(msg));
		return (-1);
	}
	else if (chdir(line_vector[1]) != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", _getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}

	return (0);
}

/**
 * _atoi - .
 * @lines: .
 * @counter: .
 * @env: .
 * @current: .
 * @line: .
 * @line_vector: .
 * Return: .
 *
 */
void free_all(char **lines, int counter, list_path *env,
				list_path *current, char *line, char **line_vector)
{
	if (lines)
	{
		free(lines[counter]);
		if (lines)
			free(lines);
	}
			free_list(env);
			free_list(current);
			free_l_v(line, line_vector);
}
