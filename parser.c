#include "shell.h"

/**
 * my_cmd - Checks if a file is an executable command.
 * @myinfo: A structure containing information.
 * @path: The file's path.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int my_cmd(display_info *myinfo, char *path)
{
	struct stat st;

	(void)myinfo;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Create a duplicate of a range of characters from a string.
 * @pathstr: The source string.
 * @begin: The starting index of the range.
 * @halt: The ending index of the range.
 *
 * Return: A pointer to a new buffer containing the duplicated characters.
 */

char *dup_chars(char *pathstr, int begin, int halt)
{
	static char buf[1024];
	int j = 0, l = 0;

	for (l = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buf[l++] = pathstr[j];
	buf[l] = 0;
	return (buf);
}

/**
 * find_pathstr - Search for a command within the PATH strings.
 * @myinfo: contains the structure parameter information.
 * @pathstr: The PATH environment variable.
 * @cmd: The command to locate.
 *
 * Return: The full path of the command if found, or NULL if not found.
 */

char *find_pathstr(display_info *myinfo, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_lenstr(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (my_cmd(myinfo, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (my_cmd(myinfo, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
