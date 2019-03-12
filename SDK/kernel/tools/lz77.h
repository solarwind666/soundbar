/****************************************************************************
 * tools/lz77.h
 *
 * Copyright (C) 2015 YunOS Project. All rights reserved.
 *
 * header file for lz77 inflate/deflate
 *
 * released as it is for any usage for your own risk
 *
 ****************************************************************************/

#ifndef __LZ77_H__
#define __LZ77_H__

#ifndef __GNUC__
#define inline
#endif

#ifdef __KERNEL__
#define lz77_warning printk
#else
#define lz77_warning printf
#endif

#ifdef DEBUG
#ifdef __KERNEL__
#define lz77_printf printk
#else
#define lz77_printf printf
#endif
#else
#define lz77_printf(fmt,arg...)
#endif

#define LZ77_COMPRESSED (0xF0)
#define LZ77_RAW (0x0F)

#define SIZE_BITS (4)

#define WIN_BITS (12)
#define WIN_LEN (1<<WIN_BITS)

#define MIN_LEN (3)
#define MAX_LEN (64)
#define OPT_LEN (8)

/*
tranform table:
static int len_table[1<<(SIZE_BITS)] = {
	3, 4, 5, 6, 7, 8, 9, 10,
	11, 12, 13, 14, 15, 16,
	32, 64
}
*/

static inline int size_to_index(int s) {
    if(s <= 16) {
        return (s - 3);
    } else if(s > 63) {
        return 15;
    } else if(s > 31) {
        return 14;
    } else {
        return 13;
    }
}

static inline int index_to_size(int i) {
	static int len_table[1<<(SIZE_BITS)] = {
		3, 4, 5, 6, 7, 8, 9, 10,
		11, 12, 13, 14, 15, 16,
		32, 64
	};

	return len_table[i];
}

int lz77_inflate(unsigned char *, int, unsigned char *, int, unsigned char **);

#define HASH_BITS (11)
#define HASH_SIZE ((1<<(HASH_BITS+1)))
#define HASH_VALUE(d1,d2,d3) ((d1<<(HASH_BITS-8))^((d2)<<(HASH_BITS-10))^(d3))

#define WORKSPACE_HASH(buf) (buf)
#define WORKSPACE_INDEX(buf) ((void *)((uint8_t *)(buf)+HASH_SIZE))

#define LZ77_WORKSPACE_SIZE(winlen) (HASH_SIZE+sizeof(short)*(winlen))
int lz77_deflate(unsigned char *, int, unsigned char *, int, void *, int);
#endif
