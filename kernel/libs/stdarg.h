#ifndef __STDARG_H__
#define __STDARG_H__

#ifdef __32BIT__

typedef unsigned char *va_list;
#define va_start(vl, p) (vl = (((va_list)&p+sizeof(p))))
#define va_arg(vl, t) (*(t *)((vl += sizeof(t)) - sizeof(t)))
#define va_copy(vldest, vlsrc) (vldest = vlsrc)

#endif //32bit

#define va_end(vl) (vl = NULL)

#endif //stdarg.h