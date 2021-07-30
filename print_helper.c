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

/**
 * is_letter - Checks if the given character is a letter
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_letter(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ? TRUE : FALSE);
}

/**
 * print_unknown_spec - Prints an unknown spec
 * @format: The format string
 * @pos: The position to start from
 * @length: The length of the unknown spec
 *
 * Return: number of positions to advance by
 */
int print_unknown_spec(const char *format, int pos, int length)
{
	int i = 0;

	_putchar('%');
	for (; i < length; i++)
	{
		if (!is_length(format[pos + i]))
			_putchar(format[pos + i]);
	}
	return (i - 1);
}
