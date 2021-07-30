#include "holberton.h"

/**
 * max_3 - Returns the maximum of three numbers
 * @a: The first number
 * @b: The second number
 * @c: The third number
 *
 * Return: The largest number
*/
int max_3(int a, int b, int c)
{
	int largest = a;

	if (b > a && b > c)
		largest = b;
	if (c > a && c > b)
		largest = c;
	return (largest);
}

/**
 * can_pad - Checks if the given fmt_info_t can use padding.
 * @f_inf: The format info
 *
 * Return: True or false
 */
char can_pad(fmt_info_t *f_inf)
{
	return (f_inf->pad == '0' || f_inf->is_precision_set);
}
