/*
 * Copyright (C) 2016 YunOS Project. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @brief System configuration data
 *
 */

#ifndef YOC_CONF_H
#define YOC_CONF_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OTA_VERSION_LEN  64
#define DEVICE_ACTIVATED 0x41434544 //"ACED"

typedef struct {
    char ssid[33];
    char pwd[65];
} yoc_persistent_conf_wifi_t;

typedef struct {
    char ota_version[OTA_VERSION_LEN];
    int  sys_version;
} yoc_persistent_conf_ota_t;

typedef struct {
    int                flags;
    unsigned long long time;
} yoc_persistent_conf_factory_test_t;

/*
 * each time change struct, change version too
 */
#define YOC_CONF_VERSION 1

/*
 * ----------------------- CAUTION ------------------------
 * don't use any #ifdef to conditionally define struct here
 * we don't want to earse flash each just a config changed
 * ----------------------- CAUTION ------------------------
 */
typedef struct {
    size_t                             magic;
    unsigned char                      version;
    char                               padding[sizeof(size_t) - 1];
    yoc_persistent_conf_wifi_t         wifi;
    yoc_persistent_conf_ota_t          ota;
    yoc_persistent_conf_factory_test_t ft;
    int                                emulate_id2_index;
    int                                log_level;
    int                                in_stress_test;
    /* more persistent config here */
} yoc_persistent_conf_t __attribute__((__aligned__(sizeof(size_t))));

int yoc_pconf_init(void);

yoc_persistent_conf_t *yoc_pconf_get(void);

void yoc_pconf_renew_magic(void);

#ifdef __cplusplus
}
#endif

#endif /* YOC_CONF_H */

