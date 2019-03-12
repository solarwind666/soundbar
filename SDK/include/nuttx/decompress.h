/****************************************************************************
 * include/nuttx/decompress.h
 *
 * Copyright (C) 2015 YunOS Project. All rights reserved.
 *
 ****************************************************************************/

#ifndef __INCLUDE_NUTTX_DECOMPRESS_H
#define __INCLUDE_NUTTX_DECOMPRESS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <sys/types.h>

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: do_decompress
 *
 * Description:
 *
 * Input Parameters:
 *  input:  Address of Compressed Image
 *  len  :  Size of Compressed Image
 *  output: Address of Decomressed Image
 *
 * Returned values:
 *  >=0: Size of Decompressed Image
 *  <0 : Failed
 *
 ****************************************************************************/

#define MAGIC (('Y'<<24)|('O'<<16)|('C'<<8)|'C')
struct decomp_info {
    uint32_t magic;
    uint32_t orig_size;
    uint32_t comp_size;
    uint32_t block_size;
};

int get_decompress_info(uint8_t **input, int len, struct decomp_info *info);
int do_decompress(uint8_t **input, int len, uint8_t *output, int olen);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __INCLUDE_NUTTX_DECOMPRESS_H */
