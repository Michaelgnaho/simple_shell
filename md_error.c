#include "shell.h"

#include "shell.h"

/**
 * md_puts_err - Prints an input string to the error stream.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void md_puts_err(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		md_put_err_char(str[i]);
		i++;
	}
}

/**
 * md_put_err_char - Writes the character to the error stream.
 * @c: The character to print.
 *
 * Return: On success, returns 1. On error, returns -1, and sets
 *			errno appropriately.
 */
int md_put_err_char(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * md_putfd - Writes the character to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, returns 1. On error, returns -1,
 *			and sets errno appropriately.
 */
int md_putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * md_putsfd - Prints an input string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int md_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += md_putfd(*str++, fd);
	}
	return (i);
}
