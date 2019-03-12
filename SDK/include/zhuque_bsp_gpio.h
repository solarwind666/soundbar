/************************************************************************************
 * id.kernel/hardware/id.bsp/include/zhuque_bsp_gpio.h
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

#ifndef _ZHUQUE_BSP_GPIO_H__
#define _ZHUQUE_BSP_GPIO_H__

#include <bsp_errno.h>

#undef MAKE_ERROR_CODE
#define MAKE_ERROR_CODE(api, errno) \
  (BSP_ERROR_GPIO_BASE | ((api & 0xff) << 8) | (errno & 0xff))
#define ZHUQUE_BSP_API_GPIO_SET_MODE             0x01
#define ZHUQUE_BSP_API_GPIO_SET_VALUE            0x02
#define ZHUQUE_BSP_API_GPIO_GET_VALUE            0x03
#define ZHUQUE_BSP_API_GPIO_REG_INT              0x04
#define ZHUQUE_BSP_API_GPIO_UREG_INT             0x05

enum irq_mode {
    RISING_EDGE,
    FALLING_EDGE,
    DOUBLE_EDGE,
    LOW_LEVEL,
    HIGH_LEVEL
};

enum gpio_mode
{
    PULLING_HIGH,
    PULLING_NONE,
    PULLING_DOWN,
    HANG_IN,
    OD_OUT,
    PUSH_PULL
};

enum gpio_direction
{
    GPIO_IN,
    GPIO_OUT
};

enum gpio_value
{
    GPIO_VALUE_LOW = 0,
    GPIO_VALUE_HIGH= 1
};

typedef int (*gpio_interrupt_t)(int irqno);

/****************************************************************************
 * Name: zhuque_bsp_gpio_get_value
 *
 * Description:
 *    get  the value of  selected GPIO pin
 *    value - the addr of gpio value
 * Returned Values:
 *    OK or error code
 ****************************************************************************/
int zhuque_bsp_gpio_get_value(uint32_t pin, uint32_t *value);

/****************************************************************************
 * Name: zhuque_bsp_gpio_set_value
 *
 * Description:
 *   set one or zero to the selected GPIO pin.
 *   value - the gpio value
 * Returned Values:
 *    zero on success.
 ****************************************************************************/
int zhuque_bsp_gpio_set_value(uint32_t pin, enum gpio_value value);

/************************************************************************************
 * Name: zhuque_bsp_gpio_set_mode
 *
 * Description:
 *   set the mode of the gpio.
 *
 * Input Parameters:
 *   pin - gpio number.
 *   dir - the direction of gpio .
 *   mode - the mode of gpio .
 *
 * Returned Values:
 *   It will return OK while getting type succsessfully. Otherwise return !OK.
 *************************************************************************************/
int zhuque_bsp_gpio_set_mode(uint32_t pin, enum gpio_direction dir, enum gpio_mode mode);

/************************************************************************************
 * Name: zhuque_bsp_gpio_register_interrupt
 *
 * Description:
 *   register the gpio interrupt.
 *
 * Input Parameters:
 *   pin - gpio number.
 *   _irqmode - the irq mode of the gpio.
 *   handler - the interrupt handler function.
 *
 * Returned Values:
 *   It will return OK while getting type succsessfully. Otherwise return !OK.
 *************************************************************************************/
int zhuque_bsp_gpio_register_interrupt(uint32_t pin, enum irq_mode irqmode, gpio_interrupt_t handler);

/************************************************************************************
 * Name: zhuque_bsp_gpio_unregister_interrupt
 *
 * Description:
 *   unregister the gpio interrupt.
 *
 * Input Parameters:
 *   pin - gpio number.
 *
 * Returned Values:
 *   It will return OK while getting type succsessfully. Otherwise return !OK.
 *************************************************************************************/
int zhuque_bsp_gpio_unregister_interrupt(uint32_t pin);

#endif
