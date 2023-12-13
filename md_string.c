#include "shell.h"

/**
 * mdStrlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of the string
 */
int mdStrlen(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;
	return (length);
}

/**
 * mdStrcmp - performs lexicographic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero
 *			if str1 == str2
 */
int mdStrcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str2 == *str1)
	{
		return (0);
	}
	else
	{
		return (*str2 > *str1 ? -1 : 1);
	}
}

/**
 * mdStartsWith - checks if needle starts with hayStack
 * @hayStack: string to search
 * @needle: the substring to find
 *
 * Return: address of the next character of hayStack or NULL
 */
char *mdStartsWith(const char *hayStack, const char *needle)
{
	while (*needle)
		if (*needle++ != *hayStack++)
			return (NULL);
	return ((char *)hayStack);
}

/**
 * mdStrcat - concatenates two strings
 * @dest: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *mdStrcat(char *dest, char *source)
{
	char *result = dest;

	while (*dest)
	{
		dest++;
	}
	while (*source)
	{
		*dest++ = *source++;
	}
	*dest = *source;
	return (result);
}
