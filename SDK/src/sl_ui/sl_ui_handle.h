#ifndef __SL_UI_HANDLE_H__
#define __SL_UI_HANDLE_H__
#include <semaphore.h>

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define AUDIO_ENERGY_DEBUG
#define IIS_SAMP_48K		1
#define IIS_SAMP_44K		0


//BASS/TREBLE|¡§???¡§¡é?????¡ì??|¡§??¡§o???100???¡ì2?¡§¡è?¡ìa1??DB?¡§¡é????¡ì?12DB
#define BASS_TREBLE_GAIN_MAX 600
//BASS/TREBLE|¡§?????¡ìoy
#define BASS_TREBLE_LEVEL  7
//BASS/TREBLE|¡§??2????|¡§?
#define BASS_TREBLE_STEP  1
//BASS/TREBLE|¡§?????¡ì???2????|¡§?
#define BASS_TREBLE_GAIN_STEP  (BASS_TREBLE_GAIN_MAX/BASS_TREBLE_LEVEL)
//MIC?¡§¡é????¡ì??¡ì????¡ì?¨¦?
#define MAX_MIC_VOL		32
//MIC ?¡§¡é????¡ì???¡ì?3?¡ì??
#define MAX_MIC_DELAY	5
//MIC ?¡§¡é????¡ì???¡ì???¡ì?
#define MAX_MIC_MIX		16
//MIC ?¡§¡é????¡ì???¡ì??¡ìo?¡§¡è|¡§??¡ì?¡ì??
#define MAX_MIC_DELAY		5

// Dy??¨º?¨¨
/*Dy??¨º?¨¨?¡§¡é?D?AD?|¡§?*/
#define KNOB_MIN			600		//0x258 //0x190
/*Dy??¨º?¨¨?¡§¡é????¡ì?AD?|¡§?*/
#define KNOB_MAX			3320	//0xc18 //0xdb5
/*????¡ì????¡ì?¨¦?Dy??¨º?¨¨??¨¨???*/
#define KNOB_MAIN_VOL_DEGREE			32
/*??|¡§??¡ìa?¡ì???Dy??¨º?¨¨??¨¨???*/
#define KNOB_TNB_VOL_DEGREE				12
/*MICDy??¨º?¨¨??¨¨???*/
#define KNOB_MIC_DEGREE					15
/*????¡ì????¡ì?¨¦?Dy??¨º?¨¨??¨¨??¡§¡è???¡ìo*/
#define KNOB_DEVIDE_MAIN		((KNOB_MAX-KNOB_MIN)/KNOB_MAIN_VOL_DEGREE)	
/*??|¡§??¡ìa?¡ì???Dy??¨º?¨¨??¨¨??¡§¡è???¡ìo*/
#define KNOB_DEVIDE_TNB			((KNOB_MAX-KNOB_MIN)/KNOB_TNB_VOL_DEGREE)	
/*??¡ì?????¨¨?Dy??¨º?¨¨??¨¨??¡§¡è???¡ìo*/
#define KNOB_DEVIDE_MIC			((KNOB_MAX-KNOB_MIN)/KNOB_MIC_DEGREE)	
/*??2??|¡§?*/
#define KNOB_BACK_DIFF			25
/*??¡ì?2aDy??¨º?¨¨???|¡§????¡ê¡è?¡§¡é????¨¨???¡§?*/
#define KNOB_RANGE(a,b)		    ((abs(a-b) >= KNOB_BACK_DIFF) ? 1 : 0)

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/
extern bool bt_connected;
extern sem_t iic_state_sem;
//extern bool is_usb_load;
//extern bool is_sd_load;
extern unsigned char power_level;
extern int ui_source_select;
extern bool bt_force_disconnect;
extern bool is_set_spdif;
extern int clear_sdf_pad_cnt;
extern int eq_sel;
extern bool need_reload_eq;
extern bool is_start_to_update;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/
void bt_chk_and_disp(void);
void bt_init_sem(void);
void ui_goback_source(int delay);
void ui_handle_down(void);
void ui_handle_file_load(int total_num, int folder_num);
void ui_handle_load_sd(void);
void ui_handle_load_usb(void);
void ui_handle_mode(void);
void ui_handle_mute(void);
void ui_handle_next(void);
void ui_handle_pause_play(void);
void ui_handle_stopplay(void);
void ui_handle_power(void);
void ui_handle_prev(void);
void ui_handle_sd_unload(void);
void ui_handle_up(void);
void ui_handle_usb_out(void);
void ui_handle_vol_dec_long_press(void);
void ui_handle_vol_inc_long_press(void);
void ui_handle_vol_long_press_up(void);
void ui_update_music_time(void);

void ui_handle_next_long_pressdown(void);
void ui_handle_prev_long_pressdown(void);
void ui_handle_eq(void);
void ui_handle_repeat(void);
void ui_handle_repeat_one(void);
void ui_handle_finish(void);
void ui_handle_fm_seek_auto_init(void);
void ui_handle_fm_seek_auto(void);
void ui_handle_knob(int arg2, int mode);
void ui_goback_source(int delay);
void ui_ad_handle(void);
void ui_handle_mic_pullout(void);

void sync_dsp_startup(void);
void IIC_init_sem(void);
void chk_usb_sd_disp(void);
void battery_management(int value);
void chk_power_disp(void);
unsigned short *deal_ad_result_muti_buf(unsigned short *value);

void set_channel_vol(int ch, int vol);
void set_decoder_channel_vol(int ch, int vol);

void reload_reverb(void);
void handle_bass_treble(int mode);
void ui_handle_mic_vol(int mode);
void ui_handle_mic_mix(int mode);
void ui_handle_mic_echo(void);
void ui_handle_mic_pair(void);
void ui_handle_eq_music(void);
void ui_handle_eq_movie(void);
void ui_handle_eq_dialog(void);

#ifdef CONFIG_CEC
int action_hdmion_send(void);
int action_hdmi_poweron_init(void);

int action_hdmi_on(void);
int action_hdmi_off(void);
int action_hdmi_standby(void);
int action_hdmi_poweron(void);
void ui_handle_cec_inactive_source(void);
void ui_handle_cec_active_source(void);
#endif

void sl_ui_set_reqrate(void);

void set_reg_spec(void);

void handle_bt_dispair(void);
void juset_for_test(void);
void ui_handle_set_samp(bool flag);
void ui_handle_reload_eq(int sel);
void ui_handle_check_playing(void);
void ui_handle_balence_vol(int flag);
void ui_handle_hdmi_poweroff(void);
void ui_handle_cec_insert(void);
void ui_handle_cec_pull_out(void);
void ui_handle_usb_emu_timeout(void);
void ui_handle_bt_set_vol(int value);

#endif

