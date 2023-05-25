#include "shell.h"

/*will edit betty soon*/
/**
 * get_av_wooh_fla_help - .
 * @token: .
 * @line: .
 * @av: .
 * @status: .
 * Return: .
*/

char *get_av_wooh_fla_help(char *token, char *line, char **av, int status)
{
		char *var, *cmd, *line_cpy;

	line_cpy = line;
		if (token == NULL)
	{
		free(av);
		free(line_cpy);
		return (NULL);
	}
	if (_strlllp("$$", token) == 0)
		cmd = get_pro_io();
	else if (_strlllp("$?", token) == 0)
		cmd = get_sta(status);
	else if ((token[0] == '$') && (token[1]))
	{
		var = _gellnv(&token[1]);
		if (var)
			cmd = _stvvvp(var);
		else
			cmd = _stvvvp("");
	}
	else
		cmd = _stvvvp(token);

	return (cmd);
}
/**
 * geat_av_wooh_fl - .
 * @line: .
 * @status: .
 * Return: .
 */
char **geat_av_wooh_fl(char *line, int status)
{
	char *line_cpy, *token, **av, *var, *cmd;
	int z = 0, c_count;

	handle_comments(line);
	if (line[0] == '\0')
		return (NULL);
	line_cpy = _stvvvp(line);
	if (line_cpy == NULL)
		return (NULL); /*can't cpy*/
	c_count = char_cnt(line_cpy, ' ');
	av = malloc((c_count + 1) * sizeof(char *));
	token = _saak(line_cpy, TOK_D);

	cmd = get_av_wooh_fla_help(token, line, av, status);
	av[z++] = cmd;
	while (token != NULL)
	{
		token = _saak(NULL, TOK_D);
		if (token != NULL)
		{
			if (_strlllp("$$", token) == 0)
				cmd = get_pro_io();
			else if (_strlllp("$?", token) == 0)
				cmd = get_sta(status);
			else if ((token[0] == '$') && (token[1]))
			{
				var = _gellnv(&token[1]);
				if (var)
					cmd = _stvvvp(var);
				else
					cmd = _stvvvp("");
			}
			else
				cmd = _stvvvp(token);
			av[z++] = cmd;
		}
	}
	av[z] = NULL;
	free(line_cpy);
	return (av);
}
/**
 * exit_cha - .
 * @nread: .
 * @exit_cmd: .
 * Return: void
 */
void exit_cha(int nread, char *exit_cmd)
{
	if (nread == EOF)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	if (_strlllp(exit_cmd, "exit") == 0)
	{
		exit(0);
	}
	if (_strlllp(exit_cmd, "exit") == 0)
	{
		exit(0);
	}
}

/**
 * _gellnv - .
 * @name: .
 * Return: .
 */

char *_gellnv(char *name)
{
	int z = 0, j = 0;

	if (name == NULL)
		return (NULL);
	while (environ[z])
	{
		j = 0;
		while (environ[z][j] != '=')
		{
			if (environ[z][j] != name[j])
				break;
			if (environ[z][j] == name[j] && (environ[z][j + 1] == '='))
				return (&environ[z][_srren(name) + 1]);
			j++;
		}
		z++;
	}
	return (NULL);
}

/**
 * char_cnt - .
 * @str: .
 * @c: .
 * Return: .
 */

unsigned int char_cnt(char *str, char c)
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
