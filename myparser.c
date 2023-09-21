#include "shell.h"
#include <string.h>

#define MAX_ARGS 10

/**
 * parseCmd - Parse the input string into arguments.
 * @input: The input string to parse.
 * @args: An array to store the parsed arguments.
 *
 * Return: The number of arguments parsed.
 */
int parseCmd(char *input, char **args)
{
	int num_args = 0;
	char *new_line = strchr(input, '\n');

	if (new_line)
	{
		*new_line = '\0';
	}

	char *token;
	char *saveptr = NULL;

	for (token = my_strtok(input, " ", &saveptr); token != NULL;
token = my_strtok(NULL, " ", &saveptr))
	{
		args[num_args] = token;
		num_args++;

		if (num_args >= MAX_ARGS)
		{
			char error_message[] = "Too many arguments. Maximum allowed is 10.\n";
			int i;

			for (i = 0; error_message[i] != '\0'; i++)
			{
				_putchar(error_message[i]);
			}
			return (-1);
		}
	}

	args[num_args] = NULL;
	return (num_args);
}

/**
 * executeCmd - Execute a command with the given arguments.
 * @args: An array of command arguments.
 * @num_args: The number of arguments in the array.
 *
 * Return: None.
 */
void executeCmd(char **args, int num_args)
{
	if (num_args > 0)
	{
		if (strcmp(args[0], "exit") == 0)
		{
			exitShell();
		}
		else if (strcmp(args[0], "env") == 0)
		{
			printEnvironment();
		}
		else
		{
			pid_t pid = fork();

			if (pid == 0)
			{
				execvp(args[0], args);
				char error_message[] = "Executable cannot be found\n";
				int i;

				for (i = 0; error_message[i] != '\0'; i++)
				{
					_putchar(error_message[i]);
				}
				exit(1);
			}
			else if (pid > 0)
			{
				wait(NULL);
			}
			else
			{
				perror("fork");
			}
		}
	}
}

