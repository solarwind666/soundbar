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
 * @file yoc/service.h
 * @brief YOC Service Framework APIs
 * @version since 5.5.0
 */

#ifndef YOC_SERVICE_API_H
#define YOC_SERVICE_API_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <yoc/framework.h>

/**
 * @brief Init yoc hal for devices
 * @param None
 * @retval ==0 success
 * @retval !=0 failure
 * @note Please call this API after all the hal modules is registered
 *       during the system initialization.
 */
int yoc_hal_init(void);

/**
 * @brief YOC user application start point
 * @param None
 * @return None
 */
void yoc_app_main(void);

/**
 * @brief Start yoc main service
 * @param yoc_event_cb callback for receiving system events
 * @retval ==0 success
 * @retval !=0 failure
 */
int yoc_service_start(yoc_event_cb cb);

/**
 * @brief Init one service
 * @param name service name
 * @returns None
 */
void yoc_init_one_service(const char *name);

/**
 * @brief Deinit one service
 * @param name service name
 * @returns None
 */
void yoc_deinit_one_service(const char *name);

/**
 * @brief Start one service
 * @param name service name
 * @returns None
 */
void yoc_start_one_service(const char *name);

/**
 * @brief Stop one service
 * @param name service name
 * @returns None
 */
void yoc_stop_one_service(const char *name);


#ifdef __cplusplus
}
#endif

#endif /* YOC_SERVICE_API_H */

