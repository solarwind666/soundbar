/****************************************************************************
 * apps/examples/gpiotest/gpiotest_main.c
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
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "silan_gpio.h"
#include "board.h"


/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * gpiotest_main
 ****************************************************************************/

#define GPIO_TEST  GPIO1_17
 
int gpio_interrupt(int irqno)
{
    printf("gpio irq arrive\n");
    zhuque_bsp_gpio_unregister_interrupt(GPIO_TEST);
    return 0;
}


#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int gpiotest_main(int argc, char *argv[])
#endif
{
    int value = 0;
    if(argc == 2)
    {
        if ( strcmp("outhigh" , argv[1]) == 0)
        {
            zhuque_bsp_gpio_set_mode(GPIO_TEST, GPIO_OUT, PULLING_NONE);
            zhuque_bsp_gpio_set_value(GPIO_TEST,GPIO_VALUE_HIGH);
        }
        else if(strcmp("outlow" , argv[1]) == 0)
        {
            zhuque_bsp_gpio_set_mode(GPIO_TEST, GPIO_OUT, PULLING_NONE);
            zhuque_bsp_gpio_set_value(GPIO_TEST,GPIO_VALUE_LOW);
        }
        else if( strcmp("in" , argv[1]) == 0)
        {
            zhuque_bsp_gpio_set_mode(GPIO_TEST, GPIO_IN, PULLING_NONE);
            zhuque_bsp_gpio_get_value(GPIO_TEST, &value);
            printf("get the gpio value: %d\n", value);
        }
        else if( strcmp("gpioreg" , argv[1]) == 0)
        {
            zhuque_bsp_gpio_set_mode(GPIO_TEST, GPIO_IN, PULLING_NONE);
            zhuque_bsp_gpio_register_interrupt(GPIO_TEST, RISING_EDGE, gpio_interrupt);
        }
    }
    else
    {
        printf("Usage: gpiotest outlow/outhigt/in \n");
    }

      return 0;
}
