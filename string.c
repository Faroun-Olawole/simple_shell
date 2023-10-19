#include "shell.h"

/**
 * _lenstr - Calculate the length of a string.
 * @p: The string for which to determine the length.
 *
 * Return: An integer representing the length of the string.
 */

int _lenstr(char *p)
{
	int i = 0;

	if (!p)
		return (0);

	while (*p++)
		i++;
	return (i);
}

/**
 * _strcmp - Compare two strings lexicographically.
 * @p1: The first string.
 * @p2: The second string.
 *
 * Return: A negative value if p1 is lexicographically less than p2,
 *a positive value if p1 is lexicographically greater than p2,
 *or zero if p1 is lexicographically equal to p2.
 */

int _strcmp(char *p1, char *p2)
{
	while (*p1 && *p2)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	if (*p1 == *p2)
		return (0);
	else
		return (*p1 < *p2 ? -1 : 1);
}

/**
 * starts_with - Determines if source_string starts with the substring.
 * @source_string: The string to search within.
 * @substring: The substring to find at the beginning of source_string.
 *
 * Return: the address of next character in source_string
 * after the substring if found; otherwise, returns NULL.
 */

char *starts_with(const char *source_string, const char *substring)
{
	while (*substring)
		if (*substring++ != *source_string++)
			return (NULL);
	return ((char *)source_string);
}

/**
 * _strcat - this function concatenates two strings.
 * @dest: the destination buffer where the result is stored.
 * @src: the source buffer containing the string to be appended.
 *
 * Return: A pointer to the destination buffer.
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

