/************************************************************************************
 *configs/sc6138yuncore/src/sc6138_drm_core.c
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

#ifndef _SILAN_DRM_CORE_H_
#define _SILAN_DRM_CORE_H_
#include "datatype.h"

#define  _SBF(f,v)  ((v) << (f))

#define SWAP_WORD(x)  ((((x)&0xff000000)>>24) + (((x)&0x00ff0000)>>8) \
                        +(((x)&0x0000ff00)<<8)   + (((x)&0x000000ff)<<24))

#define SWAP_HWORD(x)  ((((x)&0xffff0000)>>16) + (((x)&0x0000ffff)<<16))

//BUF_CTRL
#define BUF0  0x0000
#define BUF1  0x0400

#define BUF0_CTRL        0x1000
#define BUF0_INP_CFG     0x1004
#define BUF0_OUT_CFG     0x1008
#define BUF0_WR_PTR      0x100c
#define BUF0_RD_PTR      0x1010
#define BUF0_STATUS	     0x1014
#define BUF0_DMA_RD_CFG  0x1018

#define BUF1_CTRL        0x1020
#define BUF1_INP_CFG     0x1024
#define BUF1_OUT_CFG     0x1028
#define BUF1_WR_PTR	     0x102c
#define BUF1_RD_PTR	     0x1030
#define BUF1_STATUS	     0x1034
#define BUF1_DMA_RD_CFG  0x1038

#define BUF_CFG	         0x1080

#define SECDMX_BUF_RESET        0x1
#define SECDMX_BUF_UNRESET      0x0

#define SECDMX_BUF_CPU_CHANNEL         0x0
#define SECDMX_BUF_DMA_CHANNEL         0x1
#define SECDMX_BUF_DRM_CIPHER_CHANNEL  0x2
#define SECDMX_BUF_DRM_HASH_CHANNEL    0x3
#define SECDMX_BUF_DRM_ALL_CHANNEL     0x4
#define SECDMX_BUF_SW_TS_CHANNEL       0x5

#define SECDMX_BUF_FIFO_MODE      (0x0 << 4)
#define SECDMX_BUF_DMA_MODE	      (0x1 << 4)
#define SECDMX_BUF_RAM_MODE	      (0x2 << 4)
#define SECDMX_BUF_FIFO_RAM_MODE  (0x3 << 4)



//DRM_CORE
typedef struct _DRM_CORE {
    volatile u32 key_reg0;	//initial secret key
    volatile u32 key_reg1;
    volatile u32 key_reg2;
    volatile u32 key_reg3;
    volatile u32 key_reg4;
    volatile u32 key_reg5;
    volatile u32 iv_reg0;	//initial vector
    volatile u32 iv_reg1;
    volatile u32 iv_reg2;
    volatile u32 iv_reg3;
    volatile u32 cnt_reg0;	//count value in ctr mode
    volatile u32 cnt_reg1;
    volatile u32 cnt_reg2;
    volatile u32 cnt_reg3;
    volatile u32 block_di_reg0;		//input data value in single step mode
    volatile u32 block_di_reg1;
    volatile u32 block_di_reg2;
    volatile u32 block_di_reg3;
    volatile u32 sector_size_reg;	//15-0: sector size, 31-16: block_num
    volatile u32 ctrl_reg;	//0:clear, 1:bypass_en, 2:strp_en. 3:init_en
    volatile u32 cfg_reg;	//0:decription enable, 3-1:type, 000:AES, 001:SMS4, 010:DES, 011:SDES, 100:C2
    //6-4:mode, 000:EBC,001:CBC,011:OFB100:CTR. 12-10:endian
    volatile u32 cmd_reg;	//0:block start, 1:sector start
    volatile u32 mask_reg;	//cipher mode interrupt mask enable
    volatile u32 status_reg;	//0:block_busy, 1:block_ready, 2:sector_tans, 3:sector_idle
    volatile u32 block_do_reg0;	//output data value in single step mode
    volatile u32 block_do_reg1;
    volatile u32 block_do_reg2;
    volatile u32 block_do_reg3;
    volatile u32 int_status;
} DRM_CORE;

#define DRM_CTRL_REG_CLEAR      BIT(0)
#define DRM_CTRL_REG_BYPASS_EN  BIT(1)
#define DRM_CTRL_REG_STEP_EN    BIT(2)
#define DRM_CTRL_REG_INIT_EN    BIT(3)

#define DRM_CMD_REG_BLOCK_START   BIT(0)
#define DRM_CMD_REG_SECTOR_START  BIT(1)

#define DRM_CFG_REG_DECRYPT	     BIT(0)
#define DRM_CFG_REG_TYPE(n)	     _SBF(1,  (n))
#define DRM_CFG_REG_MODE(n)	     _SBF(4,  (n))
#define DRM_CFG_REG_CFB_BYTE(n)	 _SBF(7,  (n))
#define DRM_CFG_REG_ENDIAN(n)    _SBF(16, (n))
#define DRM_CFG_REG_CSS_MOD(n)   _SBF(13, (n))
#define DRM_CFG_C2_MODE	         BIT(15)

#define DRM_STATUS_REG_BLOCK_BUSY   BIT(0)
#define DRM_STATUS_REG_BLOCK_READY  BIT(1)
#define DRM_STATUS_REG_SECTOR_TRANS BIT(2)
#define DRM_STATUS_REG_SECTOR_IDLE  BIT(3)

#define DRM_INT_REG_BLOCK_READY     BIT(0)
#define DRM_INT_REG_SECTOR_IDLE     BIT(1)

// 0 - Mask Interrput
// Only Enable Sector Idle Interrupt
#define DRM_INTERRUPT_UNMASK  0xd
#if 0
#define AES    0
#define SMS4   1
#define DES    2
#define SDES   3
#define C2     4

#define EBC    0
#define CBC    1
#define CFB    2
#define OFB    3
#define CTR    4

#define BIT8   1
#define BIT16  2
#define BIT32  3
#define BIT64  4
#endif

#define RSA_BIT_NUM (2048)
#define RSA_BYTE_NUM (RSA_BIT_NUM>>3)
#define RSA_WORD_NUM (RSA_BIT_NUM>>5)

#define DRM_RSA_C                   (0x800)
#define DRM_RSA_M                   (DRM_RSA_C + RSA_BYTE_NUM)
#define DRM_RSA_N                   (DRM_RSA_C + RSA_BYTE_NUM*2)
#define DRM_RSA_ED                  (DRM_RSA_C + RSA_BYTE_NUM*3)
#define DRM_RSA_CNTL                (DRM_RSA_C + RSA_BYTE_NUM*4)
#define DRM_RSA_INTR                (DRM_RSA_C + RSA_BYTE_NUM*4+0x4)
#define DRM_RSA_STATE               (DRM_RSA_C + RSA_BYTE_NUM*4+0x8)
#define DRM_RSA_EXCNT               (DRM_RSA_C + RSA_BYTE_NUM*4+0xC)

#define DRM_RSA_START               BIT(0)
#define DRM_RSA_UDD                 BIT(1)
#define DRM_RSA_MASK                BIT(2)
#define DRM_RSA_RAWINT              BIT(3)

#endif
