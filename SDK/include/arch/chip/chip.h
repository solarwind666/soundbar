#ifndef __ARCH_CSKYV1_SRC_SC6138_CHIP_H
#define __ARCH_CSKYV1_SRC_SC6138_CHIP_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>

/* Include the chip capabilities file */

#include <arch/chip/chip.h>

/* Include the chip memory map. */

#if defined(CONFIG_CHIP_SC6138)
#  define SC6138_NETHERNET                1   /* 100/100 Ethernet MAC */
#elif defined(CONFIG_CHIP_AP1508)

#else
#  error "Unsupported chip"
#endif

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/

#endif /* __ARCH_CSKYV1_SRC_SC6138_CHIP_H */

