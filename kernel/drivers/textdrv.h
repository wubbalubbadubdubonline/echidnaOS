#ifndef __TEXTDRV_H__
#define __TEXTDRV_H__



void text_putchar(char c);
int text_get_cursor_pos_x(void);
int text_get_cursor_pos_y(void);
void text_set_cursor_pos(int x, int y);
void text_set_cursor_palette(char c);
char text_get_cursor_palette(void);
void text_set_text_palette(char c);
char text_get_text_palette(void);
void text_clear(void);
void text_disable_cursor(void);
void text_enable_cursor(void);
void text_putstring(char *string);



#endif
