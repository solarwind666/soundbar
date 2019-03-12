#include <fcntl.h>
#include <silan_resources.h>
#include <silan_addrspace.h>
#include <stdio.h>
#include <string.h>
#include <zhuque_bsp_gpio.h>
#include "sl_bsp.h"
#include "led_api.h"
#include "led_driver.h"
#include "sl_ui_handle.h"
#include "sl_ui_cmd.h"


static unsigned short SegNum_Table[]={CHAR_0, CHAR_1, CHAR_2, CHAR_3 ,CHAR_4, CHAR_5, CHAR_6, CHAR_7,
CHAR_8, CHAR_9, CHAR_A, CHAR_B, CHAR_C, CHAR_D, CHAR_E, CHAR_F, CHAR_G, CHAR_H, CHAR_I, CHAR_J,
CHAR_K, CHAR_L, CHAR_M, CHAR_N, CHAR_O, CHAR_P, CHAR_Q, CHAR_R, CHAR_S, CHAR_T, CHAR_U, CHAR_V, 
CHAR_W, CHAR_X, CHAR_Y, CHAR_Z};

void led_test(void)
{


}

void ui_led_clear(void)
{
	bsp_led_io_init(1);
}

void ui_led_disp_all(void)
{
	bsp_led_io_init(0);
}

void ui_update_disp(void)
{
	static bool flag = false;
	if (is_start_to_update)
	{
		if (flag)
			ui_led_disp_all();
		else 
			ui_led_clear();		

		flag = flag ? false : true;
	}

}

void led_clear_buffer(void)
{

}

void ui_led_update_display(void)
{


}

void ui_led_disp_mode(unsigned char mode)
{
	bsp_led_io_init(1);

	switch (mode)
	{
		case SOURCE_SELECT_LINEIN:
			zhuque_bsp_gpio_set_mode(LED_AUX_PIN, GPIO_OUT, PUSH_PULL); 
			zhuque_bsp_gpio_set_value(LED_AUX_PIN , 0);
			break;
		case SOURCE_SELECT_LINEIN1:
			zhuque_bsp_gpio_set_mode(LED_RCA_PIN, GPIO_OUT, PUSH_PULL); 
			zhuque_bsp_gpio_set_value(LED_RCA_PIN , 0);
			break;
		case SOURCE_SELECT_SPDIFIN:
			zhuque_bsp_gpio_set_mode(LED_OPT_PIN, GPIO_OUT, PUSH_PULL); 
			zhuque_bsp_gpio_set_value(LED_OPT_PIN , 0);
			break;
		case SOURCE_SELECT_HDMI:
			zhuque_bsp_gpio_set_mode(LED_HDMI_PIN, GPIO_OUT, PUSH_PULL); 
			zhuque_bsp_gpio_set_value(LED_HDMI_PIN , 0);
			break;
		case SOURCE_SELECT_BT:
			zhuque_bsp_gpio_set_mode(LED_BT_PIN, GPIO_OUT, PUSH_PULL); 
			zhuque_bsp_gpio_set_value(LED_BT_PIN , 0);
			break;		
		/*
		case SOURCE_SELECT_USB:
			zhuque_bsp_gpio_set_mode(LED_AUX_PIN, GPIO_OUT, PUSH_PULL); 
			zhuque_bsp_gpio_set_value(LED_AUX_PIN , 0);
			zhuque_bsp_gpio_set_mode(LED_RCA_PIN, GPIO_OUT, PUSH_PULL); 
			zhuque_bsp_gpio_set_value(LED_RCA_PIN , 0);
			break;
		*/
	}

}

void ui_led_disp_state(unsigned char sta)
{

}

void ui_led_disp_filenum(int num)
{

}

void ui_led_disp_music_time(int time)
{

}

void ui_led_disp_repeat(unsigned char sta)
{

}


void ui_led_disp_trebass(unsigned char sta, int value)
{

}

void ui_led_disp_volume(int vol)
{

}


void ui_led_disp_eq(unsigned char eq)
{

}

void ui_led_disp_mic(unsigned char eq, unsigned char vol)
{

}

void ui_led_disp_col1(unsigned char flag)
{

}

void ui_led_disp_col2(unsigned char flag)
{

}

void ui_led_disp_seek(void)
{

}

void ui_led_disp_channel(int       num)
{


}




