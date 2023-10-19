#include "shell.h"

/**
 * hsh - Entry point for the main shell loop.
 * @myinfo: A struct containing parameter and return information.
 * @av: The argument vector passed from main()
 *
 * Return: 0 on success, 1 on error, or an error code.
 */
int hsh(display_info *myinfo, char **av)
{
	ssize_t r = 0;
	int builtin_return = 0;

	while (r != -1 && builtin_return != -2)
	{
		reset_display_info(myinfo);
		if (interactive_mode(myinfo))
			_puts("$ ");
		_errputchar(BUF_FLUSH);
		r = get_value(myinfo);
		if (r != -1)
		{
			set_info(myinfo, av);
			builtin_return = check_builtin(myinfo);
			if (builtin_return == -1)
				find_com(myinfo);
		}
		else if (interactive_mode(myinfo))
			_putchar('\n');
		free_display_info(myinfo, 0);
	}
	write_history(myinfo);
	free_display_info(myinfo, 1);
	if (!interactive_mode(myinfo) && myinfo->status)
		exit(myinfo->status);
	if (builtin_return == -2)
	{
		if (myinfo->error_num == -1)
			exit(myinfo->status);
		exit(myinfo->error_num);
	}
	return (builtin_return);
}

/**
 * check_builtin - Search for a built-in command.
 * @myinfo: Contains parameters and return information.
 *
 * Return:
 * -1 if the built-in command is not found.
 * 0 if the built-in command is found and executed successfully.
 * 1 if the built-in command is found but not successful.
 * 2 if the built-in command signals an exit.
 */
int check_builtin(display_info *myinfo)
{

	int j, built_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenviron},
		{"help", _myhelp},
		{"history", _history},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[j].type; j++)
	{
		if (_strcmp(myinfo->argv[0], builtintbl[j].type) == 0)
		{
			myinfo->line_count++;
			built_ret = builtintbl[j].func(myinfo);
			break;
		}
	}
	return (built_ret);
}

/**
 * find_com - Command within the directories listed in PATH.
 * @myinfo: A struct that holds parameter and return information.
 *
 * Return: This function does not return a value.
 */
void find_com(display_info *myinfo)
{
	char *path = NULL;
	int a, b;

	myinfo->path = myinfo->argv[0];
	if (myinfo->flag_linecount == 1)
	{
		myinfo->line_count++;
		myinfo->flag_linecount = 0;
	}
	for (a = 0, b = 0; myinfo->arg[a]; a++)
	{
		if (!is_delim(myinfo->arg[a], " \t\n"))
		{
			b++;
		}
	}
	if (!b)
	{
		return;
	}

	int cat = interactive_mode(myinfo);
	int dog = _getenv(myinfo, "PATH=");
	int camel = myinfo->argv[0][0] == '/';
	int ape = my_cmd(myinfo, myinfo->argv[0]);

	path = find_path(myinfo, dog, myinfo->argv[0]);

	if (path)
	{
		myinfo->path = path;
		cmd_fork(myinfo);
	}
	else
	{
		if ((cat || dog || camel) && ape)
		{
			cmd_fork(myinfo);
		}
		else if (*(myinfo->arg) != '\n')
		{
			myinfo->status = 127;
			myprint_error(myinfo, "not found\n");
		}
	}
}

/**
 * cmd_fork - Create a child process to execute a command.
 * @myinfo: A struct containing parameters and return information.
 *
 * This function forks a child process to execute a command specified by
 * the path and arguments in myinfo. It waits for the child process to
 * complete and handles error cases.
 */
void cmd_fork(display_info *myinfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork error");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(myinfo->path, myinfo->argv, get_env_str(myinfo)) == -1)
		{
			free_display_info(myinfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* Handle execve error (if reached) */
		perror("Execve error");
	}
	else
	{
		wait(&(myinfo->status));
		if (WIFEXITED(myinfo->status))
		{
			myinfo->status = WEXITSTATUS(myinfo->status);
			if (myinfo->status == 126)
				myprint_error(myinfo, "Permission denied\n");
		}
	}
}
