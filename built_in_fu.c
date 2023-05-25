#include "shell.h"
/**
 * print_eve - .
 * @status: .
 * Return: void
 */
void print_eve(int *status)
{
	int z;

	for (z = 0; environ[z] != NULL; z++)
	{
		write(STDOUT_FILENO, environ[z], _srren(environ[z]));
		write(STDOUT_FILENO, "\n", 1);
	}
	*status = 0; /*success*/
}
/**
 * get_sta - .
 * @n: .
 * Return: .
 */
char *get_sta(int n)
{
	char *status;

	status = nu_to_ch(n);
	return (status);
}


/**
 * get_pro_io - .
 * Return: .
 */
char *get_pro_io()
{
	char *ppid_s;
	pid_t pid = getpid();

	ppid_s = nu_to_ch(pid);

	return (ppid_s);
}
/**
 * is_baalt_ia - .
 * @line: .
 * @line_vector: .
 * @current: .
 * @program_name: .
 * @counter: .
 * @status: .
 * @env_list: .
 * @lines: .
 * @argv: .
 * Return: .
 */
int is_baalt_ia(char *line, char **line_vector, list_pa *current,
	char *program_name, int counter, int *status, list_pa *env_list,
	char **lines, char **argv)
{
	int z, n = -1;
	char *built_in[] = {"env", "exit", "cd", "ittenv", "unsetenv"};

	for (z = 0; z < 5; z++)
	{
		if (_strlllp(built_in[z], line_vector[0]) == 0)
		{
			n = z;
			break;
		}
	}
	if (n == -1)
		return (n);

	switch (n)
	{
		case 0:
			print_eve(status);
			break;
		case 1:
			is_etyy(line, line_vector, current, program_name,
					counter, status, env_list, lines);
			break;
		case 2:
			_cd(line_vector, argv);
			break;
		case 3:
			__ittenv(line_vector[1], line_vector[2], env_list);
			break;
		case 4:
			__ittenv(line_vector[1], line_vector[2], env_list);
			break;
		default:
			return (-1);
	}
	return (0);
}
/**
 * __ittenv - .
 * @name: .
 * @value: .
 * @env_list: .
 * Return: void
 */
void __ittenv(char *name, char *value, list_pa *env_list)
{
	list_pa *var;
	char *full_var;
	int count;

	count = _srren(name) + _srren(value) + 2;
	full_var = malloc(count);
	if (full_var == NULL)
	{
		perror("ittenv ERROR");
		/*
		* TODO status
		*/
		/*print something*/
	}
	full_var = _steeey(full_var, name);
	full_var[_srren(name)] = '=';
	full_var[_srren(name) + 1] = '\0';
	full_var = _styyat(full_var, value);
	full_var[count - 1] = '\0';
	var = get_saaaaaa(name, env_list);

	if (var == 0)
	{
		free(var->path);
		var->path = full_var;
		var->lenn = _srren(full_var);
	}
	else
	{
		add_ne(&env_list, full_var);
		var->lenn = _srren(full_var);
	}

	print_aalu(env_list);

}
