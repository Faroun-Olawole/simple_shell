#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: The destination where the duplicated string is stored.
 * @src: The source string to be duplicated.
 *
 * Return: A pointer to the destination string.
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _dup_str - duplicates a string
 * @s: The string to be duplicated.
 *
 * Return: A pointer to the duplicated string.
 */

char *_dup_str(const char *s)
{
	int size = 0;
	char *ret;

	if (s == NULL)
		return (NULL);
	while (*s++)
		size++;
	ret = malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	for (size++; size--;)
		ret[size] = *--s;
	return (ret);
}

/**
 * _puts - prints the specified string
 * @s: The string to be printed
 *
 * Return: Nothing
 */

void _puts(char *s)
{
	int a = 0;

	if (!s)
		return;
	while (s[a] != '\0')
	{
		_putchar(s[a]);
		a++;
	}
}

/**
 * _putchar - Outputs a character to the standard output (stdout).
 * @a: The character to be printed
 *
 * Return: Returns 1 on success.
 * On error, -1 is returned, and errno is set as needed.
 */

int _putchar(char a)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (a != BUF_FLUSH)
		buf[i++] = a;
	return (1);
}
