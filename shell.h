#ifndef SHELL_H
#define SHELL_H
#define MAX_ALIAS_NAME_LENGTH 100
#define MAX_ALIAS_VALUE_LENGTH 200
#define MAX_ALIASES 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stddef.h>

void executeParseCmd(char *input);
void exitShell(void);
int _putchar(char c);
void printEnvironment(void);
extern char **environ;
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);
ssize_t readInputWithBuffer(int fd, char *buffer, size_t bufSize);
char *my_strtok(char *str, const char *delim, char **saveptr);
void changeDirectory(char *path);
void handleCommandSeparator(char *input);
void handleCommands(char *input);
char *replaceVariables(char *command, bool prev_command_success);
void printAliases(void);
void printSpecificAliases(char *names[], int numNames);
void defineAlias(char *name, char *value);
int parseCmd(char *input, char **args);
void executeCmd(char **args, int num_args);
void displayPrompt(const char *prompt);
char *readInput();
void handleInput(char *input);
void executePipeCommand(const char *command);
void executeCmd(char **args, int num_args);
ssize_t my_realloc(char **lineptr, size_t *n);
void executeCommands(const char *commands);
#endif
