#include "shell.h"

/*
 * check_mode - check mode of the program
 * @argc: arguements count
 * Return : mode
 */
int check_mode(int argc)
{
	if(argc == 1)
		return (INTERACTIVE);
	else if(argc == 2)
		return (NON_INTERACTIVE);
	return (ERROR);
}


void is_exit(char *line,char **line_vector, list_path *current)
{

	if (_strcmp(line, "exit") == 0)
	{
		free(line);
		free_list(current);
		exit(0);
	}

	/*
	TODO
	exit 10

	ac ?
	is_num
	exit with status

	*/

}



void execute_command(char *path, char **av, char **env, int *status)
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
		waitpid(pid, status, WUNTRACED);
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
			return (NULL);
}
