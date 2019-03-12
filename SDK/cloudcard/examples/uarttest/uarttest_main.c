/****************************************************************************
 * apps/examples/uarttest/uarttest_main.c
 *
 * Copyright (C) 2015 The YunOS Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <nuttx/clock.h>

#include <nuttx/fs/fs.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>


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
 * serialrx_main
 ****************************************************************************/

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int uarttest_main(int argc, char *argv[])
#endif
{
	int fd;
	int number;
	char buf[100] = {0};
    struct termios oldtio;

	memset(buf, 0, 100);
	
	fd = open("/dev/ttyS1", O_RDWR);	
	if(fd < 0){
		perror("open");
		return -1;
	}

    if(tcgetattr(fd,&oldtio) != 0){
        printf("get serial error\n");
        return -1;
    }
	oldtio.c_cflag |= CS8;
	cfsetispeed(&oldtio,B115200);
	cfsetospeed(&oldtio,B115200);
	tcsetattr(fd, TCSANOW, &oldtio);
	
	printf("please enter some data\n");

	while(1){
		number = read(fd, buf, 10);
		if(number < 0)
		{
			perror("read");
			close(fd);
			return -1;
		}
		write(fd, buf, number);
	}
}





