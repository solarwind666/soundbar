/*
 * include/nuttx/usb/silan_otghs.h
 *
 *  Copyright (C) 2015 YunOS Project. All rights reserved.
 */

#ifndef __INCLUDE_NUTTX_USB_SULAN_OTGHS_H
#define __INCLUDE_NUTTX_USB_SULAN_OTGHS_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

#if defined(CONFIG_SILAN_USBHS)

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/
/* Configuration ********************************************************************/

#ifndef CONFIG_OTGHS_PRI
#  define CONFIG_OTGHS_PRI NVIC_SYSH_PRIORITY_DEFAULT
#endif

/************************************************************************************
 * Public Functions
 ************************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Name: silan_otgfshost_initialize
 *
 * Description:
 *   Initialize USB host device controller hardware.
 *
 * Input Parameters:
 *   controller -- If the device supports more than USB host controller, then
 *     this identifies which controller is being initializeed.  Normally, this
 *     is just zero.
 *
 * Returned Value:
 *   And instance of the USB host interface.  The controlling task should
 *   use this interface to (1) call the wait() method to wait for a device
 *   to be connected, and (2) call the enumerate() method to bind the device
 *   to a class driver.
 *
 * Assumptions:
 * - This function should called in the initialization sequence in order
 *   to initialize the USB device functionality.
 * - Class drivers should be initialized prior to calling this function.
 *   Otherwise, there is a race condition if the device is already connected.
 *
 ****************************************************************************/

#ifdef CONFIG_USBHOST
struct usbhost_connection_s;
FAR struct usbhost_connection_s *silan_otghshost_initialize(int controller);
#endif

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* CONFIG_SILAN_USBHS */
#endif /* __INCLUDE_NUTTX_USB_SULAN_OTGHS_H */

