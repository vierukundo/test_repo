#include "shell.h"

/*prototypes*/
void exit_check(int nread, char* exit_cmd);
int _strcmp(char *s1, char *s2);
char *_getenv(const char *name);
int has_access(char * cmd);
void free_list(list_path *head);
int _strlen(char *s);
char *_strdup(const char *str);
list_path *add_node(list_path **head, const char *path);
list_path *set_all_paths_to_list();
size_t print_list(const list_path *p);


int main(int argc, char *argv[], char *env[])
{
    int pid;
    ssize_t nread;
    char *line;
    size_t n;
    char *av[] = {NULL};
    char *en[] = {NULL};
    list_path *list_of_paths;
    
    list_of_paths = set_all_paths_to_list();
    if(list_of_paths == NULL)
    {
        write(STDERR_FILENO, "ERROR", 5);
        exit(127);
    }
    
    if (isatty(STDIN_FILENO))
    {
        while (1)
        {
            write(STDOUT_FILENO, "^_* -> ", 7);
            nread = getline(&line, &n, stdin);
            exit_check(nread, line);
            
            line[nread - 1] = '\0';

            if(access(line, X_OK) == 0)
                pid = fork();
            else
            {
                write(STDERR_FILENO, argv[0], sizeof(argv[0]));
                write(STDERR_FILENO, ": No such file or directory\n", 28);

            }
            if(pid != 0)
            {
                wait(NULL);
            }
            if(pid == 0)
            {
                printf("im child");
                fflush(stdout);
                execve(line, av, en);
            }
            
        }
    }

    /*
        TODO FREE
    */
    return (0);
}


void exit_check(int nread, char* exit_cmd)
{
	if(nread == EOF)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	if (_strcmp(exit_cmd, "exit\n") == 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
}

int has_access(char * cmd)
{
    char *path;
    
    path = _getenv("PATH");
    if(path == NULL)
        return (-1);/*var PATH not exists*/
    

    
    
    
    return (-1);/*does not have access*/
}

list_path *set_all_paths_to_list()
{
    char *path_variable, *path, *path_var_cpy, *token;
    list_path *paths_list;
    
    paths_list = NULL;
    path_variable = _getenv("PATH");
    if(path_variable == NULL)
        return (NULL);
    
    path_var_cpy = _strdup(path_variable);
    if (path_var_cpy == NULL)
        return (NULL);/*can't cpy*/
	
    token = strtok(path_var_cpy, ":");
    while (token != NULL) {
        add_node(&paths_list, token);
        token = strtok(NULL, ":");
    }
    
    return (paths_list);/*does not have access*/
}
int _strcmp(char *s1, char *s2)
{
	int i;
	for (i = 0; ((s1[i] != '\0') || (s2[i] != '\0')); i++)
	{
		if (s1[i] - s2[i] != 0)
			return (s1[i] - s2[i]);
	}
	return (0);

}


char *_getenv(const char *name)
{
	int i = 0, j = 0;
    extern char **environ;

	if (name == NULL)
		return (NULL);
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] != '=')
		{
			if(environ[i][j] != name[j])
				break;
			if(environ[i][j] == name[j] && (environ[i][j+1] == '='))
				return (&environ[i][strlen(name) + 1]);
			j++;
		}
		i++;
	}
	return (NULL);
}


list_path *add_node(list_path **head, const char *path)
{
	char *s_cpy;
	list_path *l;

	l = malloc(sizeof(list_path));
	if (l == NULL)
		return (NULL);

	if (path)
	{
		s_cpy = _strdup(path);
		if (s_cpy == NULL)
		{
			free(l);
			return (NULL);
		}
		l->path = s_cpy;
		l->len = _strlen(s_cpy);
	}
	else
	{
		l->path = NULL;
		l->len = 0;
	}
	l->next = (*head);
	*head = l;
	return (l);
}

/**
 * _strdup - creates an array of chars
 * @str: array size
 * Return: array refrance or NULL
 */
char *_strdup(const char *str)
{
	int len;
	char *arr;

	if (str == NULL)
		return (NULL);
	len = strlen(str);
	arr = malloc((sizeof(char) * len) + 1);
	if (arr == NULL)
		return (NULL);
	while (len--)
		arr[len] = str[len];
	return (arr);
}

/**
 * _strlen - returns the length of a string.
 * @s: char pointer
 * Return: the length *s
 */
int _strlen(char *s)
{
	int len;

	len = 0;
	if (s[0] == '\0')
		return (0);

	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

/**
 * free_list - frees a list_t list.
 * @head: pointer to a head pointer
 */
void free_list(list_path *head)
{

	if (head == NULL)
	{
		return;
	}
	free_list(head->next);
	if (head->path)
		free(head->path);
	free(head);
}


/**
 * print_list - print list of strings
 * @h: refrance of list_t "linked list of strings"
 * Return: list size
 */
size_t print_list(const list_path *p)
{
	int size;

	size = 0;
	if (p == NULL)
		return (0);

	while (p)
	{
		if (p->path == NULL)
			printf("[0] (nil)\n");
		else
			printf("[%d] %s\n", p->len, p->path);
		p = p->next;
		size++;
	}
	return (size);
}
