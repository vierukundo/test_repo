#include "shell.h"
/**
 * handle_comments - .
 * @line: .
 * Return: void
 */
void handle_comments(char *line)
{
	int len = strlen(line);
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

