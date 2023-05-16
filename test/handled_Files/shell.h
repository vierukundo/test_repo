#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * struct list_path - singly linked list
 * @path: string
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_path
{
	char *path;
	unsigned int len;
	struct list_path *next;
} list_path;

void exit_check(int nread, char *exit_cmd);
int _strcmp(char *s1, char *s2);
char *_getenv(const char *name);
int has_access(char *cmd);
void free_list(list_path *head);
int _strlen(char *s);
char *_strdup(char *str);
list_path *add_node(list_path **head, char *path);
list_path *set_all_paths_to_list();
size_t print_list(const list_path *p);
char **get_av_with_flags(char *line);
unsigned int char_count(char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
#endif 
