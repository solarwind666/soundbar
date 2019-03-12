#ifndef LED_API_H
#define LED_API_H


#define SOFT_VERSION	01  	//软件版本显示


#define NO_USB			0
#define NO_TF			1
#define NO_REC			2
#define DISP_VERSION	3

#define REPEAT_ONE		0
#define REPEAT_ALL		1
#define REPEAT_FOLD		2
#define REPEAT_OFF		3

#define EQ_DISP0		0
#define EQ_DISP1		1
#define EQ_DISP2		2
#define EQ_DISP3		3

#define MIC_KOL			0
#define MIC_TRE			1
#define MIC_BAS			2
#define MIC_DEL			3
#define MIC_ECO			4

#define SET_DISP_TREBLE		0
#define SET_DISP_BASS		1

extern int ir_repeat_flag; 	   
void led_test(void);
void led_clear(void);
void ui_led_update_display(void);
void ui_led_scroll_hello(void);
void ui_led_scroll_gobye(void);
void ui_led_disp_mode(unsigned char mode);
void ui_led_disp_state(unsigned char sta);
void ui_led_disp_filenum(int num);
void ui_led_disp_music_time(int time);
void ui_led_disp_repeat(unsigned char sta);
void ui_led_disp_volume(int vol);
void ui_led_disp_eq(unsigned char eq);
void ui_led_disp_mic(unsigned char eq, unsigned char vol);
void ui_led_disp_col1(unsigned char flag);
void ui_led_disp_col2(unsigned char flag);
void ui_led_disp_seek(void);
void ui_led_disp_channel(int num);
void ui_led_disp_rgb_state(unsigned char sta);
void ui_led_disp_trebass(unsigned char sta, int value);
void led_clear_buffer(void);
void ui_led_disp_all(void);
void ui_update_disp(void);



#endif

