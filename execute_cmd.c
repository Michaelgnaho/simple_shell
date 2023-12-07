/*#include "shell.h"
#include <sys/wait.h>/

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



#include "shell.h"
#include <sys/wait.h>
/**
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
	
}
*/

#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 128

/**
 * execute_cmd - execute commands
 * @cmd: the command to execute
 */
void execute_cmd(const char *cmd)
{
    /* Fork a new process */
    pid_t child_pid = fork();

    /* Check if forking was successful */
    if (child_pid == -1)
    {
        /* Print an error message if forking failed */
        write(2, "Error forking process.\n", strlen("Error forking process.\n"));
        exit(EXIT_FAILURE);
    }
    /* If we are in the child process */
    else if (child_pid == 0)
    {
        /* Declare an array to store command arguments */
        char *argue[MAX_ARGS];
        /* Initialize a counter for arguments */
        int argue_count = 0;

        /* Use getline to dynamically read the entire command line */
        size_t buffer_size = 0;
        char *buffer = NULL;
        ssize_t read_chars;

        /* Read the command line into the buffer using getline */
        read_chars = getline(&buffer, &buffer_size, (FILE *)cmd);

        /* Check if reading the command line failed */
        if (read_chars == -1)
        {
            /* Print an error message */
            write(2, "Error reading command.\n", strlen("Error reading command.\n"));
            exit(EXIT_FAILURE);
        }

        /* Tokenize the command line using spaces, tabs, and newline characters */
        char *tok;
        tok = strtok(buffer, " \t\n");
        
        /* While there are tokens and we haven't reached the maximum number of arguments */
        while (tok != NULL && argue_count < MAX_ARGS - 1)
        {
            /* Store the token in the argument array */
            argue[argue_count++] = tok;
            /* Get the next token */
            tok = strtok(NULL, " \t\n");
        }

        /* Set the last element of the argument array to NULL (required for execvp) */
        argue[argue_count] = NULL;

        /* Use execvp to execute the command with the given arguments */
        execvp(argue[0], argue);

        /* If execvp fails, print an error message */
        write(2, "Error executing command.\n", strlen("Error executing command.\n"));

        /* Free the dynamically allocated memory for the buffer */
        free(buffer);

        /* Exit the child process with a failure status */
        exit(EXIT_FAILURE);
    }
    /* If we are in the parent process */
    else
    {
        /* Wait for the child process to finish */
        wait(NULL);
    }
}
