#include "shell.h"

/**
 * _mem_set - Fills a memory area with a specific byte.
 * @s: A pointer to the memory area to be filled.
 * @a: The byte value to fill the memory area with.
 * @n: The number of bytes to be filled.
 *
 * Return: A pointer to the memory area (dest).
 */
char *_mem_set(char *s, char a, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = a;
	return (s);
}

/**
 * free_str - Deallocates memory for an array of strings.
 * @yy: The array of strings to be deallocated.
 */
void free_str(char **yy)
{
	char **a = yy;

	if (!yy)
		return;
	while (*yy)
		free(*yy++);
	free(a);
}

/**
 * mem_realloc - Reallocates a memory block.
 * @ptr: A pointer to the previously allocated memory block.
 * @size_old: The size in bytes of the previous block.
 * @size_new: The desired size in bytes of the new block.
 *
 * Return: A pointer to the reallocated memory block.
 */
void *mem_realloc(void *ptr, unsigned int size_old, unsigned int size_new)
{
	char *p;

	if (!ptr)
		return (malloc(size_new));
	if (!size_new)
		return (free(ptr), NULL);
	if (size_new == size_old)
		return (ptr);

	p = malloc(size_new);
	if (!p)
		return (NULL);

	size_old = size_old < size_new ? size_old : size_new;
	while (size_old--)
		p[size_old] = ((char *)ptr)[size_old];
	free(ptr);
	return (p);
}
