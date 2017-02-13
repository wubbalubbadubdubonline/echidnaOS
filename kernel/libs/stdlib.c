#include "stdlib.h"
#include "ctype.h"

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

/*
 * Converts an integer n to a null-terminated string using 
 * the specified base and stores the result in the array 
 * given by buf parameter.
 */
char *itoa(int n, char *buf, int base)
{
	char *cp = buf;

	if ( base == 10 && n < 0 )
		*cp++ = '-';

	while ( n )
	{
		*cp++ = base_digits[n % base];
		n /= base; 
	}

	*cp = '\0';

	return buf;
}