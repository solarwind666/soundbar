/****************************************************************************
 * id.bsp/include/bsp_rtc.h
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
 ****************************************************************************/
#ifndef _BSP_ERRNO_H_
#define _BSP_ERRNO_H_

#include <errno.h>

/* Error code field difination
   Error number is devided into 4 field:
   0x8******* : 8  : means < 0
   0x*A****** : A  : means type number: bsp(1), driver(2), hal(3), app(4)...
   0x**AB**** : AB : means module number: timer(1), rtc(2), ....
   0x****AB** : AB : means API number: module API's definition
   0x******AB : AB : means sub error number
                      0 ~ 0x80 is common error such as EPERM, refer to errno.h
                      0x80 ~ 0xFF is specific error, can difine in module

   For example 0x81020113 means:
     1. 0x8*******: value < 0, means error happened
     2. 0x*1******: type number is 1, means bsp error
     3. 0x**02****: module number is 02, means RTC error
     3. 0x****01**: module API is 01, means RTC's init
     4. 0x******13: specific error is 0x13=19=ENODEV, means no such device

   For special bsp module example, you can return:
     (BSP_ERRNO_TIMER_BASE | BSP_API_RTC_INIT | EPERM)    for rtc init error
     (BSP_ERRNO_TIMER_BASE | BSP_API_RTC_SETTIME | ENXIO) for rtc settime error

   Here list the common sub error number (0x******AB) below:
      Code          Hex    Deci   Meaning
      -------------------------------------------------------
      EPERM         0x01    1   Operation not permitted
      EIO           0x05    5   I/O error
      ENXIO         0x06    6   No such device or address
      ENOMEM        0x0C   12   Out of memory
      EACCES        0x0D   13   Permission denied
      EINVAL            0x16   22      Invalid argument
      ...
      SPEC_ERR_BASE 0x80  128   module special error number base
      ...
      ERRNO_MAX     0xFF   --   Max sub error number
 */
#ifndef BSP_OK
#define BSP_OK 0
#endif

#define GET_ERROR_TYPE(errno) \
  return (error & 0x0F000000 >> 6)

#define GET_ERROR_MODULE(error) \
  return (error & 0x00FF0000 >> 4)

#define GET_ERROR_SUB(error) \
  return (error & 0x0000FFFF)

#ifndef BSP_ERRNO_BASE
#define BSP_ERRNO_BASE     0x81000000
#endif

#define BSP_ERRNO_TIMER_BASE 0x81010000
#define BSP_ERRNO_RTC_BASE   0x81020000
#define BSP_ERRNO_PWM_BASE   0x81030000
#define BSP_ERROR_GPIO_BASE   0x81030000

#endif
