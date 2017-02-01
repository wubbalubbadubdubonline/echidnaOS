#ifndef __STDDEF_H__
#define __STDDEF_H__


#define NULL 			((void *)0)

#if defined(__32BIT__)
typedef unsigned int 		size_t;
#elif defined(__64BIT__)
typedef unsigned long		size_t;
#endif
typedef long long		ptrdiff_t;


#endif
