/* stub kernel */

#include "libs/stddef.h"
#include "libs/stdint.h"
#include "libs/string.h"
#include "drivers/system.h"
#include "drivers/textdrv.h"
#include "drivers/ata.h"
#include "drivers/memory.h"
#include "drivers/paging.h"

void _start(void) {

	uint16_t x;

	text_clear();

	text_putstring("echidnaOS\n");

	asm("xchg bx,bx");
	x=mem_load_w(0x7DFE);

	system_halt();

}
