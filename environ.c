#include "shell.h"

/**
 * _myenviron - function to prints the current environment settings.
 * @myinfo: A structure that holds potential arguments
 * Return: Always returns 0
 */
int _myenviron(display_info *myinfo)
{
	print_str_list(myinfo->env);
	return (0);
}

/**
 * _getenv -gets the value of an environ variable.
 * @myinfo: A structure that holds potential arguments
 * @var: The name of the environment variable.
 *
 * Return: The value of the specified environment variable.
 */
char *_getenv(display_info *myinfo, const char *var)
{
	list_t *node = myinfo->env;
	char *s;

	while (node)
	{
		s = starts_with(node->str, var);
		if (s && *s)
			return (s);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setenv - set a new environment variable,
 * or modify an existing one
 * @myinfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int _setenv(display_info *myinfo)
{
	if (myinfo->argc != 3)
	{
		_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(myinfo, myinfo->argv[1], myinfo->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenv -  remove  an environ variable.
 * @myinfo: A structure arguments, ensuring a consistent function prototype.
 * Return: Always returns 0
 */
int _unsetenv(display_info *myinfo)
{
	int j;

	if (myinfo->argc == 1)
	{
		_puts("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= myinfo->argc; j++)
		_unsetenv(myinfo, myinfo->argv[j]);

	return (0);
}

/**
 * initialize_env_list - initializes the environmental variable linked list
 * @myinfo: A structure that holds potential arguments
 * Return: Always returns 0
 */

int initialize_env_list(display_info *myinfo)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_last(&node, environ[j], 0);
	myinfo->env = node;
	return (0);
}
