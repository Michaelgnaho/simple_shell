#include "shell.h"


void read_cmd(char *cmd, size_t size)
{
	if (fgets(cmd, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			print_md("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf_md("Error while handling the file");
			exit(EXIT_SUCCESS);
		}
	}
}
