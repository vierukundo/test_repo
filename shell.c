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
	int mode;
	int status;
	char *line, **line_vector = NULL, *new_path;
	list_path *current;
	/*mode checking*/
	current = set_all_paths_to_list();
	mode = check_mode(argc);
	if (mode != INTERACTIVE)
		return (0);

	if (mode == NON_INTERACTIVE)
		check_file();
	while (1)
	{
		if (mode == NON_INTERACTIVE)
			line = get_command_from_file(argv[1]);
		else if (mode == INTERACTIVE)
			line = get_command_from_user(current);
		if(!line)
			continue;
		is_exit(line, line_vector, current);
		line_vector = get_av_with_flags(line);
		if (is_built_in(line_vector) == 0)
			continue;
		if (access(line_vector[0], X_OK) == 0)
			execute_command(line_vector[0], line_vector, env);
		else
		{
			if (new_path = check_access(line_vector[0], current))
			{
				free(line_vector[0]);
				line_vector[0] = new_path;
				execute_command(line_vector[0], line_vector, env);
				
			}
		}
		free(line);
		free_vector(line_vector);
	}
	return (0);
}

void execute_command(char *path, char **av, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == ERROR)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve(path, av, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		int status;
		waitpid(pid, &status, WUNTRACED);
	}
}

void free_vector(char** argv) {
    if (argv == NULL) {
        return;  // Nothing to free if argv is already NULL
    }

    char** curr = argv;
    while (*curr != NULL) {
        free(*curr);
        curr++;
    }

    free(argv);
}

char *check_access(char *line_av_1, list_path *current)
{
	char *full_path;
	int i, found = 0, len;
	pid_t pid;

	
	if (current == NULL)
		return (NULL);
	while (current)
	{
		len = _strlen(current->path) + _strlen(line_av_1) + 2; // to calculate the length of the full path
		if (len > 1024)
		{
			write(STDERR_FILENO, "ERROR: Path too long\n", 21);
			continue;
		}
		full_path = (char *)malloc(len * sizeof(char));
		_strcpy(full_path,current->path);
		_strcat(full_path, "/");
		_strcat(full_path, line_av_1);
		if (access(full_path, X_OK) == 0)
		{
			found = 1;
			break;
		}
		else
			free(full_path);

		current = current->next;
	}
	if (found)
		return (full_path);
		
	else
		{
			return (NULL);
		}
		
		
}
