#include "textdrv.h"

/* internal functions */

void clear_cursor(void);
void draw_cursor(void);
void scroll(void);

/* internal global variables */

int cursor_offset = 0;
int cursor_status = 1;
char cursor_palette = 0x07;
char text_palette = 0x70;

/* internal functions */

void clear_cursor(void) {
	char *vidmem = (char*) VIDEO_ADDRESS;
	vidmem[cursor_offset+1] = text_palette;
}

void draw_cursor(void) {
	char *vidmem = (char*) VIDEO_ADDRESS;
	if (cursor_status) {
		vidmem[cursor_offset+1] = cursor_palette;
	}
}

void scroll(void) {
	int offset;
	char *vidmem = (char*) VIDEO_ADDRESS;
	for (offset=0; offset<=VIDEO_BOTTOM-COLS; offset=offset+1) {
		vidmem[offset] = vidmem[offset+COLS];
	}
	for (offset=VIDEO_BOTTOM; offset>VIDEO_BOTTOM-COLS; offset=offset-2) {
		vidmem[offset] = text_palette;
		vidmem[offset-1] = ' ';
	}
}

/* external functions */

void text_clear(void) {
	int offset;
	char *vidmem = (char*) VIDEO_ADDRESS;
	clear_cursor();
	for (offset=0; offset<VIDEO_BOTTOM; offset=offset+2) {
		vidmem[offset] = ' ';
		vidmem[offset+1] = text_palette;
	}
	cursor_offset=0;
	draw_cursor();
}

void text_enable_cursor(void) {
	cursor_status=1;
	draw_cursor();
}

void text_disable_cursor(void) {
	cursor_status=0;
	clear_cursor();
}

void text_putchar(char c) {
	char *vidmem = (char*) VIDEO_ADDRESS;
	clear_cursor();
	vidmem[cursor_offset] = c;
	if (cursor_offset == VIDEO_BOTTOM-1) {
		scroll();
		cursor_offset = VIDEO_BOTTOM - (COLS-1);
	} else {
		cursor_offset = cursor_offset+2;
	}
	draw_cursor();
}

void text_putstring(char *string) {
	int x;
	for (x=0; string[x]!=0; x++) {
		text_putchar(string[x]);
	}
}
