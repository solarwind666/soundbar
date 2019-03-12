/****************************************************************************
 * examples/hello/keytest_main.c
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
#include <stdlib.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <nuttx/audio/audio.h>
#include <nuttx/audio/audio_silan.h>


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
 * i2s_main
 ****************************************************************************/
#define READ_SIZE 2048
char read_buf0[READ_SIZE];
char read_buf1[READ_SIZE];

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int i2stest_main(int argc, char *argv[])
#endif
{
    FILE *fp = NULL;
    char *path = NULL;
    int fd_in, fd_out0, fd_out1;
    int read_len0, read_len1;
    int need_read0 = 1, need_read1 = 1;
    int write_len0, write_len1;
    int need_write0 = 0, need_write1 = 0;
    int i2sin_dev_enable = 0;
    int i2sout_dev0_enable = 0, i2sout_dev1_enable = 0;
    struct audio_info_s info;

    printf("start i2stest_main %s\n", argv[1]);

    info.samplerate = 44100;
    info.channels = 2;
    info.format = 16;

    if (strcmp(argv[1], "i2sin") == 0)
    {
        //set i2sin dev0 for adc
        fd_in = open(I2SIN_DEV0_NAME, O_RDWR);
        if (fd_in < 0)
        {
            printf("open %s device failed!\n", I2SIN_DEV0_NAME);
            return -1;
        }
        ioctl(fd_in, AUDIOIOC_CONFIGURE, &info);
        i2sin_dev_enable = 1;
        
        //set i2sout dev1 for adc
        fd_out1 = open(I2SOUT_DEV1_NAME, O_RDWR);
        if (fd_out1 < 0)
        {
            printf("open %s device failed!\n", I2SOUT_DEV1_NAME);
            return -1;
        }
        ioctl(fd_out1, AUDIOIOC_CONFIGURE, &info);
        i2sout_dev1_enable = 1;
    }

    if ((argc == 2 && strcmp(argv[1], "i2sin") != 0) ||
            (argc == 3 && strcmp(argv[1], "i2sin") == 0))
    {
        if (argc == 2)
            path = argv[1];
        else if (argc == 3)
            path = argv[2];

        //open file
        fp = fopen(path, "r");
        if (!fp)
        {
            printf("open %s file failed!\n", argv[1]);
            return -1;
        }

        //set i2sout dev0 for play
        fd_out0 = open(I2SOUT_DEV0_NAME, O_RDWR);
        if (fd_out0 < 0)
        {
            printf("open %s device failed!\n", I2SOUT_DEV0_NAME);
            return -1;
        }
        ioctl(fd_out0, AUDIOIOC_CONFIGURE, &info);
        //ioctl(fd_out0, AUDIOIOC_SETVOLUME, 50);
        i2sout_dev0_enable = 1;
    }
    
    while (1)
    {
        if (i2sout_dev1_enable)
        {
            if (need_read1)
            {
                read_len1 = read(fd_in, read_buf1, READ_SIZE);
                if (read_len1 == READ_SIZE)
                {
                    need_read1 = 0;
                    need_write1 = 1;
                }
            }

            if (need_write1)
            {
                write_len1 = write(fd_out1, read_buf1, read_len1);
                if (write_len1 == read_len1)
                {
                    need_read1 = 1;
                    need_write1 = 0;
                }
            }
        }

        if (i2sout_dev0_enable)
        {
            if (need_read0)
            {
                read_len0 = fread(read_buf0, 1, READ_SIZE, fp);
                if (read_len0 > 0)
                {
                    need_read0 = 0;
                    need_write0 = 1;
                }
            }

            if (need_write0)
            {
                write_len0 = write(fd_out0, read_buf0, read_len0);
                if (write_len0 == read_len0)
                {
                    need_read0 = 1;
                    need_write0 = 0;
                }
            }
        }

        usleep(10);
    }

    if (i2sout_dev1_enable)
    {
        close(fd_in);
        close(fd_out1);
    }

    if (i2sout_dev0_enable)
    {
        fclose(fp);
        close(fd_out0);
    }
    return 0;
}
