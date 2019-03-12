/*
 * Copyright (C) 2014 The YunOS Project. All rights reserved.
 */

/*HEADER
 *========================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "manifest.h"

/*MACRO
 *========================================================================*/

/*TYPE
 *========================================================================*/

/*VARIABLES
 *========================================================================*/

/*FUNCTIONS 
 *========================================================================*/
static int _calculate_checksum(unsigned short *data, int data_len)
{
    int checksum = 0;
    int i = 0;

    if ( data == NULL || data_len <= 0 ) {
            return -1;
    }

    for ( ; i < data_len; i++ ) {
            checksum += data[i];
    }

    return checksum%0xFFFF;
}

/*
 * main
 * generate manifest for bootload
 * @return      succeed or error number
 */
#define UPDATE_PART_NULL    0
#define UPDATE_PART_KERNEL  1
#define UPDATE_PART_ROOTFS  2

#define STAT_OK             0
#define STAT_IN_SEC_SYS     1
#define STAT_IN_BACKUP      2

#define UPDATE_FD_1 1
#define UPDATE_FD_2 2

struct boot_data_info {
	int magic;
	int count;
	int checksum;
	int backup_len;	
	//following are used for linux
	char last_boot_method;
	char kernel_stat;
	char rootfs_stat;
	char resv;
	//above are legacy
	int update_stat;
	int backup_addr;
	int rootfs_addr;
};

int main(int argc, char* argv[])
{
    manifest_t man;
    char buf[130];
    char *cp;
    int i=0, idx, size, digest, imgend;
    int bootcfg[2];
    char *argin;
	char *data_part = NULL;
	struct boot_data_info *btupdate;

    if (argv[1] == NULL) {
        argin = "";
    }
    else {
        argin = argv[1];
    }
    sprintf(buf, "manifest%s.cfg", argin);
    FILE* fin= fopen(buf,"r+");
    sprintf(buf, "manifest%s.out", argin);
    FILE* fout= fopen(buf,"w+");

    memset(&man, 0, sizeof(man));
    man.magic = 0x61386138;
    man.size = sizeof(man);
    man.imgnum = IMAGE_NUM;

    /* get config information */
    while (fgets(buf,50,fin)>0){
        if (strstr((char*)(&buf),"VERSION")){
            cp = strstr((char*)(&buf),"=");
            cp+=1;
            man.version = (short)strtoul(cp, NULL, 10);
            continue;
        }
        if (strstr((char*)(&buf),"DIGSCH")){
            cp = strstr((char*)(&buf),"=");
            cp+=1;
            man.digsch = (short)strtoul(cp, NULL, 10);
            continue;
        }
        if (strstr((char*)(&buf),"SIGSCH")){
            cp = strstr((char*)(&buf),"=");
            cp+=1;
            man.sigsch = (short)strtoul(cp, NULL, 10);
            continue;
        }
        if (strstr((char*)(&buf),"BOOT_IDX")){
            cp = strstr((char*)(&buf),"=");
            cp+=1;
            man.boot_idx = (short)strtoul(cp, NULL, 10);
            continue;
        }
        if (strstr((char*)(&buf),"MANIFEST1_START")){
            cp = strstr((char*)(&buf),"=");
            cp+=1;
            bootcfg[0] = strtoul(cp, NULL, 10);
            continue;
        }
        if (strstr((char*)(&buf),"MANIFEST2_START")){
            cp = strstr((char*)(&buf),"=");
            cp+=1;
            bootcfg[1] = strtoul(cp, NULL, 10);
            continue;
        }
        if (strstr((char*)(&buf),"IMGEND")){
            cp = strstr((char*)(&buf),"=");
            cp+=1;
            imgend = strtoul(cp, NULL, 10);
            continue;
        }

        if (cp = strstr((char*)(&buf),"IMG")){
            cp += 3;
            idx = strtoul(cp, NULL, 10) - 1;
            for (i = 0; i < IMAGE_NUM; i++) {
                if (idx == i) {
                        if (strstr((char*)(&buf),"NAME")){
                            cp = strstr((char*)(&buf),"=");
                            cp+=1;
                            strncpy((char*)(&man.images[i].imgname), cp, 8);
                            break;
                        }
                        if (strstr((char*)(&buf),"SIZE")){
                            cp = strstr((char*)(&buf),"=");
                            cp+=1;
                            man.images[i].imgsz = strtoul(cp, NULL, 10);
                            break;
                        }
                        if (strstr((char*)(&buf),"LOAD")){
                            cp = strstr((char*)(&buf),"=");
                            cp+=1;
                            man.images[i].loadaddr = strtoul(cp, NULL, 10);
                            break;
                        }
                        if (strstr((char*)(&buf),"START")){
                            cp = strstr((char*)(&buf),"=");
                            cp+=1;
                            man.images[i].staticaddr = strtoul(cp, NULL, 10);
                            break;
                        }
                        if (strstr((char*)(&buf),"IDX")){
                            cp = strstr((char*)(&buf),"=");
                            cp+=1;
                            man.images[i].idx = strtoul(cp, NULL, 10);
                            break;
                        }
                        if (strstr((char*)(&buf),"ENC")){
                            cp = strstr((char*)(&buf),"=");
                            cp+=1;
                            man.images[i].enc = strtoul(cp, NULL, 10);
                            break;
                        }
                        if (strstr((char*)(&buf),"COPY")){
                            cp = strstr((char*)(&buf),"=");
                            cp+=1;
                            man.images[i].copy = strtoul(cp, NULL, 10);
                            break;
                        }
                }
            }
            continue;
        }
    }
    fclose(fin);

    /* generate manifest */
    for (i = 0; i < IMAGE_NUM; i++) {
        if (man.images[i].enc == 1) {
            sprintf(buf, "image%d%s.sig", i + 1, argin);
            fin = fopen(buf, "rb+");
            fread(&man.images[i].sig, 128, 1, fin);
            fclose(fin);
        }
        else if (man.images[i].enc == 2) {
            sprintf(buf, "image%d%s.bin", i + 1, argin);
            fin = fopen(buf, "rb+");
            fseek(fin, 0 , SEEK_END);
            size = ftell(fin);
            fseek(fin, 0 , SEEK_SET);
            cp = malloc(size);
            fread(cp, size, 1, fin);
            digest = _calculate_checksum((unsigned short *)cp, size/2);
            man.images[i].checksum = digest;
            free(cp);
            fclose(fin);
        }
    }
    fwrite(&man, sizeof(man), 1, fout);
    fclose(fout);

    /* generate bootcfg */
    fout= fopen("bootcfg.out","w+");
    fwrite(&bootcfg, sizeof(bootcfg), 1, fout);
    fclose(fout);

    /* generate btupdate1 */
    fout= fopen("btupdate1.out","w+");

	data_part = malloc(sizeof(struct boot_data_info));
	btupdate = (struct boot_data_info *)data_part;
	memset(btupdate, 0, sizeof(struct boot_data_info));
	btupdate->magic = 0x6138;
	btupdate->count = 1;
	btupdate->update_stat = STAT_OK;
    for (i=12; i<sizeof(struct boot_data_info); ++i)
		btupdate->checksum += data_part[i] & 0xff;

    fwrite(btupdate, sizeof(struct boot_data_info), 1, fout);
    fclose(fout);

    /* generate btupdate2 */
    fout= fopen("btupdate2.out","w+");

	btupdate->count = 0;
    for (i=12; i<sizeof(struct boot_data_info); ++i)
		btupdate->checksum += data_part[i] & 0xff;

    fwrite(btupdate, sizeof(struct boot_data_info), 1, fout);
    fclose(fout);

    /* generate image */
    sprintf(buf, "image%s.out", argin);
    fout= fopen(buf,"w+");
    cp = malloc(imgend);
    for (i = 0; i < IMAGE_NUM; i++) {
        sprintf(buf, "image%d%s.bin", i + 1, argin);
        fin = fopen(buf, "rb+");
        fseek(fin, 0 , SEEK_END);
        size = ftell(fin);
        fseek(fin, 0 , SEEK_SET);
        fread(cp + man.images[i].staticaddr, man.images[i].imgsz, 1, fin);
    }
    fwrite(cp, imgend, 1, fout);
    free(cp);
    fclose(fout);

    return 0;
}
