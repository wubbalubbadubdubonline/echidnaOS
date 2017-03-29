#ifndef __STDARG_H__
#define __STDARG_H__


typedef unsigned char *va_list;
#define va_start(vl, p) (vl = (((va_list)&p+sizeof(p) > 4 ? sizeof(p) : 4)))
#define va_arg(vl, t) (*(t *)((vl += sizeof(t) > 4 ? sizeof(t) : 4) \
                                  - (sizeof(t) > 4 ? sizeof(t) : 4)))
#define va_copy(vldest, vlsrc) (vldest = vlsrc)
#define va_end(vl) (vl = NULL)

#endif //stdarg.h