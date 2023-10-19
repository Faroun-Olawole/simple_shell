#include "shell.h"

/**
 * ptr_free - frees memory associated with a pointer and sets it to NULL.
 * @p: The address of the pointer to free.
 *
 * Return: 1 if successfully freed, 0 otherwise.
 */
int ptr_free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
