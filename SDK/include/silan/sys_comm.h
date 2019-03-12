/*--------------------------------------------------------------------
 *copyright (c) 2009-2010, Hangzhou silan Microelectronics CO.,LTD
 *					All rights reserved
 *
 *FileName:	sys_comm.h
 *Author:		Dong DongSheng
 *created:	2010-8-6
 *Edition:		1.0
 *Function:	系统公共用
 *Note:
 *History:
 *--------------------------------------------------------------------*/
#ifndef __SYS_COMM_H__ 
#define __SYS_COMM_H__

#define CPU_IS_LITTLE_ENDIAN 1

#if (CPU_IS_LITTLE_ENDIAN == 1)
	#define	MAKE_MARKER(a,b,c,d)	((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))
#elif (CPU_IS_BIG_ENDIAN == 1)
	#define	MAKE_MARKER(a,b,c,d)	(((a) << 24) | ((b) << 16) | ((c) << 8) | (d))
#endif




#define STORE_MODE_LITTLE_ENDIAN  0
#define STORE_MODE_BIG_ENDIAN     1

#define vaddr2paddr(x)			(x&0x1fffffff)
#define min(x, y)   (((x) > (y) ) ? (y) : (x))
#define max(x, y)   (((x) > (y) ) ? (x) : (y))
#define swap(a)		(((a&0xff)<<24)|((a&0xff00)<<8)|((a&0xff0000)>>8)|((a&0xff000000)>>24))
#define	swap16(a)	((((a)>>8)&0xff)|(((a)<<8)&0xff00))

#define const_fun0(addr)				(*((void(*)())addr))()
#define const_fun1(addr, para1)			(*((void(*)(UINT32))addr))(para1)

#define SLEEP(ms)			timer_wait_ms(ms)

#define __cpu_to_be32(x)	swap(x)
#define __cpu_to_be16(x)	swap16(x)
#define __be32_to_cpu(x)	swap(x)
#define __be16_to_cpu(x)	swap16(x)

#undef ntohl
#undef ntohs
#undef htonl
#undef htons

#define ___htonl(x) __cpu_to_be32(x)
#define ___htons(x) __cpu_to_be16(x)
#define ___ntohl(x) __be32_to_cpu(x)
#define ___ntohs(x) __be16_to_cpu(x)

#define htonl(x) ___htonl(x)
#define ntohl(x) ___ntohl(x)
#define htons(x) ___htons(x)
#define ntohs(x) ___ntohs(x)

//#define printf(format,...)	sie_printf(format, ##__VA_ARGS__)

#endif /*__SYS_COMM_H__*/
 
