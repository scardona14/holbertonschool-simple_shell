#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define MAX_INPUT_SIZE 1024

extern char **environ;


int _printenv(void);
char *_getenv(char *var);
char *command_lists(char *cmd);
int command_read(char *s, size_t __attribute__((unused))file_stream);
int execute(char *cmd_arr[]);

#endif /* SIMPLE_SHELL_H */
