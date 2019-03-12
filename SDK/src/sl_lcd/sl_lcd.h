#ifndef __LCD_H
#define __LCD_H

#include "typedef.h"
#define LCD_DEV_NAME ("silan-lcd")

#define LCD_IOCTL_REFRESH_SCR 100 
#define LCD_IOCTL_REFRESH_LINE 101
#define SIZE	(LCD_WIDTH * LCD_HEIGHT / 8)

#define LCD_WIDTH  128
#define LCD_HEIGHT 64

#define EN_WIDTH      8
#define EN_HEIGHT     16
#define CH_WIDTH      16
#define CH_HEIGHT     16

#define MAX_STRING_LEN 128

#define GB_UNICODE_MAP_OFFSET	0x0
#define GB_UNICODE_TBL_OFFSET	0x7500


int lcd_ioctl(int fd, int cmd, long arg);
int lcd_open(void);
bool lcd_display(int x, int y, WORD *text, int mode, int len);
void lcd_clear(void);
int gb2312_to_utf8(char *src,int src_len, char *dst);
int utf8_to_gb2312(unsigned char *src, int src_len, unsigned char *dst, int dst_maxlen);
#endif
