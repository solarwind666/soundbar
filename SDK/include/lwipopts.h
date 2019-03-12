/**
 * @file
 *
 * lwIP Options Configuration
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#ifndef LWIP_LWIPOPTS_H
#define LWIP_LWIPOPTS_H

//#include "lwip/arch.h"

/*
   -------------- MHD option --------
*/

#define MHD_PAYLOAD_MTU           					(1500)
#define MHD_ETHERNET_SIZE         					(14)
#define MAX_SDPCM_HEADER_LENGTH 					(18)
#define MAX_BUS_HEADER_LENGTH 						(12)
#define MHD_LINK_OVERHEAD_BELOW_ETHERNET_FRAME_MAX	(MAX_BUS_HEADER_LENGTH + MAX_SDPCM_HEADER_LENGTH)
#define MHD_PHYSICAL_HEADER       					(MHD_LINK_OVERHEAD_BELOW_ETHERNET_FRAME_MAX + MHD_ETHERNET_SIZE)
#define MHD_LINK_MTU              					(MHD_PAYLOAD_MTU + MHD_PHYSICAL_HEADER)

/**
 * Include user defined options first. Anything not defined in these files
 * will be set to standard values. Override anything you dont like!
 */

/*
   -------------- NO SYS --------------
*/
#define NO_SYS                          0
#define SYS_LIGHTWEIGHT_PROT            (NO_SYS == 0)

/*
   ----------- Core locking -----------
*/
#define LWIP_TCPIP_CORE_LOCKING         1
#define LWIP_TCPIP_CORE_LOCKING_INPUT   1
/*
   ---------- Memory options ----------
*/
/* If MEM_LIBC_MALLOC and MEMP_MEM_MALLOC are defined to 1,
MEM_SIZE and MEMP_NUM_XXX will be invalid */
#define MEM_LIBC_MALLOC                 1
#define MEMP_MEM_MALLOC                 1
#define MEM_ALIGNMENT                   4
/* Application data is used for packet buffer directly */
#define MEM_SIZE                        6144//(1600+500)

/*
   ---------- Internal Memory Pool Sizes ----------
*/
#if 0
#define MEMP_NUM_PBUF                   8
#define MEMP_NUM_RAW_PCB                4
#define MEMP_NUM_UDP_PCB                4
#define MEMP_NUM_TCP_PCB                5
#define MEMP_NUM_TCP_PCB_LISTEN         8
#define MEMP_NUM_TCP_SEG                16
#define MEMP_NUM_REASSDATA              5
#define MEMP_NUM_FRAG_PBUF              8
#define MEMP_NUM_ARP_QUEUE              8
#define MEMP_NUM_NETBUF                 4
#define MEMP_NUM_NETCONN                64
#define MEMP_NUM_TCPIP_MSG_API          8
#define MEMP_NUM_TCPIP_MSG_INPKT        8
/* RX buffer size of enc28j60 is 6K, PBUF_POOL can be set less like cache L2/L3 */
#define PBUF_POOL_SIZE                  8
#else
//#define MEMP_NUM_PBUF                   2
//#define MEMP_NUM_RAW_PCB                2
//#define MEMP_NUM_UDP_PCB                4
//#define MEMP_NUM_TCP_PCB                8
//#define MEMP_NUM_TCP_PCB_LISTEN         4
#define MEMP_NUM_TCP_SEG                88 //(TCP_SND_QUEUELEN+1) // 8
#define MEMP_NUM_REASSDATA              20 //(IP_REASS_MAX_PBUFS - 1)// 2
//#define MEMP_NUM_FRAG_PBUF              2
#define MEMP_NUM_ARP_QUEUE              PBUF_POOL_SIZE/2 // 8
#define MEMP_NUM_NETBUF                 PBUF_POOL_SIZE// 4
#define MEMP_NUM_NETCONN                16
//#define MEMP_NUM_TCPIP_MSG_API          32
//#define MEMP_NUM_TCPIP_MSG_INPKT        32
/* RX buffer size of enc28j60 is 6K, PBUF_POOL can be set less like cache L2/L3 */
//#define PBUF_POOL_SIZE                  8

#endif
/*
   ---------- ARP options ----------
*/
#define LWIP_ARP                        1

/*
   ---------- IP options ----------
*/
#define LWIP_IPV4                       1
#define IP_FORWARD                      0
#define IP_OPTIONS_ALLOWED              1
#define IP_REASSEMBLY                   1
#define IP_FRAG                         1
#define IP_REASS_MAXAGE                 3
#define IP_REASS_MAX_PBUFS              20 //5 //6
#define LWIP_RANDOMIZE_INITIAL_LOCAL_PORTS     1

/*
   ---------- LINGER options ----------
*/
#define LWIP_SO_LINGER                  1

/*
   ---------- ICMP options ----------
*/
#define LWIP_ICMP                       1

/*
   ---------- RAW options ----------
*/
#define LWIP_RAW                        1

/*
   ---------- DHCP options ----------
*/
#define LWIP_DHCP                       1
#define DHCP_DOES_ARP_CHECK             0

/*
   ---------- AUTOIP options ----------
*/
#define LWIP_AUTOIP                     0

/*
   ---------- SNMP options ----------
*/
#define LWIP_SNMP                       0

/*
   ---------- IGMP options ----------
*/
#define LWIP_IGMP                       1

/*
   ---------- DNS options -----------
*/
#define LWIP_DNS                        1
#define LWIP_DNS_SECURE                 0

/*
   ---------- MTU options -----------
*/
#define NET_MTU                         (MHD_PAYLOAD_MTU)

/*
   ---------- UDP options ----------
*/
#define LWIP_UDP                        1

/*
   ---------- TCP options ----------
*/
#define LWIP_TCP                        1
#if 0
#define TCP_WND                         (16 * TCP_MSS)
#define TCP_QUEUE_OOSEQ                 0
#define TCP_MSS                         1460 //1440(IPV6)//1460(IPV4)
/* lwip_sanity_check, TCP_SND_BUF must be at least as much as (2 * TCP_MSS) */
#define TCP_SND_BUF                     (8 * TCP_MSS)
#else
/* TCP Maximum segment size. */
#define TCP_MSS                 1460 //1024

/* TCP sender buffer space (bytes). */
#define TCP_SND_BUF             (12* TCP_MSS)//(8* TCP_MSS)

/* TCP sender buffer space (pbufs). This must be at least = 2 *
   TCP_SND_BUF/TCP_MSS for things to work. */
#define TCP_SND_QUEUELEN       (2 * TCP_SND_BUF/TCP_MSS)//((4* (TCP_SND_BUF) + (TCP_MSS - 1))/(TCP_MSS))

/* TCP writable space (bytes). This must be less than or equal
   to TCP_SND_BUF. It is the amount of space which must be
   available in the tcp snd_buf for select to return writable */
#define TCP_SNDLOWAT           (TCP_SND_BUF/2)

/* TCP receive window. */
#define TCP_WND                 (12 * TCP_MSS)//8096

#define TCP_WND_UPDATE_THRESHOLD   (TCP_MSS * 2)

#endif

#define LWIP_LISTEN_BACKLOG             0

#define TCP_OVERSIZE                    TCP_MSS

#define LWIP_TCP_KEEPALIVE             (1)

/*
   ---------- Pbuf options ----------
*/
#define PBUF_POOL_SIZE          72
#define PBUF_LINK_ENCAPSULATION_HLEN	(MHD_PHYSICAL_HEADER)
#define PBUF_LINK_HLEN                  16
#define PBUF_POOL_BUFSIZE               (LWIP_MEM_ALIGN_SIZE(MHD_LINK_MTU) + 16/*LWIP_MEM_ALIGN_SIZE(sizeof(struct pbuf))*/ + 1)
#define LWIP_NETIF_TX_SINGLE_PBUF       (1)

#define LWIP_XR_EXT_MBUF_SUPPORT        0
#define LWIP_XR_EXT                     0

/*
   ---------- Network Interfaces options ----------
*/
#define LWIP_NETIF_REMOVE_CALLBACK		1

/*
   ---------- LOOPIF options ----------
*/
#define LWIP_HAVE_LOOPIF                0

/*
   ---------- Thread options ----------
*/
#define TCPIP_MBOX_SIZE                 16
#define DEFAULT_ACCEPTMBOX_SIZE         8
#define DEFAULT_RAW_RECVMBOX_SIZE       4
#define DEFAULT_UDP_RECVMBOX_SIZE       10 //8
#define DEFAULT_TCP_RECVMBOX_SIZE       (PBUF_POOL_SIZE/2)//8
#define TCPIP_THREAD_STACKSIZE          4096
#define TCPIP_THREAD_PRIO               107//14

/*
   ---------- Sequential layer options ----------
*/

#define LWIP_NETCONN                    1

/*
   ---------- Socket options ----------
*/
#define LWIP_SOCKET                     1
#define LWIP_COMPAT_SOCKETS             2
#define LWIP_POSIX_SOCKETS_IO_NAMES     0
#if 0
#if !defined(FD_SET) && defined(YUNOS_CONFIG_CSP_VFS_DEV_NODES)
#define LWIP_SOCKET_OFFSET              YUNOS_CONFIG_CSP_VFS_DEV_NODES
#endif
#else
#define LWIP_SOCKET_OFFSET              20
#endif
#define LWIP_SO_SNDTIMEO                1
#define LWIP_SO_RCVTIMEO                1
#define SO_REUSE                        1
#define LWIP_SOCKET_SEND_NOCOPY         0

/*
   ---------- Statistics options ----------
*/
#define LWIP_STATS                      1
#define LWIP_STATS_DISPLAY              1
#define LINK_STATS                      0
#define ETHARP_STATS                    0
#define IP_STATS                        0
#define IPFRAG_STATS                    0
#define ICMP_STATS                      0
#define IGMP_STATS                      0
#define UDP_STATS                       0
#define TCP_STATS                       0
//#define MEM_STATS                       ((MEM_LIBC_MALLOC == 0) && (MEM_USE_POOLS == 0))
//#define MEMP_STATS                      (MEMP_MEM_MALLOC == 0)
//#define SYS_STATS                       (NO_SYS == 0)
#define IP6_STATS                       0
#define ICMP6_STATS                     0
#define IP6_FRAG_STATS                  0
#define MLD6_STATS                      0
#define ND6_STATS                       0
#define MIB2_STATS                      0

/*
   ---------- Checksum options ----------
*/

/*
   ---------- IPv6 options ---------------
*/
#define LWIP_IPV6                       0
#define LWIP_IPV6_FRAG                  0

/*
   ---------- Hook options ---------------
*/

/*
   ---------- Debugging options ----------
*/
#define LWIP_DEBUG

#define LWIP_DBG_MIN_LEVEL              LWIP_DBG_LEVEL_ALL
#define LWIP_DBG_TYPES_ON               (LWIP_DBG_ON|LWIP_DBG_TRACE|LWIP_DBG_STATE|LWIP_DBG_FRESH|LWIP_DBG_HALT)

#define MEM_DEBUG                       LWIP_DBG_OFF
#define MEMP_DEBUG                      LWIP_DBG_OFF
#define PBUF_DEBUG                      LWIP_DBG_OFF
#define API_LIB_DEBUG                   LWIP_DBG_OFF
#define API_MSG_DEBUG                   LWIP_DBG_OFF
#define TCPIP_DEBUG                     LWIP_DBG_OFF
#define NETIF_DEBUG                     LWIP_DBG_OFF
#define SOCKETS_DEBUG                   LWIP_DBG_OFF
#define IP_DEBUG                        LWIP_DBG_OFF
#define IP_REASS_DEBUG                  LWIP_DBG_OFF
#define RAW_DEBUG                       LWIP_DBG_OFF
#define ICMP_DEBUG                      LWIP_DBG_OFF
#define UDP_DEBUG                       LWIP_DBG_OFF
#define TCP_DEBUG                       LWIP_DBG_OFF
#define TCP_INPUT_DEBUG                 LWIP_DBG_OFF
#define TCP_OUTPUT_DEBUG                LWIP_DBG_OFF
#define TCP_RTO_DEBUG                   LWIP_DBG_OFF
#define TCP_CWND_DEBUG                  LWIP_DBG_OFF
#define TCP_WND_DEBUG                   LWIP_DBG_OFF
#define TCP_FR_DEBUG                    LWIP_DBG_OFF
#define TCP_QLEN_DEBUG                  LWIP_DBG_OFF
#define TCP_RST_DEBUG                   LWIP_DBG_OFF

/*
   ---------- Performance tracking options ----------
*/

/*
   ---------- PPP options ----------
*/
#define PPP_SUPPORT                     0
#define PPPOE_SUPPORT                   0

#define LWIP_NETIF_API                  1

/*
   ---------- Httpd options ---------------
*/
#define LWIP_HTTPD_CGI                  1
#define LWIP_HTTPD_SSI                  1

#endif /* LWIP_LWIPOPTS_H */
