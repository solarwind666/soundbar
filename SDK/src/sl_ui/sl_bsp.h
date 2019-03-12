#ifndef SL_BSP_H
#define SL_BSP_H
#include <stdbool.h>


#define HW_MUTE_PIN			//46 //35
#define HW_BT_MUTE_PIN		12
#define HW_BT_PWR_PIN		//37

#define HW_MIC_PAIR_PIN		0 //46

#define HW_MIC_MUTE_PIN		//14 //22

#define HW_HDMI_CEC_PIN		16
#define HW_HDMI_DET_PIN		17

#define LED_OPT_PIN		38
#define LED_AUX_PIN	 	37
#define LED_BT_PIN		36
#define LED_RCA_PIN		35
#define LED_HDMI_PIN	42

#define LED_PIN_SEG1			0
#define LED_PIN_SEG2			0
#define LED_PIN_SEG3			0
#define LED_PIN_SEG4			0
#define LED_PIN_SEG5			0

#define LED_PIN_GRID1			0
#define LED_PIN_GRID2			0
#define LED_PIN_GRID3			0
#define LED_PIN_GRID4			0
#define LED_PIN_GRID5			0
#define LED_PIN_GRID6			0
#define LED_PIN_GRID7			0
#define LED_PIN_GRID8			0
#define LED_PIN_GRID9			0
#define LED_PIN_GRID10			0
#define LED_PIN_GRID11			0
#define LED_PIN_GRID12			0


extern	bool is_power_on_unmute;
void bsp_init(void);
void Hw_Amp_Mute(void);
void Hw_Amp_UnMute(void);
void Bt_Power_On(void);
void Bt_Power_Off(void);
void Bt_Mute(void);
void Bt_UnMute(void);
void bsp_early_init(void);
void Hw_PowerOn_UnMute(void);
void bsp_led_io_init(int value);
void print_pad_reg(void);
void pad_set_clear(void);
void set_pad_spdif(void);

#endif
