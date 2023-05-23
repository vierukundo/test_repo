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
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
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
 * @env_list: .
 * Return: .
 */
int is_built_in(char *line, char **line_vector, list_path *current,
		char *program_name, int counter, int *status, list_path *env_list)
{
	int i, n = -1;
	char *built_in[] = {"env", "exit", "cd", "setenv", "unsetenv"};

	for (i = 0; i < 5; i++)
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
			is_exit(line, line_vector, current, program_name,
					counter, status, env_list);
			break;
		case 2:
			_cd(line_vector);
			break;
		case 3:
			_setenv(line_vector[1], line_vector[2], env_list);
			break;
		case 4:
			_setenv(line_vector[1], line_vector[2], env_list);
			break;
		default:
			return (-1);
	}
	return (0);
}
/**
 * _setenv - .
 * @name: .
 * @value: .
 * @env_list: .
 * Return: void
 */
void _setenv(char *name, char *value, list_path *env_list)
{
	list_path *var;
	char *full_var;
	int count;

	count = _strlen(name) + _strlen(value) + 2;
	full_var = malloc(count);
	if (full_var == NULL)
	{
		perror("setenv ERROR");
		/*
		* TODO status
		*/
		/*print something*/
	}
	full_var = _strcpy(full_var, name);
	full_var[_strlen(name)] = '=';
	full_var[_strlen(name) + 1] = '\0';
	full_var = _strcat(full_var, value);
	full_var[count - 1] = '\0';
	var = get_variable(name, env_list);

	if (var == 0)
	{
		free(var->path);
		var->path = full_var;
		var->len = _strlen(full_var);
	}
	else
	{
		add_node(&env_list, full_var);
		var->len = _strlen(full_var);
	}

	print_list(env_list);

}
/**
 * get_variable - .
 * @name: .
 * @head: .
 * Return: .
 */
list_path *get_variable(char *name, list_path *head)
{
	while (head)
	{
		if (_varcmp(name, head->path))
			return (head);
		head = head->next;
	}

	return (NULL);
}
/**
 * _varcmp - .
 * @var_name: .
 * @full_var: .
 * Return: .
 */
int _varcmp(char *var_name, char *full_var)
{
	int i;

	for (i = 0; var_name[i]; i++)
	{
		if (full_var[i])
			if (var_name[i] - full_var[i] != 0)
				return (-1);
	}
	if (full_var[i] == '=')
		return (0);

	return (-1);
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
