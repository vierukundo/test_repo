#include "shell.h"
/**
 * _strcmp - compares too strings
 * @s1: first string
 * @s2: sec string
 * Return: 0
*/

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
	arr[len];
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