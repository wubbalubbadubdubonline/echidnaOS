#ifndef __TEXTDRV_H__
#define __TEXTDRV_H__



#define VIDEO_ADDRESS 0xB8000
#define VIDEO_BOTTOM 0xF9F
#define ROWS 25
#define COLS 160

void text_putchar(char c);
int text_get_cursor_pos_x();
int text_get_cursor_pos_y();
void text_set_cursor_pos(int x, int y);
void text_set_cursor_palette(char x);
void text_set_text_palette(char x);
void text_clear(void);
void text_disable_cursor(void);
void text_enable_cursor(void);
void text_putstring(char *string);



#endif
