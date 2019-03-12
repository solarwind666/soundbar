/****************************************************************************
 * apps/system/nxplayer/nxplayer.h
 *
 *   Copyright (C) 2013 Ken Pettit. All rights reserved.
 *   Author: Ken Pettit <pettitkd@gmail.com>
 *
 * With updates, enhancements, and modifications by:
 *
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

#ifndef __APPS_SYSTEM_NXPLAYER_NXPLAYER_H
#define __APPS_SYSTEM_NXPLAYER_NXPLAYER_H 1

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifndef CONFIG_PLAYER_BUFFER_LEN
#   define CONFIG_PLAYER_BUFFER_LEN 2048
#endif

/****************************************************************************
 * Public Data
 ****************************************************************************/

typedef void (*player_cb)(int error, void *cb_para);

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
 * Name: nxplayer_create
 *
 *   Allocates and Initializes a NxPlayer context that is passed to all
 *   nxplayer routines.  The player MUST be destroyed using the
 *   nxplayer_destroy() routine since the context is reference counted.
 *   The context can be used in a mode where the caller creates the
 *   context, starts a file playing, and then forgets about the context
 *   and it will self free.  This is because the nxplayer_playfile
 *   will also create a reference to the context, so the client calling
 *   nxplayer_destroy() won't actually de-allocate anything.  The freeing
 *   will occur after the playthread has completed.
 *
 *   Alternately, the caller can create the objec and hold on to it, then
 *   the context will persist until the original creator destroys it.
 *
 * Input Parameters:    None
 *
 * Returned Value:
 *   Pointer to created NxPlayer context or NULL if error.
 *
 ****************************************************************************/

FAR void *nxplayer_create(void);

/****************************************************************************
 * Name: nxplayer_release
 *
 *   Reduces the reference count to the player and if it reaches zero,
 *   frees all memory used by the context.
 *
 * Input Parameters:
 *   pPlayer    Pointer to the NxPlayer context
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

void nxplayer_release(FAR void *pPlayer);

int player_bt_pcm_procss(short *buf, int samples, int chs, int bits);
int player_bt_dev_open(unsigned short samplerate, unsigned char bits, unsigned char chs);
#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __APPS_SYSTEM_NXPLAYER_NXPLAYER_H */
