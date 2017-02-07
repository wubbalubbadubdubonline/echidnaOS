/* stub kernel */

#include "libs/stddef.h"
#include "libs/stdint.h"
#include "libs/string.h"
#include "libs/system.h"
#include "drivers/video/textdrv.h"

void _start(void) {

	magic_breakpoint();

	text_reset();

	system_halt();

}
