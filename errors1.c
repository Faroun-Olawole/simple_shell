#include "shell.h"

/**
 *  * errors_atoi - Converts a string to an integer value.
 * @a: The input string to be converted.
 * Return:the converted integer if successful, 0 if no numbers are found,
 * or -1 in case of an error.
 */
	 int errors_atoi(char *a)
{
	int i = 0;
	unsigned long int result = 0;

	if (*a == '+')
		s++; /* TODO: why does this make main return 255? */
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * myprint_error - function is responsible for printing error messages.
 * @myinfo: The structure holding both parameter and return information.
 * @errstr: A string containing the specific error type to be displayed.
 * Return: Returns 0 if there are no numbers in the string, or
 * the converted number if present. Returns -1 in case of an error.
 */

void myprint_error(display_info *myinfo, char *errstr)
{
	_puts(myinfo->file_name);
	_puts(": ");
	print_dec(myinfo->line_count, STDERR_FILENO);
	_puts(": ");
	_puts(myinfo->argv[0]);
	_puts(": ");
	_puts(errstr);
}

/**
 * print_dec - function is responsible for printing an integer
 * number in decimal (base 10).
 * @value: The input integer.
 * @fd: The file descriptor for writing.
 * Return: The number of characters printed.
 */
int print_dec(int value, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _errputchar;
	if (input < 0)
	{
		_abs_ = -value;
		__putchar('-');
		count++;
	}
	else
		_abs_ = value;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * * num_convert - conversion function, serving as a itoa function.
 * @num: The number to be converted.
 * @base: The base for the conversion.
 * @flags: Flags for handling arguments.
 *
 * Return: A string representation of the converted number
 */

char *num_convert(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	{
		array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
		ptr = &buffer[49];
		*ptr = '\0';
	}
	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * comments_remover - remove first instance of '#' with null terminator '\0'.
 * @buf: the address of the string to be modified.
 *
 * Return: Always returns 0.
 */
void comments_remover(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
