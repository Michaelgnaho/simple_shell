#include "shell.h"

/**
 * mdMemset - fills a memory area with a specified byte
 * @str: pointer to the memory area
 * @d: the byte to fill the memory area with
 * @num: the number of bytes to fill
 *
 * Return: a pointer to the filled memory area
 */
char *mdMemset(char *str, char d, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		str[i] = d;
	return (str);
}

/**
 * mdFreeStrings - frees a string array
 * @pptr: the string array to be freed
 */
void mdFreeStrings(char **pptr)
{
	char **a = pptr;

	if (!pptr)
		return;
	while (*pptr)
		free(*pptr++);
	free(a);
}

/**
 * mdReallocateMemory - reallocates a block of memory
 * @ptr: pointer to the previous dynamically allocated block
 * @oldSize: byte size of the previous block
 * @newSize: byte size of the new block
 *
 * Return: a pointer to the reallocated block
 */
void *mdReallocateMemory(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	char *p;

	if (!ptr)
	{
		return (malloc(newSize));
	}

	if (!newSize)
	{
		return (free(ptr), NULL);
	}

	if (oldSize == newSize)
	{
		return (ptr);
	}

	p = malloc(newSize);
	if (!p)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		p[oldSize] = ((char *)ptr)[oldSize];
	free(ptr);
	return (p);
}
