#include "shell.h"

/**
* exitShell - Exits the shell program gracefully
*/
void exitShell(void)
{
char message[] = "Exiting the shell.\n";
int i;

for (i = 0; message[i] != '\0'; i++)
{
_putchar(message[i]);
}
exit(0);
}
