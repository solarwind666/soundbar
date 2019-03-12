/****************************************************************************
* pin.h
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
#ifndef _YUNOS_PIN_DEFINE_H_
#define _YUNOS_PIN_DEFINE_H_

/*define used PINs */

#define LED_CONTROL_PIN_PWM4  59
#define LED_CONTROL_PIN_PWM5  60

#define BT_UART_PINS          {1,2}
#define BT_RTS_PIN            3

#define SDIO_PINS             {44,45,46,47,48,49,50}

#define SC6138_UART1_TX      2
#define SC6138_UART1_RX      1

#define SC6138_UART2_TX      34
#define SC6138_UART2_RX      35

#define SC6138_UART3_TX      61
#define SC6138_UART3_RX      62

#define SC6138_UART4_TX      4
#define SC6138_UART4_RX      5

#define ISO7816_UART1_TX      2
#define ISO7816_UART1_RX      1

#define ISO7816_UART2_TX      34
#define ISO7816_UART2_RX      35

#define ISO7816_UART3_TX      61
#define ISO7816_UART3_RX      62

#define ISO7816_UART4_TX      4
#define ISO7816_UART4_RX      5

#define I2C1_PIN_SCL          32
#define I2C1_PIN_SDA          33

#define I2C2_PIN_SCL          61
#define I2C2_PIN_SDA          62

#define GPIO1_15               15
#define GPIO1_16               16
#define GPIO1_17               17
#define GPIO1_18               18
#define GPIO2_15               47
#define GPIO2_16               48

#define GPIO2_0                51
#define GPIO2_1                52
#define GPIO2_2                53
#define GPIO2_3                54
#define GPIO2_4                55
#define GPIO2_5                56
#define GPIO2_6                57
#define GPIO2_7                58
#define GPIO2_8                59
#define GPIO2_9                60
#define GPIO2_14               78
#define GPIO2_17               81
#define GPIO2_18               82
#define GPIO2_19               83
#define GPIO2_20               84

#define SPI_PINS              {30,31, 32, 33}

#define GMAC_PINS             {51,52,53,54,55,56,57,58,59,60}

/***************************************************************
 * ISO7816 pin & uart config
 **************************************************************/
/* io pin number */
/* reset pin number */
#ifdef CONFIG_ISO7816_RST_PIN
#define SC6138_ISO7816_RST    CONFIG_ISO7816_RST_PIN
#else
#define SC6138_ISO7816_RST    77
#endif

#define SC6138_ISO7816_IO     61

/***************************************************************
 * Wifi pins config
 **************************************************************/
#undef CONFIG_WWD_RESET_PIN
#undef CONFIG_WWD_IRQ_PIN
#undef CONFIG_WWD_WAKE_PIN

#define CONFIG_WWD_RESET_PIN        47
#define CONFIG_WWD_IRQ_PIN          48
#define CONFIG_WWD_WAKE_PIN         31

/***************************************************************
 * Soft SPI pins config
 **************************************************************/
#define SPI_CS                      33
#define SPI_SCK                     32
#define SPI_MOSI                    30
#define SPI_MISO                    31
/* It is for SYNO SE */
#define SPI_INT                     6
#define SPI_RESET                   7

/***************************************************************
 * PWM channel pins config
 **************************************************************/
#define YOC_BSP_PWM_CHANNEL0_PIN    3       /* GPIO1_0  */
#define YOC_BSP_PWM_CHANNEL1_PIN    44      /* GPIO1_23 */
#define YOC_BSP_PWM_CHANNEL2_PIN    10      /* GPIO1_7  */
#define YOC_BSP_PWM_CHANNEL3_PIN    11      /* GPIO1_8  */
#define YOC_BSP_PWM_CHANNEL4_PIN    59      /* GPIO2_8  */
#define YOC_BSP_PWM_CHANNEL5_PIN    60      /* GPIO2_9  */
#define YOC_BSP_PWM_CHANNEL6_PIN    58      /* GPIO2_7  */
#define YOC_BSP_PWM_CHANNEL7_PIN    76      /* GPIO2_10 */

#endif
