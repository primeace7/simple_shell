#ifndef _SHELL_
#define _SHELL_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void display_prompt(void);
void tokenize(char *, char ***);
void ops_error(int);
void strip(char **);
void free_buffers(void);
ssize_t get_inputline(char *[]);
pid_t fork_child(void);
void execute_child(char **, char **, char **);

#endif
