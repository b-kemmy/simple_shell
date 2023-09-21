#include "shell.h"
#include <stddef.h>

/**
* my_strtok - Split a string into tokens
* @str: The input string to tokenize
* @delim: The delimiter character used for tokenization
* @saveptr: A pointer to a char pointer to maintain state between calls
*
* Return: A pointer to the next token, or NULL if there are no more tokens
*/
char *my_strtok(char *str, const char *delim, char **saveptr)
{
char *token;

if (str == NULL)
{
str = *saveptr;
}

str += strspn(str, delim); /** Skip leading delimiters*/

if (*str == '\0')
{
*saveptr = str;
return (NULL); /** No more tokens*/
}

token = str;
str = strpbrk(token, delim); /** Find the next delimiter*/

if (str == NULL)
{
*saveptr = token + strlen(token);
}
else
{
*str = '\0'; /** Null-terminate the token*/
*saveptr = str + 1; /** Save the next character for the next call*/
}

return (token);
}
