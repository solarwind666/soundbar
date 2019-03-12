/* This file should never be included directed but, rather,
 * only indirectly through nuttx/irq.h
 */

#ifndef __ARCH_CSKY_SILAN_IRQ_H
#define __ARCH_CSKY_SILAN_IRQ_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>
#include <nuttx/irq.h>
#include <arch/chip/chip.h>

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/

#if defined(CONFIG_CHIP_SC6138)
#  include <arch/chip/sc6138/sc6138_irq.h>
#elif defined(CONFIG_CHIP_AP1508)
#  include <arch/chip/ap1508/ap1508_irq.h>
#else
#  error "Unsupported chip"
#endif

/************************************************************************************
 * Public Types
 ************************************************************************************/

/************************************************************************************
 * Public Data
 ************************************************************************************/

#ifndef __ASSEMBLY__

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif


/************************************************************************************
 * Public Functions
 ************************************************************************************/

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif/*__ASSEMBLY__*/

#endif /* __ARCH_CSKY_SILAN_IRQ_H */

