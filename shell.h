#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <sting.h>
#include <unistd.h>
void printf_md(const char *stringmd);
void dis_prompt(void);
void execute_cmd(const char *cmd);
void read_cmd(char *cmd, size_t size);
#endif
