/****************************************************************************
 *
 *   Copyright (C) 2008, 2011-2012 Gregory Nutt. All rights reserved.
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>
#include <fcntl.h>

#include <nuttx/audio/silan_audio_api.h>
#include <apps/nxplayer.h>
#include <player_cmd.h>
/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * hello_main
 ****************************************************************************/
static int do_test(int argc, FAR char *argv[])   //argv[0] is taskname"flowplay_test", argv[1] is exename"flowplay", argv[2] is equal "main argv[1]"
{
    char buffer[1024];
    char url[128];
    char *buf;
    int len;
    FILE *fd;
    int ret;
    fd = fopen(argv[2],"r");  //to open pcm file
    if (!fd) {
        printf(" >>>>>>>>>>>>>>>>>>> open file  failed!\n");
        return -1;
    }
    //len = snprintf(url, sizeof(url), "music:///pcm:///0:2:16");
    //len = snprintf(url, sizeof(url), "music:///romfs:///0:2:16");
    len = snprintf(url, sizeof(url), "music:///mp3:///0:2:16");
    //len = snprintf(url, sizeof(url), "music:///:mp3:///:pcm:///%d:%d:%d", samplerate, chs, bits);
    player_process_cmd(NP_CMD_PLAY, url, 0, NULL, NULL);
    buf = buffer;
     do {
        len = fread(buffer,1,sizeof(buffer),fd);
        if(len >0) {
            ret = player_write_to_ringbuf_direct(buf,len);
            while(ret <=0) {
                if(ret < 0 ) {
                    printf("============the ringbuf is not ready waiting...\n");
                }
                ret = player_write_to_ringbuf_direct(buf,len);
                usleep(15000);
            }
        }
        usleep(1500);
    }while(len > 0);

    printf("======================file  end\n");
    fclose(fd);

    player_process_cmd(NP_CMD_PCM_END,NULL, 0, NULL, NULL); //exit play
    return 0;
}

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int flowplay_main(int argc, char *argv[])
#endif
{
    pid_t pid;
    if(argc < 2) {
        printf("usage: pcmplay   filename\n");
        return -1;
    }
    printf("================task_create filename:%s\n",argv[1]);
    pid = task_create("flowplay_test", 5, 5096, do_test, argv);

    if (pid < 0) {
        printf("============task_create error!\n");
        return -1;
    }
  return 0;
}
