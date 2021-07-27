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
		? 1 : 0;
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
      _putchar(num < 0 ? '-' : (fmt_info->space && !fmt_info->show_sign ? ' ' : '+'));
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
 * convert_fmt_fF - Prints the decimal representation of a double
 * @args_list: The arguments list
 * @fmt_info: The format info
 *
 * Return: The number of characters written
 */
int convert_fmt_fF(va_list *args_list, fmt_info_t *fmt_info)
{
	int i, chars_count = 0, len;
	double num = va_arg(*args_list, double);
  /* int zero_pads_count = 0, exponent; */
	char *str;
  ushort_t exp_size = fmt_info->is_long_double ? 15 : 11;
  ushort_t mant_size = fmt_info->is_long_double ? 64 : 52;
  float_info_t *flt_info;

  /* printf("fmt_fF--> %s\n", "product"); */
	if (fmt_info->spec == 'F')/* Conversion is known but ignored */
		return (0);
  flt_info = new_float_info(exp_size, mant_size);
  if (flt_info)
  {
    set_float_parts(num, exp_size, mant_size, flt_info);
    str = is_invalid(flt_info);
    if (!str)
    {
      str = float_to_str(flt_info, FALSE);
      /* printf("fF--> %s\n", "product"); */
      len = str_len(str);
      /* if (fmt_info->is_precision_set)
      // 	zero_pads_count = fmt_info->prec - i > 0 ? fmt_info->prec - i : 0;
      // else if (fmt_info->is_width_set)
      // 	zero_pads_count = fmt_info->width - len > 0 ? fmt_info->width - len : 0;
      // len += zero_pads_count;
      // for (i = 0; !fmt_info->left && i < MAX(len, fmt_info->width) - len; i++)
      // 	_putchar(' ');
      // chars_count += MAX(len, fmt_info->width) - len + zero_pads_count;
      // if (fmt_info->alt)
      // 	_putstr(fmt_info->spec == 'X' ? "0X" : "0x");
      // for (i = 0; i < zero_pads_count; i++)
      // 	_putchar('0');
			*/
      for (i = 0; i < len; i++)
      {
        if (*(str + i) != '\0')
        {
          _putchar(*(str + i));
          chars_count++;
        }
      }
      /* for (i = 0; fmt_info->left && i < MAX(len, fmt_info->width) - len; i++)
      // 	_putchar(' ');
			*/
    }
    else
    {
      len = str_len(str);
      for (i = 0; i < len; i++)
        _putchar(fmt_info->spec == 'f' ? TO_LOWER(str[i]) : TO_UPPER(str[i]));
      chars_count += len;
    }
    if (str)
      free(str);
		/* printf("fF_end0--> %s\n", "product"); */
    free_float_info(flt_info);
		/* printf("fF_end1--> %s\n", "product"); */
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
		for (i = 0; i <= size && tmp > 0; i++)
		{
			*(str + i) = (tmp % 16) < 10 ? (tmp % 16) + '0'
				: (tmp % 16) - 10 + 'a' + (fmt_info->spec == 'X' ? -6 - 26 : 0);
			tmp /= 16;
			len++;
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
			{
				_putchar(*(str + i));
				chars_count++;
			}
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
    num = va_arg(*args_list, long);
  else if (fmt_info->is_short)
    num = va_arg(*args_list, int) >> 2 * 8;
  else if (fmt_info->is_char)
    num = va_arg(*args_list, int) >> 3 * 8;
  else
    num = va_arg(*args_list, long);
	str = malloc(sizeof(char) * (size));
	if (str)
	{
		mem_set(str, size, 0);
    if (num == 0)
    {
      *(str + i++) = '0';
      len++;
    }
    for (i = 0; i <= size && num < 0; i++)
		{
			*(str + i) =  (num % 8) + '0';
			num /= 8;
			len++;
		}
		for (i = 0; i <= size && num > 0; i++)
		{
			*(str + i) =  (num % 8) + '0';
			num /= 8;
			len++;
		}
		if (fmt_info->is_precision_set)
			zero_pads_count = fmt_info->prec - i > 0 ? fmt_info->prec - i : 0;
		else if (fmt_info->is_width_set)
			zero_pads_count = fmt_info->width - len > 0 ? fmt_info->width - len : 0;
		len += zero_pads_count + (fmt_info->alt && zero_pads_count == 0 ? 0 : 1);
		for (i = 0; !fmt_info->left && i < MAX(len, fmt_info->width) - len; i++)
			_putchar(' ');
		chars_count += MAX(len, fmt_info->width) - len + zero_pads_count;
		if (fmt_info->alt && zero_pads_count == 0)
		{
      _putchar('0');
      chars_count++;
    }
		for (i = 0; i < zero_pads_count; i++)
			_putchar('0');
		for (i = size - 1; i >= 0; i--)
		{
			if (*(str + i) != '\0')
			{
				_putchar(*(str + i));
				chars_count++;
			}
		}
		for (i = 0; fmt_info->left && i < MAX(len, fmt_info->width) - len; i++)
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
