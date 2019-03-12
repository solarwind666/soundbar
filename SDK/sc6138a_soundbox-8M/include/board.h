/************************************************************************************
 * configs/sc6180yuncore/include/board.h
 *
 * Copyright (C) 2015 The YunOS Open Source Project
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.

 ************************************************************************************/

#ifndef __CONFIG_SILAN_INCLUDE_BOARD_H
#define __CONFIG_SILAN_INCLUDE_BOARD_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>

#ifndef __ASSEMBLY__
#  include <stdint.h>
#  include <stdbool.h>
#endif

#ifdef __KERNEL__

#endif

#include "pin.h"
/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/


/* SDIO dividers.  Note that slower clocking is required when DMA is disabled
 * in order to avoid RX overrun/TX underrun errors due to delayed responses
 * to service FIFOs in interrupt driven mode.  These values have not been
 * tuned!!!
 *
 * SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(118+2)=400 KHz
 */

#define SDIO_INIT_CLKDIV        (118 << SDIO_CLKCR_CLKDIV_SHIFT)

/* DMA ON:  SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(1+2)=16 MHz
 * DMA OFF: SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(2+2)=12 MHz
 */

#ifdef CONFIG_SDIO_DMA
#  define SDIO_MMCXFR_CLKDIV    (1 << SDIO_CLKCR_CLKDIV_SHIFT)
#else
#  define SDIO_MMCXFR_CLKDIV    (2 << SDIO_CLKCR_CLKDIV_SHIFT)
#endif

/* DMA ON:  SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(1+2)=16 MHz
 * DMA OFF: SDIOCLK=48MHz, SDIO_CK=SDIOCLK/(2+2)=12 MHz
 */

#ifdef CONFIG_SDIO_DMA
#  define SDIO_SDXFR_CLKDIV     (1 << SDIO_CLKCR_CLKDIV_SHIFT)
#else
#  define SDIO_SDXFR_CLKDIV     (2 << SDIO_CLKCR_CLKDIV_SHIFT)
#endif

/* LED definitions ******************************************************************/
/* If CONFIG_ARCH_LEDS is not defined, then the user can control the LEDs in any
 * way.  The following definitions are used to access individual LEDs.
 */

/* LED index values for use with board_userled() */

#define BOARD_LED1        0
#define BOARD_LED2        1
#define BOARD_LED3        2
#define BOARD_LED4        3
#define BOARD_NLEDS       4

#define BOARD_LED_GREEN   BOARD_LED1
#define BOARD_LED_ORANGE  BOARD_LED2
#define BOARD_LED_RED     BOARD_LED3
#define BOARD_LED_BLUE    BOARD_LED4

/* LED bits for use with board_userled_all() */

#define BOARD_LED1_BIT    (1 << BOARD_LED1)
#define BOARD_LED2_BIT    (1 << BOARD_LED2)
#define BOARD_LED3_BIT    (1 << BOARD_LED3)
#define BOARD_LED4_BIT    (1 << BOARD_LED4)

/* If CONFIG_ARCH_LEDs is defined, then NuttX will control the 4 LEDs on board
 * The following definitions describe how NuttX controls the LEDs:
 */

#define LED_STARTED       0  /* LED1 */
#define LED_HEAPALLOCATE  1  /* LED2 */
#define LED_IRQSENABLED   2  /* LED1 + LED2 */
#define LED_STACKCREATED  3  /* LED3 */
#define LED_INIRQ         4  /* LED1 + LED3 */
#define LED_SIGNAL        5  /* LED2 + LED3 */
#define LED_ASSERTION     6  /* LED1 + LED2 + LED3 */
#define LED_PANIC         7  /* N/C  + N/C  + N/C + LED4 */

/* Button definitions ***************************************************************/


#define BUTTON_USER        0

#define NUM_BUTTONS        1

#define BUTTON_USER_BIT    (1 << BUTTON_USER)

/* Alternate function pin selections ************************************************/
/* CAN */

#define GPIO_TIM4_CH2OUT GPIO_TIM4_CH2OUT_2

/* SPI - There is a MEMS device on SPI1 using these pins: */

#define GPIO_SPI1_MISO GPIO_SPI1_MISO_1
#define GPIO_SPI1_MOSI GPIO_SPI1_MOSI_1
#define GPIO_SPI1_SCK  GPIO_SPI1_SCK_1

/* SPI2 - Test MAX31855 on SPI2 PB10 = SCK, PB14 = MISO */

#define GPIO_SPI2_MISO   GPIO_SPI2_MISO_1
#define GPIO_SPI2_MOSI   GPIO_SPI2_MOSI_1
#define GPIO_SPI2_SCK    GPIO_SPI2_SCK_1

/* I2C config to use with Nunchuk PB7 (SDA) and PB8 (SCL) */

#define GPIO_I2C1_SCL  GPIO_I2C1_SCL_2
#define GPIO_I2C1_SDA  GPIO_I2C1_SDA_1

/* Timer Inputs/Outputs (see the README.txt file for options) */

#define GPIO_TIM2_CH1IN  GPIO_TIM2_CH1IN_2
#define GPIO_TIM2_CH2IN  GPIO_TIM2_CH2IN_1

#define GPIO_TIM8_CH1IN  GPIO_TIM8_CH1IN_1
#define GPIO_TIM8_CH2IN  GPIO_TIM8_CH2IN_1

/* Ethernet *************************************************************************/


/* DMA Channl/Stream Selections *****************************************************/
/* Stream selections are arbitrary for now but might become important in the future
 * if we set aside more DMA channels/streams.
 *
 * SDIO DMA
 *   DMAMAP_SDIO_1 = Channel 4, Stream 3
 *   DMAMAP_SDIO_2 = Channel 4, Stream 6
 */

#define DMAMAP_SDIO DMAMAP_SDIO_1




#define CONFIG_ISO7816_PWM    "/dev/PWM7"

/* use uart3 */
#ifndef CONFIG_BOARD_SHENZHEN
#define CONFIG_ISO7816_UART3  y
#endif
#define ISO7816_UART_BASE     SILAN_UART3_BASE
#define ISO7816_UART_IRQID    PIC_IRQ_UART3

/* use timer 2 */
#define CONFIG_ISO7816_TIMER  2

/***************************************************************
 * Wakeup sources config
 **************************************************************/
/* SC6138 wakeup source defines */
enum silan_wakeup_sources {
    SILAN_WAKEUP_SOURCE_RTC        = (1 << 0),
    SILAN_WAKEUP_SOURCE_WDT        = (1 << 1),
    SILAN_WAKEUP_SOURCE_TIME       = (1 << 2),
    SILAN_WAKEUP_SOURCE_GPIO1      = (1 << 3),
    SILAN_WAKEUP_SOURCE_GPIO2      = (1 << 4),
    SILAN_WAKEUP_SOURCE_GPIO1_0    = (1 << 5),
    SILAN_WAKEUP_SOURCE_GPIO1_1    = (1 << 6),
    SILAN_WAKEUP_SOURCE_GPIO1_2    = (1 << 7),
    SILAN_WAKEUP_SOURCE_GPIO1_3    = (1 << 8),
    SILAN_WAKEUP_SOURCE_GPIO1_4    = (1 << 9),
    SILAN_WAKEUP_SOURCE_GPIO1_5    = (1 << 10),
    SILAN_WAKEUP_SOURCE_GPIO1_6    = (1 << 11),
    SILAN_WAKEUP_SOURCE_GPIO1_7    = (1 << 12),
    SILAN_WAKEUP_SOURCE_GPIO1_8    = (1 << 13),
    SILAN_WAKEUP_SOURCE_GPIO1_9    = (1 << 14),
    SILAN_WAKEUP_SOURCE_GPIO1_10   = (1 << 15),
    SILAN_WAKEUP_SOURCE_GPIO1_11   = (1 << 16),
    SILAN_WAKEUP_SOURCE_GPIO1_12   = (1 << 17),
    SILAN_WAKEUP_SOURCE_GPIO1_13   = (1 << 18),
    SILAN_WAKEUP_SOURCE_GPIO1_14   = (1 << 19),
    SILAN_WAKEUP_SOURCE_GPIO1_15   = (1 << 20),
    SILAN_WAKEUP_SOURCE_GPIO1_16   = (1 << 21),
    SILAN_WAKEUP_SOURCE_GPIO1_17   = (1 << 22),
    SILAN_WAKEUP_SOURCE_GPIO1_18   = (1 << 23),
    SILAN_WAKEUP_SOURCE_GPIO1_19   = (1 << 24),
    SILAN_WAKEUP_SOURCE_GPIO1_20   = (1 << 25),
    SILAN_WAKEUP_SOURCE_GPIO2_9    = (1 << 26),
    SILAN_WAKEUP_SOURCE_GPIO2_10   = (1 << 27),
    SILAN_WAKEUP_SOURCE_GPIO2_11   = (1 << 28),
    SILAN_WAKEUP_SOURCE_GPIO2_12   = (1 << 29),
};

extern uint32_t SILAN_WAKEUP_SOURCE;
extern uint32_t SILAN_WAKEUP_SOURCE_POLARITY;

#define CONFIG_SE_PWM               "/dev/PWM2"

#define SC6138_PWM_NUMBER           8

/************************************************************************************
 * Public Data
 ************************************************************************************/

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/************************************************************************************
 * Public Function Prototypes
 ************************************************************************************/

/************************************************************************************
 * Name: sc6138_boardinitialize
 *
 * Description:
 *   All CSKY architectures must provide the following entry point.  This entry point
 *   is called early in the initialization -- after all memory has been configured
 *   and mapped but before any devices have been initialized.
 *
 ************************************************************************************/

void sc6138_boardinitialize(void);

#ifdef CONFIG_GPIO_BUTTON
int sc6138_buttoninitialize(void);
#endif

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif  /* __CONFIG_SILAN_INCLUDE_BOARD_H */
