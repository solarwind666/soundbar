/****************************************************************************
 * tools/lz77_deflate.c
 *
 * Copyright (C) 2015 YunOS Project. All rights reserved.
 ****************************************************************************/

#undef DEBUG
#undef CHECK
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lz77.h"

/****************************************************************************
 * Name: lz77_search_match
 *
 * Description:
 *
 * Input Parameters:
 *
 *
 * Returned values:
 *
 *
 ****************************************************************************/

static inline int lz77_search_match(uint8_t *s1, uint8_t *s2, uint8_t *s_e)
{
    int len=0;
    while (s1<s_e) {
        if (*s1++ == *s2++) {
            len++;
        } else {
            break;
        }
    }
    return len;
}

/****************************************************************************
 * Name: lz77_init_index
 *
 * Description:
 *
 * Input Parameters:
 *
 *
 * Returned values:
 *
 *
 ****************************************************************************/

static inline void lz77_init_index(uint8_t *src, int len, void *workspace)
{
    short *hash = WORKSPACE_HASH(workspace);
    short *_index = WORKSPACE_INDEX(workspace);
    int i;

    memset(workspace, 0xFF, LZ77_WORKSPACE_SIZE(len));

    for(i=0; i<=(len - 3); i++) {
        short v = HASH_VALUE(src[i],src[i+1], src[i+2]);
        short *h = hash+v;

        #ifdef CHECK
        if(v >= (1 << HASH_BITS) || v<0) {
            lz77_warning("Warning: hash size too big!\n");
        }
        #endif

        _index[i] = *h;
        *h = i;
    }

    #ifdef CHECK
    for(i=0; i<len; i++) {
        if(_index[i] >= len || _index[i] < -1) {
            lz77_warning("Warning: index size too big!\n");
        }
    }
    #endif
}

/****************************************************************************
 * Name: lz77_exit_index
 *
 * Description:
 *
 * Input Parameters:
 *
 *
 * Returned values:
 *
 *
 ****************************************************************************/

static inline void lz77_exit_index(void *workspace)
{
    return ;
}

/****************************************************************************
 * Name: lz77_search_index
 *
 * Description:
 *
 * Input Parameters:
 *
 *
 * Returned values:
 *
 *
 ****************************************************************************/

static inline int lz77_search_index(uint8_t *ss, uint8_t *st, uint8_t *se, int *ml, void *workspace)
{
    int max_len = MIN_LEN-1;//at least 3 byte matching for not to lose
    int match_s = -1;
    short *_index = WORKSPACE_INDEX(workspace);
    int off = st-ss;
    short i = _index[off];

    se = se > (st+MAX_LEN) ? (st+MAX_LEN) : se;
    while(i >= 0 && i > (off-WIN_LEN)) {
        int m_l;
        m_l = lz77_search_match(st, ss+i, se);
        if(m_l > max_len) {
            max_len = m_l;
            match_s = i;
            if(max_len >= OPT_LEN) {
                break;
            }
        }

        i = _index[i];
    }

    if(match_s < 0) {
        return -1;
    }

    *ml = max_len;
    return (off-match_s);
}
/****************************************************************************
 * Name: lz77_deflate
 *
 * Description: 
 *
 * Input Parameters:
 * input:
 * src       source data buffer
 * len       length of source data
 * dst       destination buffer
 * dst_len   length of destination buffer
 *           it has to be at least 4 byte longer
 *           than source length for uncompressable case
 * workspace workspace buffer
 * wl        length of workspace
 * Output:
 * mode(lz77/raw)
 * section 0:
 *    type_bit * 8
 *    lit/codeword *8
 *       lit: literal ==> 1 byte
 *       codeword: size_bit*4 + addr_bit*12 ==> 2 byte
 *  section n
 *  end mark
 *
 * Returned values:
 *
 ****************************************************************************/

int lz77_deflate(uint8_t *src, int len, uint8_t *dst, int dst_len, void *workspace, int wl)
{
    int max_len, bd;
    uint8_t *d = dst;
    uint8_t *de = dst+dst_len-1;
    uint8_t *s = src;
    uint8_t *se = src+len;
    uint8_t *p;
    int i = 0;

    if(!src || !dst || dst_len<(len+4) || wl<LZ77_WORKSPACE_SIZE(len)) {
        return -1;
    }

    lz77_init_index(src, len, workspace);

    *d++ = LZ77_COMPRESSED;
    p = d++;

    while(1) {
        uint8_t type=0;

        while(i<8 && s<se && d<de) {
            bd = lz77_search_index(src, s, src+len, &max_len, workspace);

            if(bd < 0) {
                *d++ = *s++;
            }
            else{
                int size = size_to_index(max_len);
                type |= (1 << i);
                *d++ = ((size & 0x0F) << 4) | ((bd & 0xF00) >> 8);
                *d++ = bd & 0xFF;
                s += index_to_size(size);
            }

            i++;
        }

        *p = type;
        if(i == 8) {
            i = 0;
            p = d++;
            continue;
        }

        break;
    }

    if((d - dst) < len) {
        *p |= (1 << i);
        *d++ = 0;
        *d++ = 0;
    }

    if((d - dst) >= len) {//uncompressable
        int l = dst_len - 4;

        lz77_printf("uncompressble -> fall back to raw data: %d %d->%d!\n",
               dst_len, len, d - dst);

        l = l > len?len:l;
        d = dst;

        *d++ = LZ77_RAW;
        *d++ = 0;
        *d++ = l & 0xFF;
        *d++ = l >> 8;

        memcpy(d, src, l);
        d += l;
    }

    lz77_printf("delfated: %d %d->%d\n", dst_len, len, d - dst);

    lz77_exit_index(workspace);
    return (d - dst);
}

