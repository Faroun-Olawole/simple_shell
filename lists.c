#include "shell.h"

/**
 * add_node_list - Add a node to the beginning of the list.
 * @hd: A pointer to the head node pointer.
 * @str: The string field for the new node.
 * @num: The node index used in history.
 *
 * Return: The size of the updated list.
 */
list_t *add_node_list(list_t **hd, const char *str, int num)
{
	list_t *head_new;

	if (!hd)
		return (NULL);
	head_new = malloc(sizeof(list_t));
	if (!head_new)
		return (NULL);
	_mem_set((void *)head_new, 0, sizeof(list_t));
	head_new->num = num;
	if (str)
	{
		head_new->str = _dup_str(str);
		if (!head_new->str)
		{
			free(head_new);
			return (NULL);
		}
	}
	head_new->next = *hd;
	*hd = head_new;
	return (head_new);
}

/**
 * add_last - Appends a new node to the end of the linked list.
 * @hd: A pointer to the head of the linked list.
 * @str: The string value to be stored in the new node.
 * @num: An index used for history tracking.
 *
 * Return: The size of the updated linked list.
 */
list_t *add_last(list_t **hd, const char *str, int num)
{
	list_t *node_new, *node;

	if (!hd)
		return (NULL);

	node = *hd;
	node_new = malloc(sizeof(list_t));
	if (!node_new)
		return (NULL);
	_mem_set((void *)node_new, 0, sizeof(list_t));
	node_new->num = num;
	if (str)
	{
		node_new->str = _dup_str(str);
		if (!node_new->str)
		{
			free(node_new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = node_new;
	}
	else
		*hd = node_new;
	return (node_new);
}

/**
 * print_str_list - Print only the "str" elements from a list of type list_t.
 * @a: A pointer to the first node of the linked list.
 *
 * Return: The size of the list.
 */
size_t print_str_list(const list_t *a)
{
	size_t i = 0;

	while (a)
	{
		_puts(a->str ? a->str : "(nil)");
		_puts("\n");
		a = a->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_index - Remove a node at a specified index.
 * @hd: A pointer to the address of the first node.
 * @index: The index of the node to be deleted.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_index(list_t **hd, unsigned int index)
{
	list_t *node, *node_prev;
	unsigned int i = 0;

	if (!hd || !*hd)
		return (0);

	if (!index)
	{
		node = *hd;
		*hd = (*hd)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *hd;
	while (node)
	{
		if (i == index)
		{
			node_prev->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		node_prev = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_node - Release memory occupied by all nodes in a linked list.
 * @hd_ptr: Pointer to the address of the head node.
 *
 * Return: void
 */
void free_node(list_t **hd_ptr)
{
	list_t *node, *node_next, *hd;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd = *hd_ptr;
	node = hd;
	while (node)
	{
		node_next = node->next;
		free(node->str);
		free(node);
		node = node_next;
	}
	*hd_ptr = NULL;
}

