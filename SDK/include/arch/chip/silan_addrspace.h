/*
 * Copyright (C) 2015 YunOS Project. All rights reserved.
 */

#ifndef _CSKY_ADDRSPACE_H_
#define _CSKY_ADDRSPACE_H_
#include <nuttx/config.h>

#define REG8( addr )		  (*(volatile unsigned char *)(addr))
#define REG16( addr )		  (*(volatile unsigned short*)(addr))
#define REG32( addr )		  (*(volatile unsigned int  *)(addr))
#define REG64( addr )		  (*(volatile unsigned long *)(addr))

#if CONFIG_CKCPU_MMU
/*
 * Memory segments (32bit kernel mode addresses)
 */

/*
 * Map an address to a certain kernel segment
 */
#define KSEG_MSK        0xE0000000
#define KSEG0BASE       0x80000000
#define KSEG1BASE       0xA0000000
#define KSEG2BASE       0xC0000000
#define KSEG3BASE       0xE0000000
#ifdef CONFIG_TEXT_RDONLY
#define KSEG0(addr)     (((addr) & ~KSEG_MSK)  | KSEG2BASE)
#else
#define KSEG0(addr)     (((addr) & ~KSEG_MSK)  | KSEG0BASE )
#endif
#define KSEG1(addr)     (((unsigned int)(addr) & ~KSEG_MSK)  | KSEG1BASE )
#define PHYS(addr)      ((addr) & ~KSEG_MSK)

/*
 * Returns the physical address of a KSEG0/KSEG1 address
 */
#define CPHYSADDR(a)	((a) & 0x1fffffff)
#define KSEG0ADDR(a)	(CPHYSADDR(a) | KSEG0BASE)
#define KSEG1ADDR(a)	(CPHYSADDR(a) | KSEG1BASE)
#define KSEG2ADDR(a)	(CPHYSADDR(a) | KSEG2_BASE)
#define KSEG3ADDR(a)	(CPHYSADDR(a) | KSEG3_BASE)


#else /* CONFIG_MMU */

#define KSEG0ADDR(a)    (a)
#define KSEG1ADDR(a)	(a)
#define KSEG2ADDR(a)	(a)
#define KSEG3ADDR(a)	(a)

#define KSEG0(addr)     (addr)
#define KSEG1(addr)     (addr)
#define PHYS(addr)      (addr)

#endif /* CONFIG_MMU */

#endif /* __ASM_ADDRSPACE_H */

