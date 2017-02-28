#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "stdarg.h"
#include "ctype.h"
#include "../drivers/textdrv.h"

char *_itoa(int, char *, int, int);
char *_ltoa(long, char *, int, int);
//char *_lltoa(long long, char *, int, int);

int puts(const char *str)
{
    int len = strlen(str);
    text_putstring(str);
    return len;
}

#define MOD_NONE 0
#define MOD_BYTE 1
#define MOD_SHORT 2
#define MOD_LONG 3
#define MOD_LONG_LONG 4

#define PAD_RIGHT 1
#define PAD_ZERO 2

int printf(const char *format, ...)
{
    int width, pad, fp_width, mod, sign, count = 0;

    va_list args;
    va_start(args, format);

    for ( ; *format; format++ )
    {
        if ( *format == '%' )
        {
            ++format;
            width = pad = mod = sign = 0;
            fp_width = -1;

            if ( *format == '\0' ) break;
            if ( *format == '%' ) goto out;
            if ( *format == 'n' )
            {
                *va_arg(args, int *) = count;
                continue;
            }

            if ( *format == '-' )
            {
                format++;
                pad = PAD_RIGHT;

                if ( *format == '+' )
                {
                    format++;
                    sign = 1;
                }
            }
            else if ( *format == '+' )
            {
                format++;
                sign = 1;

                if ( *format == '-' )
                {
                    format++;
                    pad = PAD_RIGHT;
                }
            }

            while ( *format == '0' )
            {
                format++;
                pad |= PAD_ZERO;
            }

            if ( *format == '*' )
            {
                format++;
                width = va_arg(args, int);
                width = width > 0 ? width : 0;
            }
            else
            {
                for ( ; *format >= '0' && *format <= '9'; format++ )
                {
                    width *= 10;
                    width += *format - '0';
                }
            }

            if ( *format == '.' )
            {
                format++;

                if( *format == '*' )
                {
                    fp_width = va_arg(args, int);
                    format++;
                }
                else if ( isdigit(*format) )
                {
                    fp_width = 0;

                    for ( ; *format >= '0' && *format <= '9'; format++ )
                    {
                        fp_width *= 10;
                        fp_width += *format - '0';
                    }
                }
            }

            if ( strncmp(format, "hh", 2) == 0 )
            {
                int i = 0;

                switch ( tolower(*(format+2)) )
                {
                    case 'd':
                    case 'i':
                    case 'x':
                    case 'u':
                        mod = MOD_BYTE;
                        format += 2;
                        break;
                    default:
                        while ( format[--i] != '%' );

                        for( ; i < 3 ; i++ )
                            text_putchar(format[i]);
//                        text_putstring(format[i], (format + 3) - &format[i]);

                        format += 3;
                        continue;
                }
            }
            else if ( *format == 'h' )
            {
                int i = 0;

                switch ( tolower(*(format+1)) )
                {
                    case 'd':
                    case 'i':
                    case 'x':
                    case 'u':
                        mod = MOD_SHORT;
                        format++;
                        break;
                    default:
                        while ( format[--i] != '%' );

                        for( ; i < 2 ; i++ )
                            text_putchar(format[i]);
//                        text_putstring(format[i], (format + 2) - &format[i]);

                        format += 2;
                        continue;
                }
            }
/*            else if ( strncmp(format, "ll", 2) == 0 )
            {
                int i = 0;

                switch ( tolower(*(format+1)) )
                {
                    case 'd':
                    case 'i':
                    case 'x':
                    case 'u':
                        mod = MOD_LONG_LONG;
                        format++;
                        break;
                    default:
                        while ( format[--i] != '%' );

                        for( ; i < 3 ; i++ )
                            text_putchar(format[i]);
//                        text_putstring(format[i], (format + 3) - &format[i]);

                        format += 3;
                        continue;
                }
            }*/
            else if ( *format == 'l' )
            {
                int i = 0;

                switch ( tolower(*(format+1)) )
                {
                    case 'd':
                    case 'i':
                    case 'x':
                    case 'u':
                        mod = MOD_LONG;
                        format++;
                        break;
                    default:
                        while ( format[--i] != '%' );

                        for( ; i < 3 ; i++ )
                            text_putchar(format[i]);
//                        text_putstring(format[i], (format + 2) - &format[i]);

                        format += 2;
                        continue;
                }
            }

            //done
            if( *format == 's' )
            {
                char *s = va_arg(args, char *);
                int length = strlen(s);

                if ( width > 0 )
                {
                    count += width;
                    if ( !(pad & PAD_RIGHT) )
                    {
                        if ( length > width )
                        {
                            for ( int i = 0; i < width; i++ )
                                text_putchar(s[i]);
                        }
                        else
                        {
                            for ( int i = width - length; i; i-- )
                                text_putchar(' ');

                            text_putstring(s);
                        }
                    }
                    else
                    {
                        for ( ; width--;  )
                        {
                            *s ? text_putchar(*s++) : text_putchar(' ');
                        }
                    }
                }
                else
                {
                    text_putstring(s);
                    count += length;
                }

                continue;
            }
            //done?
            if( *format == 'd' || *format == 'i' )
            {
                char buf[21];
                char padchar = pad & PAD_ZERO ? '0' : ' ';
                uint64_t n;
                int _len;

                switch(mod)
                {
                    case MOD_BYTE:
                        n = va_arg(args, unsigned char);
                        break;

                    case MOD_SHORT:
                        n = va_arg(args, unsigned short);
                        break;

                    case MOD_NONE:
                        n = va_arg(args, unsigned int);
                        break;

                    case MOD_LONG:
                        n = va_arg(args, unsigned long);
                        break;

//                    case MOD_LONG_LONG:
//                        n = va_arg(args, unsigned long long);
                }

                _len = strlen(ltoa(n, buf, 10));
                width -= _len;

                if ( sign && buf[0] != '-' ) width--, count++;

                count += _len + (width > 0 ? width : 0);

                if ( pad && !(pad & PAD_RIGHT) )
                {
                    if ( sign && buf[0] != '-' && padchar == '0' )
                        text_putchar('+');

                    for ( ; width > 0; width-- ) 
                        text_putchar(padchar), count++;

                    if ( sign && buf[0] != '-' && padchar == ' ')
                        text_putchar('+');
                }

                text_putstring(buf);

                if ( pad & PAD_RIGHT )
                    for ( ; width > 0; width-- )
                        text_putchar(' ');

                continue;
            }
            //todo
            if( *format == 'x' )
            {
                char buf[16];
                char padchar = pad & PAD_ZERO ? '0' : ' ';
                uint64_t n;
                int _len;

                switch(mod)
                {
                    case MOD_BYTE:
                        n = va_arg(args, unsigned char);
                        break;

                    case MOD_SHORT:
                        n = va_arg(args, unsigned short);
                        break;

                    case MOD_NONE:
                        n = va_arg(args, unsigned int);
                        break;

                    case MOD_LONG:
                        n = va_arg(args, unsigned long);
                        break;

//                    case MOD_LONG_LONG:
//                        n = va_arg(args, unsigned long long);
                }

                _len = strlen(ltoa(n, buf, 16));
                width -= _len;

                count += _len + (width > 0 ? width : 0);

                if ( pad && !(pad & PAD_RIGHT) )
                    for ( ; width > 0; width-- ) 
                        text_putchar(padchar), count++;

                text_putstring(buf);

                if ( pad & PAD_RIGHT )
                    for ( ; width > 0; width-- )
                        text_putchar(' ');

                continue;
            }
            //todo
            if( *format == 'X' )
            {
                char buf[16];
                char padchar = pad & PAD_ZERO ? '0' : ' ';
                uint64_t n;
                int _len;

                switch(mod)
                {
                    case MOD_BYTE:
                        n = va_arg(args, unsigned char);
                        break;

                    case MOD_SHORT:
                        n = va_arg(args, unsigned short);
                        break;

                    case MOD_NONE:
                        n = va_arg(args, unsigned int);
                        break;

                    case MOD_LONG:
                        n = va_arg(args, unsigned long);
                        break;

//                    case MOD_LONG_LONG:
//                        n = va_arg(args, unsigned long long);
                }

                _len = strlen(ltoa(n, buf, 16));
                width -= _len;

                count += _len + (width > 0 ? width : 0);

                if ( pad && !(pad & PAD_RIGHT) )
                    for ( ; width > 0; width-- ) 
                        text_putchar(padchar), count++;

                for ( int i = 0; buf[i] = toupper(buf[i]); i++ );

                text_putstring(buf);

                if ( pad & PAD_RIGHT )
                    for ( ; width > 0; width-- )
                        text_putchar(' ');
                continue;
            }
            //todo
            if( *format == 'u' )
            {
                char buf[21], padchar;
                uint64_t n;
                switch ( mod )
                {
                    case MOD_BYTE:
                        n = va_arg(args, unsigned char);
                        break;

                    case MOD_SHORT:
                        n = va_arg(args, short);
                        break;

                    case MOD_NONE:
                        n = va_arg(args, unsigned int);
                        break;

                    case MOD_LONG:
                        n = va_arg(args, unsigned long);
                        break;

//                    case MOD_LONG_LONG:
//                        n = va_arg(args, unsigned long long);
                }

                int _len = strlen(_ltoa(n, buf, 10, 0));

                count += _len;
                if ( pad )
                {
                    width -= _len;
                    count += width > 0 ? width : 0;
                    padchar = pad & PAD_ZERO ? '0' : ' ';

                    if ( !(pad & PAD_RIGHT) )
                    {
                        for ( ; width > 0; width-- )
                            text_putchar(padchar);
                    }
                }

                text_putstring(buf);

                if ( pad & PAD_RIGHT )
                    for ( ; width > 0; width-- )
                        text_putchar(' ');

                continue;
            }
            //done
            if( *format == 'c' )
            {
                /* char are converted to int when pushed on the stack */
                text_putchar((char)va_arg(args, int));
                count++;
                continue;
            }

/*            if ( tolower(*format) == 'f' )
            {
                //
            }

            if ( tolower(*format) == 'g' )
            {
                //
            }

            if ( tolower(*format) == 'a' )
            {
                //
            }*/

        }

        else
        {
        out:
            text_putchar(*format);
            count++;
        }
    }

    va_end(args);
    return count;
}