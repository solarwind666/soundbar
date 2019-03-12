#ifndef __YOC_SYSDEP_H__
#define __YOC_SYSDEP_H__

#include <stddef.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>
#include <sys/select.h>

/* fs */
#include <poll.h>
#include <fcntl.h>

/* network */
#ifdef CONFIG_NET_LWIP
#include <lwip/netdb.h>
#include <lwip/netif.h>
#endif

#define HEAP_CHECK

//#define HAL_ARCH_USE_NATIVE_GETTIMEOFDAY 1
#define HAL_ARCH_USE_COUNTER 1

/* we cannot include stdio.h, for vfs conflict */
int printf(FAR const char *format, ...);

#endif

