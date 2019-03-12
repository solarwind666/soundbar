/*
 *  Copyright (C) 2015 YunOS Project. All rights reserved.
 */

#ifndef _SDMMC_H_
#define _SDMMC_H_

#include <silan_resources.h>
#define SYS_MAJOR_SDMMC_SILAN 16

#define SDMMC_CTRL			0x000
#define SDMMC_PWREN			0x004
#define SDMMC_CLKDIV		0x008
#define SDMMC_CLKSRC		0x00c
#define SDMMC_CLKENA		0x010
#define SDMMC_TMOUT			0x014
#define SDMMC_CTYPE			0x018
#define SDMMC_BLKSIZ		0x01c
#define SDMMC_BYTCNT		0x020
#define SDMMC_INTMASK		0x024
#define SDMMC_CMDARG		0x028
#define SDMMC_CMD			0x02c
#define SDMMC_RESP0			0x030
#define SDMMC_RESP1			0x034
#define SDMMC_RESP2			0x038
#define SDMMC_RESP3			0x03c
#define SDMMC_MINTSTS		0x040
#define SDMMC_RINTSTS		0x044
#define SDMMC_STATUS		0x048
#define SDMMC_FIFOTH		0x04c
#define SDMMC_CDETECT		0x050
#define SDMMC_WRTPRT		0x054
#define SDMMC_GPIO			0x058
#define SDMMC_FF_DAT_CNT	0x060
#define SDMMC_DEBNCE		0x064
#define SDMMC_USRID			0x068

#define SDMMC_DMAADDR		0x070
#define SDMMC_DMACTRL		0x074
#define SDMMC_RSP_SPI		0x078
#define SDMMC_BMOD			0x080
#define SDMMC_PLDMND		0x084
#define SDMMC_DBADDR		0x088
#define SDMMC_IDSTS             0x08c
#define SDMMC_IDINTEN           0x090
#define SDMMC_DSCADDR           0x094
#define SDMMC_BUFADDR           0x098
#define SDMMC_DATA              0x100

#define SDMMC_WR_DATA		0x100
#define SDMMC_RD_DATA		0x100

#define SDMMC_CTRL2			0x088

#define BIT(nr)				(1UL << (nr))
/* shift bit field */
#define _SBF(f, v)		((v) << (f))

/* Control register defines */
#define SDMMC_CTRL_O_DRAIN				BIT(24)
#define SDMMC_CTRL_ABRT_READ_DATA		BIT(8)
#define SDMMC_CTRL_SEND_IRQ_RESP		BIT(7)
#define SDMMC_CTRL_READ_WAIT			BIT(6)
#define SDMMC_CTRL_DMA_ENABLE			BIT(5)
#define SDMMC_CTRL_INT_ENABLE			BIT(4)
#define SDMMC_CTRL_DMA_RESET			BIT(2)
#define SDMMC_CTRL_FIFO_RESET			BIT(1)
#define SDMMC_CTRL_RESET				BIT(0)

/* CTRL2 defines */
#define SDMMC_CTRL2_DUAL_DATA			BIT(1)

/* Clock Enable register defines */
#define SDMMC_CLKEN_LOW_PWR				BIT(16)
#define SDMMC_CLKEN_ENABLE				BIT(0)
/* time-out register defines */
#define SDMMC_TMOUT_DATA(n)				_SBF(8,(n))
#define SDMMC_TMOUT_DATA_MSK			0xFFFFFF00
#define SDMMC_TMOUT_RESP(n)				((n)&0xFF)
#define SDMMC_TMOUT_RESP_MSK			0xFF
/* card-type register defines */
#define SDMMC_CTYPE_8BIT				0x10000
#define SDMMC_CTYPE_4BIT				BIT(0)
#define SDMMC_CTYPE_1BIT				0
/* Interrupt status & mask register defines */
#define SDMMC_INT_INX_ERR				BIT(26)
#define SDMMC_INT_CIU_DAT_DONE			BIT(25)
#define SDMMC_INT_DMA_DONE				BIT(24)
#define SDMMC_INT_ERR2					BIT(19)
#define SDMMC_INT_ERR1					BIT(18)
#define SDMMC_INT_ERR0					BIT(17)
#define SDMMC_INT_SDIO					BIT(16)
#define SDMMC_INT_EBE					BIT(15)
#define SDMMC_INT_ACD					BIT(14)
#define SDMMC_INT_SBE					BIT(13)
#define SDMMC_INT_HLE					BIT(12)
#define SDMMC_INT_FRUN					BIT(11)
#define SDMMC_INT_HTO					BIT(10)
#define SDMMC_INT_DTO					BIT(9)
#define SDMMC_INT_RTO					BIT(8)
#define SDMMC_INT_DCRC					BIT(7)
#define SDMMC_INT_RCRC					BIT(6)
#define SDMMC_INT_RXDR					BIT(5)
#define SDMMC_INT_TXDR					BIT(4)
#define SDMMC_INT_DATA_OVER				BIT(3)
#define SDMMC_INT_CMD_DONE				BIT(2)
#define SDMMC_INT_RESP_ERR				BIT(1)
#define SDMMC_INT_CD					BIT(0)
#define SDMMC_INT_ERROR					0xbfc2
/* Command register defines */
#define SDMMC_CMD_START					BIT(31)
#define SDMMC_CMD_CCS_EXP				BIT(23)
#define SDMMC_CMD_CEATA_RD				BIT(22)
#define SDMMC_CMD_UPD_CLK				BIT(21)
#define SDMMC_CMD_INIT					BIT(15)
#define SDMMC_CMD_STOP					BIT(14)
#define SDMMC_CMD_PRV_DAT_WAIT			BIT(13)
#define SDMMC_CMD_SEND_STOP				BIT(12)
#define SDMMC_CMD_STRM_MODE				BIT(11)
#define SDMMC_CMD_DAT_WR				BIT(10)
#define SDMMC_CMD_DAT_EXP				BIT(9)
#define SDMMC_CMD_RESP_CRC				BIT(8)
#define SDMMC_CMD_RESP_LONG				BIT(7)
#define SDMMC_CMD_RESP_EXP				BIT(6)
#define SDMMC_CMD_INDX(n)				((n) & 0x3F)
/* Status register defines */
#define SDMMC_GET_FCNT(x)				(((x)>>17) & 0x1FF)
#define SDMMC_FIFO_SZ					32

/* DMAC Control */
#define SDMMC_DMA_START					BIT(31)
#define DMA_BURST_INC4					3
#define DMA_BURST_INC8					5
#define DMA_BURST_INC16					7
#define SDMMC_DMA_BURST_SZ(x)			((x)<<28)
#define DMA_FIFO_INC32					0
#define DMA_FIFO_INC64					1
#define DMA_FIFO_INC128					2
#define DMA_FIFO_INC256					3
#define SDMMC_DMA_FIFO_SZ(x)			((x)<<26)
#define SDMMC_DMA_LEN(x)				((x)<<0)

#define SDMMC_CTRL_USE_IDMAC            BIT(25)
#define SDMMC_IDMAC_ENABLE              BIT(7)
#define SDMMC_IDMAC_FB                  BIT(1)
#define SDMMC_IDMAC_SWRESET             BIT(0)
#define SDMMC_IDMAC_INT_AI              BIT(9)
#define SDMMC_IDMAC_INT_NI              BIT(8)
#define SDMMC_IDMAC_INT_CES             BIT(5)
#define SDMMC_IDMAC_INT_DU              BIT(4)
#define SDMMC_IDMAC_INT_FBE             BIT(2)
#define SDMMC_IDMAC_INT_RI              BIT(1)
#define SDMMC_IDMAC_INT_TI              BIT(0)

#define MMC_VDD_165_195		0x00000080	/* VDD voltage 1.65 - 1.95 */
#define MMC_VDD_20_21		0x00000100	/* VDD voltage 2.0 ~ 2.1 */
#define MMC_VDD_21_22		0x00000200	/* VDD voltage 2.1 ~ 2.2 */
#define MMC_VDD_22_23		0x00000400	/* VDD voltage 2.2 ~ 2.3 */
#define MMC_VDD_23_24		0x00000800	/* VDD voltage 2.3 ~ 2.4 */
#define MMC_VDD_24_25		0x00001000	/* VDD voltage 2.4 ~ 2.5 */
#define MMC_VDD_25_26		0x00002000	/* VDD voltage 2.5 ~ 2.6 */
#define MMC_VDD_26_27		0x00004000	/* VDD voltage 2.6 ~ 2.7 */
#define MMC_VDD_27_28		0x00008000	/* VDD voltage 2.7 ~ 2.8 */
#define MMC_VDD_28_29		0x00010000	/* VDD voltage 2.8 ~ 2.9 */
#define MMC_VDD_29_30		0x00020000	/* VDD voltage 2.9 ~ 3.0 */
#define MMC_VDD_30_31		0x00040000	/* VDD voltage 3.0 ~ 3.1 */
#define MMC_VDD_31_32		0x00080000	/* VDD voltage 3.1 ~ 3.2 */
#define MMC_VDD_32_33		0x00100000	/* VDD voltage 3.2 ~ 3.3 */
#define MMC_VDD_33_34		0x00200000	/* VDD voltage 3.3 ~ 3.4 */
#define MMC_VDD_34_35		0x00400000	/* VDD voltage 3.4 ~ 3.5 */
#define MMC_VDD_35_36		0x00800000	/* VDD voltage 3.5 ~ 3.6 */

#define DEVICE_SD   0
#define DEVICE_SDIO 1

struct scatterlist {
    unsigned char	*buf;
    unsigned int	len;
    unsigned int	dma_addr;
};

struct mmc_command {
    unsigned int		opcode;
    unsigned int		arg;
    unsigned int 		flags;
};

//#define SDMMC_DATA_WRITE		(1 << 0)
//#define SDMMC_DATA_READ			(1 << 1)
//#define SDMMC_DATA_STREAM		(1 << 2)

struct sl_mmc_data {
    unsigned int	blksz;		/* data block size */
    unsigned int	blocks;		/* number of blocks */
    unsigned int	flags;

    unsigned int	bytes_xfered;
    struct scatterlist	*sg;		/* I/O scatter list */
};

struct mmc_request {
    struct mmc_command	*cmd;
    struct sl_mmc_data		*data;
};


#define SDMMC_BUS_WIDTH_1			0
#define SDMMC_BUS_WIDTH_4			1
#define SDMMC_BUS_WIDTH_8			2

#define SDMMC_CS_DONTCARE			0
#define SDMMC_CS_HIGH				1
#define SDMMC_CS_LOW				2

struct mmc_host;

struct mmc_ios {
    unsigned int	clock;			/* clock rate */
    unsigned char	bus_width;		/* data bus width */
    unsigned char	chip_select;		/* SPI chip select */
};


struct mmc_host_ops {
    int (*enable)(struct mmc_host *host);
    int (*disable)(struct mmc_host *host);
    int (*request)(struct mmc_host *host, struct mmc_request *req);
    int (*set_ios)(struct mmc_host *host, struct mmc_ios *ios);
    /*
     * Return values for the get_ro callback should be:
     *   0 for a read/write card
     *   1 for a read-only card
     */
    int	(*get_ro)(struct mmc_host *host);
    /*
     * Return values for the get_cd callback should be:
     *   0 for a absent card
     *   1 for a present card
     */
    int	(*get_cd)(struct mmc_host *host);
};

#define SDMMC_CAP_4_BIT_DATA			(1 << 0)	/* Can the host do 4 bit transfers */
#define SDMMC_CAP_8_BIT_DATA			(1 << 1)	/* Can the host do 8 bit transfers */
#define SDMMC_CAP_MMC_HIGHSPEED			(1 << 2)	/* Can do MMC high-speed timing */
#define SDMMC_CAP_SD_HIGHSPEED			(1 << 3)	/* Can do SD high-speed timing */
#define SDMMC_CAP_SDIO_IRQ				(1 << 4)	/* Can signal pending SDIO IRQs */
#define SDMMC_CAP_SPI					(1 << 5)	/* Talks only SPI protocols */
#define sdmmc_host_is_spi(x)			((x->caps)&SDMMC_CAP_SPI)

#define SDMMC_TYPE_SD		0
#define SDMMC_TYPE_MMC		1
#define SDMMC_TYPE_SDIO 	2
#define SDMMC_TYPE_NONE		3

#define SDMMC_MMC_RECV_STATUS	0
#define SDMMC_MMC_SEND_STATUS	1

#define SDMMC_STATUS_NONE		0
#define SDMMC_STATUS_CMD_ERR	1
#define SDMMC_STATUS_DATA_ERR	2
#define SDMMC_STATUS_CMD_DONE	3
#define SDMMC_STATUS_TRANSFER	4
#define SDMMC_STATUS_SUCCESS	5

/* Common flag combinations */
#define SL_MMC_DATA_ERROR_FLAGS	(SDMMC_INT_DTO | SDMMC_INT_DCRC | \
				 SDMMC_INT_HTO | SDMMC_INT_SBE  | \
				 SDMMC_INT_EBE)
#define SL_MMC_CMD_ERROR_FLAGS	(SDMMC_INT_RTO | SDMMC_INT_RCRC | \
				 SDMMC_INT_RESP_ERR)
#define SL_MMC_ERROR_FLAGS	(SL_MMC_DATA_ERROR_FLAGS | \
				 SL_MMC_CMD_ERROR_FLAGS  | SDMMC_INT_HLE)

#define SD_SAMPLE_INV       (0x1 << 12)
#define SD_SAMPLE_SEL       (0x1 << 13)
#define SD_SAMPLE_DELAY(x)  ((x) << 8)
#define SD_DRV_INV          (0x1 << 4)
#define SD_DRV_SEL          (0x1 << 5)
#define SD_DRV_DELAY(x)     ((x) << 0)

#define SDIO_SAMPLE_INV       (0x1 << 28)
#define SDIO_SAMPLE_SEL       (0x1 << 29)
#define SDIO_SAMPLE_DELAY(x)  ((x) << 24)
#define SDIO_DRV_INV          (0x1 << 20)
#define SDIO_DRV_SEL          (0x1 << 21)
#define SDIO_DRV_DELAY(x)     ((x) << 16)

#define PIN_SD_CLK(x)       ((x) << 20)
#define PIN_SDIO_CH1_CLK(x) ((x) << 6)
#define PIN_SDIO_CH2_CLK(x) ((x) << 24)
#define GPIO_2MA            0
#define GPIO_4MA            1
#define GPIO_8MA            2
#define GPIO_24MA           3

#define SDIO_CORE_FREQ      300000000
#define SD_CLOCK_SEL_MASK   (7 << 8)
#define SD_CLOCK_SEL_2      (0 << 8) 
#define SD_CLOCK_SEL_3      (2 << 8)
#define SD_CLOCK_SEL_4      (3 << 8)
#define SD_CLOCK_SEL_5      (4 << 8)
#define SD_CLOCK_SEL_6      (5 << 8)
#define SD_CLOCK_SEL_8      (6 << 8)
#define SD_CLOCK_SEL_16     (7 << 8)

#define SDIO_CLOCK_SEL_MASK (7 << 12)
#define SDIO_CLOCK_SEL_2    (0 << 12) 
#define SDIO_CLOCK_SEL_3    (2 << 12)
#define SDIO_CLOCK_SEL_4    (3 << 12)
#define SDIO_CLOCK_SEL_5    (4 << 12)
#define SDIO_CLOCK_SEL_6    (5 << 12)
#define SDIO_CLOCK_SEL_8    (6 << 12)
#define SDIO_CLOCK_SEL_16   (7 << 12)

struct mmc_host {
    struct mmc_host_ops *ops;
    struct mmc_request  *mrq;

    unsigned int	f_init;

    unsigned int	caps;		/* Host capabilities */
    unsigned int	type;
    int hcsd;
    int	present;
    int	read_only;

    unsigned int	bus_hz;
    unsigned int	cmd_cnt;
    unsigned int	base;
    unsigned int	sector_count;

    unsigned int	dir_status;
    int	use_dma;
    int	status;
    int err;

    int fifoth_val;
    struct scatterlist   *sg;
    unsigned int	pio_offset;

    unsigned int	resp[4];
    unsigned int minor;
};

static inline unsigned int mmc_readl(unsigned int reg )
{
    return *((volatile unsigned int *) (reg));
}

static inline void mmc_writel(unsigned int reg,unsigned int value)
{
    *((volatile unsigned int *) (reg)) = value ;
}

static inline unsigned int sl_mmc_readl(unsigned int base, unsigned int reg)
{
    return *((volatile unsigned int *) (base + reg));
}

static inline void sl_mmc_writel(unsigned int base, unsigned int reg,unsigned int value)
{
    *((volatile unsigned int *)(base + reg)) = value;
}



#endif

