#include "shell.h"

/**
 * my_exit - Exits the shell.
 * @myinfo: A structure containing potential arguments, used to maintain
 * a constant function prototype.
 * Return: Exits the shell with a given exit status. Returns 0 if
 * info.argv[0] is not equal to "exit".
 */
int my_exit(display_info *myinfo)
{
	int exit_check;

	if (myinfo->argv[1]) /* If an arguement exit */
	{
		exit_check = errors_atoi(info->argv[1]);
		if (exit_check == -1)
		{
			myinfo->status = 2;
			myprint_error(myinfo, "wrong number: ");
			_puts(myinfo->argv[1]);
			_errputchar('\n');
			return (1);
		}
		myinfo->error_num = errors_atoi(info->argv[1]);
		return (-2);
	}
	info->error_num = -1;
	return (-2);
}

/**
 * my_cd - Changes the current directory of the process.
 * @myinfo: containing potential arguments of constant function prototype.
 * Return: Always void.
 */
int my_cd(display_info *myinfo)
{
	char *a, *mydir, buffer[1024];
	int chdir_return;

	a = getcwd(buffer, 1024);
	if (!a)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!myinfo->argv[1])
	{
		mydir = _getenv(myinfo, "HOME=");
		if (!mydir)
			chdir_return = /* TODO: what should this be? */
				 chdir((mydir = _getenv(myinfo, "PWD=")) ? mydir : "/");
		else
			chdir_return = chdir(mydir);
	}
	else if (_strcmp(myinfo->argv[1], "-") == 0)
	{
		if (!_getenv(myinfo, "FORMERPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(myinfo, "FORMERPWD=")), _putchar('\n');
		chdir_return = /* TODO: what should this be? */
			 chdir((mydir = _getenv(myinfo, "FORMERPWD=")) ? mydir : "/");
	}
	else
		chdir_return = chdir(myinfo->argv[1]);
	if (chdir_return == -1)
	{
		myprint_error(myinfo, "can't cd to ");
		_puts(myinfo->argv[1]), _errputchar('\n');
	}
	else
	{
		_setenv(myinfo, "FORMERPWD", _getenv(myinfo, "PWD="));
		_setenv(myinfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - Changes the current directory of the process.
 * @myinfo: A structure containing potential arguments
 * used to maintain
 * a consistent function prototype.
 * Return: Always returns 0.
 */
int my_help(display_info *myinfo)
{
	char **argument_array;

	argument_array = myinfo->argv;
	_puts("the Function is not yet implemented and help call works.\n");
	if (0)
		_puts(*argument_array); /* temporary att_unused workaround */
	return (0);
}
