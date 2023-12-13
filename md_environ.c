#include "shell.h"

#include "shell.h"

/**
 * md_display_env - Prints the current environment variables.
 * @md_info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int md_display_env(md_info_t *md_info)
{
	md_print_list(md_info->env);
	return (0);
}

/**
 * md_get_env - Gets the value of a specified environment variable.
 * @md_info: Structure containing potential arguments.
 * @name: Name of the environment variable.
 *
 * Return: The value of the environment variable.
 */
char *md_get_env(md_info_t *md_info, const char *name)
{
	list_t *node = md_info->env;
	char *p;

	while (node)
	{
		p = mdStartsWith(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * md_set_env - Initializes a new environment variable or modifies
 *				an existing one.
 * @md_info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int md_set_env(md_info_t *md_info)
{
	if (md_info->argc != 3)
	{
		md_puts_err("Incorrect number of arguments\n");
		return (1);
	}
	if (md_setenv(md_info, md_info->argv[1], md_info->argv[2]))
		return (0);
	return (1);
}

/**
 * md_unset_env - Removes one or more environment variables.
 * @md_info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int md_unset_env(md_info_t *md_info)
{
	int i;

	if (md_info->argc == 1)
	{
		md_puts_err("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= md_info->argc; i++)
		md_unsetenv(md_info, md_info->argv[i]);

	return (0);
}

/**
 * md_populate_env_list - Populates the linked list of environment variables.
 * @md_info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int md_populate_env_list(md_info_t *md_info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addHistoryNodeEnd(&node, environ[i], 0);
	md_info->env = node;
	return (0);
}
