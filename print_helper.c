#include <stdarg.h>
#include "holberton.h"

/**
 * print_repeat - Prints a character n times
 * @c: The character to print
 * @n: The number of times to print the character
 */
void print_repeat(char c, int n)
{
	int i;

	for (i = 0; i < n; i++)
		_putchar(c);
}

/**
 * _putnchars - Prints multiple characters
 * @n: The number of characters to print
 */
void _putnchars(int n, ...)
{
	int i;
	va_list args;

	if (n <= 0)
		return;
	va_start(args, n);
	for (i = 0; i < n; i++)
	{
		_putchar(va_arg(args, int));
	}
	va_end(args);
}
