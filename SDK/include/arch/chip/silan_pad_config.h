#ifndef __SIALN_PAD_CONFIG_H__
#define __SIALN_PAD_CONFIG_H__
#include <nuttx/config.h>

#ifdef CONFIG_SILAN_I2C1
//#define SILAN_PAD_I2C1	1
#endif

#ifdef CONFIG_SILAN_I2C2
//#define SILAN_PAD_I2C2	1
#endif

#ifdef CONFIG_SYSTEM_UART1
//#define SILAN_PAD_UART1	1
#endif

#ifdef CONFIG_SYSTEM_UART2
#define SILAN_PAD_UART2	1
#endif

#if defined (CONFIG_SYSTEM_UART3) && !defined(CONFIG_BOARD_SHENZHEN) && !defined(CONFIG_SILAN_I2C2)
//#define SILAN_PAD_UART3	1
#endif

#ifdef CONFIG_SYSTEM_UART4
//#define SILAN_PAD_UART4	1
#endif

#ifdef CONFIG_BLUETOOTH
//#define SILAN_PAD_PWM		1
#endif

#ifdef CONFIG_SILAN_SPI_CTRL
#define SILAN_PAD_SPI1		1
#endif

#ifdef CONFIG_PWM
//#define SILAN_PAD_PWM		1
#endif

#endif	//__SIALN_PAD_CONFIG_H__
