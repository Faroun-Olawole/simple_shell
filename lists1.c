#include "shell.h"

/**
 * list_length -  Calculate the length of a linked list.
 * @t: Pointer to the first node in the list.
 *
 * Return: An integer representing the size of the linked list.
 */
size_t list_length(const list_t *t)
{
	size_t i = 0;

	while (t)
	{
		t = t->next;
		i++;
	}
	return (i);
}

/**
 * list_to_str - Convert a linked list of strings to an array of strings.
 * @hd: Pointer to the first node of the linked list.
 *
 * Return: An array of strings.
 */
char **list_to_str(list_t *hd)
{
	list_t *node = hd;
	size_t i = list_len(hd), j;
	char **strs;
	char *str;

	if (!hd || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_lenstr(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * myprint_list - Print all elements in a linked list of list_t.
 * @t: A pointer to the first node of the list.
 *
 * Return: The number of elements in the list.
 */

size_t myprint_list(const list_t *t)
{
	size_t i = 0;

	while (t)
	{
		_puts(num_convert(t->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(t->str ? t->str : "(nil)");
		_puts("\n");
		t = t->next;
		i++;
	}
	return (i);
}

/**
 * starts_node - returns a node whose string starts with a given prefix.
 * @node: A pointer to the head of the list.
 * @prefix: The string to match as a prefix.
 * @r: The next character after the prefix to match.
 *
 * Return: A matching node or NULL if no match is found.
 */
list_t *starts_node(list_t *node, char *prefix, char r)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((r == -1) || (*p == r)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node - Find the index of a specific node in a list.
 * @hd: A pointer to the list head.
 * @node: A pointer to the node to be located.
 *
 * Return: index of the node if found, or -1 if the node is not in the list.
 */

ssize_t get_node(list_t *hd, list_t *node)
{
	size_t i = 0;

	while (hd)
	{
		if (hd == node)
			return (i);
		hd = hd->next;
		i++;
	}
	return (-1);
}
