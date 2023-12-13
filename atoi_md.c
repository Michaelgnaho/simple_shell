#include "shell.h"

/**
 * md_is_interactive - returns true if the shell is in interactive mode
 * @md_info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int md_is_interactive(md_info_t *md_info)
{
	return (isatty(STDIN_FILENO) && md_info->md_readfd <= 2);
}

/**
 * md_is_delimiter - checks if character is a delimiter
 * @c: the char to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int md_is_delimiter(char c, char *delim)
{
	while (*delim)
	if (*delim++ == c)
		return (1);
	return (0);
}

/**
 * md_is_alpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int md_is_alpha(int c)
{
return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * md_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int md_atoi(char *s)
{
	int i, md_sign = 1, md_flag = 0, md_output;
	unsigned int md_result = 0;

	for (i = 0; s[i] != '\0' && md_flag != 2; i++)
	{
		if (s[i] == '-')
			md_sign *= -1;
	if (s[i] >= '0' && s[i] <= '9')
	{
		md_flag = 1;
		md_result *= 10;
		md_result += (s[i] - '0');
	}
	else if (md_flag == 1)
		md_flag = 2;
	}
	md_output = (md_sign == -1) ? -md_result : md_result;

	return (md_output);
}
