#include "shell.h"

#include "shell.h"

/**
 * md_clear_info - Initializes md_info_t struct
 * @md_info: Struct address
 */
void md_clear_info(md_info_t *md_info)
{
	md_info->arg = NULL;
	md_info->argv = NULL;
	md_info->path = NULL;
	md_info->argc = 0;
}

/**
 * md_set_info - Initializes md_info_t struct
 * @md_info: Struct address
 * @av: Argument vector
 */
void md_set_info(md_info_t *md_info, char **av)
{
	int i = 0;

	md_info->fname = av[0];
	if (md_info->arg)
	{
		md_info->argv = strtow(md_info->arg, " \t");
		if (!md_info->argv)
		{
			md_info->argv = malloc(sizeof(char *) * 2);
			if (md_info->argv)
			{
				md_info->argv[0] = _strdup(md_info->arg);
				md_info->argv[1] = NULL;
			}
		}
		for (i = 0; md_info->argv && md_info->argv[i]; i++)
			;
		md_info->argc = i;

		replace_alias(md_info);
		replace_vars(md_info);
	}
}

/**
 * md_free_info - Frees md_info_t struct fields
 * @md_info: Struct address
 * @all: True if freeing all fields
 */
void md_free_info(md_info_t *md_info, int all)
{
	ffree(md_info->argv);
	md_info->argv = NULL;
	md_info->path = NULL;
	if (all)
	{
		if (!md_info->cmd_buf)
			free(md_info->arg);
		if (md_info->env)
			free_list(&(md_info->env));
		if (md_info->history)
			free_list(&(md_info->history));
		if (md_info->alias)
			free_list(&(md_info->alias));
		ffree(md_info->environ);
		md_info->environ = NULL;
		bfree((void **)md_info->cmd_buf);
		if (md_info->md_readfd > 2)
			close(md_info->md_readfd);
		_putchar(BUF_FLUSH);
	}
}
