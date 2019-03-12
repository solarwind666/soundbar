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
 * @file hal/audio.h
 * @brief AUDIO HAL API for YOC
 * @version since 5.5.0
 */

#ifndef HAL_AUDIO_H
#define HAL_AUDIO_H

typedef struct hal_audio_module_s hal_audio_module_t;

struct hal_audio_module_s
{
    hal_module_base_t      base;

    /* Link to HW */
    int (*init)(hal_audio_module_t *m, void *something);
    int (*start_recording)(hal_audio_module_t *module);
    int (*stop_recording)(hal_audio_module_t *module);
    int (*read_record)(hal_audio_module_t *module, void *buf, int buf_len);

};

/**
 * @brief Arch register a new module before HAL startup
 */
void hal_audio_register_module(hal_audio_module_t *module);

/**
 * @brief Start record
 */
int  hal_audio_start_recording(hal_audio_module_t *module);

/**
 * @brief Stop record
 */
int  hal_audio_stop_recording(hal_audio_module_t *module);

/**
 * @brief Read record data from buffer
 * @buf[out] Output recorded data to user
 * @buf_len[in] Input buffer len
 */
int  hal_audio_read_record(hal_audio_module_t *module, void *buf, int buf_len);

/**
 * @brief Audio hal init
 */
int  hal_audio_init(void);

/**
 * @brief Get default module object
 */
hal_audio_module_t *hal_audio_get_default_module(void);

#endif /* HAL_AUDIO_H */

