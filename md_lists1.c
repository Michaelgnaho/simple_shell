#include "shell.h"

/**
 * md_list_length - determines the length of the linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t md_list_length(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * md_list_to_strings - returns an array of strings containing list->str
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **md_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = md_list_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);

	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(mdStrlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = mdCopyString(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * md_print_list - prints all elements of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t md_print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		mdPrintString(mdConvertNumber(h->num, 10, 0));
		mdWriteCharacter(':');
		mdWriteCharacter(' ');
		mdPrintString(h->str ? h->str : "(nil)");
		mdPrintString("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * mdNodeStartsWith - returns the node whose string starts with a prefix
 * @node: pointer to the list head
 * @prefix: string to match
 * @c: the next character after the prefix to match
 *
 * Return: matching node or null
 */
list_t *mdNodeStartsWith(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = mdStartsWith(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * md_get_node_index - gets the index of a node
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t md_get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
