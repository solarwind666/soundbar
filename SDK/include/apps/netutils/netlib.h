/****************************************************************************
 *  apps/include/netutils/netlib.h
 * Various non-standard APIs to support netutils.  All non-standard and
 * intended only for internal use.
 *
 *   Copyright (C) 2007, 2009, 2011m 2015 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Some of these APIs derive from uIP.  uIP also has a BSD style license:
 *
 *   Author: Adam Dunkels <adam@sics.se>
 *   Copyright (c) 2002, Adam Dunkels.
 *   All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __APPS_INCLUDE_NETUTILS_NETLIB_H
#define __APPS_INCLUDE_NETUTILS_NETLIB_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

#include <netinet/in.h>
#include <nuttx/net/netconfig.h>
//#include <uv.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SOCK_DGRAM is the preferred socket type to use when we just want a
 * socket for performing drive ioctls.  However, we can't use SOCK_DRAM
 * if UDP is disabled.
 */

#ifdef CONFIG_NET_UDP
# define NETLIB_SOCK_IOCTL SOCK_DGRAM
#else
# define NETLIB_SOCK_IOCTL SOCK_STREAM
#endif

/****************************************************************************
 * Public Data
 ****************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/* Convert a textual representation of an IP address to a numerical representation.
 *
 * This function takes a textual representation of an IP address in
 * the form a.b.c.d and converts it into a 4-byte array that can be
 * used by other uIP functions.
 *
 * addrstr A pointer to a string containing the IP address in
 * textual form.
 *
 * addr A pointer to a 4-byte array that will be filled in with
 * the numerical representation of the address.
 *
 * Return: 0 If the IP address could not be parsed.
 * Return: Non-zero If the IP address was parsed.
 */

bool netlib_ipaddrconv(FAR const char *addrstr, uint8_t *addr);
bool netlib_hwmacconv(FAR const char *hwstr, uint8_t *hw);

#ifdef CONFIG_NET_ETHERNET
/* Get and set IP/MAC addresses (Ethernet L2 only) */

int netlib_setmacaddr(FAR const char *ifname, const uint8_t *macaddr);
int netlib_getmacaddr(FAR const char *ifname, uint8_t *macaddr);
#endif

/* IP address support */

#ifdef CONFIG_NET_IPv4
int netlib_get_ipv4addr(FAR const char *ifname, FAR struct in_addr *addr);
int netlib_set_ipv4addr(FAR const char *ifname, FAR const struct in_addr *addr);
int netlib_set_dripv4addr(FAR const char *ifname, FAR const struct in_addr *addr);
int netlib_set_ipv4netmask(FAR const char *ifname, FAR const struct in_addr *addr);
#endif

#ifdef CONFIG_NET_IPv6
int netlib_get_ipv6addr(FAR const char *ifname, FAR struct in6_addr *addr);
int netlib_set_ipv6addr(FAR const char *ifname, FAR const struct in6_addr *addr);
int netlib_set_dripv6addr(FAR const char *ifname, FAR const struct in6_addr *addr);
int netlib_set_ipv6netmask(FAR const char *ifname, FAR const struct in6_addr *addr);

uint8_t netlib_ipv6netmask2prefix(FAR const uint16_t *mask);
void netlib_prefix2ipv6netmask(uint8_t preflen, FAR struct in6_addr *netmask);
#endif

#ifdef CONFIG_NET_ICMPv6_AUTOCONF
/* ICMPv6 Autoconfiguration */

int netlib_icmpv6_autoconfiguration(FAR const char *ifname);
#endif

/* HTTP support */

int  netlib_parsehttpurl(FAR const char *url, uint16_t *port,
                      FAR char *hostname, int hostlen,
                      FAR char *filename, int namelen);

#ifndef CONFIG_WEBCLIENT_MAXHOSTNAME
#define CONFIG_WEBCLIENT_MAXHOSTNAME 40
#endif

#ifndef CONFIG_WEBCLIENT_MAXFILENAME
#define CONFIG_WEBCLIENT_MAXFILENAME 1024
#endif

struct http_status {
    char line[256];
    uint8_t ndx;

    uint8_t state;
    uint8_t httpstatus;
    uint8_t seekable;

    uint32_t filesize;

    uint16_t port;
    char hostname[CONFIG_WEBCLIENT_MAXHOSTNAME];
    char filename[CONFIG_WEBCLIENT_MAXFILENAME];
};

int  netlib_parsehttpstatus(struct http_status *ws, char *buffer, int buflen);

/* Generic server logic */

int netlib_listenon(uint16_t portno);
void netlib_server(uint16_t portno, pthread_startroutine_t handler,
                int stacksize);

int netlib_getifstatus(FAR const char *ifname, FAR uint8_t *flags);
int netlib_ifup(FAR const char *ifname);
int netlib_ifdown(FAR const char *ifname);
int netlib_http_is_state_data(struct http_status *ws);
int netlib_http_is_status_moved(struct http_status *hs);

/* DNS server addressing */

#if defined(CONFIG_NET_IPv4) && defined(CONFIG_NETDB_DNSCLIENT)
int netlib_set_ipv4dnsaddr(FAR const struct in_addr *inaddr);
int netlib_get_ipv4dnsaddr(FAR struct in_addr *inaddr);
#endif

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __APPS_INCLUDE_NETUTILS_NETLIB_H */