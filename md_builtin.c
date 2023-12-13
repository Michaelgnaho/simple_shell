#include "shell.h"

/**
 * md_display_history - Displays the command history, showing each command
 *                      with its corresponding line number.
 * @md_info: Structure containing potential arguments.
 *
<<<<<<< HEAD
 * Return: Always 0
=======
 * Return: Exits with a given exit status (0) if md_info->argv[0] != "exit".
>>>>>>> 32aa8b7a71c94dab6a1a137bae5faf735e1a6ddf
 */
int md_display_history(md_info_t *md_info)
{
<<<<<<< HEAD
	print_list(md_info->history);
	return 0;
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

	p = _strchr(str, '=');
	if (!p)
		return 1;

	ret = delete_node_at_index(&(md_info->alias),
				   get_node_index(md_info->alias, node_starts_with(md_info->alias, str, -1)));
	return ret;
}

/**
 * md_set_alias - Sets an alias in the alias list.
 * @md_info: Parameter struct.
 * @str: The string representing the alias.
 *
 * Return: 0 on success, 1 on error
=======
	int exit_check;

	if (md_info->argv[1])  /* If there is an exit argument */
	{
		exit_check = md_erratoi(md_info->argv[1]);
		if (exit_check == -1)
		{
			md_info->status = 2;
			md_print_error(md_info, "Illegal number: ");
			md_puts_err(md_info->argv[1]);
			md_put_err_char('\n');
			return (1);
		}
		md_info->err_num = md_erratoi(md_info->argv[1]);
		return (-2);
	}
	md_info->err_num = -1;
	return (-2);
}

/**
 * md_cd - changes the current directory of the process
 * @md_info: Structure containing potential arguments.
 *
 * Return: Always 0
>>>>>>> 32aa8b7a71c94dab6a1a137bae5faf735e1a6ddf
 */
int md_set_alias(md_info_t *md_info, char *str)
{
<<<<<<< HEAD
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return 1;

	if (!*++p)
		return md_unset_alias(md_info, str);

	md_unset_alias(md_info, str);
	return (add_node_end(&(md_info->alias), str, 0) == NULL);
=======
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		mdPrintString("TODO: >>getcwd failure emsg here<<\n");

	if (!md_info->argv[1])
	{
		dir = md_get_env(md_info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = md_get_env(md_info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (mdStrcmp(md_info->argv[1], "-") == 0)
	{
		if (!md_get_env(md_info, "OLDPWD="))
		{
			mdPrintString(s);
			mdWriteCharacter('\n');
			return (1);
		}
		mdPrintString(md_get_env(md_info, "OLDPWD="));
		mdWriteCharacter('\n');
		chdir_ret = chdir((dir = md_get_env(md_info, "OLDPWD=")) ? dir : "/");
	}
	else
	{
		chdir_ret = chdir(md_info->argv[1]);
	}

	if (chdir_ret == -1)
	{
		md_print_error(md_info, "can't cd to ");
		md_puts_err(md_info->argv[1]);
		md_put_err_char('\n');
	}
	else
	{
		md_setenv(md_info, "OLDPWD", md_get_env(md_info, "PWD="));
		md_setenv(md_info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
>>>>>>> 32aa8b7a71c94dab6a1a137bae5faf735e1a6ddf
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
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return 0;
	}
	return 1;
}

/**
 * md_alias - Mimics the alias builtin in a shell.
 * @md_info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int md_alias(md_info_t *md_info)
{
<<<<<<< HEAD
	int i = 0;
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
		return 0;
	}

	for (i = 1; md_info->argv[i]; i++)
	{
		p = _strchr(md_info->argv[i], '=');
		if (p)
			md_set_alias(md_info, md_info->argv[i]);
		else
			md_print_alias(node_starts_with(md_info->alias, md_info->argv[i], '='));
	}

	return 0;
=======
	char **arg_array;

	arg_array = md_info->argv;
	mdPrintString("help call works. Function not yet implemented \n");

	if (0)
		mdPrintString(*arg_array); /* temp att_unused workaround */

	return (0);
>>>>>>> 32aa8b7a71c94dab6a1a137bae5faf735e1a6ddf
}

