#include "shell.h"

/**
 **copy_str - Copy a string to a destination string.
 * @des: The destination string to which data will be copied.
 * @src: The source string containing the data to be copied.
 * @m: The number of characters to copy from source to destination.
 *
 * Return: The destination string after copying the specified characters.
 */
char *copy_str(char *des, char *src, int m)
{
	int u, v;
	char *s = des;

	u = 0;
	while (src[u] != '\0' && u < m - 1)
	{
		des[u] = src[u];
		u++;
	}
	if (u < m)
	{
		v = u;
		while (v < m)
		{
			des[v] = '\0';
			v++;
		}
	}
	return (s);
}

/**
 **_strncat - Concatenates two strings with a specified maximum length.
 * @des: The first string.
 * @src: The source string to be appended.
 * @m: The maximum number of bytes to append from src.
 * Return: A pointer to the concatenated string (des).
 */

char *_strncat(char *des, char *src, int m)
{
	int u, v;
	char *s = des;

	u = 0;
	v = 0;
	while (des[u] != '\0')
		u++;
	while (src[v] != '\0' && v < m)
	{
		des[u] = src[v];
		u++;
		v++;
	}
	if (v < m)
		des[u] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@b: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char b)
{
	do	{
		if (*s == b)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
