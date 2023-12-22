#include "simple_shell.h"

int last_exit_status = 0;

/**
 * command_lists - function that looks for the command path
 * @cmd: command
 * Return: the paths
 */
char *command_lists(char *cmd)
{
	int index = 0;
	char *path, *tokens;
	char *path_array[100];
	char *new_path = NULL;
	struct stat buf;

	path = strdup(get_env_variable("PATH")); /* gets a dup of PATH */
	tokens = strtok(path, ":"); /* split the path in a set of tokens */
	new_path = malloc(sizeof(char) * 100);
	if (getenv("PATH")[0] == ':')
		if (stat(cmd, &buf) == 0)/* in case of success */
		{ 
		 	free(new_path);
			free(path);
			return (strdup(cmd)); /* return a copy of command */
		}	
	while (tokens != NULL)
	{
		path_array[index] = tokens; /* store results of tokens in path_array */
		index++;
		tokens = strtok(NULL, ":");
	}
	path_array[index] = NULL;
	for (index = 0; path_array[index]; index++)
	{
		size_t len = strlen(path_array[index]) + strlen(cmd) + 2;
		if (len > 100)
		{
			free(new_path);
			new_path = malloc(sizeof(char) * len);
		}
		strcpy(new_path, path_array[index]); /* copy tokens to new path */
		strcat(new_path, "/"); /* add "/" and command */
		strcat(new_path, cmd);
		strcat(new_path, "\0");
		if (stat(new_path, &buf) == 0) /* if sucess, free and return new_path */
		{
			char *exit_path = strdup(new_path);
			free(new_path);
			free(path);
			return (exit_path);
			free(strdup(new_path));
		}
		else
			new_path[0] = 0;
	}
	free(path);
	free(new_path);

	if (stat(cmd, &buf) == 0) /* After PATH checked and cmd is there locally */
	{
		return (strdup(cmd));
		free(strdup(cmd));
	}
	return (NULL);/* in case of possible errors */
	free(strdup(cmd));
}

/**
 * _printenv - it displays all the variables in the environment system
 *
 * Return: 0
 */
int _printenv(void)
{
	char *str = environ[0];
	int index = 0, file_descr = 1;

	while (str[index] != '\0')
	{
		write(file_descr, str, strlen(str));
		write(file_descr, "\n", 1);
		str = environ[++index]; 
	}
	return (0);
}

/**
 * command_read - function that reads the command
 * @input: the input of the shell
 * @characters: unused
 * Return: command execution
 */
int command_read(char *input, size_t __attribute__((unused))characters)
{
	char *token = NULL;
	char *cmd_arr[100];
	int index = 0;

	input = trim_spaces(input);

	if (strcmp(input, "") == 0)
		return (0);

	if (strcmp(input, "exit") == 0)
	{
		exit(last_exit_status);
	}
	if (strcmp(input, "env") == 0)
		return (_printenv());

	if (input[0] == 32)
	{
		return (1);
	}
	token = strtok(input, " ");

	while (token)
	{
		cmd_arr[index++] = token;
		token = strtok(NULL, " ");
	}
	cmd_arr[index] = NULL;
	return (execute(cmd_arr));
}

/**
 * execute - function that executes the command
 * @cmd_arr: This commands lists
 * Return: 0
 */
int execute(char *cmd_arr[])
{
	char *exe_path = NULL, *cmd = NULL;
	pid_t pid;
	int status;
	
	cmd = cmd_arr[0];
	exe_path = command_lists(cmd);
	if ((exe_path == NULL) || access(exe_path, X_OK) == -1)
	{
		write(2, cmd, strlen(cmd));
		write(2, ": command not found\n", 21);
		free(exe_path);
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Error:");
		free(exe_path);
		return (-1);
	}
	if (pid > 0)
	{
		wait(&status);
	}
	else if (pid == 0)
	{
		if (environ)
		{
			if (execve(exe_path, cmd_arr, environ) == -1)
			{
				perror("Error:");
				_exit(1);
			}
		}
		else
		{
			if(execve(exe_path, cmd_arr, NULL) == -1)
			{
				perror("Error:");
				_exit(1);
			}
		}
	}
	if (WIFEXITED(status))
		last_exit_status = WEXITSTATUS(status);

	free(exe_path);
	return (0);
}

char *get_env_variable(const char *name)
{
	extern char **environ;
	int index = 0;
	char *env_var = NULL;

	while (environ[index] != NULL)
	{
		if (strncmp(environ[index], name, strlen(name)) == 0)
		{
			env_var = strchr(environ[index], '=');
			if (env_var != NULL)
			{
				env_var++;
				break;
			}
		}
		index++;
	}

	return (env_var);
}
