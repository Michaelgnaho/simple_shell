#include "shell.h"

/**
 * mdIsChainDelimiter - checks if the current character in the buffer
 *						is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of the current position in buf
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise
 */
int mdIsChainDelimiter(md_info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found the end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * mdCheckChain - checks if we should continue chaining based on the
 *					last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of the current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void mdCheckChain(md_info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * mdReplaceAlias - replaces aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int mdReplaceAlias(md_info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = mdNodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = mdStrchr(node->str, '=');
		if (!p)
			return (0);
		p = mdStrdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * mdReplaceVars - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int mdReplaceVars(md_info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!mdStrcmp(info->argv[i], "$?"))
		{
			mdReplaceString(&(info->argv[i]),
				mdStrdup(mdConvertNumber(info->status, 10, 0)));
			continue;
		}
		if (!mdStrcmp(info->argv[i], "$$"))
		{
			mdReplaceString(&(info->argv[i]),
				mdStrdup(mdConvertNumber(getpid(), 10, 0)));
			continue;
		}
		node = mdNodeStartsWith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			mdReplaceString(&(info->argv[i]),
				mdStrdup(mdStrchr(node->str, '=') + 1));
			continue;
		}
		mdReplaceString(&info->argv[i], mdStrdup(""));
	}
	return (0);
}

/**
 * mdReplaceString - replaces a string
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int mdReplaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
