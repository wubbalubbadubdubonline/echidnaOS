#include "stdlib.h"
#include "ctype.h"
#include "string.h"
#include "stdint.h"
#include "math.h"

const char *base_digits = "0123456789abcdefghijklmnopqrstuvwxyz";

/* converts a base 10 number in ascii to an int */
int atoi(const char *str)
{
	int res = 0;
	int sign = 1;

	while ( isspace(*str) ) str++;

	if ( *str == '-' )
	{
		sign = -1;
		str++;
	}
	else if ( *str == '+' )
	{
		str++;
	}

	for ( ; *str; str++ )
	{
		if ( isdigit(*str) )
			res = res * 10 + (*str - '0');
		else
			return res;
	}

	return res;
}

long atol(const char *str)
{
	long res = 0;
	int sign = 1;

	while ( isspace(*str) ) str++;

	if ( *str == '-' )
	{
		sign = -1;
		str++;
	}
	else if ( *str == '+' )
	{
		str++;
	}

	for ( ; *str; str++ )
	{
		if ( isdigit(*str) )
			res = res * 10 + (*str - '0');
		else
			return res;
	}

	return res;
}

long long atoll(const char *str)
{
	long long res = 0;
	int sign = 1;

	while ( isspace(*str) ) str++;

	if ( *str == '-' )
	{
		sign = -1;
		str++;
	}
	else if ( *str == '+' )
	{
		str++;
	}

	for ( ; *str; str++ )
	{
		if ( isdigit(*str) )
			res = res * 10 + (*str - '0');
		else
			return res;
	}

	return res;
}

/*
 * Converts an integer n to a null-terminated string using 
 * the specified base and stores the result in the array 
 * given by buf parameter.
 */
char *_itoa(int n, char *buf, int base, int sign)
{
	if ( n == 0 )
	{
		buf[0] = '0';
		buf[1] = '\0';
		return buf;
	}

	/* large enough to hold binary ~0 plus the null byte */
	char tmp[(sizeof(int)*8)+1];
	unsigned int m;

	char *cp = tmp;

	/* if using base 10, enable negative numbers */
	if ( base == 10 && sign && n < 0 )
	{
		*cp++ = '-';
		n *= -1;
	}

	m = n;

	/* create number in reverse for convenience */
	while ( m )
	{
		*cp++ = base_digits[m % base];
		m /= base;
	}

	*cp = '\0';

	/* now it's time to copy the sting to buf in proper order */
	cp = buf;

	if ( base == 10 && *tmp == '-' )
		*cp++ = *tmp;

	int len = strlen(tmp);

	for ( int i = len-1; i >= 0; i-- )
		*cp++ = tmp[i];

	/* if the number is negative, then we copied the sign twice */
	if ( *tmp == '-' )
		cp--;

	*cp = '\0';

	return buf;
}

char *_ltoa(long n, char *buf, int base, int sign)
{
	if ( n == 0 )
	{
		buf[0] = '0';
		buf[1] = '\0';
		return buf;
	}

	/* large enough to hold binary ~0 plus the null byte */
	char tmp[(sizeof(long)*8)+1];
	unsigned long m;

	char *cp = tmp;

	/* if using base 10, enable negative numbers */
	if ( base == 10 && sign && n < 0 )
	{
		*cp++ = '-';
		n *= -1;
	}

	m = n;

	/* create number in reverse for convenience */
	while ( m )
	{
		*cp++ = base_digits[m % base];
		m /= base;
	}

	*cp = '\0';

	/* now it's time to copy the sting to buf in proper order */
	cp = buf;

	if ( base == 10 && *tmp == '-' )
		*cp++ = *tmp;

	int len = strlen(tmp);

	for ( int i = len-1; i >= 0; i-- )
		*cp++ = tmp[i];

	/* if the number is negative, then we copied the sign twice */
	if ( *tmp == '-' )
		cp--;

	*cp = '\0';

	return buf;
}

char *_lltoa(long long n, char *buf, int base, int sign)
{
	if ( n == 0 )
	{
		buf[0] = '0';
		buf[1] = '\0';
		return buf;
	}

	/* large enough to hold binary ~0 plus the null byte */
	char tmp[(sizeof(long long)*8)+1];
	unsigned long long m;

	char *cp = tmp;

	/* if using base 10, enable negative numbers */
	if ( base == 10 && sign && n < 0 )
	{
		*cp++ = '-';
		n *= -1;
	}

	m = n;

	/* create number in reverse for convenience */
	while ( m )
	{
		*cp++ = base_digits[m % base];
		m /= base;
	}

	*cp = '\0';

	/* now it's time to copy the sting to buf in proper order */
	cp = buf;

	if ( base == 10 && *tmp == '-' )
		*cp++ = *tmp;

	int len = strlen(tmp);

	for ( int i = len-1; i >= 0; i-- )
		*cp++ = tmp[i];

	/* if the number is negative, then we copied the sign twice */
	if ( *tmp == '-' )
		cp--;

	*cp = '\0';

	return buf;
}

char *itoa(int n, char *buf, int base)
{
	return _itoa(n, buf, base, 1);
}

char *ltoa(long n, char *buf, int base)
{
	return _ltoa(n, buf, base, 1);
}
char *lltoa(long long n, char *buf, int base)
{
	return _lltoa(n, buf, base, 1);
}

#define BIG_ENDIAN 1
#define LITTLE_ENDIAN 2
#define LITTLE_ENDIAN_FLOAT 4
#define BIG_ENDIAN_FLOAT 8
int endianness = 0;

void *endian_swap(void * arg, int size)
{
	if ( size == 2 )
	{
		uint16_t n = *((uint16_t *)arg);
		n = ((n >> 8) & 0x000000ff) | ((n << 8) & 0x0000ff00);
		*(uint16_t *)arg = n;
	}
	else if ( size == 4 )
	{
	    uint32_t n = *((uint32_t *)arg);
		n = ((n >>  8) & 0x00ff00ff) | ((n <<  8) & 0xff00ff00);
		n = ((n >> 16) & 0x0000ffff) | ((n << 16) & 0xffff0000);
		*(uint32_t *)arg = n;   
	}
	else if ( size == 8 )
	{
		uint64_t n = *((uint64_t *)arg);
		n = ((n >> 8) & UINT64_C(0x00ff00ff00ff00ff)) 
		| ((n << 8) & UINT64_C(0xff00ff00ff00ff00));

		n = ((n >> 16) & UINT64_C(0x0000ffff0000ffff))
		| ((n << 16) & UINT64_C(0xffff0000ffff0000));

		n = ((n >> 32) & UINT64_C(0x00000000ffffffff))
		| ((n << 32) & UINT64_C(0xffffffff00000000));

		*(uint64_t *)arg = n;
	}

	return arg;
}

/*
 * single precision floating point binary representation:
 * sign (1 bit); exponent (8 bits); mantissa (21 bits)
 * 1             11111111           111111111111111111111
 *
 * example: -1.75 or -1.75 x 2^0 (^ means exponentiation here)
 * 1 01111111 11000000000000000000000
 * 
 * the exponent is encoded using an offset of 127 of 0, or in other words,
 * the real exponent is the encoded offset minus 127 and vice versa
 *
 * the mantissa is normalized, meaning that the values in it are shifted all
 * the way to the left
 *
 * another thing to note is that the mantissa has an "understood" 1
 * that is not shown and takes up no space. the format assumes the presence
 * of a 1 which allows it an extra bit of precision
 *
 */

char *ftoa(float n, char *res)
{
	// Extract integer part
	int64_t ipart = (int64_t)n;

	// Extract floating part
	float fpart = n - (float)ipart;

	// convert integer part to string
	int digits = strlen(lltoa(ipart, res, 10));

	res[digits++] = '.';  // add dot

	// Get the value of fraction part upto given no.
	// of points after dot. The 2nd parameter is needed
	// to handle cases like 233.007.
	fpart = fpart * pow(10, 8);

	lltoa((int64_t)fpart, res + digits, 10);

	return res;
}

char *dtoa(double n, char *res)
{
	// Extract integer part
	int64_t ipart = (int64_t)n;

	// Extract floating part
	double fpart = n - (double)ipart;

	// convert integer part to string
	int digits = strlen(lltoa(ipart, res, 10));

	res[digits++] = '.';  // add dot

	// Get the value of fraction part upto given no.
	// of points after dot. The 2nd parameter is needed
	// to handle cases like 233.007.
	fpart = fpart * pow(10, 16);

	lltoa((int64_t)fpart, res + digits, 10);

	return res;
}

/*
 * double precision floating point binary representation:
 * sign (1 bit); exponent (11 bits); mantissa (52 bits)
 * 1  11111111111  1111111111111111111111111111111111111111111111111111
 *
 * example: -1.75 or -1.75 x 2^0 (^ means exponentiation here)
 * 1  01111111111  1100000000000000000000000000000000000000000000000000
 * 
 * the exponent is encoded using an offset of 1023 of 0, or in other words,
 * the real exponent is the encoded offset minus 1023 and vice versa
 *
 * the mantissa is normalized, meaning that the values in it are shifted all
 * the way to the left
 *
 * another thing to note is that the mantissa has an "understood" 1
 * that is not shown and takes up no space. the format assumes the presence
 * of a 1 which allows it an extra bit of precision
 *
 */

// char *dtoa(char *buf, double val)
// {
// 	//
// }

/* printf - formatted printing */

/*int printf(const char *format, ...)
{
	const char *format_offset, *prev_offset = format;
	int count = 0;

	va_list vl;
	va_start(vl, format);

	// find the positions of format specifiers and print stuff
	while ( (format_offset = strchr(prev_offset, '%')) != NULL )
	{
		// print stuff that doesn't need to be formatted 
		text_putstring(prev_offset, format_offset - prev_offset);
		count += format_offset - prev_offset;

		count += _print_format(format_offset,);
		//
	}

	// print the remainder of the format string 
	text_putstring(prev_offset, strlen(prev_offset));
	count += strlen(prev_offset);

	return count;
}*/


