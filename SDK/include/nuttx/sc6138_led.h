#ifndef __INCLUDE_NUTTX_LED_H
#define __INCLUDE_NUTTX_LED_H

#define LED_MIN   0
#define LED_MAX   3
#define LED_RED   1 //PWM5
#define LED_GREEN 0 //PWM4
#define LED_BLUE  2 //PWM6
#define LED_WHITE 3

#define PWM_ON    0x01
#define PWM_OFF   0xff

extern void led_set_off(int color);
extern void led_set_on(int color, int level);
extern void led_set_valid(int color, int valid);
extern void led_set_flash(int flash, int ms);

#endif



