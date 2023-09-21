#include "shell.h"

/**
* execute_child_process - Execute the child process.
* @pipefd: The pipe file descriptors.
* @command: The command to execute.
*/
void execute_child_process(int pipefd[2], const char *command)
{
/** Close read end of the pipe*/
close(pipefd[0]);

/** Redirect stdout to the write end of the pipe*/
dup2(pipefd[1], STDOUT_FILENO);

/** Execute the command*/
system(command);

/** Close the write end of the pipe*/
close(pipefd[1]);

exit(EXIT_SUCCESS);
}

/**
* read_and_display_output - Read and display the command's output.
* @pipefd: The pipe file descriptors.
*/
void read_and_display_output(int pipefd[2])
{
ssize_t read_bytes;
char buffer[1024];

/** Close write end of the pipe*/
close(pipefd[1]);

/** Read the command's output from the pipe*/
while ((read_bytes = read(pipefd[0], buffer, sizeof(buffer))) > 0)
{
write(STDOUT_FILENO, buffer, read_bytes);
}
}
