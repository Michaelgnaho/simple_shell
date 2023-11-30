#include "shell.h"
/**
 *printf_md - a fuction to print to the standard output
 *@stringmd: string to be printed
 */


void printf_md(const char *stringmd)
{
	write(STDOUT_FILENO, &stringmd, strlen(stringmd));
}

