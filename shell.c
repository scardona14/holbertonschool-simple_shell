#include "simple_shell.h"

/**
 * main - command interpreter
 * @argc: unused
 * @argv: arguments
 * Return: 0
 */
int main(void)
{
	char *input = NULL;
	size_t size = 0;
	ssize_t characters = 0;
	int status = 0;
	int exitst = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(1, "$ ", 2);
			
		characters = getline(&input, &size, stdin);
		if (characters == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(1, "\n", 1);
			break;
		}

		if (input[characters - 1]  == '\n')
			input[characters - 1]  = '\0';
		if (*input == '\0')
			continue;
		if (command_read(input, characters) == 2)
			break;
	}

	free(input);
	input = NULL;

	exitst = WEXITSTATUS(status);


	return (exitst);

}