#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Entry point of the shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *input = NULL;

	while (1)
	{
		displayPrompt("Cisfun$\n");
		input = readInput();

		if (input == NULL)
		{
			perror("my_getline");
			break;
		}

		handleInput(input);
		free(input);
	}

	return (0);
}

/**
 * displayPrompt - Display the shell prompt.
 * @prompt: The prompt string to display.
 */
void displayPrompt(const char *prompt)
{
	int i;

	for (i = 0; prompt[i] != '\0'; i++)
	{
		_putchar(prompt[i]);
	}
}

/**
 * readInput - Read user input from stdin.
 *
 * Return: A dynamically allocated string containing the user input.
 */
char *readInput()
{
	char *input = NULL;
	size_t input_size = 0;
	char *new_line = strchr(input, '\n');

	if (my_getline(&input, &input_size, stdin) == -1)
	{
		perror("my_getline");
		return (NULL);
	}

	if (new_line)
	{
		*new_line = '\0';
	}

	if (strlen(input) == 0)
	{
		return (NULL);
	}

	return (input);
}

/**
 * handleInput - Handle the user input.
 * @input: The user input string.
 */
void handleInput(char *input)
{
	if (strstr(input, "|") != NULL)
	{
		executePipeCommand(input);
	}
	else
	{
		executeCommands(input);
	}
}

/**
 * executePipeCommand - Execute a command with pipe.
 * @command: The command to execute with pipe.
 */
void executePipeCommand(const char *command)
{
	int pipefd[2];
	pid_t child_pid;
	ssize_t read_bytes;
	char buffer[4096];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return;
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return;
	}

	if (child_pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		system(command);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		while ((read_bytes = read(pipefd[0], buffer, sizeof(buffer))) > 0)
		{
			write(STDOUT_FILENO, buffer, read_bytes);
		}
		close(pipefd[0]);
		wait(NULL);
	}
}

