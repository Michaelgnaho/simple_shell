#include "shell.h"


/**
 * md_display_history - Displays the command history, showing each command
 *                      with its corresponding line number.
 * @md_info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int md_display_history(md_info_t *md_info)
{
	md_print_list(md_info->history);
	return (0);
}

/**
 * md_unset_alias - Removes an alias from the alias list.
 * @md_info: Parameter struct.
 * @str: The string representing the alias.
 *
 * Return: 0 on success, 1 on error
 */
int md_unset_alias(md_info_t *md_info, char *str)
{
	char *p;
	int ret;

	p = mdStrchr(str, '=');
	if (!p)
		return (1);
	ret = deleteCommandAtIndex(&(md_info->alias), md_get_node_index(md_info->alias,
			mdNodeStartsWith(md_info->alias, str, -1)));
	return (ret);
}

/**
 * md_set_alias - Sets an alias in the alias list.
 * @md_info: Parameter struct.
 * @str: The string representing the alias.
 *
 * Return: 0 on success, 1 on error
 */
int md_set_alias(md_info_t *md_info, char *str)
{
	char *p;

	p = mdStrchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (md_unset_alias(md_info, str));

	md_unset_alias(md_info, str);
	return (addHistoryNodeEnd(&(md_info->alias), str, 0) == NULL);
}

/**
 * md_print_alias - Prints an alias string.
 * @node: The alias node.
 *
 * Return: 0 on success, 1 on error
 */
int md_print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = mdStrchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			mdWriteCharacter(*a);
		mdWriteCharacter('\'');
		mdPrintString(p + 1);
		mdPrintString("'\n");
		return (0);
	}
	return (1);
}

/**
 * md_alias - Mimics the behavior of the alias builtin in a shell.
 * @md_info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int md_alias(md_info_t *md_info)
{
	int i = (0);
	char *p = NULL;
	list_t *node = NULL;

	if (md_info->argc == 1)
	{
		node = md_info->alias;
		while (node)
		{
			md_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; md_info->argv[i]; i++)
	{
		p = mdStrchr(md_info->argv[i], '=');
		if (p)
			md_set_alias(md_info, md_info->argv[i]);
		else
			md_print_alias(mdNodeStartsWith(md_info->alias, md_info->argv[i], '='));
	}

	return (0);
}
