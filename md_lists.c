#include "shell.h"

/**
 * addHistoryNode - adds a new command to the personal
 *					command history list
 * @historyHead: address of pointer to the head node of
 *				the history list
 * @command: command string to be added
 * @index: index used for tracking command history
 *
 * Return: size of the updated history list
 */
list_t *addHistoryNode(list_t **historyHead, const char *command, int index)
{
	list_t *newHistoryNode;

	if (!historyHead)
		return (NULL);

	newHistoryNode = malloc(sizeof(list_t));
	if (!newHistoryNode)
		return (NULL);

	_memset((void *)newHistoryNode, 0, sizeof(list_t));
	newHistoryNode->num = index;

	if (command)
	{
		newHistoryNode->str = mdStringDuplicate(command);
		if (!newHistoryNode->str)
		{
			free(newHistoryNode);
			return (NULL);
		}
	}

	newHistoryNode->next = *historyHead;
	*historyHead = newHistoryNode;
	return (newHistoryNode);
}

/**
 * addHistoryNodeEnd - adds a new command to the end of the
 *						personal command history list
 * @historyHead: address of pointer to the head node of the
 *				history list
 * @command: command string to be added
 * @index: index used for tracking command history
 *
 * Return: size of the updated history list
 */
list_t *addHistoryNodeEnd(list_t **historyHead, const char *command, int index)
{
	list_t *newHistoryNode, *historyNode;

	if (!historyHead)
		return (NULL);

	historyNode = *historyHead;
	newHistoryNode = malloc(sizeof(list_t));
	if (!newHistoryNode)
		return (NULL);

	_memset((void *)newHistoryNode, 0, sizeof(list_t));
	newHistoryNode->num = index;

	if (command)
	{
		newHistoryNode->str = mdStringDuplicate(command);
		if (!newHistoryNode->str)
		{
			free(newHistoryNode);
			return (NULL);
		}
	}

	if (historyNode)
	{
		while (historyNode->next)
			historyNode = historyNode->next;
		historyNode->next = newHistoryNode;
	}
	else
		*historyHead = newHistoryNode;

	return (newHistoryNode);
}

/**
 * printCommandHistory - prints only the command strings in
 *						the personal command history list
 * @history: pointer to the first node in the history list
 *
 * Return: size of the command history list
 */
size_t printCommandHistory(const list_t *history)
{
	size_t count = 0;

	while (history)
	{
		mdPrintString(history->str ? history->str : "(nil)");
		mdPrintString("\n");
		history = history->next;
		count++;
	}
	return (count);
}

/**
 * deleteCommandAtIndex - deletes a command at the given index
 *						from the personal command history list
 * @historyHead: address of pointer to the head node of the
 *						history list
 * @index: index of the command to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deleteCommandAtIndex(list_t **historyHead, unsigned int index)
{
	list_t *historyNode, *prevHistoryNode;
	unsigned int count = 0;

	if (!historyHead || !*historyHead)
		return (0);

	if (!index)
	{
		historyNode = *historyHead;
		*historyHead = (*historyHead)->next;
		free(historyNode->str);
		free(historyNode);
		return (1);
	}

	historyNode = *historyHead;
	while (historyNode)
	{
		if (count == index)
		{
			prevHistoryNode->next = historyNode->next;
			free(historyNode->str);
			free(historyNode);
			return (1);
		}
		count++;
		prevHistoryNode = historyNode;
		historyNode = historyNode->next;
	}

	return (0);
}

/**
 * clearCommandHistory - frees all nodes in the personal command history list
 * @historyHead: address of pointer to the head node of the history list
 *
 * Return: void
 */
void clearCommandHistory(list_t **historyHead)
{
	list_t *historyNode, *nextHistoryNode, *head;

	if (!historyHead || !*historyHead)
		return;

	head = *historyHead;
	historyNode = head;
	while (historyNode)
	{
		nextHistoryNode = historyNode->next;
		free(historyNode->str);
		free(historyNode);
		historyNode = nextHistoryNode;
	}
	*historyHead = NULL;
}
