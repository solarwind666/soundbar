/****************************************************************************
 * include/nuttx/audio/silan_i2s.h
 * A do-nothinig audio device driver to simplify testing of audio decoders.
 *
 *   Copyright (C) 2015 Hang Xu. All rights reserved.
 *   Author: Hang Xu <xuhang@silan.com>
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

#ifndef __INCLUDE_NUTTX_AUDIO_SILAN_I2S_H
#define __INCLUDE_NUTTX_AUDIO_SILAN_I2S_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include <nuttx/irq.h>
#include <nuttx/audio/audio.h>

#ifdef CONFIG_SILAN_I2S

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
/* Configuration ************************************************************
 *
 * CONFIG_SILAN_I2S - Enabled NULL audio device support
 * CONFIG_SILAN_I2S_MSG_PRIO - Priority of messages sent to the NULL audio
 *   device worker   thread.
 * CONFIG_SILAN_I2S_BUFFER_SIZE - Preferred buffer size
 * CONFIG_SILAN_I2S_NUM_BUFFERS - Preferred number of buffers
 * CONFIG_SILAN_I2S_WORKER_STACKSIZE - Stack size to use when creating the
 *   NULL audio device worker thread.
 */

/* Pre-requisites */

/* Use the call back intterface or not */
#define SILAN_I2S_CALLBACK_INTERFACE

#ifndef CONFIG_AUDIO
#  error CONFIG_AUDIO is required for audio subsystem support
#endif

/* Default configuration values */

#ifndef CONFIG_SILAN_I2S_MSG_PRIO
#  define CONFIG_SILAN_I2S_MSG_PRIO          1
#endif

#ifndef CONFIG_SILAN_I2S_BUFFER_SIZE
#  define CONFIG_SILAN_I2S_BUFFER_SIZE       8192
#endif

#ifndef CONFIG_SILAN_I2S_NUM_BUFFERS
#  define CONFIG_SILAN_I2S_NUM_BUFFERS       4
#endif

#ifndef CONFIG_SILAN_I2S_WORKER_STACKSIZE
#  define CONFIG_SILAN_I2S_WORKER_STACKSIZE  768
#endif

/* Channel ID definition */
#define I2S_IN          (1 << 0)
#define I2S_OUT         (1 << 1)
#define I2S_INOUT       (I2S_IN | I2S_OUT)

/* Channel ID checking */
#define IS_I2S_IN(chan_list)       ((chan_list) & I2S_IN)
#define IS_I2S_OUT(chan_list)      ((chan_list) & I2S_OUT)
#define IS_I2S_INOUT(chan_list)    (IS_I2S_IN(chan_list) && IS_I2S_OUT(chan_list))

/* Device name */
#define SILAN_I2SIN_DEV_NAME        "/dev/sl-i2sin"
#define SILAN_I2SOUT_DEV_NAME       "/dev/sl-i2sout"
#define SILAN_I2SINOUT_DEV_NAME     "/dev/sl-i2s"

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: audio_silani2s_initialize
 *
 * Description:
 *   Initialize the silan i2s device.
 *
 * Input Parameters:
 *   i2c     - An I2C driver instance
 *   i2s     - An I2S driver instance
 *   lower   - Persistent board configuration data
 *
 * Returned Value:
 *   A new lower half audio interface for the NULL audio device is returned
 *   on success; NULL is returned on failure.
 *
 ****************************************************************************/

FAR struct audio_lowerhalf_s *audio_silani2s_initialize(unsigned int chan_list);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* CONFIG_SILAN_I2S */
#endif /* __INCLUDE_NUTTX_AUDIO_SILAN_I2S_H */
