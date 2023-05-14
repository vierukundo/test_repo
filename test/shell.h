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

#endif 
