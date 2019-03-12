/*
 * ckmcu-trilorite-v1.c - initialize some global variable data
 * items.
 *
 * Copyright (C): 2010 Hangzhou C-SKY Microsystem Co.,LTD.
 * Author: Jing Qing  (qing_jing@c-sky.com)
 * Date: 2010-04-14
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <nuttx/config.h>
#include <nuttx/module.h>
#include "silan_resources.h"
#include "silan_addrspace.h"
#include "board.h"

#if CONFIG_CHIP_SC6138
#include "silan_padmux.h"
extern int disable_peripheral(void);
extern void up_udelay(useconds_t microseconds);

static void silan_platform_init(void)
{
    unsigned long value;

#if defined(CONFIG_FACT_TEST) || defined(CONFIG_RISC_TEST)
    unsigned int value;
    //printf("pad: %x \n",REG32(KSEG1(SILAN_PADMUX_CTRL)));
    //printf("pad2: %x \n",REG32(KSEG1(SILAN_PADMUX_CTRL2)));
    REG32(KSEG1(SILAN_PADMUX_CTRL)) = ((1 << SILAN_PADMUX_UART2) | (1 << SILAN_PADMUX_I2C2));
    REG32(KSEG1(SILAN_PADMUX_CTRL2)) = (1 << SILAN_PADMUX2_JTAG);
#else
#ifdef CONFIG_BOARD_SHENZHEN
    silan_pad_enable("iis_adc_sdi0");
    silan_pad_enable("iis_adc");
	silan_pad_enable("iis_dac_mclk");
    silan_pad_enable("iis_dac");
	silan_pad_enable("iis_dac_sdo0");
    silan_pad_enable("iis_dac_sdo1");
	silan_pad_enable("iis_dac_sdo2");
#endif
#if 0//def CONFIG_BOARD_SHENZHEN
    silan_pad_enable("spdif_o");
    silan_pad_enable("spdif_i1_ch2");
    silan_pad_enable("spdif_i2_ch2");
    silan_pad_enable("spdif_i3_ch2");
#endif
#if defined(CONFIG_SC6138_ETHMAC) && !defined(CONFIG_BOARD_SHENZHEN)
//#ifdef CONFIG_SC6138_ETHMAC
    uint16_t gmac_pins[] = GMAC_PINS;
    zhuque_bsp_pinmux_set(PINMUX_DEV_GMAC,sizeof(gmac_pins)/2, gmac_pins);
#endif

#ifdef CONFIG_SC6138_I2C2
    value = REG32(KSEG1(SILAN_PADMUX_CTRL));
    value |= (1 << SILAN_PADMUX_I2C2);
    REG32(KSEG1(SILAN_PADMUX_CTRL)) = value;
#endif

#ifdef CONFIG_SYSTEM_UART1
    uint16_t uart1_pins[2] = {SC6138_UART1_TX,SC6138_UART1_RX};
    zhuque_bsp_pinmux_set(PINMUX_DEV_UART,sizeof(uart1_pins)/2, uart1_pins);
#endif
#ifdef CONFIG_SYSTEM_UART2
    uint16_t uart2_pins[2] = {SC6138_UART2_TX,SC6138_UART2_RX};
    zhuque_bsp_pinmux_set(PINMUX_DEV_UART,sizeof(uart2_pins)/2, uart2_pins);
#endif
#if defined (CONFIG_SYSTEM_UART3) && !defined(CONFIG_BOARD_SHENZHEN) && !defined(CONFIG_SC6138_I2C2)
//#ifdef CONFIG_SYSTEM_UART3
    uint16_t uart3_pins[2] = {SC6138_UART3_TX,SC6138_UART3_RX};
    zhuque_bsp_pinmux_set(PINMUX_DEV_UART,sizeof(uart3_pins)/2, uart3_pins);
#endif
#ifdef CONFIG_SYSTEM_UART4
    uint16_t uart4_pins[2] = {SC6138_UART4_TX,SC6138_UART4_RX};
    zhuque_bsp_pinmux_set(PINMUX_DEV_UART,sizeof(uart4_pins)/2, uart4_pins);
#endif
   
#ifndef CONFIG_BOARD_SHENZHEN
    // gpio function: for bluetooth
    uint16_t pin_pwm0[1] = {BT_RTS_PIN};
    zhuque_bsp_pinmux_release(PINMUX_DEV_PWM,sizeof(pin_pwm0)/2, pin_pwm0);
#endif

#if	1 //def CONFIG_NO_JTAG
    value = REG32(KSEG1(SILAN_PADMUX_CTRL2));
    value &= ~(1 << SILAN_PADMUX2_JTAG);
    REG32(KSEG1(SILAN_PADMUX_CTRL2)) = value;
#endif
#ifdef CONFIG_SILAN_SD_ENABLE
    value = REG32(KSEG1(SILAN_PADMUX_CTRL));
    value |= (1 << SILAN_PADMUX_SDMMC);
    value |= (1 << SILAN_PADMUX_SDMMCDAT);
    value |= (1 << SILAN_PADMUX_SDMMCDET);
    REG32(KSEG1(SILAN_PADMUX_CTRL)) = value;
#endif
#if defined(CONFIG_BOARD_SHENZHEN) || defined(CONFIG_SILAN_SDIO_CH1_ENABLE)
//#ifdef CONFIG_SILAN_SDIO_CH1_ENABLE
    value = REG32(KSEG1(SILAN_PADMUX_CTRL));
    value |= (1 << SILAN_PADMUX_SDIO);
    value |= (1 << SILAN_PADMUX_SDIODAT);
    value |= (1 << SILAN_PADMUX_SDIODET);
    REG32(KSEG1(SILAN_PADMUX_CTRL)) = value;
#elif defined(CONFIG_SILAN_SDIO_CH2_ENABLE)
    value = REG32(KSEG1(SILAN_PADMUX_CTRL));
    value |= (1 << SILAN_PADMUX_SDIODET);
    REG32(KSEG1(SILAN_PADMUX_CTRL)) = value;

    value = REG32(KSEG1(SILAN_PADMUX_CTRL2));
    value |= (1 << SILAN_PADMUX2_SDIO_CH2);
    value |= (1 << SILAN_PADMUX2_SDIO_DAT_CH2);
    REG32(KSEG1(SILAN_PADMUX_CTRL2)) = value;
#endif

#ifdef CONFIG_SC6138_SPI_CTRL
    value = REG32(KSEG1(SILAN_PADMUX_CTRL));
    value |= (1 << SILAN_PADMUX_SPI);
    //value |= (1 << SILAN_PADMUX_SPI_EX);
    REG32(KSEG1(SILAN_PADMUX_CTRL)) = value;
#endif

#endif
    /*ethernet mii*/
    value = REG32(KSEG1(SILAN_ENET_PHY_CTRL));
    value |= (3 << 0);
    REG32(KSEG1(SILAN_ENET_PHY_CTRL)) = value;

    // Enable USB1.1 PHY HOST PULLDOWN RES
    value = REG32(KSEG1(SILAN_SYSTEM_CTL_REG16));
    value |= (1<<6) | (1<<14);
    REG32(KSEG1(SILAN_SYSTEM_CTL_REG16)) = value;
    // Reset USB1.1 PLL
    value = REG32(KSEG1(SILAN_SYSTEM_CTL_REG15));
    value &= (~(1<<18)) & (~(1<<16));
    REG32(KSEG1(SILAN_SYSTEM_CTL_REG15)) = value;
	//usb set utmi_hostdisconnect
	up_udelay(1000);
	value = REG32(KSEG1(SILAN_SYSTEM_CTL_REG11));
    value |= (1<<5);
    REG32(KSEG1(SILAN_SYSTEM_CTL_REG11)) = value;

    //udelay(50);
    up_udelay(1000);
    value = REG32(KSEG1(SILAN_SYSTEM_CTL_REG15));
//  value |= (1<<18) | (1<<16);
    value |= (1<<18);
    REG32(KSEG1(SILAN_SYSTEM_CTL_REG15)) = value;
//  udelay(500);
    up_udelay(1000);
//  value = REG32(KSEG1(SILAN_SYSTEM_CTL_REG15));
//  value |= (1<<18) | (1<<16);
    value |= (1<<16);
    REG32(KSEG1(SILAN_SYSTEM_CTL_REG15)) = value;
    /*----------------------------------------------*/
    //gpio drive strength
    value = 0xaaaaaaaa; //8mA; 0x55555555: 4mA
    REG32(KSEG1(SILAN_SYSTEM_CTL_REG17)) = value;
    REG32(KSEG1(SILAN_SYSTEM_CTL_REG18)) = value;
    REG32(KSEG1(SILAN_SYSTEM_CTL_REG19)) = value;

#ifdef CONFIG_CEC

#if 0
    //gpio1_11 CEC 
    value = REG32(KSEG1(SILAN_PADMUX_CTRL));
    value &= ~(1<<SILAN_PADMUX_SPDIF_IN2);
    REG32(KSEG1(SILAN_PADMUX_CTRL)) = value;
	
    //GPIO1_10 spdif in
    value = REG32(KSEG1(SILAN_PADMUX_CTRL));
    value |= (1<<SILAN_PADMUX_SPDIF_IN1);
    REG32(KSEG1(SILAN_PADMUX_CTRL)) = value;
#endif
    value = REG32(KSEG1(SILAN_PADMUX_CTRL2));
    value |= (1<<SILAN_PADMUX2_SPDIF_IN0_CH2);
    REG32(KSEG1(SILAN_PADMUX_CTRL2)) = value;

    value = REG32(KSEG1(SILAN_PADMUX_CTRL2));
    value |= (1<<SILAN_PADMUX2_SPDIF_IN0_SEL);
    REG32(KSEG1(SILAN_PADMUX_CTRL2)) = value;

    value = REG32(KSEG1(SILAN_PADMUX_CTRL));
    value &= ~(1<<SILAN_PADMUX_IISADC_FD0);
    REG32(KSEG1(SILAN_PADMUX_CTRL)) = value;
 
    value = REG32(KSEG1(SILAN_PADMUX_CTRL)); //disable adc
    value &= ~(1<<12);
    REG32(KSEG1(SILAN_PADMUX_CTRL)) = value;


    //enable I2C2
    value = REG32(KSEG1(SILAN_PADMUX_CTRL));
    value &= ~(1<<SILAN_PADMUX_IISADC_FD1);
    REG32(KSEG1(SILAN_PADMUX_CTRL)) = value;

    value = REG32(KSEG1(SILAN_PADMUX_CTRL));
    value &= ~(1<<SILAN_PADMUX_IISADC_FD2);
    REG32(KSEG1(SILAN_PADMUX_CTRL)) = value;
    
    value = REG32(KSEG1(SILAN_PADMUX_CTRL));
    value &= ~(1<<SILAN_PADMUX_UART3_2);
    REG32(KSEG1(SILAN_PADMUX_CTRL)) = value;

    //value = REG32(KSEG1(SILAN_PADMUX_CTRL));
    //printf("111=%x\n",readl(0xba000024));

    //value = REG32(KSEG1(SILAN_PADMUX_CTRL2));
    //printf("padmux222=%x\n",value);
   //printf("padmux2222=%x\n",REG32(KSEG1(SILAN_PADMUX_CTRL2)));
#endif	

}

#elif CONFIG_CHIP_AP1508
#include "silan_iomux.h"
#include "silan_common.h"
static void silan_platform_init(void)
{
	silan_system_misc_clk_config(SILAN_MODULE_TIMER, 0);
#if CONFIG_SC6138_SD
	silan_system_misc_clk_config(SILAN_MODULE_SDMMC, 1);
	silan_iomux_config(SILAN_IOMUX_SDMMC,1);
#endif
#if CONFIG_MMCSD_SDIO
	silan_system_misc_clk_config(SILAN_MODULE_SDIO, 1);
	silan_iomux_config(SILAN_IOMUX_SDIO,1);
#endif
#if CONFIG_SC6138_ADC
	silan_system_misc_clk_config(SILAN_MODULE_ADC, 0);
#endif
#if CONFIG_SC6138_RTC
	silan_system_misc_clk_config(SILAN_MODULE_RTC, 0);
#endif
#ifndef CONFIG_BOARD_AP_5864B
#ifdef CONFIG_SC6138_SPI_CTRL
	silan_iomux_config(SILAN_IOMUX_SPI1,1);
#endif
#endif
#if CONFIG_SC6138_I2C1
	silan_iomux_config(SILAN_IOMUX_IIC1,1);
#endif
#if CONFIG_SC6138_I2C2
	silan_iomux_config(SILAN_IOMUX_IIC2,1);
#endif
#if CONFIG_SILAN_USBHS
	usb_clock_init();
#endif
#ifdef CONFIG_PWM
    silan_iomux_config_pwm(0, 1);
#endif
}
#endif
/*
 * disable all the peripheral and assign adress of boot parameters
 */
int up_board_init(void)
{
    /*first disable all the peripheral*/
    disable_peripheral();

    /* adress of boot parameters */

    silan_platform_init();
    return 0;

}
zhuque_early_init(up_board_init);
