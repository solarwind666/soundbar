/************************************************************************************
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

#ifndef _SYS_CONF_SESSION_NAME_H_
#define _SYS_CONF_SESSION_NAME_H_
//#include "uv.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ota reboot system, close welcome music*/
#define SYS_CONF_OTA_SESSION   "OTA_OSUPDATE"
#define SYS_CONF_OTA_KEY       "ota_reboot_way"
#define SYS_CONF_CURRENT_PRIM_VERSION       "system_prim_version"
#define SYS_CONF_CURRENT_UPDATE_VERSION     "system_update_version"

/* WiFi connect info*/
#define SYS_CONF_WIFI_SESSION "wifi"
#define SYS_CONF_WIFI_SSID_KEY "ssid"
#define SYS_CONF_WIFI_PSWD_KEY "password"
#define SYS_CONF_WIFI_SETYPE_KEY "setype"
#define SYS_CONF_WIFI_FLAG_KEY "ver"

/*volume info*/
#define SYS_CONF_VOLUME_SESSION "volume"
#define SYS_CONF_VOLUME_LAST_KEY "volume_last"

/*radio url info*/
#define SYS_CONF_RADIO_SESSION  "radio"
#define SYS_CONF_RADIO_URL0     "radio_url0"
#define SYS_CONF_RADIO_URL1     "radio_url1"
#define SYS_CONF_RADIO_URL2     "radio_url2"
#define SYS_CONF_RADIO_URL3     "radio_url3"
#define SYS_CONF_RADIO_URL4     "radio_url4"
#define SYS_CONF_RADIO_URL5     "radio_url5"

#ifdef __cplusplus
}
#endif

#endif
