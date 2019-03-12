/****************************************************************************
 * tools/lz77_main.c
 *
 * Copyright (C) 2015 YunOS Project. All rights reserved.
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "lz77.h"

typedef int bool;
#define true 1
#define false 0

#define BLOCK_SIZE 0x8000

#define MAGIC (('Y'<<24)|('O'<<16)|('C'<<8)|'C')
struct fheader {
    uint32_t magic;
    uint32_t orig_size;
    uint32_t comp_size;
    uint16_t block_size;
    uint16_t padding;
};

static unsigned char workspace[LZ77_WORKSPACE_SIZE(BLOCK_SIZE)];

static void show_help(void)
{
    printf("Please enter a file!\n");
}

int main(int argc, char *argv[])
{
    int i;
    int flen = 0, dlen = 0, flen_t = 0;
    char *s_filename;
    char *d_filename, *d_mallocbuf = 0;
    int d_filenamelen;
    FILE *s_fp, *d_fp;
    char *sbuf, *dbuf, *res;
    bool with_header = false;
    int opt;

    if (argc < 2) {
        show_help();
        return -1;
    }

    while ((opt = getopt(argc, argv, "i")) != -1) {
        switch (opt) {
        case 'i':
            with_header = true;
            break;
        default:
            show_help();
            return -1;
        }
    }

    s_filename = argv[optind++];
    if (optind < argc) {
        d_filenamelen = strlen(argv[optind]);
        d_mallocbuf = (char *)malloc(d_filenamelen + 1);
        if (!d_mallocbuf) {
            return -1;
        }
        d_filename = d_mallocbuf;
        memset(d_filename, 0, d_filenamelen + 1);
        strcpy(d_filename, argv[optind]);
    } else {
          d_filename = s_filename;
    }

/*
    printf("s_filename: %s\n", s_filename);
    printf("d_filename: %s\n", d_filename);
*/
    if ((s_fp = fopen(s_filename, "rb")) == NULL) {
        perror("Open failed");
    }

    fseek(s_fp, 0L, SEEK_END);
    flen = ftell(s_fp);

    sbuf = (char *)malloc(flen * 2);
    if (!sbuf) {
        fclose(s_fp);
        goto free_sbuf;
    }

    memset (sbuf, 0, flen * 2);

    fseek(s_fp, 0L, SEEK_SET);
    fread(sbuf, flen, 1, s_fp);
    sbuf[flen] = '\0';

    fclose(s_fp);

    dbuf = (char *)malloc(flen * 2);
    if (!dbuf) {
        goto free_dbuf;
    }

    if (with_header) {
        dbuf += sizeof(struct fheader);
    }

    res = (char *)malloc(flen * 2);
    if (!res) {
        goto free_res;
    }

    flen_t = flen;
    i = 0;
    while (flen_t > 0) {
        int len = 0;
        len = lz77_deflate((uint8_t *)sbuf + i*BLOCK_SIZE, BLOCK_SIZE, (uint8_t *)dbuf + dlen, BLOCK_SIZE + 4,
                           (void *)workspace, sizeof(workspace));
        if (len < 0) {
            printf("lz77_deflate failed!\n");
            goto free_res;
        }

        dlen += len;
        flen_t -= BLOCK_SIZE;
        i++;
    }

    if ((d_fp = fopen(d_filename, "wb")) == NULL) {
        perror("Open failed");
        goto free_res;
    }

    if (with_header) {
        dbuf -= sizeof(struct fheader);
        dlen += sizeof(struct fheader);

        struct fheader *info = (struct fheader *)dbuf;
        info->magic = MAGIC;
        info->orig_size = flen;
        info->comp_size = dlen + sizeof(struct fheader);
        info->block_size = BLOCK_SIZE;
    }

    fwrite(dbuf, dlen, 1, d_fp);
    fclose(d_fp);

    printf("Compression ratio: %d/%d = %f\n", dlen, flen, (float)dlen/(float)flen);

free_res:
    free(res);
free_dbuf:
    free(dbuf);
free_sbuf:
    free(sbuf);

    if (d_mallocbuf) {
        free(d_mallocbuf);
    }

    return 0;
}

