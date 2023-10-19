#include "shell.h"

/**
 * input_buffer - This function buffers chained commands and reads input.
 *
 * @myinfo: A structure containing parameters and information.
 * @buf: The address of the buffer used for input.
 * @len: The address of the length variable, which is updated by this function.
 *
 * Return: The number of bytes read.
 */
ssize_t input_buffer(display_info *myinfo, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*ptr_free((void **)myinfo->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(myinfo, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			myinfo->flag_linecount = 1;
			comments_remover(*buf);
			build_hist_list(myinfo, *buf, myinfo->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				myinfo->cmd_buffer = buf;
			}
		}
	}
	return (r);
}

/**
 * get_value - Reads a line of text, excluding the newline character.
 * @myinfo: A structure containing function parameters.
 *
 * Return: The number of bytes read from the input.
 */
ssize_t get_value(display_info *myinfo)
{
	static char *buf; /* chain buffer ';' command  */
	static size_t u, v, len;
	ssize_t r = 0;
	char **buf_p = &(myinfo->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(myinfo, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* commands left in the chain buffer */
	{
		v = u;		 /* init new iterator to buf current position */
		p = buf + u; /* get pointer for return */

		chain_check(myinfo, buf, &v, u, len);
		while (v < len) /* iterate to semicolon or end */
		{
			if (is_chain(myinfo, buf, &v))
				break;
			v++;
		}

		u = v + 1;	  /* past nulled increment ';'' */
		if (u >= len) /* reached end of buffer? */
		{
			u = len = 0; /* reset position and length */
			myinfo->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;				/* pass back pointer to current command position */
		return (_lenstr(p)); /* return the length of the current command */
	}

	*buf_p = buf; /* If not a chain, return the buffer obtain from _getline(). */
	return (r); /* Return the size of the buffer obtained from _getline() */
}

/**
 * read_buf - Read data into a buffer.
 * @myinfo: The parameter struct containing information.
 * @buffer: The buffer to read data into.
 * @i: The size of the data to read.
 *
 * Return: r
 */
ssize_t read_buf(display_info *myinfo, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(myinfo->readfd, buffer, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _mygetline - Read the next line of input from STDIN.
 * @myinfo: A structure containing function parameters.
 * @ptr: address of a pointer to a buffer, which can be preallocated or NULL.
 * @length: The size of the preallocated buffer, if provided.
 *
 * Return: The read line as a string, or NULL on error.
 */

int _mygetline(display_info *myinfo, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_d = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = buf_read(myinfo, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_d = mem_realloc(p, s, s ? s + k : k + 1);
	if (!new_d) /* MALLOC FAILED! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_d, buf + i, k - i);
	else
		copy_str(new_d, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_d;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @signal_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

