#ifndef __DMAC_H__
#define __DMAC_H__
#define DMAC_BASE_ADDR		SILAN_DMAC0_BASE

//#define __REG( addr )		  (*(volatile unsigned int  *)(addr))


#define DMAC_INT_STS			__REG(DMAC_BASE_ADDR + 0x00)
#define DMAC_INT_TCSTS			__REG(DMAC_BASE_ADDR + 0x04)
#define DMAC_INT_TCLR			__REG(DMAC_BASE_ADDR + 0x08)
#define DMAC_INT_ERRSTS			__REG(DMAC_BASE_ADDR + 0x0c)
#define DMAC_INT_ERRCLR			__REG(DMAC_BASE_ADDR + 0x10)
#define DMAC_RAW_INTCTS			__REG(DMAC_BASE_ADDR + 0x14)
#define DMAC_RAW_INTERRSTS		__REG(DMAC_BASE_ADDR + 0x18)
#define DMAC_ENBLD_CHNS			__REG(DMAC_BASE_ADDR + 0x1c)
#define DMAC_SOFT_BREQ			__REG(DMAC_BASE_ADDR + 0x20)
#define DMAC_SOFT_SREQ			__REG(DMAC_BASE_ADDR + 0x24)
#define DMAC_SOFT_LBREQ			__REG(DMAC_BASE_ADDR + 0x28)
#define DMAC_SOFT_LSREQ			__REG(DMAC_BASE_ADDR + 0x2c)
#define DMAC_CONFIG				__REG(DMAC_BASE_ADDR + 0x30)
#define DMAC_SYNC				__REG(DMAC_BASE_ADDR + 0x34)
#define DMAC_Cx_SRC_ADDR(x)		__REG(DMAC_BASE_ADDR + 0x100 + x*0x20)
#define DMAC_Cx_DEST_ADDR(x)	__REG(DMAC_BASE_ADDR + 0x104 + x*0x20)
#define DMAC_Cx_LLI(x)			__REG(DMAC_BASE_ADDR + 0x108 + x*0x20)
#define DMAC_Cx_CONTROL(x)		__REG(DMAC_BASE_ADDR + 0x10c + x*0x20)
#define DMAC_Cx_CONFIG(x)		__REG(DMAC_BASE_ADDR + 0x110 + x*0x20)




/*
 * Description:
 *  DMA Controller - DMA Channel Registers - template structure
 *
 */

typedef volatile struct DMA_xChannel
{
    UINT32     SrcAddr;
    UINT32     DestAddr;
    UINT32     LLI;
    UINT32     Control;
    UINT32     Configuration;
    UINT32     Reserved1;
    UINT32     Reserved2;
    UINT32     Reserved3;

} DMA_sChannel;



/*
 * Description:
 *  Constants defining the size (in 32 bit words) of reserved spaces in the
 *  DMA controllers address space
 *
 */

#define DMA_NUM_RSRVD_WRDS_BEFORE_CHANNELS      ( (0x100 - 0x038) >> 2 )
#define DMA_NUM_RSRVD_WRDS_BEFORE_PERIPHERAL_ID ( (0xfe0 - 0x200) >> 2 )

/*
 * Description:
 *  DMA Controller - Template structure of entire address space of
 *  a DMA controller
 *
 */

typedef volatile struct DMA_xPort
{
    UINT32         IntStatus;              /* 0x000 */
    UINT32         IntTCStatus;
    UINT32         IntTCClear;
    UINT32         IntErrorStatus;
    UINT32         IntErrorClear;          /* 0x010 */
    UINT32         RawIntTCStatus;
    UINT32         RawIntErrorStatus;
    UINT32         ActiveChannels;

    UINT32         SoftBReq;               /* 0x020 */
    UINT32         SoftSReq;               /* 0x024 */
    UINT32         SoftLBReq;              /* 0x028 */
    UINT32         SoftSBReq;              /* 0x02C */
    
    UINT32         Configuration;          /* 0x030 */
    UINT32         Sync;                   /* 0x034 */

    UINT32         Reserved1[ DMA_NUM_RSRVD_WRDS_BEFORE_CHANNELS ];

    DMA_sChannel    sDmaChannels[ 8 ];     /* 0x100 -  */

    UINT32         Reserved2[ DMA_NUM_RSRVD_WRDS_BEFORE_PERIPHERAL_ID ];

    UINT32         PeripheralId0;          /* 0xFE0 */
    UINT32         PeripheralId1;
    UINT32         PeripheralId2;
    UINT32         PeripheralId3;
    UINT32         CellId0;                /* 0xFF0 */
    UINT32         CellId1;
    UINT32         CellId2;
    UINT32         CellId3;

} DMA_sPort;


/*
 * Description:
 *  DMA Controller - DMA Channel Control Register
 *
 */

#define bwDMA_TRANSFER_SIZE       		12   /* Transfer size */
#define bwDMA_SRC_BURST_SIZE       		3   /* Source Burst Size */
#define bwDMA_DEST_BURST_SIZE      		3   /* Destination Burst Size */
#define bwDMA_SRC_WIDTH            		3   /* Source Width */
#define bwDMA_DEST_WIDTH           		3   /* Destination Width */
#define bwDMA_SRC_BUS              		1   /* Source AHB Bus */
#define bwDMA_DEST_BUS             		1   /* Destination AHB Bus */
#define bwDMA_SRC_INCREMENT        		1   /* Source auto Increment */
#define bwDMA_DEST_INCREMENT       		1   /* Destination auto Increment */
#define bwDMA_PROTECTION           		3   /* Bus Protection Lines */
#define bwDMA_TC_INTERRUPT_ENABLE  		1   /* TC Interrupt enable */

#define bsDMA_TRANSFER_SIZE        		0
#define bsDMA_SRC_BURST_SIZE      		12
#define bsDMA_DEST_BURST_SIZE     		15
#define bsDMA_SRC_WIDTH           		18
#define bsDMA_DEST_WIDTH          		21
#define bsDMA_SRC_BUS             		24
#define bsDMA_DEST_BUS            		25
#define bsDMA_SRC_INCREMENT       		26
#define bsDMA_DEST_INCREMENT      		27
#define bsDMA_PROTECTION          		28
#define bsDMA_TC_INTERRUPT_ENABLE 		31


#define DMA_DBUS						1
#define DMA_DMEM						0

#define DMA_SBUS						1
#define DMA_SMEM						0

#define DMA_SWIDTH_8BIT					0
#define DMA_SWIDTH_16BIT				1
#define DMA_SWIDTH_32BIT				2


#define DMA_DWIDTH_8BIT					0
#define DMA_DWIDTH_16BIT				1
#define DMA_DWIDTH_32BIT				2


#define DMA_BURST_SIZE_1				0
#define DMA_BURST_SIZE_4				1
#define DMA_BURST_SIZE_8				2
#define DMA_BURST_SIZE_16				3
#define DMA_BURST_SIZE_32				4
#define DMA_BURST_SIZE_64				5
#define DMA_BURST_SIZE_128				6
#define DMA_BURST_SIZE_256				7

// DMACCnControl
#define DMA_LLI_TC_EN					(1<<31)
#define DMA_DST_ADDR_INC				(1<<27)
#define DMA_SRC_ADDR_INC				(1<<26)
#define DMA_DST_MASTER_SDRAM			(0<<25)
#define DMA_DST_MASTER_AHB				(1<<25)
#define DMA_SRC_MASTER_SDRAM			(0<<24)
#define DMA_SRC_MASTER_AHB				(1<<24)
#define DMA_DST_WIDTH_8					(0<<21)
#define DMA_DST_WIDTH_16				(1<<21)
#define DMA_DST_WIDTH_32				(2<<21)
#define DMA_SRC_WIDTH_8					(0<<18)
#define DMA_SRC_WIDTH_16				(1<<18)
#define DMA_SRC_WIDTH_32				(2<<18)


//DMACCnConfiguration
#define DMA_TC_INT_EN					(1<<15)
#define DMA_ERR_INT_EN					(1<<14)

/*
 * Description:
 * Enum of possible DMA flow directions & flow controllers
 *
 * Implementation:
 * Each DMA transfer operation must indicate the types of source and destination
 * (memory or peripheral), and when a peripheral is involved, whether it or the
 * DMA controller is controlling the flow.
 */
typedef enum apDMA_xFlowControl
{
    apDMA_MEM_TO_MEM_DMA_CTRL                            = 0,
    apDMA_MEM_TO_PERIPHERAL_DMA_CTRL                     = 1,
    apDMA_PERIPHERAL_TO_MEM_DMA_CTRL                     = 2,
    apDMA_PERIPHERAL_TO_PERIPHERAL_DMA_CTRL              = 3,
    apDMA_PERIPHERAL_TO_PERIPHERAL_DEST_PERIPHERAL_CTRL  = 4,
    apDMA_MEM_TO_PERIPHERAL_PERIPHERAL_CTRL              = 5,
    apDMA_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL              = 6,
    apDMA_PERIPHERAL_TO_PERIPHERAL_SRC_PERIPHERAL_CTRL   = 7

} apDMA_eFlowControl;


#define DMA_PER_ID_UART_RX					0
#define DMA_PER_ID_UART_TX					1
#define DMA_PER_ID_IIS51_IN2				2
#define DMA_PER_ID_IIS51_IN1				7
#define DMA_PER_ID_IIS51_OUT0				9
#define DMA_PER_ID_IIS51_IN0				11

#define DMA_PER_ID_IISPCM_OUT				5
#define DMA_PER_ID_IISPCM_IN				6
//#define DMA_PER_ID_IIS51_OUT1				8
//#define DMA_PER_ID_IIS51_OUT2				9
#define DMA_PER_ID_SPI_OUT					12
#define DMA_PER_ID_SPI_IN					13
#define DMA_PER_ID_SPDIF_OUT				14
#define DMA_PER_ID_SPDIF_IN					15

#endif /*__DMAC_H__*/

