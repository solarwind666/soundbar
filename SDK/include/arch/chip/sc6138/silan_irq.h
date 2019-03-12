/* arch/csky/ck6408evb/include/mach/irqs.h
 *
 * Copyright (c) 20010 Simtec Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __SILAN_IRQ_H
#define __SILAN_IRQ_H

#define NO_IRQ                          (-1)
/* IRQ number allocate */
#define MIPS_CPU_IRQ_BASE               0
#define MIPS_CPU_IRQ_PIC                2
#define MIPS_PERFORMANCE_IRQ            6
#define MIPS_PIC_FIRQ_BASE              16
#define MIPS_PIC_IRQ_BASE               32

/* SW int 0 for resched */
#define MIPS_CPU_IPI_RESCHED_IRQ        0
#define C_RESCHED                       C_SW0
/* SW int 1 for resched */
#define MIPS_CPU_IPI_CALL_IRQ           1
#define C_CALL                          C_SW1

/* IRQ type */
#define INTC_INT_RISE_EDGE              0
#define INTC_INT_FALL_EDGE              1
#define INTC_INT_HIGH_LEVEL             2
#define INTC_INT_LOW_LEVEL              3
#define INTC_INT_DISABLE                4

#define PIC_IRQ_BASE                    0//32

#define PIC_IRQ_UART3                   (2+PIC_IRQ_BASE)
#define PIC_IRQ_UART4                   (3+PIC_IRQ_BASE)
#define PIC_IRQ_I2C2                    (4+PIC_IRQ_BASE)
#define PIC_IRQ_ADC                     (5+PIC_IRQ_BASE)
#define PIC_IRQ_RTC                     (6+PIC_IRQ_BASE)
#define PIC_IRQ_I2C1                    (7+PIC_IRQ_BASE)
#define PIC_IRQ_TIMER1                  (8+PIC_IRQ_BASE)
#define PIC_IRQ_TIMER2                  (9+PIC_IRQ_BASE)
#define PIC_IRQ_TIMER3                  (10+PIC_IRQ_BASE)
#define PIC_IRQ_TIMER4                  (11+PIC_IRQ_BASE)
#define PIC_IRQ_CODEC                   (12+PIC_IRQ_BASE)
#define PIC_IRQ_MS                      (13+PIC_IRQ_BASE)
#define PIC_IRQ_S                       (14+PIC_IRQ_BASE)
#define PIC_IRQ_SPDIF                   (15+PIC_IRQ_BASE)
#define PIC_IRQ_DRM                     (16+PIC_IRQ_BASE)
#define PIC_IRQ_DAC_IIS                 (17+PIC_IRQ_BASE)
#define PIC_IRQ_ADC_IIS                 (18+PIC_IRQ_BASE)
#define PIC_IRQ_SDMMC                   (19+PIC_IRQ_BASE)
#define PIC_IRQ_SDIO                    (20+PIC_IRQ_BASE)
#define PIC_IRQ_GPIO1                   (21+PIC_IRQ_BASE)
#define PIC_IRQ_GPIO2                   (22+PIC_IRQ_BASE)
#define PIC_IRQ_SPDIF_IN                (23+PIC_IRQ_BASE)
#define PIC_IRQ_WTG                     (24+PIC_IRQ_BASE)
#define PIC_IRQ_USB_HOST                (25+PIC_IRQ_BASE)
#define PIC_IRQ_GMAC                    (26+PIC_IRQ_BASE)
#define PIC_IRQ_USB_OTG                 (27+PIC_IRQ_BASE)
#define MIPS_DSP_CXC_IRQ                (28+PIC_IRQ_BASE)
#define PIC_IRQ_UART1                   (29+PIC_IRQ_BASE)
#define PIC_IRQ_UART2                   (30+PIC_IRQ_BASE)
#define PIC_IRQ_DMAC0                   (31+PIC_IRQ_BASE)

#endif   /* __ASM_MACH_IRQS_H */
