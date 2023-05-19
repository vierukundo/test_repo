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


void is_exit(char *line)
{

	if (_strcmp(line, "exit") == 0)
	{
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
		wait(NULL);
	}
}

