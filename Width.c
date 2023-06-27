#include "main.h"

/**
 *
 * @format: Formatted string can print the argument
 *
 * @i: List of arguments that should printed
 * @list: list of arguments.
 *
 * get_width - Calculate the width for printing
 * Return: width
 */

int get_width( const char *format, int *i, va_list list )
{
	int curr_i;
	int width = 0;

	for ( curr_i = *i + 1; format[curr_i] != '\0'; curr_i++ )
	{
		if ( is_digit( format[curr_i] ))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if ( format[curr_i] == '*' )
		{
			curr_i++;
			width = va_arg( list, int );
			break;
		}
		else
			break;
	}

	*i=curr_i - 1;

	return ( width );
}
