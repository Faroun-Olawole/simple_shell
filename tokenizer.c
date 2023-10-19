#include "shell.h"

/**
 * **str_word - Splits a given string into words, ignoring repeated delimiters
 * @str: The input string to be split.
 * @f: The delimiter string used for splitting.
 * Return: A pointer to an array of strings or NULL in case of failure.
 */
char **str_word(char *str, char *f)
{
	int a, b, k, g, words_num = 0;
	char **u;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!f)
		f = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], f) && (is_delim(str[a + 1], f) || !str[a + 1]))
			words_num++;

	if (words_num == 0)
		return (NULL);
	u = malloc((1 + words_num) * sizeof(char *));
	if (!u)
		return (NULL);
	for (a = 0, b = 0; b < words_num; b++)
	{
		while (is_delim(str[a], f))
			a++;
		k = 0;
		while (!is_delim(str[a + k], f) && str[a + k])
			k++;
		u[b] = malloc((k + 1) * sizeof(char));
		if (!u[b])
		{
			for (k = 0; k < b; k++)
				free(u[k]);
			free(u);
			return (NULL);
		}
		for (g = 0; g < k; g++)
			u[b][g] = str[a++];
		u[b][g] = 0;
	}
	u[b] = NULL;
	return (u);
}

/**
 * **str_word2 - Splits an input string into words using a specified delimiter.
 * @str: The input string to be split.
 * @f: The delimiter used for splitting.
 * Return: A pointer to an array of strings, or NULL if the operation fails.
 */

char **str_word2(char *str, char f)
{
	int a, b, k, g, words_num = 0;
	char **u;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != f && str[a + 1] == f) ||
			 (str[a] != f && !str[a + 1]) || str[a + 1] == f)
			words_num++;
	if (words_num == 0)
		return (NULL);
	u = malloc((1 + words_num) * sizeof(char *));
	if (!u)
		return (NULL);
	for (a = 0, b = 0; b < words_num; b++)
	{
		while (str[a] == f && str[a] != f)
			a++;
		k = 0;
		while (str[a + k] != f && str[a + k] && str[a + k] != f)
			k++;
		u[b] = malloc((k + 1) * sizeof(char));
		if (!u[b])
		{
			for (k = 0; k < b; k++)
				free(u[k]);
			free(u);
			return (NULL);
		}
		for (g = 0; g < k; g++)
			u[b][g] = str[a++];
		u[b][g] = 0;
	}
	u[b] = NULL;
	return (u);
}
