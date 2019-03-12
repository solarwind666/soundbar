/****************************************************************************
 * apps/examples/i2ctest/zlg7290.h
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
#include <sys/types.h>
#include <nuttx/i2c.h>


struct zlg7290_dev_s
{
    uint8_t     addr;               /* zlg7290 I2C address */    
    bool     initd;                  /* True: The device has been initialize */
    int     freq;                   /* zlg7290 Frequency <= 3.4MHz */ 
    FAR struct i2c_dev_s *i2c;      /* Saved I2C interface instance */
};


/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: zlg7290_initialize
 *
 * Description:
 *   get the i2c bus then Iinitialize and register the zlg7290 device
 *
 ****************************************************************************/
struct zlg7290_dev_s * zlg7290_initialize(void);


/****************************************************************************
 * Name: zlg7290_uninitialize
 *
 * Description:
 *   unregister the zlg7290 driver,and then release the i2c bus and  uniinitialize zlg7290 device
 *
 ****************************************************************************/

int zlg7290_uninitialize(FAR struct zlg7290_dev_s *zlg_dev);


