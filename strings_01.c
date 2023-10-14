#include "main.h"

/**
 * _putcharerror - print char on stderror
 * @c: char
 * Return: nothing
 */
void _putcharerror(char c)
{
	write(2, &c, 1);
}

/**
 * print_number - prints an integer
 * @n: integer to be printed
 * Return: nothing
 */
void print_number(int n)
{
	unsigned int n1;

	if (n < 0)
	{
		n1 = -n;
		_putcharerror('-');
	}
	else
		n1 = n;

	if (n1 / 10)
		print_number(n1 / 10);
	_putcharerror((n1 % 10) + '0');
}
