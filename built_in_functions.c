#include "shell.h"
/**
 * print_env - .
 * @status: .
 * Return: void
 */
void print_env(int *status)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
		fflush(stdout);
	}
	*status = 0; /*success*/
}
/**
 * get_status - .
 * @n: .
 * Return: .
 */
char *get_status(int n)
{
	char *status;

	status = num_to_char(n);
	return (status);
}

int _cd(char *line_vector[])
{

	if (line_vector[1] == NULL)
	{
		chdir(_getenv("HOME"));
		return 1;
	}

	else
	{
		if (chdir(line_vector[1]) == -1)
		{
			char *msg = _strcat(line_vector[1], ": no such directory\n");
			write(STDOUT_FILENO, msg, strlen(msg));
			return -1;
		}
	}
	return 0;
}

/**
 * get_process_id - .
 * Return: .
 */
char *get_process_id()
{
	char *ppid_s;
	pid_t pid = getpid();

	ppid_s = num_to_char(pid);

	return (ppid_s);
}
/**
 * is_built_in - .
 * @line: .
 * @line_vector: .
 * @current: .
 * @program_name: .
 * @counter: .
 * @status: .
 * Return: .
 */
int is_built_in(char *line, char **line_vector, list_path *current,
		char *program_name, int counter, int *status)
{
	int i, n = -1;
	char *built_in[] = {"env", "exit", "cd"};

	for (i = 0; i < 3; i++)
	{
		if (_strcmp(built_in[i], line_vector[0]) == 0)
		{
			n = i;
			break;
		}
	}
	if (n == -1)
		return (n);

	switch (n)
	{
		case 0:
			print_env(status);
			break;
		case 1:
			is_exit(line, line_vector, current, program_name, counter, status);
			break;
		case 2:
			_cd(line_vector);
			break;
		default:
			return (-1);
	}
	return (0);
}
/**
 * num_to_char - .
 * @num: .
 * Return: .
 */
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

