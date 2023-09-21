#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>  /* For getpid */

/* Function declarations */
static void replace_variable(char **src, bool prev_command_success);
char *replace_variables(char *command, bool prev_command_success);
void handle_commands(char *input);

/**
* replace_variable - Replace a single variable in the input.
* @src: The source string.
* @prev_command_success: The success status of the previous command.
*
* This function replaces a single variable in the input string with its value.
*/
static void replace_variable(char **src, bool prev_command_success)
{
int i; /* Declare i at the beginning of the block */
if (**src == '$')
{
(*src)++;
if (**src == '?')
{
int exit_status = (prev_command_success) ? 0 : 1;
char exit_status_str[12];

snprintf(exit_status_str, sizeof(exit_status_str), "%d", exit_status);

for (i = 0; exit_status_str[i] != '\0'; i++)
{
putchar(exit_status_str[i]);
}
(*src)++;
}
else if (**src == '$')
{
int pid = getpid();
char pid_str[12];

snprintf(pid_str, sizeof(pid_str), "%d", pid);
for (i = 0; pid_str[i] != '\0'; i++)
{
putchar(pid_str[i]);
}
(*src)++;
}
else
{
putchar('$');
}
}
else
{
putchar(**src);
(*src)++;
}
}

/**
* replace_variables - Replaces special variables in a command.
* @command: The input command.
* @prev_command_success: The success status of the previous command.
*
* Return: A newly allocated string with variables replaced.
*/
char *replace_variables(char *command, bool prev_command_success)
{
char *result = malloc(strlen(command) + 1);

if (!result)
{
perror("malloc");
exit(EXIT_FAILURE);
}

char *src = command;

while (*src)
{
replace_variable(&src, prev_command_success);
}

return (result);
}

/**
* handle_commands - Handles the execution of commands.
* @input: The input string containing multiple commands.
*/
void handle_commands(char *input)
{
char *command;
bool prev_command_success = true;

/* Tokenize the input using strtok */
command = strtok(input, ";");

while (command != NULL)
{
char *trimmed_command;
char *saveptr = NULL;

trimmed_command = strtok_r(command, " \t\n\r\f\v", &saveptr);

if (trimmed_command != NULL && trimmed_command[0] != '#')
{
char *replaced_command = replace_variables(trimmed_command,
prev_command_success);

if (strcmp(replaced_command, "&&") == 0)
{
prev_command_success = true;
}
else if (strcmp(replaced_command, "||") == 0)
{
prev_command_success = false;
}
else
{
if (prev_command_success)
{
/* Execute the command here */
printf("Executing: %s\n", replaced_command);
}
}

free(replaced_command);
}

command = strtok_r(NULL, ";", &saveptr);
}
}

int main(void)
{
char input[] = "echo $USER $$$$ $? && date; /* This is a comment */";
handle_commands(input);
return (0);
}

