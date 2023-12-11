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
#include "sys/wait.h"

void execute_cmd(const char *cmd) {
    pid_t child_pid;
	char *argue[128];
    child_pid = fork();
	int argue_count = 0;

    if (child_pid == -1) {
        /* Error forking process */
        write(2, "Error forking process.\n", strlen("Error forking process.\n"));
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        /* Child process */

        /* Create a buffer to store the command */
        char buffer[150];
        strcpy(buffer, cmd);

        char *token = strtok(buffer, " ");
        while (token != NULL && argue_count < 128) {
            argue[argue_count++] = token;
            token = strtok(NULL, " ");
        }

        argue[argue_count] = NULL;

        /* Execute specific commands */
        if (strcmp(argue[0], "ls") == 0) {
            execve("/bin/ls", argue, NULL);
        } else if (strcmp(argue[0], "cat") == 0) {
            execve("/bin/cat", argue, NULL);
        } else if (strcmp(argue[0], "pwd") == 0) {
            execve("/bin/pwd", argue, NULL);
        } else if (strcmp(argue[0], "clear") == 0) {
            execve("/usr/bin/clear", argue, NULL);
        } else if (strcmp(argue[0], "vi") == 0) {
            execve("/usr/bin/vi", argue, NULL);
        } else {
            /* Command not found or not executable */
            write(2, "Command not found or not executable.\n", strlen("Command not found or not executable.\n"));
            exit(EXIT_FAILURE);
        }
    } else {
        /* Parent process */
        wait(NULL);
    }
}
