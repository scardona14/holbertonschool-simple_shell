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
#include <ctype.h>

#define MAX_INPUT_SIZE 100

extern char **environ;

char *get_env_variable(const char *name);
int _printenv(void);
char *_getenv(char *var);
char *command_lists(char *cmd);
int command_read(char *s, size_t __attribute__((unused))file_stream);
int execute(char *cmd_arr[]);
char *trim_spaces(char *str);
int is_space(char c);
void set_new_env_variable(const char *name, const char *value);
void keep_one_env_variable(const char *keep);

#endif /* SIMPLE_SHELL_H */
