#include "shell.h"

/**
 * main - entry point for my custom shell
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
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
				md_eputs(av[0]);
				md_eputs(": 0: Can't open ");
				md_eputs(av[1]);
				md_eputchar('\n');
				md_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->md_readfd = fd;
	}
	md_populate_env_list(info);
	md_read_history(info);
	mdShellLoop(info, av);
	return (EXIT_SUCCESS);
}
