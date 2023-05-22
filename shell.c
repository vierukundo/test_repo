#include "shell.h"

/**
 * main - Entry point to the shell
 * @argc: arguements count
 * @argv: arguements values
 * @env: environment vector
 * Return: the process
 */
int main(int argc, char *argv[], char *env[])
{
	int mode, counter = 0, *status, t = 0, non_int_count = 1;
	char *line, **line_vector = NULL, **lines;
	list_path *current;
	/*mode checking*/
	mode = check_mode(argc);
	if (mode != INTERACTIVE)
		lines = get_commands(mode, argv[1], argv[0]);
	current = set_all_paths_to_list();
	status = &t;
	while (++counter && non_int_count)
	{
		if (mode == NON_INTERACTIVE_PIPED || mode == NON_INTERACTIVE_FILE)
		{
			if (lines[counter - 1])
				line = lines[counter - 1];
			else
				break;
		}
		else if (mode == NON_INTERACTIVE_FILE)
			line = get_command_from_file(argv[1]);
		else if (mode == INTERACTIVE)
			line = get_command_from_user(current);
		if (!line)
			continue;
		line_vector = get_av_with_flags(line, *status);
		if (is_dir(line_vector[0]) == 0)
		{
			print_error(argv[0], counter, line_vector[0], PERMISSION_DENIED);
			*status = PERMISSION_DENIED;
			free_l_v(line, line_vector);
			continue;
		}
		if (is_built_in(line, line_vector, current, argv[0], counter, status) != 0)
			is_not_built_in(line_vector, env, status, counter, current, argv);
		free_l_v(line, line_vector);
	}

	exit(*status);
}

/**
 * is_not_built_in - Entry point to the shell
 * @line_vector: arguements count
 * @env: arguements values
 * @status: environment vector
 * @counter: arguements count
 * @current: arguements values
 * @argv: environment vector
 */
void is_not_built_in(char **line_vector, char *env[], int *status,
						int counter, list_path *current, char *argv[])
{
	char *new_path;

	if (access(line_vector[0], X_OK) == 0)
		execute_command(line_vector[0], line_vector, env, status);
	else
	{
		new_path = check_access(line_vector[0], current);
		if (new_path)
		{
			execute_command(new_path, line_vector, env, status);
			free(new_path);
		}
		else
		{
			print_error(argv[0], counter, line_vector[0], NOT_FOUND);
			*status = NOT_FOUND;
		}
	}
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
