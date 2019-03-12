/* spdif.h
*
* ALSA SoC Audio Layer - Silan S/PDIF Controller driver
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/

#ifndef _SILAN_SPDIF_OUT_H
#define _SILAN_SPDIF_OUT_H

#define SPD_USR1	0x00
#define SPD_USR2	0x04
#define SPD_USR3	0x08
#define SPD_Q2W		0x0C
#define SPD_USR_CNT	0x10
#define SPD_CSD1	0x14
#define SPD_CSD2	0x18
#define SPD_CSD3	0x1C
#define SPD_CSD4	0x20
#define SPD_CSD5	0x24
#define SPD_CSD6	0x28
#define SPD_FF_CTL	0x2C
#define SPD_FF_WDAT	0x30
#define SPD_STS		0x34
#define SPD_IRQEN	0x38
#define SPD_CTL		0x3C

#define SPD_CTL_MASK	0x1
#define SPD_CTL_ON		(1 << 0)
#define SPD_CTL_SW_RST	(1 << 3)
#define SPD_SW_MODE_EN	(1 << 4)
#define SPD_SW_MODE_OFF	(0 << 4)
#define SPD_ZERO_BUF	(0 << 1)
#define SPD_INTERVAL	(1 << 5)

#define CON_FMT_MASK	(1 << 2)
#define CON_PCM_16BIT	(0 << 2)
#define CON_PCM_24BIT	(1 << 2)

#define SPD_FF_FLUSH	(1 << 31)

#define CSTAS_SAMP_FREQ_MASK	(0xF << 24)
#define CSTAS_SAMP_FREQ_44	(0x0 << 24)
#define CSTAS_SAMP_FREQ_48	(0x2 << 24)
#define CSTAS_SAMP_FREQ_32	(0x3 << 24)
#define CSTAS_SAMP_FREQ_96	(0xA << 24)

#ifndef CONFIG_MIPS_SILAN_DLNA
#define SPD_EMPTY_NUM	(0x06 << 8)
#define SPD_FULL_NUM	(0x09)
#else
#define SPD_EMPTY_NUM	(0x18 << 8)
#define SPD_FULL_NUM	(0x1C)
#endif

#define SPD_CSD1_CFG	0x00310208
#define SPD_CSD2_CFG	0xF2
#define SPD_FF_CFG		(SPD_EMPTY_NUM | SPD_FULL_NUM)
#define SPD_STS_CLR		0x7
#define SPD_STS_CFG		(0x1 << 8)
#define SPD_IRQ_CFG		0x7
#define SPD_CTL_CFG		(CON_PCM_16BIT | SPD_SW_MODE_OFF | SPD_ZERO_BUF | SPD_INTERVAL)
#define SPD_Q2W_CFG		(0x1)

#endif
