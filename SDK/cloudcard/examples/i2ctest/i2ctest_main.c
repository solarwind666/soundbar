/****************************************************************************
 * apps/examples/i2ctest/i2ctest_main.c
 * Driver for SPI-based MX25L6433F (64Mbit) flash.
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

#include <nuttx/i2c.h>
#include "zlg7290.h"

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
 * i2c_main
 ****************************************************************************/

int silan_i2c_test(void )
{
    int ret = 0;
    int fd = -1;
    char keyvalue = 0;
    int cnt = 10;
    struct zlg7290_dev_s * zlg_dev = NULL;

    printf("Start Testing IIC. . .\n");

    //this driver is just for i2c test, so we do not initialize it when system boot up
    
    zlg_dev = zlg7290_initialize();
    if (zlg_dev == NULL)
    {
        printf("zlg7290_initialize failed \n");
        return -1;
    }

    
    fd = open("/dev/zlg7290", O_RDWR, 0666);
    if(fd < 0)
    {
        printf("open zlg7290 failed. . .\n");
        return -1;
    }
    
    write(fd,&keyvalue,1);
    
    printf("Please enter a key \n");
        
    while(cnt)
    {		
        ret = read(fd, &keyvalue, 1);
        if(ret >= 0)
        {
            if((keyvalue > 0) && (keyvalue<100))
               {
                   printf("\t\tthe keyvalue is %d \n", keyvalue);
                   /* Transmits the value of key number to 7290 to display. */
                   
                   write(fd,&keyvalue,1);
                   
                   printf("\t- - -PASS\n");
                   if(--cnt)
                   {
                       printf("\tPlease enter a key again \n");
                   }
               }
        }
   
        usleep(200000);
    }

    close(fd);
    
    zlg7290_uninitialize(zlg_dev);
    
    printf("End Testing IIC. . .\n");

    return 0;
}


#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int i2ctest_main(int argc, char *argv[])
#endif
{
    silan_i2c_test();
    return 0;
}
