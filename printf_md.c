#include "shell.h"

/**
 * printf_md - a function to print to the standard output
 * @stringmd: string to be printed
 * 
 * Return: returns nothing
 */


void printf_md(const char *stringmd)
{
	write(STDOUT_FILENO, &stringmd, strlen(stringmd));
}
