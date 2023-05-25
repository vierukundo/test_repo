#include "shell.h"

/**
 * _srren - returns the length of a string.
 * @s: char pointer
 * Return: the length *s
 */
int _srren(char *s)
{
	int lenn;

	lenn = 0;
	if (s[0] == '\0')
		return (0);

	while (s[lenn] != '\0')
	{
		lenn++;
	}
	return (lenn);
}

/**
 * _strlllp - compares too strings
 * @s1: first string
 * @s2: sec string
 * Return: 0
 */
int _strlllp(char *s1, char *s2)
{
	int z;

	for (z = 0; ((s1[z] != '\0') || (s2[z] != '\0')); z++)
	{
		if (s1[z] - s2[z] != 0)
			return (s1[z] - s2[z]);
	}
	return (0);
}

/**
 * _stvvvp - creates an array of chars
 * @str: array size
 * Return: array refrance or NULL
 */
char *_stvvvp(char *str)
{
	int lenn;
	char *arr;

	if (str == NULL)
		return (NULL);
	lenn = _srren(str);
	arr = malloc((sizeof(char) * lenn) + 1);
	if (arr == NULL)
		return (NULL);
	arr[lenn] = '\0';
	while (lenn--)
		arr[lenn] = str[lenn];
	return (arr);
}

/**
 * _steeey - copies the string pointed
 * @dest: char pointer
 * @src: char pointer
 * Return: char pinter
 */
char *_steeey(char *dest, char *src)
{
	int z;

	for (z = 0; src[z] != '\0'; z++)
	{
		dest[z] = src[z];
	}
	dest[z] = '\0';
	return (dest);
}

/**
 * _styyat - concatenates two strings
 * @dest: char pointer left side
 * @src: char pointer right side
 * Return: the length *s
 */
char *_styyat(char *dest, char *src)
{
	int lenn, z;

	lenn = _srren(dest);
	for (z = 0; src[z] != '\0'; z++)
	{
		dest[lenn + z] = src[z];
	}
	dest[lenn + z] = '\0';
	return (dest);
}
