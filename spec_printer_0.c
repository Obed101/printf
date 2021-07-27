#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
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
	int i, chars_count = 0, size = 8;
	void *ptr = va_arg(*args_list, void *);
	long tmp = (long)ptr;
	char *str;

	(void)fmt_info;
	str = malloc(sizeof(char) * (size + 1));
	if (str && ptr)
	{
		mem_set(str, size, '0');
		for (i = 0; i < 8; i++)
		{
			*(str + i) = (tmp % 16) < 10 ? (tmp % 16) + '0'
				: (tmp % 16) - 10 + 'a';
			tmp /= 16;
		}
		*(str + i) = '\0';
		rev_string(str);
		str = trim_start(str, '0', TRUE);
		_putstr("0x");
		chars_count += 2;
		for (i = 0; i < size; i++)
			_putchar(*(str + i));
		chars_count += size;
		free(str);
	}
	else
	{
		_putstr("(nil)");
		chars_count += 5;
		if (str)
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
	len = fmt_info->is_precision_set && fmt_info->prec >= 0
		? fmt_info->prec : str_len(str);
	if (!fmt_info->left)
	{
		for (i = 0; i < MAX(len, fmt_info->width) - len; i++)
			_putchar(' ');
	}
	chars_count += MAX(len, fmt_info->width) - len;
	for (i = 0; i < len && *(str + i) != '\0'; i++)
		_putchar(*(str + i));
	chars_count += len;
	if (fmt_info->left)
	{
		for (i = 0; i < MAX(len, fmt_info->width) - len; i++)
			_putchar(' ');
	}
	return (chars_count);
}
