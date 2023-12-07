/*
#include "shell.h"
#include <sys/wait.h>

void execute_cmd(const char *cmd)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);

	}
	else if (child_pid == 0)
	{
		execlp(cmd, cmd, (char *)NULL);
		perror("execlp");
		exit(EXIT_FAILURE);

	}
	else
	{
		wait(NULL);
	}
}*/




/* #include "shell.h"
#include <sys/wait.h>

 * execute_cmd - this func execute commands
 * @cmd: this is the comand
 */

/*void execute_cmd(const char *cmd)
{
	pid_t child_pid = fork();


	if (child_pid == -1)
	{
		printf_md("Error forking process. \n");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		char *argue[128];
		int argue_count = 0;

		char *tok = strtok((char *)cmd, " ");

		while (tok != NULL)
		{
			argue[argue_count++] = tok;
			tok = strtok(NULL, " ");
		}
		argue[argue_count] = NULL;
		execve(argue[0], argue, NULL);

		write(2, "Error executing command.\n", strlen("Error executing command.\n"));

	
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}

*/
#include "shell.h"
#include <sys/wait.h>

void execute_cmd(const char *cmd) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        write(2, "Error forking process.\n", strlen("Error forking process.\n"));
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        /* Child process*/
        if (execlp("/bin/sh", "/bin/sh", "-c", cmd, NULL) == -1) {
            /* If execlp fails*/
            write(2, "Error executing command.\n", strlen("Error executing command.\n"));
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process*/
        wait(NULL);
    }
}
