#include "shell.h"

void print_env(char **line_vector)
{

	extern char **environ;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
		fflush(stdout);
	}
}

char *get_status(int n)
{
	char *status;
	status = num_to_char(n);
	return (status);

}

char *get_process_id()
{
	char *ppid_s;
	pid_t pid = getpid();

	ppid_s = num_to_char(pid);

	return (ppid_s);
}

int is_built_in(char **line_vector)
{
	/*================================TODO===================*/
	int i;
	built_in_t built_in[] = {{"env", print_env};

	for (i = 0; i < 1; i++)
	{
		if (_strcmp(built_in[i].command, line_vector[0]) == 0)
		{
			built_in[i].f(line_vector);
			return (0);
		}
	}
	return (-1);
}

char *num_to_char(int num)
{
	/*count digits*/
	int c = 0, tmp = num;
	char *cp_num;
	if (num == 0)
	{
		c = 1;
	}
	else
	{
		while (tmp != 0)
		{
			tmp /= 10;
			c++;
		}
	}

	cp_num = malloc(sizeof(char) * (c + 1));
	if (!cp_num)
	{
		perror("malloc");
		return (NULL);
	}
	cp_num[c] = '\0';
	while (c != 0)
	{
		c--;
		cp_num[c] = '0' + num % 10;
		num /= 10;
	}

	return (cp_num);
}
