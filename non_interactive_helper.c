#include "shell.h"

/**
 * get_commands - .
 * @mode: .
 * @file_name: .
 * @program_name: .
 * Return: .
 */
char **get_commands(int mode, char *file_name, char *program_name)
{
	char **lines;

	if (mode == NON_INTERACTIVE_PIPED)
		lines = piped_non_interactive(program_name);
	else if (mode == NON_INTERACTIVE_FILE)
	{

		lines = file_non_interactive(file_name, program_name);
	}
	return (lines);
}


/**
 * piped_non_interactive - .
 * Return: .
 */
char **piped_non_interactive()
{
	char b[2048], *text, **lines;
	ssize_t bytesRead;
	size_t totalchar = 0;

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
		text = malloc(sizeof(char) * (2048));
	}
	else
	{
		b[totalchar - 1] = '\0';
		text = malloc(sizeof(char) * (totalchar));
	}
		

	
	if (!text)
		return (NULL);

	text = _strdup(b);
	if (text)
		lines = text_to_vector(text);
	return (lines);
}

/**
 * text_to_vector - .
 * @text: .
 * Return: .
 */
char **text_to_vector(char *text)
{
	char *token, *cmd, *text_cpy;
	char **lines;
	int i = 0;
	unsigned int c_count;

	text_cpy = text;
	if (text_cpy == NULL)
		return (NULL);
	c_count = char_count_piped(text_cpy, '\n');
	lines = malloc(c_count * sizeof(char *));
	token = _strtok(text_cpy, "\n");
	cmd = _strdup(token);
	lines[i++] = cmd;
	while (token != NULL)
	{
		token = _strtok(NULL, "\n");
		if (token != NULL)
		{
			cmd = _strdup(token);
			lines[i++] = cmd;
		}
	}
	free(text);
	return (lines);
}
/**
 * file_non_interactive - .
 * @file_name: .
 * @program_name: .
 * Return: .
 */
char **file_non_interactive(char *file_name, char *program_name)
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
				lines = text_to_vector(text);
			return (lines);
		}
		else
			exit(0);
	}
	else
	{
		/*todo print error*/
		print_cant_open(program_name, 0, file_name);
		exit(127);
	}
	return (NULL);
}
