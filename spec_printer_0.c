#include <stdarg.h>
#include <stdlib.h>
#include "holberton.h"

/**
 * convert_fmt_percent - Prints a percent sign (%)
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
int convert_fmt_percent(va_list *args_list, fmt_info_t *fmt_info)
{
	(void)args_list;
	_putchar(fmt_info->spec);
	return (1);
}

/**
 * convert_fmt_p - Prints the pointer address
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
int convert_fmt_p(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, chars_count = 0, size = 16;
	void *num = va_arg(*args_list, void *);
	size_t tmp;
	char *str;

	(void)fmt_info;
	str = malloc(sizeof(char) * (size));
	if (str)
	{
		mem_set(str, 16, '0');
		tmp = ((size_t)&num);
		for (i = 0; i <= size && tmp > 0; i++)
		{
			*(str + i) = (tmp % 16) < 10 ? (tmp % 16) + '0'
				: (tmp % 16) - 10 + 'A';
			tmp /= 16;
		}
		for (i = size - 1; i >= 0; i--)
			_putchar(*(str + i));
		chars_count += size;
		free(str);
	}
	return (chars_count);
}

/**
 * convert_fmt_c - Prints a character
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
int convert_fmt_c(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, chars_count = 0, len = 1;
	char str = va_arg(*args_list, int);

	if (!fmt_info->left)
	{
		for (i = 0; i < MAX(len, fmt_info->width) - len; i++)
			_putchar(fmt_info->pad);
	}
	_putchar(str == '\0' ? ' ' : str);
	chars_count += MAX(len, fmt_info->width) - len + 1;
	if (fmt_info->left)
	{
		for (i = 0; i < MAX(len, fmt_info->width) - len; i++)
			_putchar(' ');
	}
	return (chars_count);
}

/**
 * convert_fmt_s - Prints a string
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
int convert_fmt_s(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, chars_count = 0, len;
	char *str = va_arg(*args_list, char *);
	char null_str[] = "(null)";

	str = str ? str : null_str;
	len = str_len(str);
	if (!fmt_info->left)
	{
		for (i = 0; i < MAX(len, fmt_info->width) - len; i++)
			_putchar(fmt_info->pad);
	}
	chars_count += MAX(len, fmt_info->width) - len;
	_putstr(str);
	chars_count += str_len(str);
	if (fmt_info->left)
	{
		for (i = 0; i < MAX(len, fmt_info->width) - len; i++)
			_putchar(' ');
	}
	return (chars_count);
}
