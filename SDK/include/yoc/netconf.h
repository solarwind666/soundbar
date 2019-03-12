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
 * @file netconf.h
 * @brief net configuration module api for third party
 * @detail exported apis which mannage wifi config
 * @version since 5.5.0
 */

#ifndef YOC_NETCONF_API_H
#define YOC_NETCONF_API_H

#if defined(__cplusplus)
extern "C"
{
#endif

/** @defgroup yoc_netconf NetConf API
 *  @{
 */

/**
 * @brief Enter smart config mode, waiting for WiFi configuration
 *        from other devices, typically Smart Phone.
 * @param None
 * @retval ==0 success
 * @retval !=0 failure
 */
int yoc_netconf_start_smartconfig(void);

/**
 * @brief Leave smart config mode.
 * @param None
 * @retval ==0 success
 * @retval !=0 failure
 */
int yoc_netconf_stop_smartconfig(void);

/**
 * @brief Start to connect the WiFi saved in device's flash
 * @param None
 * @retval ==0 success
 * @retval !=0 failure
 */
int yoc_netconf_connect_saved_wifi(void);

/**
 * @brief Start to disconnect the WiFi
 * @param None
 * @retval ==0 success
 * @retval !=0 failure
 */
int yoc_netconf_disconnect_wifi(void);

/** @} */ //end of NetConf API

#if defined(__cplusplus)
}
#endif

#endif /* YOC_NETCONF_API_H */

