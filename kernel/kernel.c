/* stub kernel */

#include "libs/stddef.h"
#include "libs/stdint.h"
#include "libs/string.h"
#include "drivers/system.h"
#include "drivers/textdrv.h"
#include "drivers/ata.h"
#include "drivers/memory.h"
#include "drivers/paging.h"
#include "drivers/pic.h"

void _start(void) {

	text_clear();

	text_putstring("echidnaOS\n\n");

	text_putstring("Initialising PIC...");

	map_PIC(0x20, 0x28);

	text_putstring("Done.\n");

	system_halt();

}
