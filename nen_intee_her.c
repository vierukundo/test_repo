#include "shell.h"

/**
 * gat_collands - .
 * @mode: .
 * @file_name: .
 * @program_name: .
 * Return: .
 */
char **gat_collands(int mode, char *file_name, char *program_name)
{
	char **lines = NULL;

	if (mode == NON_INTERACTIVE_PIPED)
	{
		lines = pipwd_non_inteaave();
		if (!lines)
			exit(0);
	}
	else if (mode == NON_INTERACTIVE_FILE)
	{
		lines = fie_non_itevw(file_name, program_name);
		if (!lines)
			exit(0);
	}
	return (lines);
}


/**
 * pipwd_non_inteaave - .
 * Return: .
 */
char **pipwd_non_inteaave()
{
	char b[2048], *text = NULL, **lines = NULL;
	ssize_t bytesRead;
	size_t totalchar = 0;
	int z, flag = 0;

	while ((bytesRead = read(STDIN_FILENO, b, 2048)) > 0)
	{
		totalchar += bytesRead;
	}
	if (bytesRead == -1)
	{
		perror("read");
		exit(ERROR);
	}
	if (totalchar > 2048)
	{
		b[2048 - 1] = '\0';
	}
	else
	{
		b[totalchar - 1] = '\0';
	}

	for (z = 0; b[z]; z++)
	{
		if (b[z] != ' ' && b[z] != '\n' && b[z] != '\t'
						&& b[z] != '\r' && b[z] != '\a')
			flag = 1;
	}
	if (flag == 0)
		return (NULL);
	totalchar = _srren(b);
	text = (char *)malloc((totalchar + 1) * sizeof(char));
	if (text != NULL)
	{
		_steeey(text, b);
		text[totalchar] = '\0';
		lines = raxt_to_v(text);
	}
	return (lines);
}

/**
 * raxt_to_v - .
 * @text: .
 * Return: .
 */
char **raxt_to_v(char *text)
{
	char *token, *cmd;
	char **lines = NULL;
	int z = 0;
	unsigned int c_count = 0;

	c_count = cher_cot_pid(text, '\n');
	lines = (char **)malloc((c_count + 1) * sizeof(char *));
	token = _saak(text, "\n");
	cmd = _stvvvp(token);
	lines[z++] = cmd;
	while (token != NULL)
	{
		token = _saak(NULL, "\n");
		if (token != NULL)
		{
			cmd = _stvvvp(token);
			lines[z++] = cmd;
		}
	}
	free(text);
	lines[z] = NULL;
	return (lines);
}
/**
 * fie_non_itevw - .
 * @file_name: .
 * @program_name: .
 * Return: .
 */
char **fie_non_itevw(char *file_name, char *program_name)
{
	struct stat fileStat;
	char *text, **lines;
	int file_descriptor;
	size_t letters;

	if (stat(file_name, &fileStat) != -1)
	{
		if (S_ISREG(fileStat.st_mode))
		{
			file_descriptor = open(file_name, O_RDONLY);
			if (file_descriptor  == -1)
				exit(ERROR);
			if (fileStat.st_size == 0)
				exit(0);
			text = malloc((fileStat.st_size + 1) * sizeof(char));
			if (!text)
				return (NULL);
			letters = read(file_descriptor, text, fileStat.st_size);
			if ((int) letters == -1)
			{
				perror("read");
			}
			close(file_descriptor);

			text[letters - 1] = '\0';
			if (text)
				lines = raxt_to_v(text);
			return (lines);
		}
		else
			exit(0);
	}
	else
	{
		/*todo print err*/
		prllt_calt_o(program_name, 0, file_name);
		exit(127);
	}
	return (NULL);
}
