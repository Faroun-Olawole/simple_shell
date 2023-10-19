#include "shell.h"

/**
 * get_history - Fetch the history file.
 * @myinfo: The structure containing parameters.
 *
 * Return: An allocated string containing the history file.
 */
char *get_history(display_info *myinfo)
{
	char *buf, *dir;

	dir = _getenv(myinfo, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_lenstr(dir) + _lenstr(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - Create a new file or append to an existing one.
 * @myinfo: The parameter struct containing relevant information.
 *
 * Return: 1 on success, or -1 on failure.
 */
int write_history(display_info *myinfo)
{
	ssize_t fd;
	char *filename = get_history(myinfo);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = myinfo->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist - Read and load the command history from a file.
 * @myinfo: A structure containing relevant parameters.
 *
 * Return: histcount entries on success, or 0 on failure.
 */

int read_hist(display_info *myinfo)
{
	int j, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history(myinfo);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (j = 0; j < fsize; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			build_hist_list(myinfo, buf + last, linecount++);
			last = j + 1;
		}
	if (last != j)
		build_hist_list(myinfo, buf + last, linecount++);
	free(buf);
	myinfo->histcount = linecount;
	while (myinfo->histcount-- >= HIST_MAX)
		delete_node_index(&(myinfo->history), 0);
	renum_hist(myinfo);
	return (myinfo->histcount);
}

/**
 * build_hist_list - adds entry to a linked list representing history.
 * @myinfo: Structure holding relevant information.
 * @buf: The buffer containing the command to be added to the history.
 * @linecount: The current linecount or histcount.
 *
 * Return: Always returns 0.
 */
int build_hist_list(display_info *myinfo, char *buf, int linecount)
{
	list_t *node = NULL;

	if (myinfo->history)
		node = myinfo->history;
	add_last(&node, buf, linecount);

	if (!myinfo->history)
		myinfo->history = node;
	return (0);
}

/**
 * renum_hist - Update the numbering of entries in the history after changes.
 * @myinfo: A structure containing possible arguments.
 *
 * Return: The new histcount.
 */
int renum_hist(display_info *myinfo)
{
	list_t *node = myinfo->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (myinfo->histcount = i);
}
