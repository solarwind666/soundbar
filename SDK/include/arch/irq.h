/* This file should never be included directed but, rather, only indirectly
 * through nuttx/irq.h
 */

#ifndef __ARCH_CSKY_INCLUDE_IRQ_H
#define __ARCH_CSKY_INCLUDE_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/* Include NuttX-specific IRQ definitions */

#include <nuttx/irq.h>

/* Include chip-specific IRQ definitions (including IRQ numbers) */

#include <arch/chip/irq.h>

/* Include CSKY architecture-specific IRQ definitions (including register
 * save structure and irqsave()/irqrestore() macros)
 */

#if defined(CONFIG_ARCH_CK610)
#  include <arch/cskyv1/irq.h>
#elif defined(CONFIG_ARCH_CSKYV2L)
#  include <arch/cskyv2-l/irq.h>
#else
#  include <arch/cskyv2-h/irq.h>
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Inline functions
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifndef __ASSEMBLY__
#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

#undef EXTERN
#ifdef __cplusplus
}
#endif
#endif

#endif /* __ARCH_CSKY_INCLUDE_IRQ_H */

