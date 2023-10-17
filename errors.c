#include "shell.h"

/**
 * _puts - function outputs a given string to the standard output.
 * @str: The string to be printed.
 *
 * Return: This function does not return a value.
 */

	 void _puts(char *str)
{
	int l = 0;

	if (!str)
		return;
	while (str[l] != '\0')
	{
		_errputchar(str[l]);
		l++;
	}
}

/**
 * _errputchar - Outputs the char 'a' to the standard error stream (stderr).
 * @a: The character to be printed
 *
 * Return: Returns 1 on success,
 * if an error occurs, it returns -1, and errno is set accordingly
 */

int _errputchar(char a)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (a != BUF_FLUSH)
		buf[i++] = a;
	return (1);
}

/**
 * _putfd - Outputs a character 'a' to the specified file descriptor 'fd'.
 * @a: The character to be written
 * @fd: The target file descriptor for writing
 *
 * Return: Returns 1 on success. On an error, it returns -1,
 * and the error indicator (errno) is set accordingly.
 */
int _putfd(char a, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (a != BUF_FLUSH)
		buf[i++] = a;
	return (1);
}

/**
 * _putsfd - function writes the provided str to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor for writing.
 *
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
	int l = 0;

	if (!str)
		return (0);
	while (*str)
	{
		l += _putfd(*str++, fd);
	}
	return (l);
}
