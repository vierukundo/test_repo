#include "shell.h"

void print_env(char **line_vector)
{
	extern char **environ;
	int i;

	for (i=0; environ[i]!=NULL; i++) 
	{
        printf("%s\n" ,environ[i]);
		fflush(stdout);
    }
	
}

void print_status(char **line_vector)
{
	printf("0\n");
	fflush(stdout);
}

void print_ppid(char **line_vector)
{
	pid_t pid = getpid();
	printf("%d\n", pid);
	fflush(stdout);
}

int is_built_in(char **line_vector)
{
	/*================================TODO===================*/
	int i;
	built_in_t built_in[] = {{"env", print_env}, {"$?", print_status}, {"$$", print_ppid}};

	for (i = 0; i < 3; i++)
	{
		if (_strcmp(built_in[i].command, line_vector[0]) == 0)
		{
			built_in[i].f(line_vector);
			return (0);
		}
	}
	return (-1);
}
