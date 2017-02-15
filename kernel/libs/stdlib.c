#include "stdlib.h"
#include "ctype.h"
#include "string.h"

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

/*
 * Converts an integer n to a null-terminated string using 
 * the specified base and stores the result in the array 
 * given by buf parameter.
 */
char *itoa(int n, char *buf, int base)
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
	if ( base == 10 && n < 0 )
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

char *ltoa(long n, char *buf, int base)
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
	if ( base == 10 && n < 0 )
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