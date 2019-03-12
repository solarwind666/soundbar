/****************************************************************************
 *                                                                          *
 * C-Sky Microsystems Confidential                                          *
 * -------------------------------                                          *
 * This file and all its contents are properties of C-Sky Microsystems. The *
 * information contained herein is confidential and proprietary and is not  *
 * to be disclosed outside of C-Sky Microsystems except under a             *
 * Non-Disclosured Agreement (NDA).                                         *
 *                                                                          *
 ****************************************************************************
 FILE_NAME           : ckmem.ld
 AUTHOR              : xialf(lifang_xia@c-sky.com)
 FUNCTION            : the file is linker file:
                       set the memory address to put the inst and data
 ******************************************************************************/

/*
 * memory map
 *    0x0     0x800000      0x8000000     0x10000000             0xffffffff
 *    |-------|-------------|-------------|----------------------|  
 *    flash    reserved     SDRAM         I/O     
 *
 * SDRAM map
 *    0x8000000     0x8600000           0x8640000            0x87fffff
 *    |-------------|-------------------|--------------------|  
 *    kernel        no cache(for dma)    this application     
 */

ENTRY(__start)

MEMORY
{
	MEM0 : ORIGIN = 0x80000000 , LENGTH = 0x200000
}

PROVIDE (__origin = 0x0);
PROVIDE (__length = 0x07600000);

/* 4K for fast interrupt stack */
PROVIDE (__fstack = 0x80800000 - 0x8);
PROVIDE (__stack =  0x80600000 - 0x8);
PROVIDE (__heap_start =  0x80800000);
PROVIDE (__heap_end   =  0x80d00000);
PROVIDE (__heap_size  =  __heap_end - __heap_start);

REGION_ALIAS("REGION_TEXT",   MEM0);
REGION_ALIAS("REGION_CUSTOM1", MEM0);
REGION_ALIAS("REGION_CUSTOM2", MEM0);
REGION_ALIAS("REGION_RODATA", MEM0);
REGION_ALIAS("REGION_DATA",   MEM0);
REGION_ALIAS("REGION_BSS",    MEM0);

