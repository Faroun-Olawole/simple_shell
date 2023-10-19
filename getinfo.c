#include "shell.h"

/**
* initialize_display_info - Initializes the display_info structure.
* @myinfo: A pointer to the display_info structure to be initialized.
*/

void initialize_display_info(display_info *myinfo)
{
	myinfo->arg = NULL;
	myinfo->argv = NULL;
	myinfo->path = NULL;
	myinfo->argc = 0;
}

/**
 * set_display_info -  Initialize the display_info structure.
 * @myinfo: Pointer to the display_info struct.
 * @av: Argument vector.
 */
void set_display_info(display_info *myinfo, char **av)
{
	int j = 0;

	myinfo->file_name = av[0];
	if (myinfo->arg)
	{
		myinfo->argv = str_word(myinfo->arg, " \t");
		if (!myinfo->argv)
		{
			myinfo->argv = malloc(sizeof(char *) * 2);
			if (myinfo->argv)
			{
				myinfo->argv[0] = _dup_str(myinfo->arg);
				myinfo->argv[1] = NULL;
			}
		}
		for (j = 0; myinfo->argv && myinfo->argv[j]; j++)
			;
		myinfo->argc = j;

		rep_alias(myinfo);
		rep_vars(myinfo);
	}
}

/**
 * free_display_info - frees resources held by a display_info struct.
 * @myinfo: A pointer to the display_info struct.
 * @all: A boolean flag (true to free all fields).
 */

void free_display_info(display_info *myinfo, int all)
{
	ffree(myinfo->argv);
	myinfo->argv = NULL;
	myinfo->path = NULL;
	if (all)
	{
		if (!myinfo->cmd_buf)
			free(myinfo->arg);
		if (myinfo->env)
			free_node(&(myinfo->env));
		if (myinfo->history)
			free_node(&(myinfo->history));
		if (myinfo->alias)
			free_node(&(myinfo->alias));
		ffree(myinfo->environ);
		myinfo->environ = NULL;
		ptr_free((void **)myinfo->cmd_buf);
		if (myinfo->readfd > 2)
			close(myinfo->readfd);
		_putchar(BUF_FLUSH);
	}
}
