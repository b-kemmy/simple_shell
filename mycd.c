#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * changeDirectory - Change the current working directory.
 * @path: The path to the new working directory.
 *
 * This function changes the current working directory to the specified path.
 * It also saves the old and new working directories.
 *
 * Return: None.
 */

void changeDirectory(char *path)
{
char *oldpwd = NULL;
char *newpwd = NULL;

/** Save the current working directory (oldpwd) for future reference*/
oldpwd = getcwd(NULL, 0);

if (oldpwd == NULL)
{
perror("getcwd");
return;
}

/** Change the current working directory*/
if (chdir(path) == -1)
{
perror("chdir");
free(oldpwd);
return;
}

/** Save the new current working directory (newpwd)*/
newpwd = getcwd(NULL, 0);

if (newpwd == NULL)
{
perror("getcwd");
free(oldpwd);
return;
}

/** Update the PWD environment variable*/
if (setenv("PWD", newpwd, 1) == -1)
{
perror("setenv");
}

/** Free allocated memory*/
free(oldpwd);
free(newpwd);
}
