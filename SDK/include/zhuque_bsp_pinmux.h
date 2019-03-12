/****************************************************************************
 * id.kernel/hardware/id.bsp/include/zhuqe_bsp_pinmux.h
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
#ifndef _ZHUQUE_BSP_PINMUX_H
#define _ZHUQUE_BSP_PINMUX_H

#include <stdint.h>


/*note: definition of devices is to be continued */
typedef enum pinmux_device_s {
	PINMUX_DEV_GPIO           = 0,    /*GPIO is the lowest priority functionality, only other functionality released it can be valid. all GPIO share the same device type*/
	PINMUX_DEV_UART,
	PINMUX_DEV_I2C,
	PINMUX_DEV_SPI,
	PINMUX_DEV_PWM,
	PINMUX_DEV_CAN,
	PINMUX_DEV_IIS,
	PINMUX_DEV_USB,
	PINMUX_DEV_ADC,
	PINMUX_DEV_SPIFLASH,
	PINMUX_DEV_SDIO,
	PINMUX_DEV_SDMMC,
	PINMUX_DEV_SPDIF_I,
	PINMUX_DEV_SPDIF_O,
	PINMUX_DEV_GMAC,                /*phy or mac?*/


	PINMUX_DEV_NUM    /*not a real device ,but for record the count of devices*/
} pinmux_device_t;


/****************************************************************************
 * Function: zhuqe_bsp_pinmux_set
 *
 * Description: set pin mux functionality
 *
 * Parameters:  dev - pin mux functionality, valid value refers pinmux_device_t
 *              pin_num - pin number in pin_list
 *              pin_list - pin list
 *
 * Returned Value: 0 - success , other - error code
 *
 * Assumptions:
 *
 ****************************************************************************/
int zhuqe_bsp_pinmux_set(pinmux_device_t dev,uint8_t pin_num, const uint16_t *pin_list);


/****************************************************************************
 * Function: zhuqe_bsp_pinmux_set
 *
 * Description: release pin mux functionality
 *
 * Parameters:  dev - pin mux functionality, valid value refers pinmux_device_t
 *              pin_num - pin number in pin_list
 *              pin_list - pin list
 *
 * Returned Value: 0 - success , other - error code
 *
 * Assumptions:
 *
 ****************************************************************************/
int zhuqe_bsp_pinmux_release(pinmux_device_t dev,uint8_t pin_num, const uint16_t *pin_list);


#endif
