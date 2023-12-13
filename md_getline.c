#include "shell.h"


/**
 * md_input_buffer - buffers chained commands
 * @md_info: structure containing shell information
 * @buf: address of buffer
 * @len: address of len variable
 *
 * Return: bytes read
 */
ssize_t md_input_buffer(md_info_t *md_info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, md_sigint_handler);

#if USE_GETLINE
		bytes_read = getline(buf, &len_p, stdin);
#else
		bytes_read = md_get_line(md_info, buf, &len_p);
#endif

		if (bytes_read > 0)
		{
			if ((*buf)[bytes_read - 1] == '\n')
			{
				(*buf)[bytes_read - 1] = '\0'; /* remove trailing newline */
				bytes_read--;
			}

			md_info->linecount_flag = 1;
			md_remove_comments(*buf);
			md_build_history_list(md_info, *buf, md_info->histcount++);

			/* if (md_strchr(*buf, ';')) is this a command chain? */
			{
				*len = bytes_read;
				md_info->cmd_buf = buf;
			}
		}
	}
	return (bytes_read);
}

/**
 * md_get_input - gets a line minus the newline
 * @md_info: structure containing shell information
 *
 * Return: bytes read
 */
ssize_t md_get_input(md_info_t *md_info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t bytes_read = 0;
	char **buf_p = &(md_info->arg);
	char *p;

	mdWriteCharacter(BUF_FLUSH);
	bytes_read = md_input_buffer(md_info, &buf, &len);

	if (bytes_read == -1) /* EOF */
		return (-1);

	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		mdCheckChain(md_info, buf, &j, i, len);

		while (j < len) /* iterate to semicolon or end */
		{
			if (mdIsChainDelimiter(md_info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			md_info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (mdStrlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from md_get_line() */
	return (bytes_read); /* return length of buffer from md_get_line() */
}

/**
 * md_read_buffer - reads a buffer
 * @md_info: structure containing shell information
 * @buf: buffer
 * @i: size
 *
 * Return: bytes read
 */
ssize_t md_read_buffer(md_info_t *md_info, char *buf, size_t *i)
{
	ssize_t bytes_read = 0;

	if (*i)
		return (0);

	bytes_read = read(md_info->md_readfd, buf, READ_BUF_SIZE);

	if (bytes_read >= 0)
		*i = bytes_read;

	return (bytes_read);
}

/**
 * md_get_line - gets the next line of input from STDIN
 * @md_info: structure containing shell information
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: bytes read
 */
int md_get_line(md_info_t *md_info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytes_read = 0, total_bytes = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		total_bytes = *length;

	if (i == len)
		i = len = 0;

	bytes_read = md_read_buffer(md_info, buf, &len);

	if (bytes_read == -1 || (bytes_read == 0 && len == 0))
		return (-1);

	c = md_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = mdReallocateMemory(p, total_bytes, total_bytes ? total_bytes + k : k + 1);

	if (!new_p) /* MALLOC FAILURE! */
		return (p ? (free(p), -1) : -1);

	if (total_bytes)
		md_strncat(new_p, buf + i, k - i);
	else
		md_strncpy(new_p, buf + i, k - i + 1);

	total_bytes += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = total_bytes;

	*ptr = p;
	return (total_bytes);
}

/**
 * md_sigint_handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void md_sigint_handler(__attribute__((unused))int sig_num)
{
	mdPrintString("\n");
	mdPrintString("$ ");
	mdWriteCharacter(BUF_FLUSH);
}
