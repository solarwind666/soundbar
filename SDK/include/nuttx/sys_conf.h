/************************************************************************************
 * id.kernel/include/nuttx/sys_conf.h
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

#ifndef _SYS_CONF_H_
#define _SYS_CONF_H_

#include "sys_conf_session_name.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SUCCESS
#define SUCCESS          0x00
#endif
#define ERROR_ARGUMENT_MISSING  0xC1
#define ERROR_MALLOC_FAIL       0xC2
#define ERROR_FILE_NOT_FOUND    0xC3
#define ERROR_SECTION_NOT_FOUND 0xC4
#define ERROR_KEY_NOT_FOUND     0xC5
#define ERROR_FILE_WRITE_FAIL   0xC6
#define ERROR_FILE_CREAT_FAIL   0xC7
#define ERROR_UNKNOW_FORMAT     0xC8
#define ERROR_FILE_READ_FAIL    0xC9
#define ERROR_CRC_CHECK_FAIL    0xCA
#define ERROR_JSON_PARSE_FAIL   0xCB
#define ERROR_FILE_LOCKED       0xCC
#define ERROR_JSON_PRINT_FAIL   0xCD
#define ERROR_SECTION_NOT_FOUND 0x11

/* Value format define */
#if 1
#define SYS_CONF_FALSE  (1 << 0)
#define SYS_CONF_TRUE   (1 << 1)
#define SYS_CONF_NULL   (1 << 2)
#define SYS_CONF_NUMBER (1 << 3)
#define SYS_CONF_STRING (1 << 4)
#define SYS_CONF_ARRAY  (1 << 5)
#define SYS_CONF_OBJECT (1 << 6)
#else
#define SYS_CONF_FALSE  0
#define SYS_CONF_TRUE   1
#define SYS_CONF_NULL   2
#define SYS_CONF_NUMBER 3
#define SYS_CONF_STRING 4
#define SYS_CONF_ARRAY  5
#define SYS_CONF_OBJECT 6
#endif
typedef struct _config_header_t
{
    uint32_t checksum;
    uint32_t version;
    uint32_t length;
}config_header_t;

typedef struct _uv_arg_t
{
    const char *section;
    const char *key;
    int32_t max_len;
    int32_t value_format;
    void *input;
    void *output;
    int32_t ret;
    void (*call_back)(void *);
}uv_arg_t;

/*
 * zhuque_sys_factory_reset
 * reset config files
 * @return       succeed or error
 */
int32_t zhuque_sys_factory_reset();

/*
 * zhuque_sys_conf_set
 * add or rewrite a value in sys_conf.json
 * @section[in]  the section name
 * @key[in]      the key of the output
 * @value_format[in]  string or int
 * @input[in]    the input key value
 * @cb[in]       the callback at write finish
 * @return       succeed or error
 */
int32_t zhuque_sys_conf_set(const char *section,
                         const char *key,
                         int32_t value_format,
                         void *input);

/*
 * zhuque_sys_conf_get
 * get key value from sys_conf.json
 * @section[in]  the section name
 * @key[in]      the key of the output
 * @max_len[in]  the max length of output
 * @value_format[in]  string or int
 * @output[out]  the output key value string
 * @return       succeed or error
 */
int32_t zhuque_sys_conf_get(const char *section,
                         const char *key,
                         int32_t max_len,
                         int32_t value_format,
                         void *output);


#ifdef __cplusplus
}
#endif

#endif
