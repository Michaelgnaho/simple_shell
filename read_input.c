#include "shell.h"
/**
 * read_cmd - this fuction reads command
 * @cmd: command to be read
 * @size: size of the comand
 */


void read_cmd(char *cmd, size_t size)
{
	if (fgets(cmd, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			printf_md("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf_md("Error while handling the file");
			exit(EXIT_SUCCESS);
		}
		cmd[strcspn(cmd, "\n")] = '\0';
	}
}
