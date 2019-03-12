/****************************************************************************
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

#ifndef __AUDIO_SILAN_H__
#define __AUDIO_SILAN_H__

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <nuttx/config.h>

#ifdef CONFIG_AUDIO_SILAN

/* Channel ID definition */
#define I2SIN_DEV0  2
#define I2SIN_DEV1  3
#define I2SOUT_DEV0 0
#define I2SOUT_DEV1 1
#define I2SIN_PCM   4
#define I2SOUT_PCM  5

/* Device name */
#define I2SIN_DEV0_NAME   "/dev/i2sin_dev0"
#define I2SIN_DEV1_NAME   "/dev/i2sin_dev1"
#define I2SOUT_DEV0_NAME  "/dev/i2sout_dev0"
#define I2SOUT_DEV1_NAME  "/dev/i2sout_dev1"
#define I2SIN_PCM_NAME    "/dev/i2sin_pcm"
#define I2SOUT_PCM_NAME   "/dev/i2sout_pcm"

#endif /* CONFIG_SC6138_I2S */
#endif /* __SC6138_I2S_H__ */
