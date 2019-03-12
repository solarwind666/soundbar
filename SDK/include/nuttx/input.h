/************************************************************************************
 * include/nuttx/input.h
 *
  * Copyright (C) 2015 The YunOS Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ************************************************************************************/

#ifndef __INCLUDE_NUTTX_INPUT_H
#define __INCLUDE_NUTTX_INPUT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <queue.h>
#include <sys/time.h>
#include <time.h>

#ifdef  __cplusplus
extern "C"
{
#endif


/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/


/*General value define */
#define  VALUE_FAIL            0
#define  VALUE_SUCCESS         1
#define  VALUE_NULL            0xffffffff
#define  EV_NULL               0xffff
#define  CODE_NULL             0xffff

/*Reserve event*/
#define  EV_SYN                0x00

/*General key define*/
#define  EV_KEY                0x01
#define  CODE_KEY_UP        1
#define  CODE_KEY_DOWN      2
#define  CODE_KEY_CLICK     3

#define  CODE_RECORD           21
#define  CODE_VOLUME           22//Reserve
#define  CODE_VOLUME_INC       23
#define  CODE_VOLUME_DEC       24
#define  CODE_PLAY_PAUSE       25
#define  CODE_MUTE             26
#define  CODE_CHANNEL          27
#define  CODE_NEXT             28
#define  CODE_RECORD_PRE       29
#define  CODE_MODE             30
#define  CODE_CHANNEL_NEXT     31
#define  CODE_CHANNEL_PREV     32
#define  CODE_FUNC             33
#define  CODE_EQ               34
#define  CODE_RESET            0x1001
#define  CODE_REBOOT           0x1002


/*General key value*/
#define  VALUE_KEY_UP          0
#define  VALUE_KEY_DOWN        1
#define  VALUE_KEY_CLICK       2
#define  VALUE_KEY_LTCLICK     3
#define  VALUE_KEY_DBCLICK     4

/*Reserve event*/
#define  EV_REL                0x02
#define  EV_ABS                0x03
#define  EV_MSC                0x04
#define  EV_LED                0x11
#define  EV_SND                0x12
#define  EV_REP                0x14
#define  EV_PWR                0x16

/*System event define*/
#define  EV_SYS                0x20
#define  CODE_BOOT_DATA_CHN    0x100
#define  CODE_BOOT_CMD_CHN     0x101
#define  CODE_AUDIO_READY      0x102
#define  CODE_RTC_UPDATE       0x200
#define  CODE_EASYSETUP        0x1000
#define  CODE_APSETUP          0x1001

/*General channel value*/
#define  VALUE_SYS_CHN_CONNECTED    0
#define  VALUE_SYS_CHN_CONNECTING 1
#define  VALUE_SYS_CHN_DISCONNECTED 2

/*Reserve event*/
#define  EV_KNOD               0x21

/*SD card event*/
#define  EV_SD                 0x22
#define  CODE_SD_PLUG          1
#define  VALUE_SD_OUT          0
#define  VALUE_SD_IN           1

/*LAN Driver event*/
#define  EV_LAN                0x23
#define  VALUE_LAN_OUT         0
#define  VALUE_LAN_IN          1

/*WiFi Driver event*/
#define  EV_WIFI                          0x24
#define  CODE_WIFI_INIT_COMPLETE          1
#define  CODE_WIFI_STA_START              2
#define  CODE_WIFI_STA_COMPLETE           3
#define  CODE_WIFI_ES_START               4
#define  CODE_WIFI_ES_COMPLETE            5
#define  CODE_WIFI_AP_START               6
#define  CODE_WIFI_AP_COMPLETE            7
#define  CODE_WIFI_NEWDEVICE_JOINT        8
#define  CODE_WIFI_STA_RECONNECT        9

/*Net event define */
#define  EV_NET                           0x25
#define  CODE_NET_DHCP_START              1
#define  CODE_NET_DHCP_RESULT             2
#define  CODE_NET_IP_STATIC               3
#define  CODE_NET_STATUS                  4
#define  VALUE_NET_LAN_OK                 0x01
#define  VALUE_NET_WIFI_OK                0x02


/*OTA event define */
#define  EV_OTA                           0x26
#define  CODE_OTA_UPDATE_DETECT           1
#define  CODE_OTA_DETECTRESULT_UPDATE     2
#define  CODE_OTA_ENSUREDINFO_UPDATE      3
#define  CODE_OTA_DOWNLOAD_START          4
#define  CODE_OTA_DOWNLOAD_RESULT         5
#define  CODE_OTA_UPDATE_START            6
#define  CODE_OTA_UPDATE_RESULT           7
#define  VALUE_OTA_UPDATEINFO_UNEXIST     0
#define  VALUE_OTA_UPDATEINFO_EXIST       1
#define  VALUE_OTA_UNUPDATE               0
#define  VALUE_OTA_UPDATE                 1

/*Usb driver event*/
#define  EV_USB                           0x27
#define  VALUE_USB_OUT                    0
#define  VALUE_USB_IN                     1

/*PM event*/
#define  EV_PM                            0x28
#define  CODE_PM_ENTER_INFORM             1
#define  CODE_PM_ENTER                    2
#define  CODE_PM_DONE                     3
#define  CODE_PM_QUIT                     4
#define  CODE_PM_SHUTDOWN_INFORM          5
#define  CODE_PM_STARTUP_INFORM           6
#define  CODE_PM_LOWPOWER_INFORM          7
#define  CODE_PM_POWERRECOVER_INFORM      8
#define  VALUE_PM_IDLE_INFORM             1
#define  VALUE_PM_POWERBUTTON_INFORM      2

/*File system event*/
#define  EV_FSYS                          0x29
#define  CODE_FSYS_SD_LOAD                1
#define  CODE_FSYS_UDISK_LOAD             2
#define  CODE_FSYS_FLASH_LOAD             3
#define  CODE_FSYS_SD_SPACE               4
#define  CODE_FSYS_UDISK_SPACE            5
#define  CODE_FSYS_FLASH_SPACE            6
#define  CODE_FSYS_UPDATE_FILE            7

/*Security event*/
#define  EV_MAC                           0x30

/* Blue tooth */
#define  EV_BT                            0x31
#define CODE_BT_DEVICE_CONNECT            1
#define CODE_BT_DEVICE_DISCONNECT         2
#define CODE_BT_MODE_ON                   3
#define CODE_BT_MODE_OFF                  4
#define CODE_BT_STATUS_CHANGE             5
#define CODE_BT_EVENT_QUERY               10
#define CODE_BT_PHONE_IN                  11
#define CODE_BT_VOICE_CONNECT             12
#define CODE_BT_VOICE_DISCONNECT          13

/* DLNA */
#define  EV_DLNA                            0x32
#define CODE_DLNA_DEVICE_CONNECT            1
#define CODE_DLNA_DEVICE_DISCONNECT         2
#define CODE_DLNA_MODE_ON                   3
#define CODE_DLNA_MODE_OFF                  4

/* AIRPLAY */
#define  EV_AIRPLAY                            0x33
#define CODE_AIRPLAY_DEVICE_CONNECT            1
#define CODE_AIRPLAY_DEVICE_DISCONNECT         2
#define CODE_AIRPLAY_MODE_ON                   3
#define CODE_AIRPLAY_MODE_OFF                  4

#define  EV_DUEROS                            0x34
#define CODE_DUEROS_DEVICE_CONNECT            1
#define CODE_DUEROS_DEVICE_DISCONNECT         2

/* Player event*/
#define EV_PLAYER                         0x40
#define CODE_PLAYER_PLAY_PROGRESS         1
#define CODE_PLAYER_PLAY_FINISH           2
#define CODE_PLAYER_PLAY_ERROR            3
#define CODE_PLAYER_RECORD_ON             4
#define CODE_PLAYER_RECORD_OFF            5
#define CODE_PLAYER_REPORT_VOLUME         6
#define CODE_PLAYER_TONE_FINISH           7
#define CODE_PLAYER_BUFFER_LOW            8
#define CODE_PLAYER_PLAY_STOP             9
#define CODE_PLAYER_START                 10
/*Driver key*/
#define EV_KEYDRV                         0x41

/* Yunio event */
#define EV_YUNIO                   0X42
#define CODE_RTC_HB                1
/* idjs event*/

#define EV_UI               0x70
#define CODE_UI_UPDATE_DONE		0x1
#define CODE_UI_SD_LOAD			0x2
#define CODE_UI_SD_IN			0x3
#define CODE_UI_SD_UNLOAD   	0x4
#define CODE_UI_SD_OUT			0x5
#define CODE_UI_USB_LOAD		0x6
#define CODE_UI_USB_IN			0x7
#define CODE_UI_USB_UNLOAD   	0x8
#define CODE_UI_USB_OUT			0x9
#define CODE_UI_ALARM_OFF		0xa

#define EV_IR				0x71
#define CODE_IR_PRESS		0x1
#define CODE_IR_LONG_PRESS	0x2

#define EV_CEC						0x72
#define CODE_CEC_ACTIVE_SOURCE		0x1
#define CODE_CEC_INACTIVE_SOURCE	0x2

#define EV_IDJS_REPORTEVENT 0X50
#define CODE_IDJS_UNCHECK 1
#define CODE_IDJS_CHECK   2

/****************************************************************************
 * Public Type Definitions
 ****************************************************************************/
typedef struct input_event {
    struct timeval time;
    uint16_t type;
    uint16_t code;
    uint32_t value;
    uint32_t extra;
} input_event_t;

typedef void (*key_translate_t)(struct input_event *key2event);

#ifdef CONFIG_INPUT_EVENT
/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: input_add_event
 *
 * Description:
 *   this function add the event to the event list.
 *
 * Input Parameters:
 *    event  the event add to queue
 *    event.time  can ignore this member init
 *
 * Returned Values:
 *   zero is on success.
 *
 ****************************************************************************/
int input_add_event(struct input_event *event);


/****************************************************************************
 * Name: input_add_event_ext
 *
 * Description:
 *   this function add the event to the event list.
 *
 * Input Parameters:
 *   type  event type
 *   code  event code
 *   value event value
 *
 * Returned Values:
 *   zero is on success.
 *
 ****************************************************************************/

int input_add_event_ext(uint16_t type, uint16_t code, uint32_t value);


/****************************************************************************
 * Name: input_register_translate
 *
 * Description:
 *   Register translate callback
 *
 * Input Parameters:
 *    cb  translate callback
 *
 * Returned Values:
 *   void
 ****************************************************************************/
void input_register_translate(key_translate_t cb);
#else
static inline int input_add_event(struct input_event *event){ return 0;}
static inline int input_add_event_ext(uint16_t type, uint16_t code, uint32_t value){ return 0;}
static inline void input_register_translate(key_translate_t cb){ return 0;}
#endif


#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCLUDE_NUTTX_CRYPTO_AES_H */

