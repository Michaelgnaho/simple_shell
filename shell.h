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

#endif  /* SHELL_H */
