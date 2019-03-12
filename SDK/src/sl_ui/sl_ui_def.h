#ifndef __SL_UI_DEF_H__
#define __SL_UI_DEF_H__
#include <nuttx/config.h>
#include <nuttx/input.h>

#define VOLUME_ADJ_STEP 10

#define CONTEXT_URL_LEN	32
#define VALUE_LEN	16
#define INFO_LEN    	256
#define NAME_LEN 	16

#define FORMAT_ASCII    0
#define FORMAT_UTF16BE  1
#define FORMAT_UTF16SE  2
#define FORMAT_UTF8     3

#ifndef CONFIG_UI_MSG_PRIO
#define CONFIG_UI_MSG_PRIO 1
#endif

#define LOGO_LINE       1
#define TIME_LINE       0
#define NAME_LINE       2
#define INFO_LINE       3
#define MEDIA_LINE      1
#define LIST_LINE_MAX   4

#define SHOW_DELAY_MAX  100
#define SEARCH_NAME     "/media"
#define SEARCH_USB_NAME "/media/usb"
#define SEARCH_SD_NAME  "/media/sd"
#define PREFIX_MEDIA	"/media"
#define PREFIX_SD		"/sd"
#define PREFIX_USB		"/usb"
#define PREFIX_MP3		"mp3:///"
#define PREFIX_DLNA		"http://192."
#define PREFIX_CLOUD	"http://"
#define PREFIX_BT		"bt:///pcm:///"
#define PREFIX_AIRPLAY	"airplay:///pcm:///"

//#define SL_UI_DBG   1

#ifdef CONFIG_SYSTEM_UI_ROMFS
#define SECTORSIZE   64
#define NSECTORS(b)  (((b)+SECTORSIZE-1)/SECTORSIZE)
#define ROMFSDEV     "/dev/ram0"
#define ROMFS_MOUNTPT	"/media/flash"
#define MP3_NAME_NUM	5
extern int mp3_idx;
extern char *music_name[MP3_NAME_NUM];
#endif

#ifdef CONFIG_RTC
#include <nuttx/timers/rtc.h>
#include <nuttx/rtc_interface.h>
#include <pthread.h>
#define RTC_PATH           "/dev/rtc0"
#endif

enum ui_state_machine_e {
	SL_UI_STATE_MACHINE_NULL = 0,
	SL_UI_STATE_MACHINE_LPM,
	SL_UI_STATE_MACHINE_FREQ,
	SL_UI_STATE_MACHINE_MAX,
};

#ifdef CONFIG_RTC
enum ui_alarm_stat_e {
	SL_UI_ALARM_STAT_NULL = 0,
	SL_UI_ALARM_STAT_SET,
	SL_UI_ALARM_STAT_EXEC,
	SL_UI_ALARM_STAT_MAX,
};
#endif

#ifdef CONFIG_FAT32_FILELIST
enum ui_local_mode_e {
	SL_UI_LOCAL_MODE_NULL = 0,
#ifdef CONFIG_SILAN_USBHS
	SL_UI_LOCAL_MODE_USB,
#endif
#ifdef CONFIG_SC6138_SD
	SL_UI_LOCAL_MODE_SD,
#endif
	SL_UI_LOCAL_MODE_MAX,
};
#endif

enum ui_error_e {
	SL_UI_ERROR_NULL = 0,
	SL_UI_ERROR_INIT,
	SL_UI_ERROR_MQ,
	SL_UI_ERROR_BUSY,
	SL_UI_ERROR_MALLOC,
	SL_UI_ERROR_NO_FILE,
	SL_UI_ERROR_NO_FOLDER,
	SL_UI_ERROR_LOCAL_MODE,
	SL_UI_ERROR_OPEN,
	SL_UI_ERROR_PARAM,
	SL_UI_ERROR_CHILD,
	SL_UI_ERROR_REGISTER,
	SL_UI_ERROR_NO_DIALOG,
	SL_UI_ERROR_NO_SWITCH,
	SL_UI_ERROR_MAX_MATCH,
	SL_UI_ERROR_MAX,
};

enum ui_dialog_mode_type_e {
	SL_UI_DIALOG_TYPE_MODE_NULL = -1,
	SL_UI_DIALOG_TYPE_MODE_SOURCE,
	SL_UI_DIALOG_TYPE_MODE_PLAY,
#ifdef CONFIG_WIRELESS
	SL_UI_DIALOG_TYPE_MODE_NET,
#endif
#ifdef CONFIG_PM
	SL_UI_DIALOG_TYPE_MODE_LPM,
	SL_UI_DIALOG_TYPE_MODE_FREQ,
	SL_UI_DIALOG_TYPE_MODE_POWER,
#endif
#ifdef CONFIG_RTC
	SL_UI_DIALOG_TYPE_MODE_ALARM,
#endif
#ifdef CONFIG_SYSTEM_AVS
	SL_UI_DIALOG_TYPE_MODE_AVS,
#endif
	SL_UI_DIALOG_TYPE_MODE_MAX,
};

enum ui_dialog_source_type_e {
	SL_UI_DIALOG_TYPE_SOURCE_NULL = -1,
#ifdef CONFIG_FAT32_FILELIST
	SL_UI_DIALOG_TYPE_SOURCE_LOCAL,
#endif
	SL_UI_DIALOG_TYPE_SOURCE_LINEIN,
#ifdef CONFIG_SPDIFIN
	SL_UI_DIALOG_TYPE_SOURCE_SPDIFIN,
#endif
#ifdef CONFIG_CEC
	SL_UI_DIALOG_TYPE_SOURCE_HDMI,
#endif
#ifdef CONFIG_WIRELESS
	SL_UI_DIALOG_TYPE_SOURCE_RADIO,
#endif
#ifdef CONFIG_SYSTEM_UI_ROMFS
	SL_UI_DIALOG_TYPE_SOURCE_MIX,
#endif
	SL_UI_DIALOG_TYPE_SOURCE_MAX,
};

#ifdef CONFIG_FAT32_FILELIST
enum ui_dialog_local_mode_type_e {
	SL_UI_DIALOG_TYPE_LOCAL_MODE_NULL = -1,
#ifdef CONFIG_SC6138_SD
	SL_UI_DIALOG_TYPE_LOCAL_MODE_SD,
#endif
#ifdef CONFIG_SILAN_USBHS
	SL_UI_DIALOG_TYPE_LOCAL_MODE_USB,
#endif
	SL_UI_DIALOG_TYPE_LOCAL_MODE_MAX,
};

enum ui_dialog_local_play_mode_type_e {
	SL_UI_DIALOG_TYPE_LOCAL_PLAY_MODE_NULL = -1,
	SL_UI_DIALOG_TYPE_LOCAL_PLAY_MODE_FILE,
	SL_UI_DIALOG_TYPE_LOCAL_PLAY_MODE_FOLDER,
	SL_UI_DIALOG_TYPE_LOCAL_PLAY_MODE_MAX,
};

#ifdef CONFIG_SC6138_SD
enum ui_dialog_sd_mode_type_e {
	SL_UI_DIALOG_TYPE_SD_MODE_NULL = -1,
	SL_UI_DIALOG_TYPE_SD_MODE_FILE,
	SL_UI_DIALOG_TYPE_SD_MODE_FOLDER,
	SL_UI_DIALOG_TYPE_SD_MODE_MAX,
};
#endif

#ifdef CONFIG_SILAN_USBHS
enum ui_dialog_usb_mode_type_e {
	SL_UI_DIALOG_TYPE_USB_MODE_NULL = -1,
	SL_UI_DIALOG_TYPE_USB_MODE_FILE,
	SL_UI_DIALOG_TYPE_USB_MODE_FOLDER,
	SL_UI_DIALOG_TYPE_USB_MODE_MAX,
};
#endif
#endif

enum ui_dialog_linein_type_e {
	SL_UI_DIALOG_TYPE_LINEIN_NULL = -1,
	SL_UI_DIALOG_TYPE_LINEIN_ON,
	SL_UI_DIALOG_TYPE_LINEIN_OFF,
	SL_UI_DIALOG_TYPE_LINEIN_MAX,
};

enum ui_dialog_lineinon_type_e {
	SL_UI_DIALOG_TYPE_LINEINON_NULL = -1,
	SL_UI_DIALOG_TYPE_LINEINON,
	SL_UI_DIALOG_TYPE_LINEINON_MAX,
};

enum ui_dialog_lineinoff_type_e {
	SL_UI_DIALOG_TYPE_LINEINOFF_NULL = -1,
	SL_UI_DIALOG_TYPE_LINEINOFF,
	SL_UI_DIALOG_TYPE_LINEINOFF_MAX,
};

#ifdef CONFIG_SPDIFIN
enum ui_dialog_spdifin_type_e {
	SL_UI_DIALOG_TYPE_SPDIFIN_NULL = -1,
	SL_UI_DIALOG_TYPE_SPDIFIN_ON,
	SL_UI_DIALOG_TYPE_SPDIFIN_OFF,
	SL_UI_DIALOG_TYPE_SPDIFIN_MAX,
};

enum ui_dialog_spdifinon_type_e {
	SL_UI_DIALOG_TYPE_SPDIFINON_NULL = -1,
	SL_UI_DIALOG_TYPE_SPDIFINON,
	SL_UI_DIALOG_TYPE_SPDIFINON_MAX,
};

enum ui_dialog_spdifinoff_type_e {
	SL_UI_DIALOG_TYPE_SPDIFINOFF_NULL = -1,
	SL_UI_DIALOG_TYPE_SPDIFINOFF,
	SL_UI_DIALOG_TYPE_SPDIFINOFF_MAX,
};
#endif

#ifdef CONFIG_CEC
enum ui_dialog_hdmi_type_e {
	SL_UI_DIALOG_TYPE_HDMI_NULL = -1,
	SL_UI_DIALOG_TYPE_HDMI_ON,
	SL_UI_DIALOG_TYPE_HDMI_OFF,
	SL_UI_DIALOG_TYPE_HDMI_STANDBY,
	SL_UI_DIALOG_TYPE_HDMI_POWERON,
	SL_UI_DIALOG_TYPE_HDMI_MAX,
};

enum ui_dialog_hdmion_type_e {
	SL_UI_DIALOG_TYPE_HDMION_NULL = -1,
	SL_UI_DIALOG_TYPE_HDMION,
	SL_UI_DIALOG_TYPE_HDMION_MAX,
};

enum ui_dialog_hdmioff_type_e {
	SL_UI_DIALOG_TYPE_HDMIOFF_NULL = -1,
	SL_UI_DIALOG_TYPE_HDMIOFF,
	SL_UI_DIALOG_TYPE_HDMIOFF_MAX,
};

enum ui_dialog_hdmistandby_type_e {
	SL_UI_DIALOG_TYPE_HDMISTANDBY_NULL = -1,
	SL_UI_DIALOG_TYPE_HDMISTANDBY,
	SL_UI_DIALOG_TYPE_HDMISTANDBY_MAX,
};

enum ui_dialog_hdmipoweron_type_e {
	SL_UI_DIALOG_TYPE_HDMIPOWERON_NULL = -1,
	SL_UI_DIALOG_TYPE_HDMIPOWERON,
	SL_UI_DIALOG_TYPE_HDMIPOWERON_MAX,
};
#endif

#ifdef CONFIG_WIRELESS
enum ui_dialog_radio_type_e {
	SL_UI_DIALOG_TYPE_RADIO_NULL = -1,
	SL_UI_DIALOG_TYPE_RADIO_ON,
	SL_UI_DIALOG_TYPE_RADIO_OFF,
	SL_UI_DIALOG_TYPE_RADIO_MAX,
};

enum ui_dialog_radioon_type_e {
	SL_UI_DIALOG_TYPE_RADIOON_NULL = -1,
	SL_UI_DIALOG_TYPE_RADIOON,
	SL_UI_DIALOG_TYPE_RADIOON_MAX,
};

enum ui_dialog_radiooff_type_e {
	SL_UI_DIALOG_TYPE_RADIOOFF_NULL = -1,
	SL_UI_DIALOG_TYPE_RADIOOFF,
	SL_UI_DIALOG_TYPE_RADIOOFF_MAX,
};
#endif

#ifdef CONFIG_SYSTEM_UI_ROMFS
enum ui_dialog_mix_type_e {
	SL_UI_DIALOG_TYPE_MIX_NULL = -1,
	SL_UI_DIALOG_TYPE_MIX_ON,
	SL_UI_DIALOG_TYPE_MIX_OFF,
	SL_UI_DIALOG_TYPE_MIX_MAX,
};

enum ui_dialog_mixon_type_e {
	SL_UI_DIALOG_TYPE_MIXON_NULL = -1,
	SL_UI_DIALOG_TYPE_MIXON,
	SL_UI_DIALOG_TYPE_MIXON_MAX,
};

enum ui_dialog_mixoff_type_e {
	SL_UI_DIALOG_TYPE_MIXOFF_NULL = -1,
	SL_UI_DIALOG_TYPE_MIXOFF,
	SL_UI_DIALOG_TYPE_MIXOFF_MAX,
};
#endif

enum ui_dialog_play_type_e {
	SL_UI_DIALOG_TYPE_PLAY_REPEAT_NULL = -1,
	SL_UI_DIALOG_TYPE_PLAY_REPEAT_ONCE,
	SL_UI_DIALOG_TYPE_PLAY_REPEAT_ALL,
	SL_UI_DIALOG_TYPE_PLAY_MAX,
};

#ifdef CONFIG_WIRELESS
enum ui_dialog_net_type_e {
	SL_UI_DIALOG_TYPE_NET_NULL = -1,
	SL_UI_DIALOG_TYPE_NET,
	SL_UI_DIALOG_TYPE_NET_MAX,
};
#endif

#ifdef CONFIG_PM
enum ui_dialog_lpm_type_e {
	SL_UI_DIALOG_TYPE_LPM_NULL = -1,
	SL_UI_DIALOG_TYPE_LPM,
	SL_UI_DIALOG_TYPE_LPM_MAX,
};

enum ui_dialog_freq_type_e {
	SL_UI_DIALOG_TYPE_FREQ_NULL = -1,
	SL_UI_DIALOG_TYPE_FREQ,
	SL_UI_DIALOG_TYPE_FREQ_MAX,
};

enum ui_dialog_power_type_e {
	SL_UI_DIALOG_TYPE_POWER_NULL = -1,
	SL_UI_DIALOG_TYPE_POWER,
	SL_UI_DIALOG_TYPE_POWER_MAX,
};
#endif

#ifdef CONFIG_RTC
enum ui_dialog_alarm_type_e {
	SL_UI_DIALOG_TYPE_ALARM_NULL = -1,
	SL_UI_DIALOG_TYPE_ALARM_ON,
	SL_UI_DIALOG_TYPE_ALARM_OFF,
	SL_UI_DIALOG_TYPE_ALARM_MAX,
};

enum ui_dialog_alarmon_type_e {
	SL_UI_DIALOG_TYPE_ALARMON_NULL = -1,
	SL_UI_DIALOG_TYPE_ALARMON,
	SL_UI_DIALOG_TYPE_ALARMON_MAX,
};

enum ui_dialog_alarmoff_type_e {
	SL_UI_DIALOG_TYPE_ALARMOFF_NULL = -1,
	SL_UI_DIALOG_TYPE_ALARMOFF,
	SL_UI_DIALOG_TYPE_ALARMOFF_MAX,
};
#endif

#ifdef CONFIG_SYSTEM_AVS
enum ui_dialog_avs_type_e {
	SL_UI_DIALOG_TYPE_AVS_NULL = -1,
	SL_UI_DIALOG_TYPE_AVS,
	SL_UI_DIALOG_TYPE_AVS_MAX,
};
#endif

enum ui_dialog_vol_up_type_e {
	SL_UI_DIALOG_TYPE_VOL_UP_NULL = -1,
	SL_UI_DIALOG_TYPE_VOL_UP,
	SL_UI_DIALOG_TYPE_VOL_UP_MAX,
};

enum ui_dialog_vol_dn_type_e {
	SL_UI_DIALOG_TYPE_VOL_DN_NULL = -1,
	SL_UI_DIALOG_TYPE_VOL_DN,
	SL_UI_DIALOG_TYPE_VOL_DN_MAX,
};

enum ui_dialog_wire_type_e {
	SL_UI_DIALOG_TYPE_WIRE_NULL = -1,
	SL_UI_DIALOG_TYPE_WIRE,
	SL_UI_DIALOG_TYPE_WIRE_MAX,
};

enum ui_dialog_stop_type_e {
	SL_UI_DIALOG_TYPE_STOP_NULL = -1,
	SL_UI_DIALOG_TYPE_STOP,
	SL_UI_DIALOG_TYPE_STOP_MAX,
};

enum ui_dialog_next_type_e {
	SL_UI_DIALOG_TYPE_NEXT_NULL = -1,
	SL_UI_DIALOG_TYPE_NEXT,
	SL_UI_DIALOG_TYPE_NEXT_MAX,
};

enum ui_dialog_prev_type_e {
	SL_UI_DIALOG_TYPE_PREV_NULL = -1,
	SL_UI_DIALOG_TYPE_PREV,
	SL_UI_DIALOG_TYPE_PREV_MAX,
};

enum ui_dialog_pause_type_e {
	SL_UI_DIALOG_TYPE_PAUSE_NULL = -1,
	SL_UI_DIALOG_TYPE_PAUSE,
	SL_UI_DIALOG_TYPE_PAUSE_MAX,
};

enum ui_dialog_resume_type_e {
	SL_UI_DIALOG_TYPE_RESUME_NULL = -1,
	SL_UI_DIALOG_TYPE_RESUME,
	SL_UI_DIALOG_TYPE_RESUME_MAX,
};

enum ui_media_e {
	MEDIA_UNKNOWN = 0,
	MEDIA_SD,      
	MEDIA_USB,      
#ifdef CONFIG_WIRELESS
	MEDIA_BLUETOOTH, 
	MEDIA_AIRPLAY,  
	MEDIA_DLNA,   
	MEDIA_RADIO,    
#endif
#ifdef CONFIG_SYSTEM_UI_ROMFS
	MEDIA_ROMFS,
#endif
	MEDIA_MAX,    
};

//according to nxplayer
enum ui_play_mode_e {
	SL_UI_PLAY_WIFI_MODE = 0,
	SL_UI_PLAY_BT_MODE,
	SL_UI_PLAY_DLNA_MODE,
	SL_UI_PLAY_AIRPLAY_MODE,
#ifdef CONFIG_SPDIFIN
	SL_UI_PLAY_SPDIFIN_MODE,
#endif
};

enum ui_state_e {
	UI_STATE_IDLE = 0,
	UI_STATE_PLAYING,
	UI_STATE_DECODED,  
	UI_STATE_PAUSED,   
	UI_STATE_STOPED,  
	UI_STATE_RECORDING,
	UI_STATE_RECORDOFF,
	UI_STATE_STOPFORTONE, 
	UI_STATE_TONEPLAY,   
	UI_STATE_TONEIDLE,   
	UI_STATE_BTPLAY,
	UI_STATE_BTSUSPEND,
	UI_STATE_RESFROMTONE,
	UI_STATE_PLAYNEW,
	UI_STATE_PLAYRESUME,
	UI_STATE_PLAYDLNA, 
#ifdef CONFIG_SPDIFIN
	UI_STATE_PLAYSPDIFIN, 
#endif
	UI_STATE_PLAYAIRPLAY,
};

#endif
