#ifndef __GDT_H__
#define __GDT_H__

#include "../libs/stdint.h"
#include "../libs/stddef.h"

void create_GDT(void);
void load_segments(void);

#endif
