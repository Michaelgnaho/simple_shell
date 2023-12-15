#include "shell.h"

/**
 * mdShellLoop - main loop of the shell
 * @mdInfo: pointer to the parameter and return information struct
 * @mdAv: argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int mdShellLoop(md_info_t *mdInfo, char **mdAv)
{
	ssize_t inputResult = 0;
	int builtinResult = 0;

	while (inputResult != -1 && builtinResult != -2)
	{
		md_clear_info(mdInfo);
		if (md_is_interactive(mdInfo))
			mdPrintString("Micheal_Dare_SHELL$ ");
		md_eputchar(BUF_FLUSH);
		inputResult = mdGetInput(mdInfo);
		if (inputResult != -1)
		{
			mdSetInfo(mdInfo, mdAv);
			builtinResult = mdFindBuiltin(mdInfo);
			if (builtinResult == -1)
				mdFindCmd(mdInfo);
		}
		else if (md_is_interactive(mdInfo))
			mdWriteCharacter('\n');
		mdFreeInfo(mdInfo, 0);
	}
	mdWriteHistory(mdInfo);
	mdFreeInfo(mdInfo, 1);
	if (!md_is_interactive(mdInfo) && mdInfo->status)
		exit(mdInfo->status);
	if (builtinResult == -2)
	{
		if (mdInfo->err_num == -1)
			exit(mdInfo->status);
		exit(mdInfo->err_num);
	}
	return (builtinResult);
}

/**
 * mdFindBuiltin - finds a builtin command
 * @mdInfo: pointer to the parameter and return information struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int mdFindBuiltin(md_info_t *mdInfo)
{
	int i, builtinResult = -1;
	builtin_table builtintbl[] = {
		{"exit", md_exit},
		{"env", md_display_env},
		{"help", md_help},
		{"history", md_display_history},
		{"setenv", md_set_env},
		{"unsetenv", md_unset_env},
		{"cd", md_cd},
		{"alias", md_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (mdStrcmp(mdInfo->argv[0], builtintbl[i].type) == 0)
		{
			mdInfo->line_count++;
			builtinResult = builtintbl[i].func(mdInfo);
			break;
		}
	return (builtinResult);
}

/**
 * mdFindCmd - finds a command in PATH
 * @mdInfo: pointer to the parameter and return information struct
 *
 * Return: void
 */
void mdFindCmd(md_info_t *mdInfo)
{
	char *path = NULL;
	int i, k;

	mdInfo->path = mdInfo->argv[0];
	if (mdInfo->linecount_flag == 1)
	{
		mdInfo->line_count++;
		mdInfo->linecount_flag = 0;
	}
	for (i = 0, k = 0; mdInfo->arg[i]; i++)
		if (!mdIsDelim(mdInfo->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = mdFindPath(mdInfo, md_get_env(mdInfo, "PATH="), mdInfo->argv[0]);
	if (path)
	{
		mdInfo->path = path;
		mdForkCmd(mdInfo);
	}
	else
	{
		if ((md_is_interactive(mdInfo) || md_get_env(mdInfo, "PATH=")
			|| mdInfo->argv[0][0] == '/') && mdIsCommand(mdInfo, mdInfo->argv[0]))
			mdForkCmd(mdInfo);
		else if (*(mdInfo->arg) != '\n')
		{
			mdInfo->status = 127;
			mdPrintError(mdInfo, "not found\n");
		}
	}
}

/**
 * mdForkCmd - forks an exec thread to run cmd
 * @mdInfo: pointer to the parameter and return information struct
 *
 * Return: void
 */
void mdForkCmd(md_info_t *mdInfo)
{
	pid_t childPid;

	childPid = fork();
	if (childPid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (childPid == 0)
	{
		if (execve(mdInfo->path, mdInfo->argv, mdGetEnviron(mdInfo)) == -1)
		{
			mdFreeInfo(mdInfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(mdInfo->status));
		if (WIFEXITED(mdInfo->status))
		{
			mdInfo->status = WEXITSTATUS(mdInfo->status);
			if (mdInfo->status == 126)
				mdPrintError(mdInfo, "Permission denied\n");
		}
	}
}
