#include "shell.h"

/**
 * mdSplitString - splits a string into words, ignoring repeated delimiters
 * @str: the input string
 * @delimiter: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **mdSplitString(char *str, char *delimiter)
{
	int i, j, k, l, numWords = 0;
	char **words;

	if (str == NULL || str[0] == 0)
		return (NULL);

	if (!delimiter)
		delimiter = " ";

	for (i = 0; str[i] != '\0'; i++)
		if (!mdIsDelim(str[i], delimiter) &&
		(mdIsDelim(str[i + 1], delimiter) || !str[i + 1]))
			numWords++;

	if (numWords == 0)
		return (NULL);

	words = malloc((1 + numWords) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < numWords; j++)
	{
		while (mdIsDelim(str[i], delimiter))
			i++;

		k = 0;
		while (!mdIsDelim(str[i + k], delimiter) && str[i + k])
			k++;

		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (l = 0; l < k; l++)
			words[j][l] = str[i++];
		words[j][l] = 0;
	}
	words[j] = NULL;
	return (words);
}

/**
 * mdSplitString2 - splits a string into words
 * @str: the input string
 * @delimiter: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **mdSplitString2(char *str, char delimiter)
{
	int i, j, k, l, numWords = 0;
	char **words;

	if (str == NULL || str[0] == 0)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delimiter && str[i + 1] == delimiter) ||
			(str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
				numWords++;

	if (numWords == 0)
		return (NULL);

	words = malloc((1 + numWords) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < numWords; j++)
	{
		while (str[i] == delimiter && str[i] != delimiter)
			i++;

		k = 0;
		while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
			k++;

		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (l = 0; l < k; l++)
			words[j][l] = str[i++];
		words[j][l] = 0;
	}
	words[j] = (NULL);
	return (words);
}
