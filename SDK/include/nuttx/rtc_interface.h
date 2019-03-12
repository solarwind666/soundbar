/************************************************************************************
 *include/nuttx/ota_interface.h
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

#ifndef _RTC_INTERFACE_H_
#define _RTC_INTERFACE_H_

#include <stdint.h>
#include <nuttx/timers/rtc.h>
#include <sys/time.h>
#include <time.h>

/****************************************************************************
* Name: rtc_starttimer
*
* Description:
*   start RTC timer
*
* Input parameters:
*   sec - the time in second
*   cb  - callback
*   arg - callback's arg
*
* Returned Value:
*   the timer id. if error happends, return Negtive.
*
* Assumptions:
*
*****************************************************************************/
int32_t rtc_starttimer(int sec, alarmcb_t cb, void *arg);

/****************************************************************************
* Name: rtc_stoptimer
*
* Description:
*   Stop RTC timer
*
* Input parameters:
*   timerid - the timerid which return from rtc_starttimer().
*
* Returned Value:
*   if stop success, return OK(Zero), otherwise return NZero.
*
* Assumptions:
*
*****************************************************************************/
int32_t rtc_stoptimer(timerid);

/****************************************************************************
* Name: yunos_rtc_gettimeofday
*
* Description:
*   gettimeofday with RTC
*
* Input parameters:
*   None.
*
* Returned Value:
*   if success, return OK(Zero), otherwise return NZero.
*
* Assumptions:
*
*****************************************************************************/

int yunos_rtc_gettimeofday(struct timeval *tv, struct timezone *tz);

/****************************************************************************
* Name: yunos_rtc_settimeofday
*
* Description:
*   settimeofday with RTC
*
* Input parameters:
*   None.
*
* Returned Value:
*   if success, return OK(Zero), otherwise return NZero.
*
* Assumptions:
*
*****************************************************************************/

int yunos_rtc_settimeofday(const struct timeval *tv, const struct timezone *tz);

#endif
