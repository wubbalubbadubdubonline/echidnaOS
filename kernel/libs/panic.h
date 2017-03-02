#ifndef __PANIC_H__
#define __PANIC_H__

#include <stdint.h>
#include <stddef.h>
#include "../drivers/textdrv.h"
#include "../drivers/system.h"


void panic(const char *msg);


#endif
