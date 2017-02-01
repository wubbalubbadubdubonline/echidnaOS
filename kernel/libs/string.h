#ifndef __STRING_H__
#define __STRING_H__


#include "stddef.h"

size_t strlen(const char *);

int    strcmp(const char *, const char *);
int    strncmp(const char *, const char *, size_t);

const char  *strcpy(char *, const char *);
const char  *strncpy(char *, const char *, size_t);
const char  *strcat(char *, const char *);
const char  *strncat(char *, const char *, size_t);

const char  *strchr(const char *, int);
const char  *strrchr(const char *, int);
const char  *strstr(const char *, const char *);

void  *memset(void *, int, size_t);
int    memcmp(const void *, const void *, size_t);
void  *memcpy(void *, const void *, size_t);
void  *memmove(void *, const void *, size_t);

const void  *memchr(const void *, int, size_t);

#include "string.c"  //QOL feature for while the os is still small


#endif
