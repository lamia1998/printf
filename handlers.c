#include "main.h"

/**
 *
 *
 * @ind: index can be the number starts in the buffer
 * @length: length of number
 * @width: spicify width
 * @flags: spicify flags
 *
 * write_pointer - write the memory address
 * @buffer: arrays of chars
 * @padd: the paddign represent by char
 * 
 * @extra_c: represent the extra char
 * @padd_start: index can the padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer( char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start )
{
	int i;

	if ( width > length )
	{
		for ( i = 3; i < width - length + 3; i++ )
			buffer[i] = padd;
		buffer[i] = '\0';
		if ( flags & F_MINUS && padd == ' ' )
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if ( extra_c )
				buffer[--ind] = extra_c;
			return ( write( 1, &buffer[ind], length ) + write( 1, &buffer[3], i - 3 ) );
		}
		else if (!( flags & F_MINUS ) && padd == ' ' )
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if ( extra_c )
				buffer[--ind] = extra_c;
			return ( write( 1, &buffer[3], i - 3 ) + write( 1, &buffer[ind], length ) );
		}
		else if (!( flags & F_MINUS ) && padd == '0' )
		{
			if ( extra_c )
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return ( write( 1, &buffer[padd_start], i - padd_start ) + write( 1, &buffer[ind], length - ( 1 - padd_start) - 2 ) );
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if ( extra_c )
		buffer[--ind] = extra_c;
	return ( write( 1, &buffer[ind], BUFF_SIZE - ind - 1 ) );
}



/**
 * write_number - Prints the string
 * @is_negative: List of arguments
 * @ind: types of char
 *
 * @buffer: buffer array to handle print
 * @flags:  calculate the active flags
 * @width: get width.
 *
 * @precision: precision specifier
 * @size: spicify size
 *
 * Return: Number of chars printed.
 */
int write_number( int is_negative, int ind, char buffer[], int flags, int width, int precision, int size )
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED( size );

	if (( flags & F_ZERO ) && !( flags & F_MINUS ))
		padd = '0';
	if ( is_negative )
		extra_ch = '-';
	else if ( flags & F_PLUS )
		extra_ch = '+';
	else if ( flags & F_SPACE )
		extra_ch = ' ';

	return ( write_num( ind, buffer, flags, width, precision, length, padd, extra_ch ));
}


/**
 * write_num - Write the number using the bufffer
 *@buffer: buffer
 * @ind: Index can the number starts on the buffer
 * 
 * @prec: Precision specifier
 * @flags: flags
 * @width: width
 *
 * @extra_c: Extra char
 * @length: Number length
 * @padd: pading char
 *
 *
 * Return: Number of printed chars.
 */
int write_num( int ind, char buffer[], int flags, int width, int prec, int length, char padd, char extra_c )
{
	int i, padd_start=1;

	if ( prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0 )
		return (0);
	if ( prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' )
		buffer[ind] = padd = ' ';
	if ( prec > 0 && prec < length )
		padd = ' ';
	while ( prec > length )
		buffer[--ind] = '0', length++;
	if ( extra_c != 0 )
		length++;
	if ( width > length )
	{
		for ( i = 1; i < width - length + 1; i++ )
			buffer[i] = padd;
		buffer[i] = '\0';
		if ( flags & F_MINUS && padd == ' ' )
		{
			if ( extra_c )
				buffer[--ind] = extra_c;
			return ( write( 1, &buffer[ind], length ) + write( 1, &buffer[1], i - 1 ));
		}
		else if (!( flags & F_MINUS ) && padd == ' ' )
		{
			if ( extra_c )
				buffer[--ind] = extra_c;
			return ( write( 1, &buffer[1], i - 1 ) + write( 1, &buffer[ind], length ) );
		}
		else if (!( flags & F_MINUS ) && padd == '0' )
		{
			if ( extra_c )
				buffer[--padd_start] = extra_c;
			return ( write( 1, &buffer[padd_start], i - padd_start ) + write( 1, &buffer[ind], length - ( 1 - padd_start ) ));
		}
	}
	if ( extra_c )
		buffer[--ind] = extra_c;
	return ( write( 1, &buffer[ind], length ));
}

/**
 * handle_write_char - Prints the string
 *
 * @c: types of char
 * @buffer: buffer array to handle print
 * @flags:  calculate the active flags.
 *
 * @width: get width.
 * @precision: precision specifier
 * @size: spicify size
 *
 * Return: Number of chars printed.
 */

int handle_write_char( char c, char buffer[], int flags, int width, int precision, int size )
{
	int i = 0;
	char padd = ' ';

	UNUSED( size );
	UNUSED( precision );

	if ( flags & F_ZERO )
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if ( width > 1 )
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for ( i = 0; i < width - 1; i++ )
			buffer[BUFF_SIZE - i - 2] = padd;

		if ( flags & F_MINUS )
			return ( write( 1, &buffer[0], 1 ) + write( 1, &buffer[BUFF_SIZE - i - 1], width - 1 ));
		else
			return (write( 1, &buffer[BUFF_SIZE - i - 1], width - 1 ) + write( 1, &buffer[0], 1 ));
	}

	return ( write( 1, &buffer[0], 1 ));
}

/**
 *
 * @ind: Index can be the number starts in the buffer
 * @buffer: Array of char
 * @flags: spicify flags
 *
 * write_unsgnd - Writes the unsigned number
 * @is_negative: if the number is negative will be indicating
 *
 * @width: spicify width 
 * @precision: Precision specifier
 * @size: spicify size
 *
 * Return: Number of written chars.
 */
int write_unsgnd( int is_negative, int ind, char buffer[], int flags, int width, int precision, int size )
{
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED( size );
	UNUSED( is_negative );

	if ( precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' )
		return ( 0 );

	if ( precision > 0 && precision < length )
		padd = ' ';

	while ( precision > length )
	{
		buffer[--ind] = '0';
		length++;
	}

	if (( flags & F_ZERO ) && !( flags & F_MINUS ))
		padd = '0';

	if ( width > length )
	{
		for ( i = 0; i < width - length; i++ )
			buffer[i] = padd;

		buffer[i] = '\0';

		if ( flags & F_MINUS )
		{
			return ( write( 1, &buffer[ind], length ) + write( 1, &buffer[0], i ) );
		}
		else
		{
			return ( write( 1, &buffer[0], i ) + write( 1, &buffer[ind], length ) );
		}
	}

	return ( write( 1, &buffer[ind], length ) );
}
