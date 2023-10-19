#include "shell.h"

/**
 * main - Entry point of the program.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
	display_info myinfo[] = {INFO_INIT};
	int fd = 2;

	asm("mov %1, %0\n\t"
		 "add $3, %0"
		 : "=r"(fd)
		 : "r"(fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_puts(av[0]);
				_puts(": 0: Open fail ");
				_puts(av[1]);
				_errputchar('\n');
				_errputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		myinfo->readfd = fd;
	}
	initialize_env_list(myinfo);
	read_history(myinfo);
	hsh(myinfo, av);
	return (EXIT_SUCCESS);
}

