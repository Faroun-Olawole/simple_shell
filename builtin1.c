#include "shell.h"
/**
 * _history - shows history list, displaying line numbers, beginning at 0.
 * @myinfo: holds possible arguments to ensure consistent function prototype.
 * Return: Always returns 0
 */

int _history(display_info *myinfo)
{
	myprint_list(info->history);
	return (0);
}

/**
 * unset_alias - the provided string as an alias.
 * @myinfo: A parameter structure.
 * @str: The string representing the alias.
 *
 * Return: Returns 0 on success and 1 on error.
 */

int unset_alias(display_info *myinfo, char *str)
{
	char *s, p;
	int ret;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	p = *s;
	*s = 0;
	ret = delete_node_index(&(myinfo->alias),
	get_node(myinfo->alias, starts_node(myinfo->alias, str, -1)));
	*s = p;
	return (ret);
}

/**
 * set_alias - Assigns an alias to a given string.
 * @myinfo: A structure containing parameters.
 * @str: The string representing the alias.
 *
 * Return: Returns 0 on success and 1 on error.
 */

int set_alias(display_info *myinfo, char *str)
{
	char *s;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	if (!*++s)
		return (unset_alias(myinfo, str));

	unset_alias(myinfo, str);
	return (add_last(&(myinfo->alias), str, 0) == NULL);
}

/**
 * myprint_alias -function is responsible for displaying an alias string.
 * @node: reference to the alias node
 *
 * Return: Returns 0 upon successful execution, and 1 in the case of an error.
 */

int myprint_alias(list_t *node)
{
	char *s = NULL, *b = NULL;

	if (node)
	{
		s = _strchr(node->str, '=');
		for (b = node->str; b <= s; b++)
		_putchar(*b);
		_putchar('\'');
		_puts(s + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - this function replicates the behavior of the alias.
 * @myinfo: a structure that holds possible arguments
 * Return: Always returns 0
 */

int _alias(display_info *myinfo)
{
	int j = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (myinfo->argc == 1)
	{
		node = myinfo->alias;
		while (node)
		{
			myprint_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; myinfo->argv[j]; j++)
	{
		p = _strchr(myinfo->argv[j], '=');
		if (p)
			set_alias(myinfo, myinfo->argv[j]);
		else
			myprint_alias(starts_node(myinfo->alias, myinfo->argv[j], '='));
	}

	return (0);
}

