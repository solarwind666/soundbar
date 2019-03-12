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
 * @file hal/ota.h
 * @brief OTA HAL API for YOC
 * @version since 5.5.0
 */

#ifndef HAL_OTA_H
#define HAL_OTA_H

typedef struct hal_ota_module_s hal_ota_module_t;

struct hal_ota_module_s
{
    hal_module_base_t base;

    /* Link to HW */
    int (*init)(hal_ota_module_t *m, void *something);
    int (*ota_write_flash_cb)(hal_ota_module_t *m, int writed_size, char *buf,
                              int buf_len, int type);
    int (*ota_finish_cb)(hal_ota_module_t *m, int finish_result,
                         char* updated_version);
};

/**
 * @brief Arch register a new module before HAL startup
 */
void hal_ota_register_module(hal_ota_module_t *module);

int  hal_ota_init(void);

int  hal_ota_write_ota_cb(hal_ota_module_t *m, int32_t writed_size,
                                   uint8_t *buf, int32_t buf_len, int type);

int  hal_ota_ota_finish_cb(hal_ota_module_t *m, int32_t finish_result,
                                    char* updated_version);

hal_ota_module_t *hal_ota_get_default_module(void);
hal_ota_module_t *hal_ota_get_next_module(hal_ota_module_t *m);

#endif /* HAL_OTA_H */

