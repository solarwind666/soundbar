/************************************************************************************
 * include/usr_event_type.h
 *
  * Copyright (C) 2016 The YunOS Open Source Project
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

#ifndef __INPUT_H
#define __INPUT_H

#include <yoc/kernel.h>
#include <yoc/framework.h>
#include <yoc/internal/event_type_code.h>
#include <apps/usr_event_type.h>


/*General value define */
#define VALUE_FAIL            0
#define VALUE_SUCCESS         1
#define VALUE_NULL            0xffffffff
#define EV_NULL               0xffff
#define CODE_NULL             0xffff

/*WiFi Driver event*/
#define CODE_WIFI_ES_START               4
#define CODE_WIFI_ES_COMPLETE            5
#define CODE_WIFI_AP_START               6
#define CODE_WIFI_AP_COMPLETE            7
#define CODE_WIFI_NEWDEVICE_JOINT        8

/*System event define*/
#define CODE_BOOT_DATA_CHN    0x100
#define CODE_BOOT_CMD_CHN     0x101
#define CODE_AUDIO_READY      0x102
#define CODE_RTC_UPDATE       0x200
#define CODE_EASYSETUP        0x1000
#define CODE_APSETUP          0x1001
#define CODE_REBOOT           0x1002

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

/*File system event*/
#define EV_FSYS                          EV_FS


/*Security event*/
#define EV_MAC                           0x30

/** Net event define */
#define  CODE_NET_UP                      5
#define  CODE_NET_DOWN                    6


//#define input_event_register yoc_local_event_listener_register
//#define input_add_event_ext yoc_local_event_post

#endif /* __INPUT_H */

