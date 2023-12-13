#include "shell.h"

/**
 * md_strncpy - copies a string
 * @dest: the destination string to copy to
 * @src: the source string
 * @n: the maximum number of characters to copy
 * Return: the pointer to the modified destination string
 */
char *md_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	/* Copy up to 'n' characters from 'src' to 'dest' */
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	/*
	*	Fill the remaining space in 'dest' with null characters if 'src'
	*	length is less than 'n'
	*/
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (result);  /* Return the pointer to the modified 'dest' */
}

/**
 * md_strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the maximum number of characters to concatenate
 * Return: the pointer to the concatenated string
 */
char *md_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	/* Find the end of 'dest' */
	while (dest[i] != '\0')
		i++;
	j = 0;
	/* Concatenate up to 'n' characters from 'src' to the end of 'dest' */
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	/* Terminate the concatenated string if 'src' length is less than 'n' */
	if (j < n)
		dest[i] = '\0';
	return (result);  /* Return the pointer to the concatenated string */
}

/**
 * md_strchr - locates a character in a string
 * @s: the string to search
 * @c: the character to find
 * Return: a pointer to the first occurrence of 'c' in 's', or NULL
 *			if not found
 */
char *md_strchr(char *s, char c)
{
	do {
		/* Check if the current character in 's' is equal to 'c' */
		if (*s == c)
			return (s);  /* Return the pointer to the memory area in 's' */
	} while (*s++ != '\0');

	return (NULL);  /* Return NULL if 'c' is not found in 's' */
}
