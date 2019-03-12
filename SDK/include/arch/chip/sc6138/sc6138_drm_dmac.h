/************************************************************************************
 *arch/cskyv1/src/sc6138/sc6138_drm_dmac.h
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

#ifndef __SILAN_DMAC_H__
#define __SILAN_DMAC_H__

//#include "silan_drm.h"

#define PL080_INT_STATUS      (0x00)
#define PL080_TC_STATUS	      (0x04)
#define PL080_TC_CLEAR        (0x08)
#define PL080_ERR_STATUS      (0x0C)
#define PL080_ERR_CLEAR	      (0x10)
#define PL080_RAW_TC_STATUS	  (0x14)
#define PL080_RAW_ERR_STATUS  (0x18)
#define PL080_EN_CHAN         (0x1c)
#define PL080_SOFT_BREQ	      (0x20)
#define PL080_SOFT_SREQ	      (0x24)
#define PL080_SOFT_LBREQ      (0x28)
#define PL080_SOFT_LSREQ      (0x2C)

#define PL080_CONFIG          (0x30)
#define PL080_CONFIG_M2_BE    (1 << 2)
#define PL080_CONFIG_M1_BE    (1 << 1)
#define PL080_CONFIG_ENABLE	  (1 << 0)

#define PL080_SYNC            (0x34)

/* Per channel configuration registers */

#define PL080_Cx_STRIDE	      (0x20)
#define PL080_Cx_BASE(x)      ((0x100 + (x * 0x20)))
#define PL080_Cx_SRC_ADDR(x)  ((0x100 + (x * 0x20)))
#define PL080_Cx_DST_ADDR(x)  ((0x104 + (x * 0x20)))
#define PL080_Cx_LLI(x)	      ((0x108 + (x * 0x20)))
#define PL080_Cx_CONTROL(x)	  ((0x10C + (x * 0x20)))
#define PL080_Cx_CONFIG(x)    ((0x110 + (x * 0x20)))
#define PL080S_Cx_CONTROL2(x) ((0x110 + (x * 0x20)))
#define PL080S_Cx_CONFIG(x)	  ((0x114 + (x * 0x20)))

#define PL080_CH_SRC_ADDR     (0x00)
#define PL080_CH_DST_ADDR     (0x04)
#define PL080_CH_LLI          (0x08)
#define PL080_CH_CONTROL      (0x0C)
#define PL080_CH_CONFIG	      (0x10)
#define PL080S_CH_CONTROL2    (0x10)
#define PL080S_CH_CONFIG      (0x14)

#define PL080_LLI_ADDR_MASK   (0x3fffffff << 2)
#define PL080_LLI_ADDR_SHIFT  (2)
#define PL080_LLI_LM_AHB2     (1 << 0)

#define PL080_CONTROL_TC_IRQ_EN	  (1 << 31)
#define PL080_CONTROL_PROT_MASK	  (0x7 << 28)
#define PL080_CONTROL_PROT_SHIFT  (28)
#define PL080_CONTROL_PROT_CACHE  (1 << 30)
#define PL080_CONTROL_PROT_BUFF	  (1 << 29)
#define PL080_CONTROL_PROT_SYS    (1 << 28)
#define PL080_CONTROL_DST_INCR    (1 << 27)
#define PL080_CONTROL_SRC_INCR    (1 << 26)
#define PL080_CONTROL_DST_AHB2    (1 << 25)
#define PL080_CONTROL_SRC_AHB2    (1 << 24)
#define PL080_CONTROL_DWIDTH_MASK (0x7 << 21)
#define PL080_CONTROL_DWIDTH_SHIFT  (21)
#define PL080_CONTROL_SWIDTH_MASK   (0x7 << 18)
#define PL080_CONTROL_SWIDTH_SHIFT  (18)
#define PL080_CONTROL_DB_SIZE_MASK  (0x7 << 15)
#define PL080_CONTROL_DB_SIZE_SHIFT (15)
#define PL080_CONTROL_SB_SIZE_MASK  (0x7 << 12)
#define PL080_CONTROL_SB_SIZE_SHIFT (12)
#define PL080_CONTROL_TRANSFER_SIZE_MASK  (0xfff << 0)
#define PL080_CONTROL_TRANSFER_SIZE_SHIFT (0)

#define PL080_BSIZE_1    (0x0)
#define PL080_BSIZE_4    (0x1)
#define PL080_BSIZE_8    (0x2)
#define PL080_BSIZE_16   (0x3)
#define PL080_BSIZE_32   (0x4)
#define PL080_BSIZE_64   (0x5)
#define PL080_BSIZE_128  (0x6)
#define PL080_BSIZE_256	 (0x7)

#define PL080_WIDTH_8BIT   (0x0)
#define PL080_WIDTH_16BIT  (0x1)
#define PL080_WIDTH_32BIT  (0x2)

#define PL080_CONFIG_HALT                (1 << 18)
#define PL080_CONFIG_ACTIVE              (1 << 17)  /* RO */
#define PL080_CONFIG_LOCK                (1 << 16)
#define PL080_CONFIG_TC_IRQ_MASK         (1 << 15)
#define PL080_CONFIG_ERR_IRQ_MASK        (1 << 14)
#define PL080_CONFIG_FLOW_CONTROL_MASK   (0x7 << 11)
#define PL080_CONFIG_FLOW_CONTROL_SHIFT  (11)
#define PL080_CONFIG_DST_SEL_MASK        (0xf << 6)
#define PL080_CONFIG_DST_SEL_SHIFT       (6)
#define PL080_CONFIG_SRC_SEL_MASK        (0xf << 1)
#define PL080_CONFIG_SRC_SEL_SHIFT       (1)
#define PL080_CONFIG_ENABLE	             (1 << 0)

#define PL080_FLOW_MEM2MEM      (0x0)
#define PL080_FLOW_MEM2PER      (0x1)
#define PL080_FLOW_PER2MEM      (0x2)
#define PL080_FLOW_SRC2DST      (0x3)
#define PL080_FLOW_SRC2DST_DST  (0x4)
#define PL080_FLOW_MEM2PER_PER  (0x5)
#define PL080_FLOW_PER2MEM_PER  (0x6)
#define PL080_FLOW_SRC2DST_SRC  (0x7)

typedef void(*dma_callback)(void);

enum dma_data_direction {
    DMA_TO_DEVICE,
    DMA_FROM_DEVICE,
};

enum dma_buswidth {
    DMA_SLAVE_BUSWIDTH_UNDEFINED = 0,
    DMA_SLAVE_BUSWIDTH_1_BYTE = 1,
    DMA_SLAVE_BUSWIDTH_2_BYTES = 2,
    DMA_SLAVE_BUSWIDTH_4_BYTES = 4,
};

struct burst_table {
    int burstwords;
    unsigned int reg;
};

struct dma_chan {
    u32 chan_id;
    void volatile *dma_base_addr;
    void volatile *dma_cx_base_addr;
    u32 cctl;
    u32 ccfg;
    u32 src_addr;
    u32 dst_addr;
    u32 period_len;
    u32 buffer_len;
    u32 off;
    u32 peri_id;
    u32 burst_size;
};

#endif
