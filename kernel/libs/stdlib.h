#ifndef __STDLIB_H__
#define __STDLIB_H__


char *itoa(int, char *, int);
char *ltoa(long, char *, int);
char *lltoa(long long, char *, int);
int atoi(const char *);
long atol(const char *);
long long atoll(const char *);
void *endian_swap(void *, int);
char *ftoa(float, char *);
char *dtoa(double, char *);
int puts(const char *);
int printf(const char *, ...);


#endif