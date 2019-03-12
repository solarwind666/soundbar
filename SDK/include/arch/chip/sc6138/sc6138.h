/************************************************************************************
 * arch/cskyv1/src/sc6138/sc6138.h
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

#ifndef __ARCH_CSKYV1_SRC_SC6138_SC6138_H
#define __ARCH_CSKYV1_SRC_SC6138_SC6138_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "up_internal.h"

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/

/* Additional Configuration *********************************************************/
/* Custom debug settings used in the csky port.  These are managed by csky-specific
 * logic and not the common logic in include/debug.h.  NOTE:  Some of these also
 * depend on CONFIG_DEBUG_VERBOSE
 */

#ifndef CONFIG_DEBUG
#  undef CONFIG_DEBUG_DMA
#  undef CONFIG_DEBUG_RTC
#  undef CONFIG_DEBUG_I2C
#  undef CONFIG_DEBUG_CAN
#  undef CONFIG_DEBUG_PWM
#  undef CONFIG_DEBUG_SENSORS
#endif

/* Peripherals **********************************************************************/

#include "chip.h"
#include "silan_gpio.h"
#endif /* __ARCH_CSKYV1_SRC_SC6138_SC6138_H */

