#include "shell.h"
/**
 * main - main func
 * Return: 0
 */

int main(void)
{
	char cmd[150];

	while (1)
	{
		dis_prompt();
		read_cmd(cmd, sizeof(cmd));
		execute_cmd(cmd);

	}
	return (0);
}
