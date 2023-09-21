#include "shell.h"
#include <unistd.h>

/**
* printEnvironment - Prints the environment variables
*/
void printEnvironment(void)
int i;
{
char **env_var = environ; /** Access the environment variables*/

for (i = 0; env_var[i] != NULL; i++)
{
char *env = env_var[i];
while (*env)
{
_putchar(*env);
env++;
}
_putchar('\n');
}
}
