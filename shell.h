#ifndef SHELL_H
#define SHELL_H
/*
 * these are the libraries needed
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
/*
 * these are the funcion prototypes
 */

void printf_md(const char *stringmd);
void dis_prompt(void);
void execute_cmd(const char *cmd);
void read_cmd(char *cmd, size_t size);
int main(void);

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int md_readfd;
	int histcount;
} md_info_t;

/*for atoi_md.c*/
int md_is_interactive(md_info_t *md_info);
int md_is_delimiter(char c, char *delim);
int md_is_alpha(int c);
int md_atoi(char *s);

/*md_builtin.c*/
int md_exit(md_info_t *md_info);
int md_cd(md_info_t *md_info);
int md_help(md_info_t *md_info);

/*md_builtin_1.c*/
int md_display_history(md_info_t *md_info);
int md_unset_alias(md_info_t *md_info, char *str);
int md_set_alias(md_info_t *md_info, char *str);
int md_print_alias(list_t *node);
int md_alias(md_info_t *md_info);






/************************************* DASURF FUNCTION PROTOTYPES *********************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/



/* md_lists.c prototypes */
list_t *addHistoryNode(list_t **historyHead, const char *command, int index);
list_t *addHistoryNodeEnd(list_t **historyHead, const char *command, int index);
size_t printCommandHistory(const list_t *history);
int deleteCommandAtIndex(list_t **historyHead, unsigned int index);
void clearCommandHistory(list_t **historyHead);


/* md_lists1.c prototypes */
size_t md_list_length(const list_t *h);
char **md_list_to_strings(list_t *head);
size_t md_print_list(const list_t *h);
list_t *md_node_starts_with(list_t *node, char *prefix, char c);
ssize_t md_get_node_index(list_t *head, list_t *node);


/* md_memory.c prototypes */
int mdFree(void **ptr);


/* md_parser.c prototypes */
char *mdFindPath(info_t *info, char *pathstr, char *cmd);
int mdIsCommand(info_t *info, char *path);
char *mdDuplicateChars(char *pathstr, int start, int stop);


/* md_realloc.c prototypes */
void mdFreeStrings(char **pptr);
void *mdReallocateMemory(void *ptr, unsigned int oldSize, unsigned int newSize);
char *mdMemset(char *str, char d, unsigned int num);

/* md_shell_loop.c prototypes */
int mdShellLoop(info_t *mdInfo, char **mdAv);
int mdFindBuiltin(info_t *mdInfo);
void mdFindCmd(info_t *mdInfo);
void mdForkCmd(info_t *mdInfo);

/* md_string.c prototypes */
int mdStrlen(char *str);
int mdStrcmp(char *str1, char *str2);
char *mdStartsWith(const char *hayStack, const char *needle);
char *mdStrcat(char *dest, char *src);

/* md_string1.c prototypes */
char *mdCopyString(char *destination, char *source);
char *mdStringDuplicate(const char *str);
void mdPrintString(char *str);
int mdWriteCharacter(char character);


#endif  /* SHELL_H */
