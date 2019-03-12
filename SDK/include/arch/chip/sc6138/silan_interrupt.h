/*
 * silan_interrupt.h
 *
 *  Created on: 2013-1-17
 *      Author: Junbo Wu
 */

#ifndef _SILAN_INTERRUPT_H_
#define _SILAN_INTERRUPT_H_
//#include <configs/silan.h>
#include "silan_resources.h"
#include "silan_irq.h"
#include <nuttx/config.h>

typedef unsigned int    SL_REG;
typedef unsigned short  SL_SREG;
/*
 * define the registers structure of the interrupt controller
 */
typedef struct CKS_INTC {
    SL_REG IRQ_INTEN;
    SL_REG IRQ_REV1;
    SL_REG IRQ_INTMASK;
    SL_REG IRQ_REV2;
    SL_REG INTFORCE;
    SL_REG IRG_REV3;
    SL_REG IRG_RAWSTATUS;
    SL_REG IRQ_REV4;
    SL_REG IRQ_STATUS;
    SL_REG IRQ_REV5;
    SL_REG IRQ_MASKSTATUS;
    SL_REG IRQ_REV6;
    SL_REG IRQ_FINALSTATUS;
} CKStruct_INTC, *PCKStruct_INTC;

#if CONFIG_CKCPU_MMU
#define CKPIC_BASE  SILAN_INTL_BASE
#else
#define CKPIC_BASE  SILAN_INTL_PHY_BASE
#endif
#define PCK_INTC    ((PCKStruct_INTC)CKPIC_BASE)

/*
 *  Bit Definition for the PIC Interrupt control register
 */
#define ICR_AVE   0x80000000  /* Select vectored interrupt */
#define ICR_FVE   0x40000000  /* Unique vector number for fast vectored*/
#define ICR_ME    0x20000000  /* Interrupt masking enabled */
#define ICR_MFI   0x10000000  /* Fast interrupt requests masked by MASK value */


void enable_normalirq(int irq);
void disable_normalirq(int irq);


#endif /* _SILAN_INTERRUPT_H_ */
