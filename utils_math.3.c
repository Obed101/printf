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
