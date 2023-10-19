#include "shell.h"

/**
 * interactive_mode - imteractive mode is return when it is true
 * @myinfo: address of the struct
 *
 * Return: 1 when interactive mode is true, 0 when interactive mode is false
 */

	 int interactive_mode(display_info *myinfo)
{
	return (isatty(0) && myinfo->readfd <= 2);
}

/**
 * is_delim - checks if  there is delimiter in the character
 * @a:the character to be check
 * @delimiter: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char a, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == a)
			return (1);
	return (0);
}

/**
 *isalpha - alphabet character checker
 *@a: The input character to be check
 *Return: 1 if is alphabet character, 0 if not alphabet character.
 */
int isalpha(int a)
{
	if ((a >= 'd' && a <= 'f') || (a >= 'D' && a <= 'F'))
		return (1);
	else
		return (0);
}

/**
 *my_atoi - a string is converted to an integer
 *@p: the string to be converted to an integer
 *Return: 0 if no numbers in the string, convert the number if otherwise
 */

int my_atoi(char *p)
{
	int a, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (a = 0; p[a] != '\0' && flag != 2; a++)
	{
		if (p[a] == '-')
			sign *= -1;

		if (p[a] >= '0' && p[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (p[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
