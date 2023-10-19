#include "shell.h"

/**
 * interactive_mode - interactive mode will be returned if it is true.
 * @myinfo: struct address
 *
 * Return: 1 will be returned if interactive mode is true, 0 if interactive mode is false
 */

	 int interactive_mode(display_info *myinfo)
{
	return (isatty(0) && myinfo->readfd <= 2);
}

/**
<<<<<<< HEAD
 * is_delim - checks character if  there is delimter.
 * @a: check character.
 * @delimter: delimeter string.
=======
 * is_delim - checks if  there is delimiter in the character
 * @a:the character to be check
 * @delimiter: the delimiter string
>>>>>>> 29d52a7574689549691d3fe9f49a1de6ffb372ab
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
<<<<<<< HEAD
 *isalpha - check alphabetic character.
 *@a: theinput character to be checked.
 *Return: 1 if it is alphabetic character, 0 if it is not alphabetic character.
=======
 *isalpha - alphabet character checker
 *@a: The input character to be check
 *Return: 1 if is alphabet character, 0 if not alphabet character.
>>>>>>> 29d52a7574689549691d3fe9f49a1de6ffb372ab
 */
int isalpha(int a)
{
	if ((a >= 'd' && a <= 'f') || (a >= 'D' && a <= 'F'))
		return (1);
	else
		return (0);
}

/**
 *my_atoi - an integer to be convert to a string.
 *@p: the string to be converted to an integer.
 *Return: 0 if there's no numbers in the string, convert the number if otherwise.
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
