#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "sl_lcd.h"

#include <nuttx/spi/spi.h>
#include "silan_gpio.h"

extern unsigned char enfont_tbl[];
static unsigned char *enfont_buf = enfont_tbl;

static unsigned char *lcd_buf = NULL;

#ifdef CONFIG_SC6138_SPI_CTRL
static  struct sc6138_spidev_s *priv = NULL;

#if CONFIG_CHIP_SC6138
#define INIT_GPIO() { \
    gpio_direction_output(16, 0);\
}
#define A0(i) zhuque_bsp_gpio_set_value(16, i)
#elif CONFIG_CHIP_AP1508
#define INIT_GPIO() { \
    gpio_direction_output(5, 0);\
}
#define A0(i) zhuque_bsp_gpio_set_value(5, i)
#endif

#define RES(i) //zhuque_bsp_gpio_set_value(7, i)

static void send_data(unsigned char *data, int len)
{
    struct spi_dev_s *spi_priv = (struct spi_dev_s *)priv;
	SPI_SNDBLOCK(spi_priv, data, len);
}

static void lcd_wr_cmd(unsigned char cmdx)
{
    A0(0);
	send_data(&cmdx, 1);
}

static void lcd_wr_data(unsigned char *data, int len)
{
    A0(1);
    send_data(data, len);
}
#else
#define GPIO_START_NUM 0//1*32

#define INIT_GPIO() { \
    int i; \
    for (i = 0; i < 4; i ++) \
    { \
        gpio_direction_output(GPIO_START_NUM + 15 + i, 0); \
    } \
    gpio_direction_output(GPIO_START_NUM + 7, 1); \
}

#define CS(i) zhuque_bsp_gpio_set_value(GPIO_START_NUM + 18, i)
//#define RES(i) //zhuque_bsp_gpio_set_value(GPIO_START_NUM + 14, i)
#define RES(i) zhuque_bsp_gpio_set_value(GPIO_START_NUM + 7, i)
#define A0(i) zhuque_bsp_gpio_set_value(GPIO_START_NUM + 16, i)
#define SI(i) zhuque_bsp_gpio_set_value(GPIO_START_NUM + 15, i)
#define SCL(i) zhuque_bsp_gpio_set_value(GPIO_START_NUM + 17, i)

void send_byte(unsigned char dat)
{
    unsigned char i;
    int j;

    for (i = 0; i < 8; i ++)
    {
        SCL(0);
        if ((dat & 0x80) != 0)
            SI(1);
        else
            SI(0);

        dat <<= 1;
        //up_ndelay(30);
        for (j = 0; j < 3; j++);
        SCL(1);
        for (j = 0; j < 3; j++);
        //ndelay(30);
    }
}

void lcd_wr_cmd(unsigned char cmdx)
{
    A0(0);
    CS(0);
    send_byte(cmdx);
    CS(1);
}

void lcd_wr_data(unsigned char *cmdx, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
    A0(1);
    CS(0);
    send_byte(cmdx[i]);
    CS(1);
    }
}
#endif

static void lcd_setx(unsigned char x)
{
    lcd_wr_cmd(0x10 | (x >> 4));
    lcd_wr_cmd(x & 0x0f);
}

static void lcd_sety(unsigned char page)
{
    lcd_wr_cmd(page | 0xb0);
}

static void lcd_refresh_line(unsigned char* buf, int line)
{
    lcd_setx(0);
    lcd_sety(line);
    lcd_wr_data(buf + line*LCD_WIDTH, LCD_WIDTH);	//zxh
}

static void lcd_refresh(unsigned char* buf)
{
    int j;

    for (j = 0; j < LCD_HEIGHT/8; j ++)
        lcd_refresh_line(buf, j);
}

static void lcd_hardware_init(void)
{
    INIT_GPIO();
/*
    RES(0); //reset
    up_mdelay(100);	//???
    RES(1);
*/
/*
    lcd_wr_cmd(0xe2);	//reset inside
    up_mdelay(20);
*/

//    lcd_wr_cmd(0x2c);	//Booster circuit ON
//    lcd_wr_cmd(0x2e);	//volatage regulator circuit ON
    lcd_wr_cmd(0x2f);	//voltage follower circuit ON
/*
    lcd_wr_cmd(0x23);
	lcd_wr_cmd(0x24);
*/
//    lcd_wr_cmd(0x81);
//    lcd_wr_cmd(0x28);
//  lcd_wr_cmd(0xa2);	//lcd bias 1/9
//  lcd_wr_cmd(0xa3);	//lcd bias 1/7
//  lcd_wr_cmd(0xa0);	//normal array
//  lcd_wr_cmd(0xa1);	//reverse array
//	lcd_wr_cmd(0xa6);	//normal display
//	lcd_wr_cmd(0xa7);	//reverse display
//	lcd_wr_cmd(0xa4);
//	lcd_wr_cmd(0xa5);	//display all points ON
  lcd_wr_cmd(0xc8);
//  lcd_wr_cmd(0xc0);	//x display reverse
//zxh
//	lcd_wr_cmd(0xf8);	//boost ratio mode
//	lcd_wr_cmd(0x00);
//
    lcd_wr_cmd(0xaf);	//lcd close ????
//    lcd_refresh(lcd_buf); //clear lcd
}

int lcd_open(void)//(struct inode* inode, struct file* filp)
{
	return 0;
}

int lcd_ioctl(int fd, int cmd, long arg)
{
    switch(cmd) {
        case LCD_IOCTL_REFRESH_SCR:
            lcd_refresh(lcd_buf);
            break;
        case LCD_IOCTL_REFRESH_LINE:
            lcd_refresh_line(lcd_buf, arg);
            break;
        default:
            break;
    }

    return 0;
}

#include "font.h"
#define	MAX_FONT_SIZE					64
BYTE font_buf_in[MAX_FONT_SIZE * (MAX_FONT_SIZE/PIXELS_PER_BYTE)];
BYTE font_buf_out[MAX_FONT_SIZE * (MAX_FONT_SIZE/PIXELS_PER_BYTE)];
static int cn_font_fd = 0;

int lcd_main(void)
{
    int ret;
#ifdef CONFIG_SC6138_SPI_CTRL
    struct spi_dev_s *spi_priv;
    spi_priv = up_spiinitialize(0);
    priv = (struct sc6138_spidev_s *)spi_priv;
	SPI_SETBITS(spi_priv, 8);
#else
	return -1;
#endif
	lcd_hardware_init();
    lcd_buf = (unsigned char*)malloc(SIZE);
	memset(lcd_buf, 0x0, SIZE);
    lcd_refresh(lcd_buf);

    cn_font_fd = font_init(CONFIG_CH_FNT_DEVNAME);
    if(cn_font_fd)
            ;
    else {
        printf("open file:%s failed!\n", CONFIG_CH_FNT_DEVNAME);
        return -1;
    }
	return tbl_init(CONFIG_TBL_DEVNAME);
}

static unsigned char *read_english_char(unsigned char mb)
{
    int offset, size;
    size = (EN_WIDTH/8)*EN_HEIGHT;
    offset = mb*size;

    return (unsigned char*)(enfont_buf + offset);
}

static void write_to_buf(int x, int y, int width, int height, unsigned char *data, bool chinese_skip)
{
	int i, j, offset;
	offset = y*LCD_WIDTH + x;
 	for (i = 0; i < height/8; i ++) {
    	for (j = 0; j < width; j ++) {
            if (x + j > LCD_WIDTH)
                continue;
      		*(lcd_buf + offset + j) = *(data + j);
		}
        offset += LCD_WIDTH;
        data += width;
   	}
}

/*
 *  mode=0, normal; mode=1, reverse;
 */
static bool show_value(int x, int y, WORD *string, int mode, int len)
{
    bool is_exceed = false;
    int i, j;
	int nWidth = 0;
    unsigned char *data;
    WORD wCode;
	WORD bytesPerLine = 0;
    x = x*CH_WIDTH;
	y = 2*y;
    for (i=0; i<len; i++) {
        wCode = string[i];      
        if (wCode < 0x80) {
            data = read_english_char((unsigned char)wCode);
            write_to_buf(x, y, EN_WIDTH, EN_HEIGHT, data, false);
            x += EN_WIDTH;
        }
        else {
	    if (cn_font_fd) {
		    nWidth = font_read_char_distX(wCode);
		    if(font_read_char_dot_array(wCode, font_buf_in, &bytesPerLine)) {
			memset(font_buf_out, 0, MAX_FONT_SIZE * (MAX_FONT_SIZE/PIXELS_PER_BYTE));
			display_char(font_get_ysize(), bytesPerLine, font_buf_in, font_buf_out);
			write_to_buf(x, y, bytesPerLine*8, font_get_ysize(), font_buf_out, true);
			x += bytesPerLine*8;
		    }
	    }
	    else {
		    wCode = '?';
		    data = read_english_char((unsigned char)wCode);
		    write_to_buf(x, y, EN_WIDTH, EN_HEIGHT, data, false);
		    x += EN_WIDTH;
	    }
        }
        if (x >= LCD_WIDTH) {
            is_exceed = true;
            break;
        }
    }
//	lcd_ioctl(0, LCD_IOCTL_REFRESH_SCR, 0);
	if (mode == 0)
		;
	else {
		for(j = y*LCD_WIDTH; j < (y+2)*LCD_WIDTH; ++j)
			*(lcd_buf+j) = ~(*(lcd_buf+j));
	}
	lcd_ioctl(0, LCD_IOCTL_REFRESH_LINE, y);
	lcd_ioctl(0, LCD_IOCTL_REFRESH_LINE, y + 1);
	for(j = y*LCD_WIDTH; j < (y+2)*LCD_WIDTH; ++j)
		*(lcd_buf+j) = 0;
    return is_exceed;
}

/*
 *  mode=0, normal; mode=1, reverse;
 *  format=0, gb2312/ascii; format=1, utf8;
 */
bool lcd_display(int x, int y, WORD *text, int mode, int len)
{
	return show_value(x, y, text, mode, len);
}

void lcd_clear(void)
{
	memset(lcd_buf, 0, SIZE);
	lcd_ioctl(0, LCD_IOCTL_REFRESH_SCR, 0);
}

//app_entry(lcd_main);
