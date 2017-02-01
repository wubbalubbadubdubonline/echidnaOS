#ifndef __STDINT_H__
#define __STDINT_H__


#include "stddef.h"

typedef char			int8_t;
typedef short			int16_t;
typedef int			int32_t;
#if defined(__32BIT__)
typedef long long		int64_t;
#elif defined(__64BIT__)
typedef long			int64_t;
#endif
typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned int		uint32_t;
#if defined(__32BIT__)
typedef unsigned long long	uint64_t;
#elif defined(__64BIT__)
typedef unsigned long		uint64_t;
#endif

#define SIZE_MAX		((size_t)0x7FFFFFFF)
#define PTRDIFF_MAX		((ptrdiff_t)0x7FFFFFFFFFFFFFFF)
#define PTRDIFF_MIN		((ptrdiff_t)0x8000000000000000)

#define INT8_MIN 		((int8_t)0x80)
#define INT16_MIN 		((int16_t)0x8000)
#define INT32_MIN 		((int32_t)0x80000000)
#define INT64_MIN 		((int64_t)0x8000000000000000)

#define INT8_MAX 		((int8_t)0x7F)
#define INT16_MAX		((int16_t)0x7FFF)
#define INT32_MAX		((int32_t)0x7FFFFFFF)
#define INT64_MAX		((int64_t)0x7FFFFFFFFFFFFFFF)

#define INTMAX_C 		INT64_C
#define UINTMAX_C		UINT64_C

#define INT8_C(n)		(##nSS)
#define INT16_C(n)		(##nS)
#define INT32_C(n)		(##n)
#if defined(__32BIT__)
#define INT64_C(n)		(##nLL)
#elif defined(__64BIT__)
#define INT64_C(n)		(##nL)
#endif

#define UINT8_C(n)		(##nSSU)
#define UINT16_C(n)		(##nSU)
#define UINT32_C(n)		(##nU)
#if defined(__32BIT__)
#define UINT64_C(n)		(##nLLU)
#elif defined(__64BIT__)
#define UINT64_C(n)		(##nLU)
#endif


#endif
