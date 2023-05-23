#include "shell.h"

/**
 * _strtok - .
 * @str: .
 * @delim: .
 * Return: .
 */
char *_strtok(char *str, const char *delim)
{
	static char *str_begining, *str_begining_cpy;
	unsigned int i;

	if (str != NULL)
		str_begining_cpy = str;
	str_begining = str_begining_cpy;
	if (str_begining == NULL)
		return (NULL);
	for (i = 0; str_begining[i] != '\0'; i++)
	{
		if (_chrCheck(str_begining[i], delim) == 0)
			break;
	}
	if (str_begining_cpy[i] == '\0' || str_begining_cpy[i] == '#')
	{
		str_begining_cpy = NULL;
		return (NULL);
	}
	str_begining = str_begining_cpy + i;
	str_begining_cpy = str_begining;
	for (i = 0; str_begining_cpy[i] != '\0'; i++)
	{
		if (_chrCheck(str_begining_cpy[i], delim) == 1)
			break;
	}
	if (str_begining_cpy[i] == '\0')
		str_begining_cpy = NULL;
	else
	{
		str_begining_cpy[i] = '\0';
		str_begining_cpy = str_begining_cpy + i + 1;
		if (*str_begining_cpy == '\0')
			str_begining_cpy = NULL;
	}
	return (str_begining);
}
/*
*   int main()
*   {
* //char *str = "Cukur Her Yerde <...>";
* char str[] = "Cukur Her Yerde <...>";
* char *token;
*
* token = _strtok(str, " ");
*
* while (token != NULL)
* {
* printf("%s\n", token);
* token = _strtok(NULL, " ");
* }
*
* return 0;
*}
 */


/**
 * _chrCheck - .
 * @c: .
 * @str: .
 * Return: .
 */
unsigned int _chrCheck(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}
