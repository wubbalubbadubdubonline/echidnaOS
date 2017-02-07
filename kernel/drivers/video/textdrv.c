#include "textdrv.h"

/* internal global variables */

//int cursor_offset=0;
//int cursor_status=1;
//char cursor_palette=0x70;
//char text_palette=0x07;

/* internal functions */

void text_reset(void) {
	char text_palette=0x70;
	int offset=0;
    char *vidmem = (char*) VIDEO_ADDRESS;
	for ( ; offset<0xFA0; offset=offset+2) {
		vidmem[offset] = ' ';
		vidmem[offset+1] = text_palette;
	}
}


