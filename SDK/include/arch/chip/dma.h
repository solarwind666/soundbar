#ifndef __DMA_H__
#define __DMA_H__

#define DMA_DIR_M_TO_M						(0)
#define DMA_DIR_UART_TO_M					(1)
#define DMA_DIR_M_TO_UART					(2)
#define DMA_DIR_IIS_TO_M					(3)
#define DMA_DIR_M_TO_IIS					(4)
#define DMA_DIR_SPI_TO_M					(5)
#define DMA_DIR_M_TO_SPI					(6)
#define DMA_DIR_SPDIF_TO_M					(7)
#define DMA_DIR_M_TO_SPDIF					(8)
#define DMA_DIR_IIS0_TO_M					(9)
#define DMA_DIR_IIS1_TO_M					(10)
#define DMA_DIR_IIS2_TO_M					(11)
#define DMA_DIR_IISPCM_TO_M					(12)
#define DMA_DIR_M_TO_IISPCM					(13)


// dma channel define

#define DMA_CHANNEL_IIS_IN		0
#define DMA_CHANNEL_IIS_OUT		1
#define DMA_CHANNEL_SPDIF_IN	3
#define DMA_CHANNEL_SPDIF_OUT	2
#define DMA_CHANNEL_UART_RX		6
#define DMA_CHANNEL_TEMP		6


#define DMA_TS_WIDTH_8BIT			0
#define DMA_TS_WIDTH_16BIT			1
#define DMA_TS_WIDTH_32BIT			2

/* ---------------------------------------------------------------------------
 * Description: 
 * Raw Linked List Item used with API for peripheral/memory transfers.
 *
 * Implementation:
 * This structure is only used internally by the DMA driver. Users should
 * never read or write to these fields.
 *
 */
typedef struct apDMA_xRawLLI
{
    /* The DMA driver fills these fields */

    UINT32 SrcAddr;
    UINT32 DstAddr;
    UINT32 NextLLI;
    UINT32 TransferCtrl;

} apDMA_sRawLLI;



typedef struct apDMA_xLLI
{
    /* The DMA driver fills in the first field.*/

    apDMA_sRawLLI   sRaw;

    /* The user has to fill in the remaining fields */

    UINT32                   NumTransfers;   	/* number of transfers to perform */
    void                      *pSrcAddr;   		/* Source address */
    void                      *pDstAddr;   		/* Destination address */
    struct apDMA_xLLI   *pNextLLI;      	/* Ptr to next LLI or aNULL if this is the last */

} apDMA_sLLI;


typedef struct request_xDMA
{
	apDMA_sLLI * dma_LLI;
	void (*callback)(struct request_xDMA *);
	int result;
	UINT32 lli_num_int;				// 第几个LLI完成时产生TC中断源
	UINT32 lli_num;					// 一共有几个LLI
	UINT8 ch;						// 使用DMA第几个通道
	UINT8 dma_dir;					// DMA的流向，参考上面的宏定义
	UINT8 width;						// DMA两端的最小位宽
	UINT8 use_once;					// 是否完成中断后释放该通道
	UINT8 int_enable;				// 中断使能
}request_sDMA;

struct DMA_CHS_xCB
{
	UINT8 active;
	request_sDMA * request;
	void (*callback)(struct request_xDMA *);
};
typedef struct DMA_CHS_xCB DMA_CHS_sCB;


#endif /*__DMA_H__*/

