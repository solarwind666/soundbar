/************************************************************************************
 *configs/sc6138yuncore/src/silan_resources.h
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

#ifndef __SILAN_RESOURCES_H__
#define __SILAN_RESOURCES_H__
#include <nuttx/config.h>

#define SILAN_SOFT_RESET_BASE             0xBA0D2000
#define SILAN_SOFT_RESET_PHY_BASE         0x1A0D2000
#define SILAN_SOFT_RESET_SIZE             0x4

#define SILAN_HOSTUSB_BASE                0xBF000000
#define SILAN_HOSTUSB_PHY_BASE            0x1F000000
#define SILAN_HOSTUSB_SIZE                0x2FFFF

#define SILAN_OTGUSB_BASE                 0xBD000000
#define SILAN_OTGUSB_PHY_BASE             0x1D000000
#define SILAN_OTGUSB_SIZE                 0x2FFFF

#define SILAN_GMAC_BASE                   0xBA030000
#define SILAN_GMAC_PHY_BASE               0x1A030000
#define SILAN_GMAC_SIZE                   0x7FFF

#define SILAN_DMAC0_BASE                  0xBC000000
#define SILAN_DMAC0_PHY_BASE              0x1C000000
#define SILAN_DMAC0_SIZE                  0x7FFF

//SD/MMC
#define SILAN_SD_BASE                     0xBA050000
#define SILAN_SD_PHY_BASE                 0x1A050000
#define SILAN_SD_SIZE                     0x7FFF

//SDIO/EMMC
#define SILAN_MMC_BASE                    0xBA060000
#define SILAN_MMC_PHY_BASE                0x1A060000
#define SILAN_MMC_SIZE                    0x7FFF

#define SILAN_CR_BASE                     0xBA000000
#define SILAN_CR_PHY_BASE                 0x1A000000
#define SILAN_CR_SIZE                     0xFFF

#define SILAN_SPI_REG_BASE                0xB9000000
#define SILAN_SPI_REG_PHY_BASE            0x19000000
#define SILAN_SPI_REG_SIZE                0xFFFF

//RTC
#define SILAN_RTC_BASE                    0xBA0D0000
#define SILAN_RTC_PHY_BASE                0x1A0D0000
#define SILAN_RTC_SIZE                    0xFFF

//UART_LS
#define SILAN_UART2_BASE                  0xBE010000
#define SILAN_UART2_PHY_BASE              0x1E010000
#define SILAN_UART2_SIZE                  0xFFF

//UART_HS
#define SILAN_UART1_BASE                  0xBE000000
#define SILAN_UART1_PHY_BASE              0x1E000000
#define SILAN_UART1_SIZE                  0xFFF

//UART_3
#define SILAN_UART3_BASE                  0xBE070000
#define SILAN_UART3_PHY_BASE              0x1E070000
#define SILAN_UART3_SIZE                  0xFFF

//UART_4
#define SILAN_UART4_BASE                  0xBE080000
#define SILAN_UART4_PHY_BASE              0x1E080000
#define SILAN_UART4_SIZE                  0xFFF

#define SILAN_SPI_FLASH_BASE             0xBA070000
#define SILAN_SPI_FLASH_PHY_BASE          0x1A070000
#define SILAN_SPI_FLASH_SIZE              0xFFF

//SPI_CTRL
#define SILAN_SPI_CTRL_BASE               0xBA080000
#define SILAN_SPI_CTRL_PHY_BASE           0x1A080000
#define SILAN_SPI_CTRL_SIZE               0xFFF

#define SILAN_I2C1_BASE                   0xBE060000
#define SILAN_I2C1_PHY_BASE               0x1E060000
#define SILAN_I2C1_SIZE                   0xFFF

#define SILAN_I2C2_BASE                   0xBE0A0000
#define SILAN_I2C2_PHY_BASE               0x1E0A0000
#define SILAN_I2C2_SIZE                   0xFFF

#define SILAN_TIMER1_BASE                  0xBA0A0000
#define SILAN_TIMER1_PHY_BASE              0x1A0A0000
#define SILAN_TIMER1_SIZE                  0xFFF

#define SILAN_TIMER2_BASE                  0xBA0A0010
#define SILAN_TIMER2_PHY_BASE              0x1A0A0010
#define SILAN_TIMER2_SIZE                  0xFFF

#define SILAN_TIMER3_BASE                  0xBA0A0020
#define SILAN_TIMER3_PHY_BASE              0x1A0A0020
#define SILAN_TIMER3_SIZE                  0xFFF

#define SILAN_TIMER4_BASE                  0xBA0A0030
#define SILAN_TIMER4_PHY_BASE              0x1A0A0030
#define SILAN_TIMER4_SIZE                  0xFFF

#define SILAN_GPIO1_BASE                  0xBA010000
#define SILAN_GPIO1_PHY_BASE              0x1A010000
#define SILAN_GPIO1_SIZE                  0xFFF

#define SILAN_GPIO2_BASE                  0xBA020000
#define SILAN_GPIO2_PHY_BASE              0x1A020000
#define SILAN_GPIO2_SIZE                  0xFFF

#define SILAN_PWM_BASE                    0xBA0F0000
#define SILAN_PWM_PHY_BASE                0x1A0F0000
#define SILAN_PWM_SIZE                    0xFFF

#define SILAN_ICTL1_BASE                  0xBA090000
#define SILAN_ICTL1_PHY_BASE              0x1A090000
#define SILAN_ICTL1_SIZE                  0xFFF

#define SILAN_CXC_BASE                    0xBA0B0000
#define SILAN_CXC_PHY_BASE                0x1A0B0000
#define SILAN_CXC_SIZE                    0xFFF

#define SILAN_DSPCFG_BASE                 0xBA0C0000
#define SILAN_DSPCFG_PHY_BASE             0xBA0C0000
#define SILAN_DSPCFG_SIZE                 0xFFF

//PMU
#define SILAN_PMU_BASE                    0xBA040000
#define SILAN_PMU_PHY_BASE                0x1A040000
#define SILAN_PMU_SIZE                    0xFFF

//WATCHDOG
#define SILAN_WTG_BASE                    0xBA0D1000
#define SILAN_WTG_PHY_BASE                0x1A0D1000
#define SILAN_WTG_SIZE                    0xFFF

#define SILAN_ADC_BASE                    0xBA0D3000
#define SILAN_ADC_PHY_BASE                0x1A0D3000
#define SILAN_ADC_SIZE                    0xFFF

#define SILAN_IISDAC_BASE                 0xBE030000
#define SILAN_IISDAC_PHY_BASE             0x1E030000
#define SILAN_IISDAC_SIZE                 0xFFF

#define SILAN_IISADC_BASE                 0xBE040000
#define SILAN_IISADC_PHY_BASE             0x1E040000
#define SILAN_IISADC_SIZE                 0xFFF

#define SILAN_SPDIF_BASE                  0xBE050000
#define SILAN_SPDIF_PHY_BASE              0x1E050000
#define SILAN_SPDIF_SIZE                  0xFFF

#define SILAN_SPDIF_IN_BASE               0xBE020000
#define SILAN_SPDIF_IN_PHY_BASE           0x1E020000
#define SILAN_SPDIF_IN_SIZE               0xFFF

#define SILAN_UNICOM_BASE                 0xBA040000
#define SILAN_UNICOM_PHY_BASE             0x1A040000
#define SILAN_UNICOM_SIZE                 0xFFF

#define SILAN_DRM_DMA_BASE                0xBF100000
#define SILAN_DRM_DMA_PHY_BASE            0x1F100000
#define SILAN_DRM_DMA_SIZE                0xFFF

#define SILAN_DRM_BUF_BASE                0xBF180000
#define SILAN_DRM_BUF_PHY_BASE            0x1F180000
#define SILAN_DRM_BUF_SIZE                0xFFF

#define SILAN_DRM_CORE_BASE               0xBF190000
#define SILAN_DRM_CORE_PHY_BASE           0x1F190000
#define SILAN_DRM_CORE_SIZE               0xFFF

#define SILAN_UNICOM_CXC_BASE             0xBA040000
#define SILAN_UNICOM_CXC_PHY_BASE         0x1A040000
#define SILAN_UNICOM_CXC_SIZE             0xFFF

#define SILAN_CODEC_BASE				  0xBA0E0000
#define SILAN_CODEC_PHY_BASE			  0x1A0E0000
#define SILAN_CODEC_SIZE                  0xFFF

#define SILAN_INTL_BASE				      0xBA090000
#define SILAN_INTL_PHY_BASE				  0x1A090000
#define SILAN_INTL_SIZE                   0xFFF
#define SILAN_SPU_TIMER_PHY_BASE		  0x1A0A0000

#ifdef ARCH_SILAN_FPGA
#define SILAN_PHY_BASE                  0x1 /*FPGA*/
#else
#define SILAN_PHY_BASE                  0x1 /*ASIC*/
#endif

#define PAD_ON  1
#define PAD_OFF 0

/*sys register*/
#if CONFIG_CKCPU_MMU
#define SILAN_PADMUX_CTRL				0xba000024
#else
#define SILAN_PADMUX_CTRL				0x1a000024
#endif
#define SILAN_PADMUX_UART1              0
#define SILAN_PADMUX_UART2              1
#define SILAN_PADMUX_IISDAC_MCLK        2
#define SILAN_PADMUX_UART4_1            3
#define SILAN_PADMUX_UART4_2            4
#define SILAN_PADMUX_SPI                5
#define SILAN_PADMUX_SPI_EX             6
#define SILAN_PADMUX_SDMMC              7
#define SILAN_PADMUX_SDIO               8
#define SILAN_PADMUX_SDMMCDET           9
#define SILAN_PADMUX_SDIODET            10
#define SILAN_PADMUX_SF_DAT23           11
#define SILAN_PADMUX_IISADC             12
#define SILAN_PADMUX_UART3_1            13
#define SILAN_PADMUX_UART3_2            14
#define SILAN_PADMUX_IISDAC             15
#define SILAN_PADMUX_IISDAC_FD0         16
#define SILAN_PADMUX_IISDAC_FD1         17
#define SILAN_PADMUX_IISDAC_FD2         18
#define SILAN_PADMUX_IISADC_FD0         19
#define SILAN_PADMUX_IISADC_FD1         20
#define SILAN_PADMUX_IISADC_FD2         21
#define SILAN_PADMUX_SPDIF              22
#define SILAN_PADMUX_SDMMCDAT           23
#define SILAN_PADMUX_SDIODAT            24
#define SILAN_PADMUX_I2C2               25
#define SILAN_PADMUX_GMAC               26
#define SILAN_PADMUX_I2C1               27
#define SILAN_PADMUX_SPDIF_IN0          28
#define SILAN_PADMUX_SPDIF_IN1          29
#define SILAN_PADMUX_SPDIF_IN2          30
#define SILAN_PADMUX_SPDIF_IN3          31

#if CONFIG_CKCPU_MMU
#define SILAN_PADMUX_CTRL2				0xba00001c
#else
#define SILAN_PADMUX_CTRL2				0x1a00001c
#endif
#define SILAN_PADMUX2_PWM0              0
#define SILAN_PADMUX2_PWM1              1
#define SILAN_PADMUX2_PWM2              2
#define SILAN_PADMUX2_PWM3              3
#define SILAN_PADMUX2_PWM4              4
#define SILAN_PADMUX2_PWM5              5
#define SILAN_PADMUX2_PWM6              6
#define SILAN_PADMUX2_PWM7              7
#define SILAN_PADMUX2_SPDIF_IN0_CH2     8
#define SILAN_PADMUX2_SPDIF_IN1_CH2     9
#define SILAN_PADMUX2_SPDIF_IN2_CH2     10
#define SILAN_PADMUX2_SPDIF_IN3_CH2     11
#define SILAN_PADMUX2_IISADC_FD1_CH2    12
#define SILAN_PADMUX2_IISADC_FD2_CH2    13
#define SILAN_PADMUX2_UART1_CH2         14
#define SILAN_PADMUX2_SDIODET_CH2       15
#define SILAN_PADMUX2_IISADC_MODE       16
#define SILAN_PADMUX2_IISDAC_MODE       17
#define SILAN_PADMUX2_CODEC_ADC_SEL     18
#define SILAN_PADMUX2_CODEC_DAC_SEL     19
#define SILAN_PADMUX2_SPDIF_IN0_SEL     20
#define SILAN_PADMUX2_SPDIF_IN1_SEL     21
#define SILAN_PADMUX2_PWM2_CH2          24
#define SILAN_PADMUX2_PWM3_CH2          25
#define SILAN_PADMUX2_PWM1_CH2          26
#define SILAN_PADMUX2_SDIO_CH2          27
#define SILAN_PADMUX2_SDIO_DAT_CH2      28
#define SILAN_PADMUX2_JTAG              31


/*ENET PHY CTRL*/
#if CONFIG_CKCPU_MMU
#define SILAN_ENET_PHY_CTRL				0xba000020
#else
#define SILAN_ENET_PHY_CTRL				0x1a000020
#endif

#define SILAN_BB_MISC_BASE				0x1fa50000
#define SILAN_BB_MISC_DXMP0				(SILAN_BB_MISC_BASE+0x8)
#define SILAN_BB_MISC_DXMP1				(SILAN_BB_MISC_BASE+0xc)
#define SILAN_BB_MISC_DXMP2				(SILAN_BB_MISC_BASE+0x10)
#define SILAN_BB_MISC_DXMP_XPU			0x4
#define SILAN_BB_MISC_DXMP_GPU			0x9
#define SILAN_BB_MISC_DXMP_VPP			0xa
#define SILAN_BB_MISC_DXMP_DMABAR		0x2
#define SILAN_BB_MISC_DXMP_XPU_DMA		0x1
#define SILAN_BB_MISC_DXMP_VIDEO		0x8
#define SILAN_BB_MISC_DXMP_JPEG		    0x7
#define SILAN_BB_MISC_DXMP_PXBAR	    0xa
#define SILAN_BB_MISC_DXMP_DSP0			0x5
#define SILAN_BB_MISC_DXMP_DSP1			0x6

#define SILAN_BB_MISC_DDR				0x4
#define SILAN_BB_MISC_DSP0				0x2
#define SILAN_BB_MISC_DSP1				0x1
#define SILAN_BB_MISC_MIPS_SPM			0x3

#define SILAN_HSP_MISC_BASE				0x1fb69000 /*pjg 0xbfb68000*/
#define SILAN_HSP_MISC_USB				(SILAN_HSP_MISC_BASE+0x0)
#define SILAN_HSP_USB_DPPD_HOST			0
#define SILAN_HSP_USB_DNPD_HOST			0
#define SILAN_HSP_USB_IDDIG_HOST		0

#define SILAN_HSP_MISC_ENDIAN			(SILAN_HSP_MISC_BASE+0x4)
#define SILAN_HSP_ENDIAN_D_HOST			0
#define SILAN_HSP_ENDIAN_R_HOST			0
#define SILAN_HSP_ENDIAN_D_OTG			0
#define SILAN_HSP_ENDIAN_R_OTG			0
#define SILAN_HSP_ENDIAN_D_SATA			0
#define SILAN_HSP_ENDIAN_R_SATA			0
#define SILAN_HSP_ENDIAN_D_GMAC			0
#define SILAN_HSP_ENDIAN_R_GMAC			0
#define SILAN_HSP_ENDIAN_PX_AHB			0
#define SILAN_HSP_ENDIAN_GMAC_SPEED		0

#define SILAN_LSP_MISC_BASE				0x1fbd7000
#define SILAN_LSP_MISC_CTRL				(SILAN_LSP_MISC_BASE+0x0)
#define SILAN_LSP_WDT_CLK_EN			1
#define SILAN_LSP_TIMER_CLK_EN1			1
#define SILAN_LSP_TIMER_CLK_EN2			1
#define SILAN_LSP_SD_CLK_SEL			0
#define SILAN_LSP_SPI_CLK_SEL			0

/*System Control Register*/
#if CONFIG_CKCPU_MMU
#define SILAN_SYSTEM_CTL_BASE			0xba000000
#else
#define SILAN_SYSTEM_CTL_BASE			0x1a000000
#endif
#define SILAN_SYSTEM_CTL_REG1			(SILAN_SYSTEM_CTL_BASE+0x4)
#define SILAN_SYSTEM_CTL_REG2			(SILAN_SYSTEM_CTL_BASE+0x8)
#define SILAN_SYSTEM_CTL_REG3			(SILAN_SYSTEM_CTL_BASE+0xc)
#define SILAN_SYSTEM_CTL_REG4			(SILAN_SYSTEM_CTL_BASE+0x10)
#define SILAN_SYSTEM_CTL_REG5			(SILAN_SYSTEM_CTL_BASE+0x14)
#define SILAN_SYSTEM_CTL_REG6			(SILAN_SYSTEM_CTL_BASE+0x18)
#define SILAN_SYSTEM_CTL_REG7			(SILAN_SYSTEM_CTL_BASE+0x1c)
#define SILAN_SYSTEM_CTL_REG8			(SILAN_SYSTEM_CTL_BASE+0x20)
#define SILAN_SYSTEM_CTL_REG9			(SILAN_SYSTEM_CTL_BASE+0x24)
#define SILAN_SYSTEM_CTL_REG10			(SILAN_SYSTEM_CTL_BASE+0x28)
#define SILAN_SYSTEM_CTL_REG11			(SILAN_SYSTEM_CTL_BASE+0x2c)
#define SILAN_SYSTEM_CTL_REG12			(SILAN_SYSTEM_CTL_BASE+0x30)
#define SILAN_SYSTEM_CTL_REG13			(SILAN_SYSTEM_CTL_BASE+0x34)
#define SILAN_SYSTEM_CTL_REG14			(SILAN_SYSTEM_CTL_BASE+0x38)
#define SILAN_SYSTEM_CTL_REG15			(SILAN_SYSTEM_CTL_BASE+0x3c)
#define SILAN_SYSTEM_CTL_REG16			(SILAN_SYSTEM_CTL_BASE+0x40)
#define SILAN_SYSTEM_CTL_REG17			(SILAN_SYSTEM_CTL_BASE+0x44)
#define SILAN_SYSTEM_CTL_REG18			(SILAN_SYSTEM_CTL_BASE+0x48)
#define SILAN_SYSTEM_CTL_REG19			(SILAN_SYSTEM_CTL_BASE+0x4c)

#define SILAN_SYSTEM_CTL_REG21          (SILAN_SYSTEM_CTL_BASE+0x54)
#define SILAN_SYSTEM_CTL_REG22          (SILAN_SYSTEM_CTL_BASE+0x58)

#define SPI_BASE_ADDR     SILAN_SPI_PHY_BASE
#define SPI_MEM_1BIT      0x107c0
#define SPI_PAGE_CTRL     (SPI_BASE_ADDR | 0x500)
#define SPI_MAP_ADDR      0x1fbb0000
#define SPI_MAP_END_ADDR  0x1fbc0000
#endif

