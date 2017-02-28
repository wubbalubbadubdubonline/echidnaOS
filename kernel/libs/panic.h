#ifndef __PANIC_H__
#define __PANIC_H__

#include "../libs/stdint.h"
#include "../libs/stddef.h"
#include "../drivers/textdrv.h"
#include "../drivers/system.h"


void panic(const char *msg);


#endif
