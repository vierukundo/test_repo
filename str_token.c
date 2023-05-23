#include "shell.h"

/**
 * _strtok - .
 * @str: .
 * @delim: .
 * Return: .
 */
char *_strtok(char *str, const char *delimiters)
{
	return (strtok(str, delimiters));
}

/**
 * _chrCheck - .
 * @c: .
 * @str: .
 * Return: .
 */
unsigned int _chrCheck(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

/**
 * free_l_v - Entry point to the shell
 * @line: arguements count
 * @line_vector: arguements values
 */
void free_l_v(char *line, char **line_vector)
{
	free(line);
	free_vector(line_vector);
}

/**
 * is_dir - Entry point to the shell
 * @line: arguements count
 * Return: is dir or not
 */
int is_dir(char *line)
{
	struct stat st;

	if (stat(line, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			return (0);
		}
	}
	return (-1);
}
