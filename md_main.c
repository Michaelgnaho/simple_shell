#include "shell.h"

/**
 * mdMain - entry point for my custom shell
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int mdMain(int ac, char **av)
{
	md_info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				md_puts_err(av[0]);
				md_puts_err(": 0: Can't open ");
				md_puts_err(av[1]);
				md_put_err_char('\n');
				md_put_err_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->md_readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	mdShell(info, av);
	return (EXIT_SUCCESS);
}
