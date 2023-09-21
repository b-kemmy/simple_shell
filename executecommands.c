#include "shell.h"
/**
* executeCommands - Execute the user input as shell commands.
* @input: The user input string.
*/
void executeCommands(const char *input)
{
char *token;
char *commands[100];
int num_commands = 0;
token = strtok((char *)input, " ");
pid_t child_pid = fork();
commands[num_commands] = NULL;

while (token != NULL)
{
commands[num_commands] = token;
num_commands++;
token = strtok(NULL, " ");
}

if (child_pid == -1)
{
perror("fork");
return;
}
if (child_pid == 0)
{
if (execvp(commands[0], commands) == -1)
{
perror("execvp");
exit(EXIT_FAILURE);
}
}
else
{
int status;
waitpid(child_pid, &status, 0);

if (WIFEXITED(status))
{
int exit_status = WEXITSTATUS(status);
printf("Command exited with status %d\n", exit_status);
}
}
}
