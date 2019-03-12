#ifndef SL_UI_CMD_H__
#define SL_UI_CMD_H__

#include "nxplayer.h"
#include "player_cmd.h"
#include "sl_ui_old.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define VOL_STEP  1 //(100.0f/31)

#define BYPASS_MODE 0
#define BYPASS_VOL_IN_MAX   -2
#define BYPASS_VOL_IN_MIN   -25
#define BYPASS_VOL_IN_STEP ((-2.0f - -25)/31)

#define INNERADC_MODE 0

#define MIX_6_CH_MIC 0

/****************************************************************************
 * Public Types
 ****************************************************************************/

/*开关机状态*/
enum
{
    POWER_START = -1,
    POWER_ON,
    POWER_OFF,
    POWER_END,
} POWER;

enum ui_cmd_e {
	UI_CMD_NULL = 200,

	UI_CMD_USB_IN,
	UI_CMD_USB_OUT,
	UI_CMD_USB_UNLOAD,
	UI_CMD_SD_IN,
	UI_CMD_SD_OUT,
	UI_CMD_SD_UNLOAD,

	UI_NET_EASYSETUP,
	UI_NET_STA_SUCCESS,
	UI_NET_STA_FAIL,
	UI_NET_STA_CONNECTTING,
	UI_NET_STA_DISCONNECTED,

	UI_CMD_PLAYER_FINISH,
	UI_CMD_PLAYER_TONE_FINISH,

	UI_CMD_BT_PHONE_IN,
	UI_CMD_BT_VOICE_CONNECT,
	UI_CMD_BT_VOICE_DISCONNECT,

	UI_CMD_SHOW_TITLE,
	UI_CMD_SHOW_STATUS,
	UI_CMD_BUFFERING,

	/*************above cant change****************/
	/*************user add start*******************/	
#ifdef CONFIG_CEC    
		UI_CEC_INACTIVE_SOURCE,
		UI_CEC_ACTIVE_SOURCE,
#endif  
	UI_CMD_SD_LOAD,
	UI_CMD_USB_LOAD,

	UI_CMD_BT_UP,
	UI_CMD_BT_DOWN,
	UI_CMD_BT_NEXT,
	UI_CMD_BT_PREV,
	UI_CMD_BT_OK,
	UI_CMD_BT_MODE,
	UI_CMD_BT_FUNC,
	UI_CMD_BT_EQ,
	UI_CMD_BT_STOP,

	UI_CMD_BT_MUTE,
	UI_CMD_BT_POWER,
	UI_CMD_VOLUME_DEC_DOWN,

	UI_CMD_VOLUME_DEC_UP,
	UI_CMD_VOLUME_INC_DOWN,
	UI_CMD_VOLUME_INC_UP,
	UI_CMD_BT_PREV_LONG_DOWN,
	UI_CMD_BT_PLAY_LONG_DOWN,
	UI_CMD_BT_PLAY_LONG_UP,
	UI_CMD_BT_NEXT_LONG_DOWN, 
	UI_CMD_FILES_IS_LOAD,
	UI_CMD_MIC_PULL_OUT,
	UI_CMD_KNOB,
	UI_CMD_BT_REPEAT,
	UI_CMD_IR_BT_MODE,
	UI_CMD_IR_USB_MODE,
	UI_CMD_IR_SD_MODE,
	UI_CMD_IR_OPT_MODE,  //250
	UI_CMD_IR_COAX_MODE,
	UI_CMD_IR_AUX_MODE,
	UI_CMD_IR_HDMI_MODE,
	UI_CMD_IR_RCA_MODE,
	
	UI_CMD_IR_DISPLAY,
	UI_CMD_IR_RETURN,

	UI_CMD_TREBLE_UP,
    UI_CMD_TREBLE_DOWN,
    UI_CMD_BASS_UP,
    UI_CMD_BASS_DOWN,
	
	UI_CMD_BT_PAIR,
	UI_CMD_BT_MIC_PAIR,

	UI_CMD_EQ_MUSIC,
	UI_CMD_EQ_MOVIE,	
	UI_CMD_EQ_DIALOG,

	UI_CMD_STOP,
	UI_CMD_HDMION_SEND,
	UI_CMD_HDMION_DEINIT,
	UI_CMD_FOR_TEST,

	UI_CMD_SET_48K,
	UI_CMD_SET_44K,
	UI_CMD_SET_VOL,

	UI_CMD_EQ_RELOAD,

	UI_CEC_HDMI_PULL_OUT,
	UI_CEC_HDMI_INSERT,

	UI_CMD_USB_EMU_TIMEOUT,

	UI_CMD_MAX,
};

#define NET_STATUS_ESSETUP          0
#define NET_STATUS_STA_SUCCESS      1
#define NET_STATUS_STA_FAIL         2
#define NET_STATUS_STA_CONNECTTING  3
#define NET_STATUS_STA_DISCONNECTED 4
#define NET_STATUS_MAX              5

/*UI消息队列信息*/
struct ui_s
{
    mqd_t mq;
    char mqname[16];
};

typedef int (*CMD_FUNC)();
struct ui_cmd_func {
	int cmd;
	CMD_FUNC func;
};

/*静音状态*/
enum
{
    UI_MUTE_START = -1,
    UNMUTE,
    MUTE,
    UI_MUTE_END,
} UI_MUTE;

/*通道选择*/
enum
{
    SET_CHANNEL_0 = 0,
    SET_CHANNEL_L,
    SET_CHANNEL_R,
    SET_CHANNEL_END,
} SET_CHANNEL_SEL;


/*音源选择*/
enum
{
    SOURCE_SELECT_START = -1,
	SOURCE_SELECT_BT,
    SOURCE_SELECT_LINEIN,
	SOURCE_SELECT_LINEIN1,
	SOURCE_SELECT_SPDIFIN, 
	SOURCE_SELECT_HDMI,
	SOURCE_SELECT_END,
	SOURCE_SELECT_USB,
	
	SOURCE_SELECT_FM,
	SOURCE_SELECT_COAX,
	SOURCE_SELECT_SD,
    
} UI_SELECT_SOURCE;
	
/****************************************************************************
 * Public Data
 ****************************************************************************/
extern int ui_power;
extern bool is_usb_load;
extern bool is_sd_load;
extern int adc_fd;
extern unsigned short Adc_Read_Buf[6];
extern bool en_adc_detect_flag;

struct ui_cmd_func *sl_ui_parse_cmd(int cmd);
//bool is_player_cmd(int cmd);
//bool is_forced_cmd(int cmd);
//bool is_post_cmd(int cmd);
//bool is_processing_cmd(int cmd);
bool is_processing_done(void);
int forced_action(void);
//int post_action(void);
int processing_action(void);
int set_sl_ui_cmd(int cmd, void *param, int arg);

//adapt to old version
ui_info_t get_all_play_info(void);
extern void player_get_info(ui_info_t *info);
extern bool player_get_tag(TagInfo *tag_in, char* tag_info);

#endif
