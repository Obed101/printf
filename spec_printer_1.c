#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "holberton.h"

/**
 * convert_fmt_di - Prints a signed integer
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
int convert_fmt_di(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, chars_count = 0, len, zero_pads_count = 0;
	long num;
	char *str;

	if (fmt_info->is_long)
		num = va_arg(*args_list, long);
	else if (fmt_info->is_short)
		num = va_arg(*args_list, int) >> 2 * 8;
	else if (fmt_info->is_char)
		num = va_arg(*args_list, int) >> 3 * 8;
	else
		num = va_arg(*args_list, int);
	str = long_to_str(num);
	len = num < 0 || (num >= 0 && (fmt_info->show_sign || fmt_info->space))
						? 1
						: 0;
	if (str)
	{
		len += str_len(str);
		if (fmt_info->is_precision_set)
			zero_pads_count = fmt_info->prec - len > 0 ? fmt_info->prec - len : 0;
		else if (fmt_info->is_width_set && fmt_info->pad == '0' && !fmt_info->left)
			zero_pads_count = fmt_info->width - len > 0 ? fmt_info->width - len : 0;
		len += zero_pads_count;
		for (i = 0; !fmt_info->left && i < MAX(len, fmt_info->width) - len; i++)
			_putchar(' ');
		if (num < 0 || (num >= 0 && (fmt_info->show_sign || fmt_info->space)))
			_putchar(num < 0 ? '-'
				: (fmt_info->space && !fmt_info->show_sign ? ' ' : '+'));
		for (i = 0; i < zero_pads_count; i++)
			_putchar('0');
		for (i = num < 0 ? 1 : 0; *(str + i) != '\0'; i++)
			_putchar(*(str + i));
		chars_count += MAX(len, fmt_info->width) - len;
		chars_count += len;
		for (i = 0; fmt_info->left && i < MAX(len, fmt_info->width) - len; i++)
			_putchar(' ');
		free(str);
	}
	return (chars_count);
}

/**
 * convert_fmt_xX - Prints the hexadecimal format of an unsigned int argument
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
int convert_fmt_xX(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, chars_count = 0, size = 8, len = fmt_info->alt ? 2 : 0;
	unsigned int num = va_arg(*args_list, unsigned int), tmp;
	int zero_pads_count = 0;
	char *str;

	str = malloc(sizeof(char) * (size));
	if (str)
	{
		size = fmt_info->is_short ? 4 : (fmt_info->is_char ? 2 : 8);
		mem_set(str, 8, 0);
		tmp = num;
		for (i = 0; i <= size && tmp > 0; i++, len++)
		{
			*(str + i) = (tmp % 16) < 10 ? (tmp % 16) + '0'
				: (tmp % 16) - 10 + 'a' + (fmt_info->spec == 'X' ? -6 - 26 : 0);
			tmp /= 16;
		}
		if (fmt_info->is_precision_set)
			zero_pads_count = fmt_info->prec - i > 0 ? fmt_info->prec - i : 0;
		else if (fmt_info->is_width_set)
			zero_pads_count = fmt_info->width - len > 0 ? fmt_info->width - len : 0;
		len += zero_pads_count;
		for (i = 0; !fmt_info->left && i < MAX(len, fmt_info->width) - len; i++)
			_putchar(' ');
		chars_count += MAX(len, fmt_info->width) - len + zero_pads_count;
		if (fmt_info->alt)
			_putstr(fmt_info->spec == 'X' ? "0X" : "0x");
		for (i = 0; i < zero_pads_count; i++)
			_putchar('0');
		for (i = size - 1; i >= 0; i--)
		{
			if (*(str + i) != '\0')
				_putchar(*(str + i));
			chars_count += (*(str + i) != '\0' ? 1 : 0);
		}
		for (i = 0; fmt_info->left && i < MAX(len, fmt_info->width) - len; i++)
			_putchar(' ');
		free(str);
	}
	return (chars_count);
}

/**
 * convert_fmt_o - Prints the octadecimal format of a signed int argument
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
int convert_fmt_o(va_list *args_list, fmt_info_t *fmt_info)
{
	int i = 0, chars_count = 0, zero_pads_count = 0, size = 21, len = 0;
	long num;
	char *str;

	if (fmt_info->is_long)
		num = va_arg(*args_list, unsigned long);
	else if (fmt_info->is_short || fmt_info->is_char)
		num = va_arg(*args_list, unsigned int) >> (fmt_info->is_short ? 2 : 3) * 8;
	else
		num = va_arg(*args_list, unsigned int);
	str = long_to_oct(num);
	if (str)
	{
		size = str_len(str);
		len += size;
		if (fmt_info->is_precision_set)
			zero_pads_count = fmt_info->prec - len > 0 ? fmt_info->prec - len : 0;
		else if (fmt_info->is_width_set)
			zero_pads_count = fmt_info->width - len > 0 ? fmt_info->width - len : 0;
		len += zero_pads_count + (fmt_info->alt && zero_pads_count == 0 ? 0 : 1);
		for (i = 0; !fmt_info->left && i < MAX(len, fmt_info->width) - len; i++)
			_putchar(' ');
		chars_count += MAX(len, fmt_info->width) - len + zero_pads_count;
		if (fmt_info->alt && zero_pads_count == 0)
			_putchar('0');
		chars_count += (fmt_info->alt && zero_pads_count == 0 ? 1 : 0);
		for (i = 0; i < zero_pads_count; i++)
			_putchar('0');
		for (i = 0; i < size; i++)
		{
			_putchar(*(str + i));
			chars_count++;
		}
		for (i = 0; fmt_info->left && i <= MAX(len, fmt_info->width) - len; i++)
			_putchar(' ');
		free(str);
	}
	return (chars_count);
}

/**
 * convert_fmt_u - Prints an unsigned integer
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
int convert_fmt_u(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, chars_count = 0, len, zero_pads_count = 0;
	unsigned long num;
	char *str;

	if (fmt_info->is_short)
		num = va_arg(*args_list, unsigned int) >> 2 * 8;
	else
		num = va_arg(*args_list, unsigned long);
	str = u_long_to_str(num);
	if (str)
	{
		len = str_len(str);
		if (fmt_info->is_precision_set)
			zero_pads_count = fmt_info->prec - len > 0 ? fmt_info->prec - len : 0;
		len += zero_pads_count;
		for (i = 0; !fmt_info->left && i < MAX(len, fmt_info->width) - len; i++)
			_putchar(' ');
		for (i = 0; i < zero_pads_count; i++)
			_putchar('0');
		for (i = 0; *(str + i) != '\0'; i++)
			_putchar(*(str + i));
		chars_count += MAX(len, fmt_info->width) - len;
		chars_count += len;
		for (i = 0; fmt_info->left && i < MAX(len, fmt_info->width) - len; i++)
			_putchar(' ');
		free(str);
	}
	return (chars_count);
}
