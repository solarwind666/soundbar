/************************************************************************************
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

#ifndef __SILAN_GPIO_H__
#define __SILAN_GPIO_H__

#include "silan_generic.h"
#include "zhuque_bsp_gpio.h"

#define GPIO1_1                1

#define GPIO_CTRL         (SILAN_GPIO2_BASE|0x400)
#define GPIO_DATA         (SILAN_GPIO2_BASE|0x000)

#define SET_GPIO(n)       sl_writel(sl_readl(GPIO_DATA) | (1UL<<(n)), GPIO_DATA)
#define GET_GPIO(n)       (sl_readl(GPIO_DATA) & (1UL<<(n)))

/***********************************************************************************
 * Name: gpio_irq_reg
 *
 * Description:
 *     register the gpio irq function.
 *
 * Input Parameters:
 *     pin - gpio pin.from 0 to 63.
 *     cb - The function wanted to register
 *
 * Returned Values:
 *     Zero on success. -1 on falure.
 ************************************************************************************/
int gpio_irq_reg(uint32_t pin, gpio_interrupt_t cb);

/*****************************************************************************
 * Name: gpio_irq_unreg
 *
 * Description:
 *     unregister the gpio irq function.
 *
 * Input Parameters:
 *     pin - gpio pin.from 0 to 63.
 *
 * Returned Values:
 *     Zero on success. -1 on falure.
 ****************************************************************************/
int gpio_irq_unreg(uint32_t pin);

/****************************************************************************
 * Name: gpio_direction_input
 *
 * Description:
 *   Configure a GPIO intput pin based on bit-encoded description of the pin.
 *
 * Returned Values:
 *    return the input voltage.zero is low voltage.1 is high voltage.
 ****************************************************************************/
int gpio_direction_input(uint32_t pin);

/****************************************************************************
 * Name: gpio_direction_output
 *
 * Description:
 *   Configure a GPIO output pin based on bit-encoded description of the pin.
 *
 * Returned Values:
 *   zero on success.
 ****************************************************************************/
int gpio_direction_output(uint32_t pin, int value);

/****************************************************************************
 * Name: gpio_irq_mode
 *
 * Description:
 *   Configure a GPIO gpio_irq_mode.
 *
 * Returned Values:
 *   zero on success. -1 on falure.
 ****************************************************************************/
int gpio_irq_mode(uint32_t pin, enum irq_mode _irqmode);

int gpio_pull_mode(uint32_t pin, enum gpio_mode mode);
#endif
