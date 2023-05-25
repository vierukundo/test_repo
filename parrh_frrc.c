#include "shell.h"
/**
 * add_ne - a function to modify the path
 * @head: the first node of the path
 * @path: .
 * Return: pointer
 */

list_pa *add_ne(list_pa **head, char *path)
{
	char *s_cpy;
	list_pa *l;

	l = malloc(sizeof(list_pa));
	if (l == NULL)
		return (NULL);

	if (path)
	{
		s_cpy = _stvvvp(path);
		if (s_cpy == NULL)
		{
			free(l);
			return (NULL);
		}
		l->path = s_cpy;
		l->lenn = _srren(s_cpy);
	}
	else
	{
		l->path = NULL;
		l->lenn = 0;
	}
	l->next = (*head);
	*head = l;
	return (l);
}

/**
 * frrr_li - frees a list_t list.
 * @head: pointer to a head pointer
 */
void frrr_li(list_pa *head)
{

	if (head == NULL)
	{
		return;
	}
	frrr_li(head->next);
	if (head->path)
		free(head->path);
	free(head);
}

/**
 * set_al_pls_to_li - .
 * Return: .
 */
list_pa *set_al_pls_to_li()
{
	char *path_variable, *path_var_cpy, *token;
	list_pa *paths_list;

	paths_list = NULL;

	path_variable = _gellnv("PATH");
	if (path_variable == NULL)
		return (NULL);

	path_var_cpy = _stvvvp(path_variable);
	if (path_var_cpy == NULL)
		return (NULL); /*can't cpy*/

	token = _saak(path_var_cpy, ":");
	while (token != NULL)
	{
		add_ne(&paths_list, token);
		token = _saak(NULL, ":");
	}
	free(path_var_cpy);
	return (paths_list); /*does not have access*/
}
/**
 * sxt_al_vor_o_lz - .
 * Return: .
 */
list_pa *sxt_al_vor_o_lz()
{
	char *path_var_cpy;
	list_pa *paths_list;
	int z = 0;

	paths_list = NULL;

	if (environ == NULL)
		return (NULL);
	while (environ[z])
	{
		path_var_cpy = environ[z];
		if (path_var_cpy == NULL)
			return (NULL);
		add_ne(&paths_list, path_var_cpy);
		z++;
	}
	return (paths_list); /*does not have access*/
}

/**
 * crrok_arr - .
 * @line_av_1: .
 * @current: .
 * Return: .
 */

char *crrok_arr(char *line_av_1, list_pa *current)
{
	char *full_path;
	int foend = 0, lenn;

	if (current == NULL)
		return (NULL);
	while (current)
	{
		lenn = _srren(current->path) + _srren(line_av_1) + 2;
		/* to calculate the length of the full path*/
		if (lenn > 1024)
		{
			write(STDERR_FILENO, "ERROR: Path too long\n", 21);
			continue;
		}
		full_path = (char *)malloc(lenn * sizeof(char));
		_steeey(full_path, current->path);
		_styyat(full_path, "/");
		_styyat(full_path, line_av_1);
		if (access(full_path, X_OK) == 0)
		{
			foend = 1;
			break;
		}
		else
			free(full_path);

		current = current->next;
	}
	if (foend)
		return (full_path);

	else
		return (NULL);
}
