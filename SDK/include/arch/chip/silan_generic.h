/************************************************************************************
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
 *
 ************************************************************************************/


#ifndef __SILAN_GENERIC_H__
#define __SILAN_GENERIC_H__
#include "sys/types.h"
#include "datatype.h"

#define readb(addr) \
    ({ unsigned char __v = (*(volatile unsigned char *) (addr)); __v; })
#define readw(addr) \
    ({ unsigned short __v = (*(volatile unsigned short *) (addr)); __v; })
#define readl(addr) \
    ({ unsigned int __v = (*(volatile unsigned int *) (addr)); __v; })

#define writel(b,addr) (void)((*(volatile unsigned int *) (addr)) = (b))
#define writeb(b,addr) (void)((*(volatile unsigned char *) (addr)) = (b))
#define writew(b,addr) (void)((*(volatile unsigned short *) (addr)) = (b))

#define BIT(n) ((long)1 << n)

static inline void sl_writeb(u8 val, unsigned long reg)
{
    *(volatile u8 *)(reg) = val;
#ifdef CONFIG_MIPS
    __asm__ volatile ("ehb");
#endif
}

static inline void sl_writew(u16 val, unsigned long reg)
{
    *(volatile u16 *)(reg) = val;
#ifdef CONFIG_MIPS
    __asm__ volatile ("ehb");
#endif
}

static inline void sl_writel(u32 val, unsigned long reg)
{
    *(volatile u32 *)(reg) = val;
#ifdef CONFIG_MIPS
    __asm__ volatile ("ehb");
#endif
}

static inline u8 sl_readb(unsigned long reg)
{
    return (*(volatile u8 *)reg);
}

static inline u16 sl_readw(unsigned long reg)
{
    return (*(volatile u16 *)reg);
}

static inline u32 sl_readl(unsigned long reg)
{
    return (*(volatile u32 *)reg);
}

#endif

