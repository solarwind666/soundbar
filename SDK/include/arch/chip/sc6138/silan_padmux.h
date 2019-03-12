#ifndef _PADMUX_H
#define _PADMUX_H

#include <stdint.h>

#include "zhuque_bsp_pinmux.h"

#define PADMUX int
#define PAD_ON_OFF int

extern int silan_pad_enable(char *name);
extern int silan_pad_disable(char *name);


/*sc6138 private devices definiton*/
typedef enum sc6138_device_s {
	SC6138_DEV_GPIO = 0,    /*GPIO is the lowest priority functionality, only other functionality released it can be valid. all GPIO share the same device type*/

	SC6138_DEV_PWM0,
	SC6138_DEV_PWM1,
	SC6138_DEV_PWM2,
	SC6138_DEV_PWM3,
	SC6138_DEV_PWM4,
	SC6138_DEV_PWM5,
	SC6138_DEV_PWM6,
	SC6138_DEV_PWM7,

	SC6138_DEV_I2C1,
	SC6138_DEV_I2C2,

	SC6138_DEV_SPI,

	SC6138_DEV_SPIFLASH,

	SC6138_DEV_SDIO,

	SC6138_DEV_SDMMC,

	SC6138_DEV_UART1,
	SC6138_DEV_UART2,
	SC6138_DEV_UART3,
	SC6138_DEV_UART4,

	SC6138_DEV_SPDIF_I0,
	SC6138_DEV_SPDIF_I1,
	SC6138_DEV_SPDIF_I2,
	SC6138_DEV_SPDIF_I3,

	SC6138_DEV_SPDIF_O,

	SC6138_DEV_GMAC,

	SC6138_DEV_NUM    /*not a real device ,but for record the count of devices*/

} sc6138_device_t;






#endif






