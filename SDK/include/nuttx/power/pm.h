/****************************************************************************
 * include/nuttx/power/pm.h
 * NuttX Power Management Interfaces
 *
 *   Copyright (C) 2011-2012, 2015 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/
/* Definition of terms.  Various "sleep" and low power consumption states
 * have various names and are sometimes used in conflicting ways.  In the
 * PM logic, we will use the following terminology:
 *
 * NORMAL  - The normal, full power operating mode.
 * IDLE    - This is still basically normal operational mode, the system is,
 *           however, IDLE and some simple simple steps to reduce power
 *           consumption provided that they do not interfere with normal
 *           Operation.  Simply dimming a backlight might be an example
 *           something that would be done when the system is idle.
 * STANDBY - Standby is a lower power consumption mode that may involve more
 *           extensive power management steps such has disabling clocking or
 *           setting the processor into reduced power consumption modes. In
 *           this state, the system should still be able to resume normal
 *           activity almost immediately.
 * SLEEP   - The lowest power consumption mode.  The most drastic power
 *           reduction measures possible should be taken in this state. It
 *           may require some time to get back to normal operation from
 *           SLEEP (some MCUs may even require going through reset).
 *
 * State changes always proceed from higher to lower power usage:
 *
 * NORMAL->IDLE->STANDBY->SLEEP
 *   ^       |      |        |
 *   |       V      V        V
 *   +-------+------+--------+
 */

#ifndef __INCLUDE_NUTTX_POWER_PM_H
#define __INCLUDE_NUTTX_POWER_PM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/fs/ioctl.h>
#include <stdbool.h>

#include <queue.h>

#ifdef CONFIG_PM

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
/* Power Manager IOCTL command defines */
#define PMIOC_ENTERLPM       _PMIOC(0x0001)
#define PMIOC_EXITLPM        _PMIOC(0x0002)
#define PMIOC_FLUSH          _PMIOC(0x0003)

#define PMIOC_DYNAMICFREQ    _PMIOC(0x0004)

#ifndef CONFIG_PM_DEV_PATH
#define CONFIG_PM_DEV_PATH          "/dev/pm"
#endif

/* Configuration ************************************************************/
/* CONFIG_IDLE_CUSTOM. Some architectures support this definition.  This,
 * if defined, will allow you replace the default IDLE loop with your
 * own, custom idle loop to support board-specific IDLE time power management
 */

/* Time slices.  The power management module collects activity counts in
 * time slices.  At the end of the time slice, the count accumulated during
 * that interval is applied to an averaging algorithm to determine the
 * activity level.
 *
 * CONFIG_PM_SLICEMS provides the duration of that time slice.  Default: 100
 * Milliseconds
 */

#ifndef CONFIG_PM_SLICEMS
#  define CONFIG_PM_SLICEMS  100 /* Default is 100 msec */
#endif

/* The function pm_acitivy is not needed now. System can't enter low power mode
 * while tasks running.
 */
#  define pm_activity(prio)
/****************************************************************************
 * Public Types
 ****************************************************************************/

/* This enumeration provides all power management states.  Receipt of the
 * state indication is the state transition event.
 */

enum pm_state_e
{
  PM_NORMAL = 0,   /* Normal full power operating mode.  If the driver is in
                    * a reduced power usage mode, it should immediately re-
                    * initialize for normal operatin.
                    *
                    * PM_NORMAL may be followed by PM_IDLE.
                    */
  PM_IDLE,         /* Drivers will receive this state change if it is
                    * appropriate to enter a simple IDLE power state.  This
                    * would include simple things such as reducing display back-
                    * lighting.  The driver should be ready to resume normal
                    * activity instantly.
                    *
                    * PM_IDLE may be followed by PM_STANDBY or PM_NORMAL.
                    */
  PM_STANDBY,      /* The system is entering standby mode. Standby is a lower
                    * power consumption mode that may involve more extensive
                    * power management steps such has disabling clocking or
                    * setting the processor into reduced power consumption
                    * modes. In this state, the system should still be able
                    * to resume normal activity almost immediately.
                    *
                    * PM_STANDBY may be followed PM_SLEEP or by PM_NORMAL
                    */
  PM_SLEEP,        /* The system is entering deep sleep mode.  The most drastic
                    * power reduction measures possible should be taken in this
                    * state. It may require some time to get back to normal
                    * operation from SLEEP (some MCUs may even require going
                    * through reset).
                    *
                    * PM_SLEEP may be following by PM_NORMAL
                    */
  PM_FSTANDBY,     /* enter Standby forcely, such as PM_STANDBY
                    */
  PM_FSLEEP,       /* enter Sleep forcely, such as PM_SLEEP
                    */
  PM_POWEROFF,     /* system try to reboot, all device should be closed
                    */
};

enum pm_prepare_ret {

    PM_PREPARE_OK = 0x0,    /* OK, system can enter new state */

    PM_PREPARE_WRONG = 0x1, /* Wrong, system can't enter new state */
};

enum pm_wakeup_source {

    PM_SOURCE_KEY1 = 0,     /* wakeup sources. When CPU enter low power, */
    PM_SOURCE_KEY2,         /* users can using these keys to wakeup      */
    PM_SOURCE_KEY3,         /* system. In apps/system/power, using these */
    PM_SOURCE_KEY4,         /* to config which key can wakeup system.    */
};

/* This structure contains platform's callbacks which used to set wakeup
 * sources, execute standby instruction and execute reboot opreation. It
 * initial by pm_initilize.
 */
struct pm_operations
{
    /* This callback is used to set wakeup sources, it points to platform
     * interface
     */
    void (*wakeup_source)(enum pm_wakeup_source);

    /* This callback is used to execute standby instruction, it points to
     * platform interface
     */
    void (*enter_standby)(void);
};

/* This structure contain pointers callback functions in the driver.  These
 * callback functions can be used to provide power management information
 * to the driver.
 */

struct pm_callback_s
{
  struct sq_entry_s entry;   /* Supports a singly linked list */

  pid_t pid;                 /* the thread pid want to in PM white list */

  bool iswhite;              /* the thread is in PM white list or black list */

  /**************************************************************************
   * Name: prepare
   *
   * Description:
   *   Request the driver to prepare for a new power state. This is a
   *   warning that the system is about to enter into a new power state.  The
   *   driver should begin whatever operations that may be required to enter
   *   power state.  The driver may abort the state change mode by returning
   *   a non-zero value from the callback function
   *
   * Input Parameters:
   *   cb      - Returned to the driver.  The driver version of the callback
   *             structure may include additional, driver-specific state
   *             data at the end of the structure.
   *   pmstate - Identifies the new PM state
   *
   * Returned Value:
   *   0 (OK) means the event was successfully processed and that the driver
   *   is prepared for the PM state change.  Non-zero means that the driver
   *   is not prepared to perform the tasks needed achieve this power setting
   *   and will cause the state change to be aborted.  NOTE:  The prepare
   *   method will also be recalled when reverting from lower back to higher
   *   power consumption modes (say because another driver refused a lower
   *   power state change).  Drivers are not permitted to return non-zero
   *   values when reverting back to higher power consumption modes!
   *
   **************************************************************************/

  enum pm_prepare_ret (*prepare)(FAR struct pm_callback_s *cb, enum pm_state_e pmstate);

  /**************************************************************************
   * Name: notify
   *
   * Description:
   *   Notify the driver of new power state.  This callback is called after
   *   all drivers have had the opportunity to prepare for the new power
   *   state.
   *
   * Input Parameters:
   *   cb      - Returned to the driver.  The driver version of the callback
   *             structure may include additional, driver-specific state
   *             data at the end of the structure.
   *   pmstate - Identifies the new PM state
   *
   * Returned Value:
   *   None.  The driver already agreed to transition to the low power
   *   consumption state when when it returned OK to the prepare() call.
   *   At that time it should have made all preprations necessary to enter
   *   the new state.  Now the driver must make the state transition.
   *
   **************************************************************************/

  void (*notify)(FAR struct pm_callback_s *cb, enum pm_state_e pmstate);
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/
/****************************************************************************
 * Name: pm_initialize
 *
 * Description:
 *   This function is called by MCU-specific logic at power-on reset in
 *   order to provide one-time initialization the power management subsystem.
 *   This function must be called *very* early in the initialization sequence
 *   *before* any other device drivers are initialized (since they may
 *   attempt to register with the power management subsystem).
 *
 * Input parameters:
 *   wake_source - function to set wakeup source
 *
 * Returned value:
 *    None.
 *
 ****************************************************************************/

int pm_initialize(void);

/****************************************************************************
 * Name: pm_register
 *
 * Description:
 *   This function is called by a device driver in order to register to
 *   receive power management event callbacks.
 *
 * Input parameters:
 *   callbacks - An instance of struct pm_callback_s providing the driver
 *               callback functions.
 *
 * Returned value:
 *    Zero (OK) on success; otherwise a negater errno value is returned.
 *
 ****************************************************************************/

int pm_register(FAR struct pm_callback_s *callbacks);

/****************************************************************************
 * Name: pm_unregister
 *
 * Description:
 *   This function is called by a device driver in order to unregister to
 *   receive power management event callbacks.
 *
 * Input parameters:
 *   callbacks - An instance of struct pm_callback_s providing the driver
 *               callback functions.
 *
 * Returned value:
 *    Zero (OK) on success; otherwise a negater errno value is returned.
 *
 ****************************************************************************/

int pm_unregister(FAR struct pm_callback_s *callbacks);


/****************************************************************************
 * Name: pm_checkstate
 *
 * Description:
 *   This function is called from the MCU-specific IDLE loop to monitor the
 *   the power management conditions.  This function returns the "recommended"
 *   power management state based on the PM configuration and activity
 *   reported in the last sampling periods.  The power management state is
 *   not automatically changed, however.  The IDLE loop must call
 *   pm_changestate() in order to make the state change.
 *
 *   These two steps are separated because the platform-specific IDLE loop may
 *   have additional situational information that is not available to the
 *   the PM sub-system.  For example, the IDLE loop may know that the
 *   battery charge level is very low and may force lower power states
 *   even if there is activity.
 *
 *   NOTE: That these two steps are separated in time and, hence, the IDLE
 *   loop could be suspended for a long period of time between calling
 *   pm_checkstate() and pm_changestate().  The IDLE loop may need to make
 *   these calls atomic by either disabling interrupts until the state change
 *   is completed.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   The recommended power management state.
 *
 ****************************************************************************/

enum pm_state_e pm_checkstate(void);

/****************************************************************************
 * Name: pm_changestate
 *
 * Description:
 *   This function is used to platform-specific power management logic.  It
 *   will announce the power management power management state change to all
 *   drivers that have registered for power management event callbacks.
 *
 * Input Parameters:
 *   newstate - Identifies the new PM state
 *
 * Returned Value:
 *   PM_PREPARE_OK means that the callback function for all registered drivers
 *   returned OK (meaning that they accept the state change). PM_PREPARE_WRONG
 *   means system can't enter new state. PM_PREPARE_REBOOT means system should
 *   reboot.
 *
 ****************************************************************************/

enum pm_prepare_ret pm_changestate(enum pm_state_e newstate);

/****************************************************************************
 * Name: pm_request
 *
 * Description:
 *     Request to change system state.
 *
 * Input Parameters:
 *     newstate ---- system new state
 *
 * Returned Value:
 *     None
 *
 *
 ****************************************************************************/
void pm_request(enum pm_state_e newstate);

/****************************************************************************
 * Name: pm_sync
 *
 * Description:
 *   update PM counter.
 *
 * Input Parameters:
 *   None.
 *
 * Returned Value:
 *   None.
 *
 * Assumptions:
 *
 ****************************************************************************/
void pm_sync(int sec);

/****************************************************************************
 * Name: pm_holdon
 *
 * Description:
 *   This function is used to hold PM state. 
 *
 * Input Parameters:
 *   dev ---- the dev id witch return by pm_register.
 *
 * Returned Value:
 *   NONE.
 *
 ****************************************************************************/
int pm_holdon(int dev);

/****************************************************************************
 * Name: pm_release
 *
 * Description:
 *   This function is used to enter low power mode. 
 *
 * Input Parameters:
 *   mode ---- the low power mode.
 *
 * Returned Value:
 *   NONE.
 *
 ****************************************************************************/

int pm_release(int dev);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */

/****************************************************************************
 * Stubs
 ****************************************************************************/

#else /* CONFIG_PM */

/* Stubbed out versions of all of PM interface functions that may be used to
 * avoid so much conditional compilation in driver code when PM is disabled:
 */

#  define pm_initialize(wake_source)
#  define pm_register(cb)       (0)
#  define pm_activity(prio)
#  define pm_checkstate()       (0)
#  define pm_changestate(state)
#  define pm_wakeup_source(source)

#endif /* CONFIG_PM */
#endif /* __INCLUDE_NUTTX_POWER_PM_H */
