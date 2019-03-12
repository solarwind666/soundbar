// ##################################################################
//                          TYPE DEFINATION
// ##################################################################

#ifndef _HARDWARE_DEFINES_H_
#define _HARDWARE_DEFINES_H_
#ifndef __USE_OWN_TYPE_DEF__
/**********************************************************
 *                GENERAL TYPE DEFINATIONS
 *
 * Description
 * --------------
 *
 **********************************************************/

#define UINT8          unsigned char
#define UINT16         unsigned short
#define UINT32         unsigned long
#define UINT64         unsigned long long

#define INT8           signed char
#define INT16          signed short
#define INT32          signed long
#define INT64          signed long long

#define UINT           unsigned int          // CPU DATA LINE WIDTH.
#define INT            int

#define BYTE           UINT8
#define SBYTE          INT8
#define	_BYTE_DEFINED
//#define HWORD          UINT16
//#define SHWORD         INT16
#define WORD           UINT16
#define SWORD          INT16
#define _WORD_DEFINED
#define DWORD          UINT32
#define SDWORD         INT32
#define _DWORD_DEFINED
#define CHAR           char
#define UCHAR		unsigned char
#define USHORT		unsigned short

#define __int32			long
#define __int64			long long

#if 0 //ndef _ASSEMBLE_
typedef 	unsigned char		uchar;
typedef		unsigned char		unchar;
typedef 	unsigned short		ushort;
typedef 	unsigned int		uint;
typedef 	unsigned long		ulong;
typedef 	signed long long 	s64;
typedef 	unsigned long long 	u64;
typedef 	unsigned long long 	__u64;
typedef   	unsigned int 		size_t;
typedef 	unsigned int 		time_t;
typedef char                int8_t;
typedef unsigned char       uint8_t;	      
typedef unsigned char       u8;
typedef unsigned char       __u8;
typedef short               int16_t;
typedef unsigned short      __le16;
typedef unsigned short      uint16_t;
typedef unsigned short      u16;
typedef int                 atomic_t;
typedef int                 int32_t;
typedef unsigned int        uint32_t;
typedef unsigned int        __le32;
typedef unsigned int        u32;
typedef long long           int64_t;      
typedef long long           loff_t;
typedef unsigned long long  uint64_t;
typedef int                 irqreturn_t;
typedef unsigned short      __u16;
typedef unsigned int        __u32;
#define size_t              unsigned int
#endif

#ifndef HANDLE
#define HANDLE		void *
#endif
#define LPBYTE		unsigned char *
#define PUCHAR		unsigned char *
#define BOOLEAN		unsigned char
#ifndef PDWORD
#define PDWORD		unsigned int *
#endif
#ifndef PBYTE
#define PBYTE		unsigned char *
#endif
/**********************************************************
 *                      REGISTER TYPE
 *
 * Description
 * --------------
 *
 **********************************************************/
#define __REGl(x)		(*(volatile unsigned long *)(x))
#define __REGw(x)	(*(volatile unsigned short *)(x))
#define __REG8(x)	(*(volatile unsigned char *)(x))
#define __REG16(x)	(*(volatile unsigned short *)(x))
#define __REG32(x)	(*(volatile unsigned int *)(x))
#define __REG2(x,y)	(*(volatile unsigned long *)((x) + (y)))
#define __REG(addr)         (*(volatile UINT32 *)(addr))
#define __REGh(addr)        (*(volatile UINT16 *)(addr))
#define __REGb(addr)        (*(volatile UINT8 *)(addr))

#define __sREG(addr,offset)    (*(volatile UINT32 *)((addr)+(offset)))
#define __sREGh(addr,offset)   (*(volatile UINT16 *)((addr)+(offset)))
#define __sREGb(addr,offset)   (*(volatile UINT8 *)((addr)+(offset)))

#define HWR_WRITE(reg,data)  ((reg)=(data))

/**********************************************************
 *                  FUNCTION RETURN TYPE
 *
 * Description
 * --------------
 *
 **********************************************************/

#define FRT_T    INT32
#define FRT_OK   (INT32)0
#define FRT_ERR  (INT32)-1
#define FRT_BUG  (INT32)1

#define FRT_IS_OK(rt_val)      (rt_val==FRT_OK)
#define FRT_NOT_OK(rt_val)     (!(FRT_IS_OK(rt_val)))
#define FRT_WITH_BUG(rt_val)   (rt_val>=FRT_OK)

/**********************************************************
 *                   MACRO FOR POINTER
 *
 * Description
 * ----------------
 *
 **********************************************************/

#ifdef NULL
#undef NULL
#endif
#define NULL (void *)0

#ifdef PTR_ERR
#undef PRT_ERR
#endif
#define PTR_ERR (void *)(-1)

/**********************************************************
 *                   BOOL TYPE DEFINATIONS
 *
 * Description
 * --------------
 * BOOL type definations:
 *    > BOOL
 *    > TRUE
 *    > FALSE
 **********************************************************/

#ifndef _ASSEMBLE_

#ifdef BOOL
#undef BOOL
#endif

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

typedef enum {
	FALSE = 0,
	TRUE = 1,
}BOOL;

#ifndef bool
#define bool    BOOL
#endif
#ifndef true
#define true    TRUE
#endif
#ifndef false
#define false   FALSE
#endif

#endif /* _ASSEMBLE_ */

/***********************************************************
 *               CALL_BACK FUNCTION DEFINATION
 ***********************************************************/

#ifndef _ASSEMBLE_
typedef FRT_T (*callback_f)(void *param);
#endif /* _ASSEMBLE_ */

/***********************************************************
 *                          ENDIAN
 ***********************************************************/

#define ENDIAN_T UINT32
#define ENDIAN_LITTLE       0
#define ENDIAN_BIG          1
#define	LITTLE_ENDIAN
/***********************************************************
 *                    BLOCK ADDRESS TYPE
 ***********************************************************/

#ifndef _ASSEMBLE_

typedef struct {             /* Block Address for Buffer               */
	BYTE loc;                /* Location Extent : 0~255                */
	BYTE size;               /* Size     Extent : 0~255                */
}blk_mini_addr_t;

typedef struct {             /* Block Address Recorded by HWORD        */
	WORD loc;               /* Location Extent : 0 ~ 65535            */
	WORD size;              /* Size     Extent : 0 ~ 65535            */
}blk_short_addr_t;

typedef struct {             /* Block Address Recorded by WORD         */
	DWORD loc;                /* Location Extent : 0 ~ 4'294'967'925    */
	DWORD size;               /* Size     Extent : 0 ~ 4'294'967'925    */
}blk_long_addr_t;

#endif /* _ASSEMBLE_ */
#endif /*__USE_OWN_TYPE_DEF__*/
#endif   /* _HARDWARE_DEFINES_H_ */
