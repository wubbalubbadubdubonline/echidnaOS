#include "string.h"

size_t strlen(const char *s)
{
  size_t len;

  for ( len = 0; s[len]; len++ );

  return len;
}

int strcmp(const char *str1, const char *str2)
{
  size_t i;
  for ( i = 0; str1[i] || str2[i]; i++ )
  {
    if ( str1[i] > str2[i] ) return 1;
    if ( str1[i] < str2[i] ) return -1;
  }
  return 0;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
  size_t i;
  for ( i = 0; (str1[i] || str2[i]) && (i < len); i++ )
  {
    if ( str1[i] > str2[i] ) return 1;
    if ( str1[i] < str2[i] ) return -1;
  }
  return 0;
}

char *strcpy(char *dest, const char *src)
{
  for ( int i = 0; src[i]; i++ )
    dest[i] = src[i];

  return dest;
}

char *strncpy(char *dest, const char *src, size_t len)
{
  for ( int i = 0; src[i] && (i < len); i++ )
    dest[i] = src[i];

  return dest;
}

void *memset(void *arr, int val, size_t len)
{
  for (size_t i = 0; i < len; i++ )
    ((unsigned char *)arr)[i] = (unsigned char)val;

  return arr;
}

int memcmp(const void *m1, const void *m2, size_t len)
{
  size_t i;
  for ( i = 0; i < len; i++ )
  {
    if ( ((unsigned char *)m1)[i] > ((unsigned char *)m2)[i] )
      return 1;

    if ( ((unsigned char *)m1)[i] < ((unsigned char *)m2)[i] )
      return -1;
  }
  return 0;
}

void *memcpy(void *dest, const void *src, size_t len)
{
  for ( int i = 0; i < len; i++ )
    ((unsigned char *)dest)[i] = ((unsigned char *)src)[i];

  return dest;
}

/* MUST BE REIMPLEMENTED ONCE MALLOC IS IMPLEMENTED */
/* current implementation is vulnerable to a stack overflow */
void *memmove(void *dest, const void *src, size_t len)
{
  unsigned char cpy[len];
  memcpy(cpy, src, len);
  return memcpy(dest, cpy, len);
}

