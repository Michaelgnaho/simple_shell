#include "shell.h"


/**
 * md_exit - exits the shell
 * @md_info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0) if md_info->argv[0] != "exit".
 */
int md_exit(md_info_t *md_info)
{
	int exit_check;

	if (md_info->argv[1])  /* If there is an exit argument */
	{
		exit_check = md_erratoi(md_info->argv[1]);
		if (exit_check == -1)
		{
			md_info->status = 2;
			mdPrintError(md_info, "Illegal number: ");
			md_eputs(md_info->argv[1]);
			md_eputchar('\n');
			return (1);
		}
		md_info->err_num = md_erratoi(md_info->argv[1]);
		return (-2);
	}
	md_info->err_num = -1;
	return (-2);
}

/**
 * md_cd - changes the current directory of the process
 * @md_info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int md_cd(md_info_t *md_info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		mdPrintString("TODO: >>getcwd failure emsg here<<\n");

	if (!md_info->argv[1])
	{
		dir = md_get_env(md_info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = md_get_env(md_info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (mdStrcmp(md_info->argv[1], "-") == 0)
	{
		if (!md_get_env(md_info, "OLDPWD="))
		{
			mdPrintString(s);
			mdWriteCharacter('\n');
			return (1);
		}
		mdPrintString(md_get_env(md_info, "OLDPWD="));
		mdWriteCharacter('\n');
		chdir_ret = chdir((dir = md_get_env(md_info, "OLDPWD=")) ? dir : "/");
	}
	else
	{
		chdir_ret = chdir(md_info->argv[1]);
	}

	if (chdir_ret == -1)
	{
		mdPrintError(md_info, "can't cd to ");
		md_eputs(md_info->argv[1]);
		md_eputchar('\n');
	}
	else
	{
		md_setenv(md_info, "OLDPWD", md_get_env(md_info, "PWD="));
		md_setenv(md_info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * md_help - displays help information
 * @md_info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int md_help(md_info_t *md_info)
{
	char **arg_array;

	arg_array = md_info->argv;
	mdPrintString("help call works. Function not yet implemented \n");

	if (0)
		mdPrintString(*arg_array); /* temp att_unused workaround */

	return (0);
}
