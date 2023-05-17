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
	char *line, **line_vector;
	/*mode checking*/
	mode = check_mode(argc);
	if(mode != INTERACTIVE)
		return (0);
	
	if(mode == NON_INTERACTIVE)
		check_file();
	while (1)
	{
		if(mode == NON_INTERACTIVE)
			line = get_command_from_file(argv[1]);
		else if(mode == INTERACTIVE)
			line = get_command_from_user();

		is_exit(line);
		line_vector = get_av_with_flags(line);
		if(is_built_in(line_vector) == 0)
			continue;
		if(access(line_vector[0], X_OK) == 0)
			execute_command(line_vector[0],line_vector, env);
		else
		{
			printf("TODO\n");
			fflush(stdout);
			/*
			line_vector[0] = ls
			line_vector[0] .free
			line_vector[0] = /bin/ls
			check_access(ls)
			/bin/ls

			NULL or char *
			*/
			
		}
	}


    free(line);
	return (0);
}

void execute_command(char *path, char **av, char **env)
{
	pid_t pid;

	pid = fork();
	if(pid == ERROR)
	{
		perror("fork");
        exit(EXIT_FAILURE);
	}
	if( pid == 0)
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
