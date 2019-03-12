/************************************************************************************
 * include/nuttx/power/power.h
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


#ifndef __INCLUDE_NUTTX_POWER_POWER_H
#define __INCLUDE_NUTTX_POWER_POWER_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/fs/ioctl.h>

#include <stdbool.h>
#include <semaphore.h>
#include <fixedmath.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* Power types */
enum power_type_e {
    POWER_TYPE_AC = 0,  /* Power type is AC
                         */

    POWER_TYPE_CHARGER, /* Power type is charger
                         */

    POWER_TYPE_BATTERY, /* Power type is battery
                         */
};

/* Command of ioctl */
enum POWER_IOCTL_CMD {
    PWR_IOC_TYPE = 0,   /* using ioctl to get power type
                         */

    PWR_IOC_CURRENT,    /* using ioctl to get power current value
                         */

};

 /* This structure defines the lower half battery interface */

struct power_dev_s;
struct power_operations_s
{
  /* return the type power, see enum power_type_e */

  int (*power_type)(struct power_dev_s *dev, int *status);

  /* return the current power value*/

  int (*current_value)(struct power_dev_s *dev, int *value);
};

/* This structure defines the battery driver state structure */

struct power_dev_s
{
  /* Fields required by the upper-half driver */

  FAR const struct power_operations_s *ops; /* Battery operations */
  sem_t batsem;  /* Enforce mutually exclusive access */

  /* Data fields specific to the lower-half driver may follow */
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/
/****************************************************************************
 * Name: power_register
 *
 * Description:
 *   Register a power driver with the common, upper-half
 *   battery driver.
 *
 * Input parameters:
 *   devpath - The location in the pseudo-filesystem to create the driver.
 *     Recommended standard is "/dev/power".
 *   dev - An instance of the battery state structure .
 *
 * Returned value:
 *    Zero on success or a negated errno value on failure.
 *
 ****************************************************************************/

int power_register(FAR const char *devpath,
                             FAR struct power_dev_s *dev);


#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __INCLUDE_NUTTX_POWER_BATTERY_H */
