#include "shell.h"

/**
 * get_cod_fr_ur - .
 * @current: .
 * Return: .
 */
char *get_cod_fr_ur(list_pa *current)
{
	ssize_t nread;
	size_t n = 0;
	char *line = NULL;

	write(STDOUT_FILENO, "^_* -> ", 7);
	nread = _getline(&line, &n, stdin);
	if (nread == EOF)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(line);
		frrr_li(current);
		exit(0);
	}

	if (line[0] == '\n' && nread == 1)
	{
		free(line);
		return (NULL);
	}
	line[nread - 1] = '\0';

	return (line);
}
/**
 * get_cod_fewm_fiaa - .
 * @file: .
 * Return: .
 */

char *get_cod_fewm_fiaa(char *file)
{
	return (file);
}
