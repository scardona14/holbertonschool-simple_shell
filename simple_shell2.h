#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
* main - super simple shell rogram that runs shell command
*
* when this program is compiled and exeecuted, created a child
* process and reads the input from stdin
* This input should be the path to an executable
*
* Return: Always 0
*/

int main(int argc, char *argv[], char **env)
{
	char *buff = NULL, * prompt = "$ ";
	size_t buff_size = 0;
	ssize_t bytes;
	pid_t wpid;
	int wstatus;
	bool from_pipe = false
	struct stat statbuf;

	while (1 && !from_pipe)
	{
		/* checks is date is piped into program or entered from terminal */
		if (isatty(STDIN_FILENO) == 0)
			from_pipe = true;
		/* Print the prompt sign '$ ' on the terminal */
		write(STDOUT_FILENO, prompt, 2);

		/* Read data from the standard input */
		bytes = getline(&buff, &buff_size, stdin);
		if (bytes == -1)
		{
			perror("Error (getline)");
			free(buff); /* If getline fails, free memory */
			exit(EXIT_FAILURE);
		}
		/* replace the newline character with a null terminator */
		if (buff[bytes - 1] == '\n')
			buff[bytes - 1] = '\0';

		/* Create a child process and use it to execute the command */
		wpid = fork();
		if (wpid == -1) /* if fork fails */
		{
			perror("Error (fork)");
			exit(EXIT_FAILURE);
		}
		if (wpid == 0) /* child process */
		_execute(buff, &statbuf, env);
		
		/* parent process should wait for the child to finish */
		if (waitpid(wpid, &wstatus, 0) == -1)
		{
			perror("Error (wait)");
			exit(EXIT_FAILURE);
		}
	}
	free(buff);
	return (0);
}

int _execute(char *arguments, struct stat *statbuf, char **envp)
{
	int argc;
	char **argv;
	char *exe;
	/* char *env[] = {"PROJECT = shell", NULL}; */
	argv = split_string(arguments, "", &argc);

	/* check if executable file exists */
	if (!check_file_status(argv[0], statbuf))
	{
		perror("Error (file status)");
		exit(EXIT_FAILURE);
	}
	execve(argv[0], argv, envp);
	/* free the dynamically allocated argv array */
	/* free_vector(argv, 20) */

	/* If execve failed */

	perror("Error (execve)");
	exit(EXIT_FAILURE);
}

bool check_file_status(char *pathname, struct stat *statbuf)
{
	int stat_return;

	stat_return = stat(pathname, statbuf);
	if (stat_return == 0)
		return (true);

		return (false);
}

void handle_error(pid_t pid)
{
	if (pid == -1)
	{
		printf("Error");
		exit(EXIT_FAILURE);
	}
}


















