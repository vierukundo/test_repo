#include "shell.h"

/**
 * main - Entry point to the shell
 * @argc: arguements count
 * @argv: arguements values
 * @env: environment vector
 * Return: the process
 */
int main(int argc, char *argv[], char *env[])
{
	int mode, counter = 0, *status, t = 0, non_int_count = 1;
	char *line, **line_vector = NULL, **lines = NULL;
	list_pa *current;
	/*mode checking*/
	status = &t;
	mode = chddk_mllo(argc);
	if (mode != INTERACTIVE)
		lines = gat_collands(mode, argv[1], argv[0]);
	current = set_al_pls_to_li();
	while (++counter && non_int_count)
	{
		if (mode == NON_INTERACTIVE_PIPED || mode == NON_INTERACTIVE_FILE)
		{
			if (lines[counter - 1])
				line = lines[counter - 1];
			else
			{
				free(lines);
				break;
			}
		}
		else if (mode == INTERACTIVE)
			line = get_cod_fr_ur(current);
		if (!line)
			continue;
		line_vector = geat_av_wooh_fl(line, *status);
		if (!line_vector)
		{
			free(line);
			continue;
		}
		if (is_dar(line_vector[0], argv, counter, line_vector, status, line) == 0)
			continue;
		if (is_baalt_ia(line, line_vector, current,
			argv[0], counter, status, NULL, lines, argv) != 0)
			is_nat_bqt_i(line_vector, env, status, counter, current, argv);
		free_e_v(line, line_vector);
	}
	frrr_li(current);
	exit(*status);
}
/**
 * print_aalu - print list of strings
 * @p: refrance of list_t "linked list of strings"
 * Return: list size
 */
size_t print_aalu(const list_pa *p)
{
	int size;

	size = 0;
	if (p == NULL)
		return (0);

	while (p)
	{
		if (p->path == NULL)
		{
			printf("[0] (nil)\n");
			fflush(stdout);
		}

		else
		{
			printf("[%d] %s\n", p->lenn, p->path);
			fflush(stdout);
		}

		p = p->next;
		size++;
	}
	return (size);
}


/**
 * sat_luat_eav - print list of strings
 * @p: refrance of list_t "linked list of strings"
 * Return: list size
 */
void sat_luat_eav(list_pa *p)
{
	/*
	*Freeeeeeeeeeeeeeeeeeeeee
	 */
	int size;
	int list_size;
	char **env;

	size = 0;
	if (p == NULL)
		return;
	/*get env count*/
	list_size = evv_lsat_lan(p);
	env = malloc(sizeof(char *) * (list_size));
	if (env == NULL)
	{
		perror("dont have size for env");
		return;
	}
	while (p)
	{
		/*reverce here*/
		if (p->path != NULL)
		{
			env[size++] = p->path;
			p = p->next;
		}

	}
	environ = env;
}


/**
 * evv_lsat_lan - print list of strings
 * @p: refrance of list_t "linked list of strings"
 * Return: list size
 */
size_t evv_lsat_lan(const list_pa *p)
{
	int size;

	size = 0;
	if (p == NULL)
		return (0);

	while (p)
	{

		p = p->next;
		size++;
	}
	if (size - 2 > 0)
		return (size - 2);
	else
		return (0);
}
/**
 * is_nat_bqt_i - Entry point to the shell
 * @line_vector: arguements count
 * @env: arguements values
 * @status: environment vector
 * @counter: arguements count
 * @current: arguements values
 * @argv: environment vector
 */
void is_nat_bqt_i(char **line_vector, char *env[], int *status,
		int counter, list_pa *current, char *argv[])
{
	char *new_path;

	if (access(line_vector[0], X_OK) == 0)
		execute_command(line_vector[0], line_vector, env, status);
	else
	{
		new_path = crrok_arr(line_vector[0], current);
		if (new_path)
		{
			execute_command(new_path, line_vector, env, status);
			free(new_path);
		}
		else
		{
			if (access(line_vector[0], F_OK) == 0)
			{
				priwt_ewwr(argv[0], counter, line_vector[0], PERMISSION_DENIED);
				*status = PERMISSION_DENIED;
			}
			else
			{
				priwt_ewwr(argv[0], counter, line_vector[0], NOT_FOUND);
				*status = NOT_FOUND;
			}
		}
	}
}
