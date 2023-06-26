#include "main.h"
/**
 *
 * @buff_ind:  add next char, represents the length.
 *
 * @buffer: Array of chars
 *
 * print_buffer - show The details of the buffer if it exist
 */
void print_buffer( char buffer[], int *buff_ind )
{

	if ( *buff_ind > 0 )
		write( 1, &buffer[0], *buff_ind );

	*buff_ind=0;

}

void print_buffer( char buffer[], int *buff_ind );

/**
 * Return: Print the char
 * @format: format
 * _printf - Show the function
 */
int _printf( const char *format, ... )
{

	int flags, width, precision, size, buff_ind = 0;
	int i, printed=0, printed_chars = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if ( format == NULL )
		return ( -1 );

	va_start ( list, format );
	for ( i=0; format && format[i] != '\0'; i++)
	{

		if ( format[i] != '%')
		{
			buffer[buff_ind++]=format[i];
			if ( buff_ind == BUFF_SIZE )
				print_buffer( buffer, &buff_ind );
			printed_chars++;
		}
		else
		{
			print_buffer( buffer, &buff_ind );

			precision = get_precision( format, &i, list );
			width = get_width( format, &i, list );
			size = get_size( format, &i );
			flags = get_flags( format, &i );

			++i;
			printed = handle_print( format, &i, list, buffer, flags, width, precision, size );
			if ( printed == -1 )
				return ( -1 );
			printed_chars += printed;
		}
	}

	print_buffer( buffer, &buff_ind );
	va_end( list );
	
	return ( printed_chars );
}
