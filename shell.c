#include "shell.h"

/*
 * main - Entry point to the shell
 * @argc: arguements count
 * @argv: arguements values
 * @env: environment vector
 * Return : the process
 */
int main(int argc, char *argv[], char *env[])
{
	int mode, counter = 0, *status, t = 0, non_int_count = 1;
	char *line, **line_vector = NULL, *new_path;
	list_path *current;
	/*mode checking*/
	current = set_all_paths_to_list();
	mode = check_mode(argc);
	status = &t;
		

	if (mode == NON_INTERACTIVE)
		check_file(argv[1]);
	while (++counter && non_int_count)
	{
		if (mode == NON_INTERACTIVE)
		{
			line = get_command_from_file(argv[1]);
			non_int_count = 0;/*stop*/
		}
		else if (mode == INTERACTIVE)
			line = get_command_from_user(current);
		if(!line)
			continue;
		is_exit(line, line_vector, current);
		handle_comments(line);
		line_vector = get_av_with_flags(line, *status);
		if (is_built_in(line_vector) == 0)
		{
			free(line);
			free_vector(line_vector);
			continue;
		}
		if (access(line_vector[0], X_OK) == 0)
			execute_command(line_vector[0], line_vector, env, status);
		else
		{
			if (new_path = check_access(line_vector[0], current))
			{
				execute_command(new_path, line_vector, env, status);
				free(new_path);
			}
			else
			{
				print_error(argv[0] , counter, line_vector[0]);
				*status = 127;
			}
		}
		free(line);
		free_vector(line_vector);
	}
	return (0);
}

void print_error(char *program_name , int counter,char *command)
{
	char * counter_s;

	counter_s = num_to_char(counter);
	write(STDERR_FILENO, program_name, _strlen(program_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, counter_s, _strlen(counter_s));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "not found\n", 10);
	free(counter_s);
}
