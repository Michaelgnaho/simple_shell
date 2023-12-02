#ifndef SHELL_H
#define SHELL_H
/*
 * these are the libraries needed
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*
 * these are the funcion prototypes
 */

void printf_md(const char *stringmd);
void dis_prompt(void);
void execute_cmd(const char *cmd);
void read_cmd(char *cmd, size_t size);
#endif
