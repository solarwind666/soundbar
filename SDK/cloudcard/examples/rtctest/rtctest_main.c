/************************************************************************************
 *apps/examples/rtctest_main.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/input.h>
#include <nuttx/module.h>
#include <nuttx/power/pm.h>
#include <nuttx/timers/rtc.h>
#include <nuttx/rtc_interface.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Type Declarations
 ****************************************************************************/


/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/


/****************************************************************************
 * Private Data
 ****************************************************************************/
static int rtc_timerid = -1;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rtc_callback
 *
 * Description:
 *   RTC test callback.
 *
 * Input Parameters:
 *	 arg - from calling rtc_starttimer.
 *
 * Returned values:
 *	 None.
 ****************************************************************************/

static void rtc_callback(void *arg)
{
    syslog(LOG_INFO, "[RTC TEST]RTC Timeup, calling callback, args: %x\n", arg);
}

/****************************************************************************
 * Name: show_usage
 *
 * Description:
 *   show rtctest usage.
 *
 * Input Parameters:
 *   None
 *
 * Returned values:
 *	 None.
 ****************************************************************************/

static void show_usage(void)
{
    printf("rtctest usage:\n");
    printf("retctest start seconds\n");
    printf("retctest stop\n");
}


/****************************************************************************
 * Public Functions
 ****************************************************************************/

#define TEST_RTC_PATH           "/dev/rtc0"
/****************************************************************************
 * Name: rtctest_main
 *
 * Input Parameters:
 *	None.
 *
 * Returned values:
 *	None.
 *
 * Demo:
 *   nsh> rtctest start 30
 *   ...(after 30 seconds)
 *   RTC callback print
 *   
 ****************************************************************************/
#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int rtctest_main(int argc, char *argv[])
#endif
{
#if 0
    int ret = OK;
    int sec = 0;
    if (argc != 2 && argc != 3) {
        show_usage();
        return -1;
    }

    if (argc == 3) {
        if (0 != memcmp("start", argv[1], sizeof("start"))) {
            show_usage();
            return -1;
        }

        sec = atoi(argv[2]);
        rtc_timerid = rtc_starttimer(sec, rtc_callback, 0x12345678);
        if (rtc_timerid < 0) {
            printf("start RTC timer error\n");
        }
    }

    if (argc == 2) {
        if (0 != memcmp("stop", argv[1], sizeof("stop"))) {
            show_usage();
            return -1;
        }
        if (rtc_timerid > 0) {
            rtc_stoptimer(rtc_timerid);
        }

	rtc_timerid = -1;
    }
    return OK;
#else

    int fd;
    int ret;
    struct tm tmtime;
    struct timeval tv;

    fd = open(TEST_RTC_PATH, O_RDWR);
    if (fd < 0)
    {
        printf("open rtc error\n");
        return fd;
    }
    
    gettimeofday(&tv, NULL);
    printf("gettimeofday sec %d %d\n", tv.tv_sec, tv.tv_usec);

    if (!strcmp(argv[1], "rdtime"))
    {
        ret = ioctl(fd, RTC_RD_TIME, &tmtime);
        printf("rtc_test rdtime y %d m %d d %d h %d m %d s %d\n", tmtime.tm_year, tmtime.tm_mon, tmtime.tm_mday, tmtime.tm_hour, tmtime.tm_min, tmtime.tm_sec);

        if (tmtime.tm_year >= 1900)
            tmtime.tm_year -= 1900;
        if (tmtime.tm_mon > 0)
            tmtime.tm_mon -= 1;

        tv.tv_sec = mktime(&tmtime);
        printf("rtc_test tv->tv_sec %ld\n", tv.tv_sec);
    }
    else if (!strcmp(argv[1], "settime"))
    {
        gmtime_r(&(tv.tv_sec), &tmtime);
        tmtime.tm_year += 1900;
        tmtime.tm_mon += 1;
        printf("rtc_test settime y %d m %d d %d h %d m %d s %d\n", tmtime.tm_year, tmtime.tm_mon, tmtime.tm_mday, tmtime.tm_hour, tmtime.tm_min, tmtime.tm_sec);
        ret = ioctl(fd, RTC_SET_TIME, &tmtime);
    }

    close(fd);
#endif
}
