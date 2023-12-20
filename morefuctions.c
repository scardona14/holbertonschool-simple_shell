#include "simple_shell.h"

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

char *trim_spaces(char *str)
{
    char *end;
    while (is_space((unsigned char)*str)) str++;
    
    if (*str == 0)
        return str;
    
    end = str + strlen(str) - 1;
    while (end > str && is_space((unsigned char)*end)) end--;
    
    end[1] = '\0';

    return (str);
}

