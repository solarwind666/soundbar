
#ifndef __SILAN_SPDIF_IN_REG_H
#define __SILAN_SPDIF_IN_REG_H __FILE__

#define SPDIF_IN_DR0                0x00
#define SPDIF_IN_DR1                0x04
#define SPDIF_IN_CONF0              0x08
#define SPDIF_IN_CONF1              0x0c
#define SPDIF_IN_STATUS             0x10
#define SPDIF_IN_FLS                0x14
#define SPDIF_IN_LENGTH             0x18
#define SPDIF_IN_LENGTH_DLT         0x1c
#define SPDIF_IN_FS48K              0x20
#define SPDIF_IN_FS96K              0x24
#define SPDIF_IN_FS192K             0x28
#define SPDIF_IN_FS44K              0x2c
#define SPDIF_IN_FS88K              0x30
#define SPDIF_IN_FS176K             0x34
#define SPDIF_IN_SUBFINTRV          0x38
#define SPDIF_IN_FSSTATUS           0x3c

#define SPDIF_IN_RAWINT             0x40
#define SPDIF_IN_MASKINT            0x44
#define SPDIF_IN_INTCLR             0x48
#define SPDIF_IN_INTMASK            0x4c
#define SPDIF_IN_FRAMES             0x50
#define SPDIF_IN_FS32K              0x54

#define SPDIF_IN_CS_REG0            0x58
#define SPDIF_IN_CS_REG1            0x5C
#define SPDIF_IN_CS_REG2            0x60
#define SPDIF_IN_CS_REG3            0x64
#define SPDIF_IN_CS_REG4            0x68
#define SPDIF_IN_CS_REG5            0x6c

#define SPDIF_IN_UB_REG0            0x70
#define SPDIF_IN_UB_REG1            0x74
#define SPDIF_IN_UB_REG2            0x78
#define SPDIF_IN_PCPD               0x7C

/* spdif_in_confg0 */
#define SPDIF_IN_SHAPED             (1 << 1)
#define SPDIF_IN_DATAIN_SEL         (1 << 2)
#define SPDIF_IN_RETRY              (1 << 3)    /* Fs_detector retry */
#define SPDIF_IN_MODE               (1 << 4)    /* 1 start from block; 0 start from frame */
#define SPDIF_IN_EN                 (1 << 5)    /* spdif enable signal */
#define SPDIF_IN_DMAEN              (1 << 6)    /* Dma enable signal */
#define SPDIF_IN_RSWRESET           (1 << 7)    /* not used */
#define SPDIF_IN_CAPTURE            (1 << 8)
#define SPDIF_IN_SYNC               (2 << 8)

/* spdif in status */
#define SPDIF_IN_PCM_FLAG           (1 << 18)

/* spdif_in_raw_int */
#define SPDIF_IN_PARITY_ERR         (1 << 0)    /* parity error interrupt */
#define SPDIF_IN_FRAME0             (1 << 1)    /* frame interrupt */
#define SPDIF_IN_OVER_FLOW          (1 << 2)    /* over flow interrupt */
#define SPDIF_IN_LOCK               (1 << 3)    /* lock interrupt */
#define SPDIF_IN_UNLOCK             (1 << 4)    /* unlock interrupt */
#define SPDIF_IN_RXTIDE             (1 << 5)    /* rx tide interrupt */
#define SPDIF_IN_CS_STROBE          (1 << 6)    /* cs reg strobe interrupt */
#define SPDIF_IN_UB_STROBE          (1 << 7)    /* user block strobe interrupt*/
#define SPDIF_IN_CS_DIF             (1 << 8)    /* cs reg dif interrupt*/
#define SPDIF_IN_UB_DIF             (1 << 9)    /* user reg dif interrupt*/
#define SPDIF_IN_PCM_RAW            (1 << 10)    /* pcm raw interrupt*/

/* spdif_in_int_mask */
#define SPDIF_IN_IRQ_ENABLE         (0x3ff)
#define SPDIF_IN_IRQ_DISABLE        (0x0)
#define SPDIF_IN_PARITY_ERR_MASK    (1 << 0)
#define SPDIF_IN_FRAME0_MASK        (1 << 1)
#define SPDIF_IN_OVER_FLOW_MASK     (1 << 2)
#define SPDIF_IN_LOCK_MASK          (1 << 3)
#define SPDIF_IN_UNLOCK_MASK        (1 << 4)
#define SPDIF_IN_RXTIDE_MASK        (1 << 5)
#define SPDIF_IN_CS_STROBE_MASK     (1 << 6)
#define SPDIF_IN_UB_STROBE_MASK     (1 << 7)
#define SPDIF_IN_CS_DIF_MASK        (1 << 8)
#define SPDIF_IN_UB_DIF_MASK        (1 << 9)
#define SPDIF_IN_PCM_RAW_MASK       (1 << 10)

/* spdif_in_fs_status */
#define SPDIF_IN_RATE_MASK          (0xff)

#endif /* __SILAN_SPDIF_IN_REG_H */

