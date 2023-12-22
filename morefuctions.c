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

void set_new_env_variable(const char *name, const char *value)
{
    extern char **environ;
    int i;
    char **new_environ;
    char *new_variable;

    /* Count the current number of environment variables */
    for (i = 0; environ[i] != NULL; i++);

    /* Allocate new_environ */
    new_environ = malloc(sizeof(char *) * (i + 2));  /* +2 for the new variable and the NULL terminator */
    if (new_environ == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    /* Copy over the existing environment variables */
    for (i = 0; environ[i] != NULL; i++)
    {
        new_environ[i] = environ[i];
    }

    /* Add the new environment variable */
    new_variable = malloc(strlen(name) + strlen(value) + 2);  /* +2 for the '=' and the '\0' */
    if (new_variable == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    sprintf(new_variable, "%s=%s", name, value);
    new_environ[i] = new_variable;

    /* NULL terminate new_environ */
    new_environ[i + 1] = NULL;

    /* Replace environ with new_environ */
    environ = new_environ;
}

void keep_one_env_variable(const char *keep)
{
    extern char **environ;
    char **new_environ;
    int i, j = 0, count = 0;

    /* Count the number of environment variables to keep */
    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], keep, strlen(keep)) == 0 && environ[i][strlen(keep)] == '=')
        {
            count++;
        }
    }

    /* Allocate new_environ */
    new_environ = malloc(sizeof(char *) * (count + 1));  /* +1 for the NULL terminator */
    if (new_environ == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    /* Copy over the environment variables to keep */
    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], keep, strlen(keep)) == 0 && environ[i][strlen(keep)] == '=')
        {
            new_environ[j] = environ[i];
            j++;
        }
    }

    /* NULL terminate new_environ */
    new_environ[j] = NULL;

    /* Replace environ with new_environ */
    environ = new_environ;
}
