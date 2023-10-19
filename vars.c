#include "shell.h"

/**
 * is_chain - the current character in the buffer is a chain delimiter.
 * @myinfo: A structure containing parameters and context information.
 * @buf: A character buffer.
 * @c: A pointer to the current position within the buffer.
 *
 * Return: Returns 1 if the character is a chain delimiter, and 0 otherwise.
 */
int is_chain(display_info *myinfo, char *buf, size_t *c)
{
	size_t i = *c;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		myinfo->cmd_buf_type = CMD_OR;
	}
	else if (buf[i] == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		myinfo->cmd_buf_type = CMD_AND;
	}
	else if (buf[i] == ';') /* found the end of this command */
	{
		buf[i] = 0; /* null to replace semicolon*/
		myinfo->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*c = i;
	return (1);
}

/**
 * chain_check - the chain should continue based on the last execution status.
 * @myinfo: A structure containing function parameters.
 * @buf: The character buffer.
 * @c: A pointer to the current position in buf.
 * @j: The starting position in buf.
 * @length: The length of buf.
 *
 * Return: does not return a value (void).
 */
void chain_check(
	display_info *myinfo,
	char *buf,
	size_t *c,
	size_t j,
	size_t length
	)
{
	size_t i = *c;

	if (myinfo->cmd_buf_type == CMD_AND)
	{
		if (myinfo->status)
		{
			buf[j] = 0;
			i = length;
		}
	}
	if (myinfo->cmd_buf_type == CMD_OR)
	{
		if (!myinfo->status)
		{
			buf[j] = 0;
			i = length;
		}
	}

	*c = i;
}

/**
 * rep_alias - substitutes aliases within the tokenized string.
 * @myinfo: A struct containing parameters.
 *
 * Return: 1 if an alias is successfully replaced, 0 otherwise.
 */
int rep_alias(display_info *myinfo)
{
	int j;
	list_t *node;
	char *c;

	for (j = 0; j < 10; j++)
	{
		node = starts_with(myinfo->alias, &myinfo->argv[0], '=');
		if (!node)
			return (0);
		free(myinfo->argv[0]);
		c = _strchr(node->str, '=');
		if (!c)
			return (0);
		c = _dup_str(c + 1);
		if (!c)
			return (0);
		myinfo->argv[0] = c;
	}
	return (1);
}

/**
 * rep_vars - replaces variables in a tokenized string
 * @myinfo: A structure containing parameters and information
 *
 * Return: 1 if replacements are made, 0 otherwise
 */
int rep_vars(display_info *myinfo)
{
	int i = 0;
	list_t *node;

	for (i = 0; myinfo->argv[i]; i++)
	{
		if (myinfo->argv[i][0] != '$' || !myinfo->argv[i][1])
			continue;

		if (!_strcmp(myinfo->argv[i], "$?"))
		{
			replace_string(&(myinfo->argv[i]),
								_dup_str(num_convert(myinfo->status, 10, 0)));
			continue;
		}
		if (!_strcmp(myinfo->argv[i], "$$"))
		{
			replace_string(&(myinfo->argv[i]),
								_dup_str(num_convert(getpid(), 10, 0)));
			continue;
		}
		node = starts_with(myinfo->env, &myinfo->argv[i][1], '=');
		if (node)
		{
			replace_string(&(myinfo->argv[i]),
								_dup_str(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&myinfo->argv[i], _dup_str(""));
	}
	return (0);
}

/**
 * replace_string - for replacing string.
 * @oldstr: Pointer to the old string.
 * @newstr: The replacement(new) string.
 * Return: 1 if replacements were made, 0 otherwise.
 */
int replace_string(char **oldstr, char *newstr)
{
	free(*oldstr);
	*oldstr = newstr;
	return (1);
}
