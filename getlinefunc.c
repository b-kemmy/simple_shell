#include "shell.h"
/**
* my_getline - Read a line of text from the input stream.
* @lineptr: A pointer to the buffer where the line will be stored.
* @n: The size of the buffer.
* @stream: The input stream to read from.
* Return: The number of characters read (including the newline character),
*         or -1 on failure, or 0 if the end of the stream is reached.
*/
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
size_t i = 0;
int c;

if (*lineptr == NULL || *n == 0)
{
*n = 128; /** Initial buffer size */
*lineptr = (char *)malloc(*n);
if (*lineptr == NULL)
{
return (-1); /** Allocation failure */
}
}

while (1)
{
c = fgetc(stream);
if (c == EOF)
{
if (i == 0)
{
return (0); /** End of file */
}
break; /** End of line */
}
(*lineptr)[i++] = (char)c;
if (i >= *n)
{
ssize_t realloc_result = my_realloc(lineptr, n);
if (realloc_result == -1)
{
return (-1); /** Allocation failure */
}
}
if (c == '\n')
{
break; /** End of line */
}
}
(*lineptr)[i] = '\0'; /** Null-terminate the string */
return (i); /** Number of characters read */
}
/**
* my_realloc - Reallocate memory for the lineptr buffer.
* @lineptr: A pointer to the buffer where the line is stored.
* @n: The current size of the buffer.
*
* Return: 0 on success, -1 on failure.
*/
ssize_t my_realloc(char **lineptr, size_t *n)
{
*n += 128; /** Extend buffer size */
char *temp = (char *)realloc(*lineptr, *n);
if (temp == NULL)
{
return (-1); /** Allocation failure */
}
*lineptr = temp;
return (0);
}
