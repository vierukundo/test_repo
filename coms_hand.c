#include "shell.h"
/**
 * handle_comments - .
 * @line: .
 * Return: void
 */
void handle_comments(char *line)
{
	int lenn = _srren(line);
	int n = 0;
	int _strating = 0;

	for (n = 0; n < lenn; n++)
	{
		if (line[n] == ' ')
		{
			_strating = 0;
		}
		else if (line[n] == '#')
		{
			if (!_strating)
			{
				line[n] = '\0';
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
 * @argv: .
 * Return: .
 */
int _cd(char **line_vector, char **argv)
{
	char *dir = line_vector[1];
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return (1);
	}
	if (dir == NULL || _strlllp(dir, "~") == 0)
		dir = _gellnv("HOME");
	else if (_strlllp(dir, "-") == 0)
		dir = _gellnv("OLDPWD");
	if (chdir(dir) == -1)
	{
		write(STDERR_FILENO, argv[0], _srren(argv[0]));
		write(STDERR_FILENO, ": 1", 3);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, line_vector[0], _srren(line_vector[0]));
		write(STDERR_FILENO, ": can't cd to ", 14);
		write(STDERR_FILENO, line_vector[1], _srren(line_vector[1]));
		write(STDERR_FILENO, "\n", 1);
		return (1);
	}
	else
	{
		setenv("OLDPWD", cwd, 1);
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd() error");
			return (1);
		}
	}
	return (0);
}


/**
 * free_all - .
 * @lines: .
 * @counter: .
 * @env: .
 * @current: .
 * @line: .
 * @line_vector: .
 * Return: .
 *
 */
void free_all(char **lines, int counter, list_pa *env,
		list_pa *current, char *line, char **line_vector)
{
	if (lines)
	{
		free(lines[counter]);
		if (lines)
			free(lines);
	}
	frrr_li(env);
	frrr_li(current);
	free_e_v(line, line_vector);
}
