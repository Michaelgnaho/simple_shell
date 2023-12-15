#include "shell.h"

/**
 * mdCopyString - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *mdCopyString(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == NULL)
		return destination;

	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}
	

	destination[index] = 0;
	return destination;
}

/**
 * mdStrdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *mdStrdup(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return NULL;

	while (*str++)
		length++;

	result = malloc(sizeof(char) * (length + 1));

	if (!result)
		return NULL;

	for (length++; length--;)
		result[length] = *--str;

	return result;
}

/**
 * mdPrintString - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void mdPrintString(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		mdWriteCharacter(str[index]);
		index++;
	}
}

/**
 * mdWriteCharacter - writes the character to stdout
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int mdWriteCharacter(char character)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE]; /* Original name is WRITE_BUF_SIZE */

	if (character == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}

	if (character != BUF_FLUSH)
		buffer[index++] = character;

	return 1;
}
