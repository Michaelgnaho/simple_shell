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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

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

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


	typedef struct builtin
{
	char *type;
	int (*func)(md_info_t *);
} builtin_table;

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

/*md_environ.c*/
int md_display_env(md_info_t *md_info);
char *md_get_env(md_info_t *md_info, const char *name);
int md_set_env(md_info_t *md_info);
int md_unset_env(md_info_t *md_info);
int md_populate_env_list(md_info_t *md_info);

/*md_error.c*/
void md_puts_err(char *str);
int md_put_err_char(char c);
int md_putfd(char c, int fd);
int md_putsfd(char *str, int fd);

/*md_error_1.c*/
int md_erratoi(char *s);
void md_print_error(md_info_t *info, char *estr);
int md_print_d(int input, int fd);
char *md_convert_number(long int num, int base, int flags);
void md_remove_comments(char *buf);

/*md_exit.c*/
char *md_strncpy(char *dest, char *src, int n);
char *md_strncat(char *dest, char *src, int n);
char *md_strchr(char *s, char c)

/*md_getline.c*/
ssize_t md_input_buffer(md_info_t *md_info, char **buf, size_t *len);
ssize_t md_get_input(md_info_t *md_info);
ssize_t md_read_buffer(md_info_t *md_info, char *buf, size_t *i);
int md_get_line(md_info_t *md_info, char **ptr, size_t *length);
void md_sigint_handler(__attribute__((unused))int sig_num);


/* md_getenviron.c */

char **md_get_environ(md_info_t *md_info);
int md_unsetenv(md_info_t *md_info, char *var);
int md_setenv(md_info_t *md_info, char *var, char *value);

/* md_getinfo.c */
void md_clear_info(md_info_t *md_info);
void md_set_info(md_info_t *md_info, char **av);
void md_free_info(md_info_t *md_info, int all);

/* md_history.c */
char *md_get_history_file(md_info_t *md_info);
int md_write_history(md_info_t *md_info);
int md_read_history(md_info_t *md_info);
int md_build_history_list(md_info_t *md_info, char *buf, int linecount);
int md_renumber_history(md_info_t *md_info);
#endif  /* SHELL_H */
