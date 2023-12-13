#include "shell.h"

/**
 * mdFree - releases memory occupied by a pointer and sets it to NULL
 * @ptr: address of the pointer to be freed
 *
 * Return: 1 if successfully freed, otherwise 0.
 */
int mdFree(void **ptr)
{
	if (*ptr && ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
