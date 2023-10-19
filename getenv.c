#include "shell.h"

/**
 * get_env_str - Create a copy of the environ string array.
 * @myinfo: contain potential arguments, ensuring a constant prototype.
 *
 * Return: Always returns 0.
 */

char **get_env_str(display_info *myinfo)
{
	if (!myinfo->environ || myinfo->env_changed)
	{
		myinfo->environ = list_to_str(myinfo->env);
		myinfo->env_changed = 0;
	}

	return (myinfo->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @myinfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(display_info *myinfo, char *var)
{
	list_t *node = myinfo->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			myinfo->env_changed = delete_node_index(&(myinfo->env), i);
			i = 0;
			node = myinfo->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (myinfo->env_changed);
}

/**
 * _setenv -  Set or modify an environment variable.
 * @myinfo: potential function arguments to maintain a consistent prototype.
 * @var: The name of the environment variable.
 * @data: The value to assign to the environment variable.
 *
 * Return: Always returns 0.
 */
int _setenv(display_info *myinfo, char *var, char *data)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !data)
	return (0);

	buf = malloc(_lenstr(var) + _lenstr(data) + 2);
	if (!buf)
	return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, data);
	node = myinfo->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			myinfo->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_last(&(myinfo->env), buf, 0);
	free(buf);
	myinfo->env_changed = 1;
	return (0);
}
