/*
 * Copyright (C) 2014 The YunOS Project. All rights reserved.
 */

/*HEADER
 *========================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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

#define LEN (1*1024*1024)
#define FILE_IN_NAME "program.binary"
#define FILE_IN_ADDR	(0x0)
#define FILE_IN_SIZE	(0x400000)

#define SYSDATA_START	(0x314000)
#define SYSDATA_SIZE	(0x1000)
#define FILE_IN_SYSDATA "sysdata.bin"

#define WIFIBIN_START	(0x315000)
#define WIFIBIN_SIZE	(0x70000)
#define FILE_IN_WIFIBIN "wifi_firmware.bin"

#define USER_START	(0x386000)
#define USER_SIZE	(0x23000)
#define FILE_IN_USER "userspace.bin"

#define TONE_LOGO   "silan_tone "
#define TONE_START	(0x3a9000)
#define TONE_SIZE	(0x30000)
#define FILE_IN_TONE_NAME "tone_data.bin"

#define TBL_START	(0x3d9000)
#define TBL_SIZE	(0x12000)
#define GB_UNICODE_MAP_OFFSET	0x0
#define GB_UNICODE_TBL_OFFSET	0x8000
#define GB_UNICODE_MAP_NAME	"gb_unicode_map.bin"
#define GB_UNICODE_TBL_NAME	"gb_unicode_tbl.bin"

#define CH_FONT_START (0x3eb000)
#define CH_FONT_SIZE (0xf5000)
#define FILE_IN_CH_NAME "unicode_font.bin"

#define FILE_OUT_NAME "program_final.binary"
/*
 * main
 * generate manifest for bootload
 * @return      succeed or error number
 */
static int parse_flash_info(const char * info, int *addr, int *size)
{
    char * ptmp;
    char * saveptr = NULL;
    char srcinfo[64];

    strcpy(srcinfo, info);
    ptmp = strtok_r(srcinfo, ",", &saveptr);
    if(ptmp != NULL)
    {
        ;
    }
    ptmp = strtok_r(NULL, ",", &saveptr);
    if(ptmp != NULL)
    {
        *addr = strtol(ptmp,NULL,16);
    }
    ptmp = strtok_r(NULL, ",", &saveptr); if(ptmp != NULL)
    {
        *size= strtol(ptmp,NULL,16);
    }
}

static check_file(char *name, int *size)
{

	FILE *fin = NULL;
	int total_size = 0;
    fin = fopen(name, "r");
    if (NULL == fin) {
        printf("open file failed:%s\n", name); 
		*size = 0;
        return -1;
    }
    fseek(fin, 0, SEEK_END);
	total_size = ftell(fin);
	printf("file:%s total size:%d size:%d\n", name, total_size, *size);
	if (total_size > *size) {
		printf("file exceed length!\n");	
		*size = 0;
	}
	close(fin);
	return 0;
}

static int copy_file(char *name, FILE* fout, char *data, int in_len)
{
	if (0 == in_len)
		return -1;
	FILE *fin = NULL;
    int read_len = 0;
    int total_len = 0;
	int offset = ftell(fout);
    fin = fopen(name, "r");
    if (NULL == fin) {
        printf("open file failed:%s\n", name); 
        return -1;
    }

    total_len = 0;
    do{
        memset(data, 0, LEN);
        read_len = fread(data, sizeof(char), LEN, fin); 
        if (read_len == 0) {
            printf("%s %d end of file \n", __func__, __LINE__); 
            break;
        }
        else if (read_len < 0) {
            printf("%s %d read file error \n", __func__, __LINE__); 
            break;
        }
        else {
            total_len += read_len;
            //printf("%s %d len:%d\n", __func__, __LINE__, read_len);
            fwrite(data, read_len, 1, fout);
        }
    }while(1);
    printf("%s %d total_len:%d name:%s, offset:0x%x\n", __func__, __LINE__, total_len, name, offset);
	close(fin);
	return 0;
}

int main(int argc, char* argv[])
{
    char *data = NULL;
    FILE* fout = NULL;
	int ret, tmp_size;
	int boot_addr, boot_size;
	int	btconf_addr, btconf_size;
	int	in_file_addr, in_file_size;
    int tone_addr, ch_font_addr, tbl_addr, user_addr, sysdata_addr, wifibin_addr;
    int tone_size, ch_font_size, tbl_size, user_size, sysdata_size, wifibin_size;
	int gb_unicode_map_offset, gb_unicode_map_size, gb_unicode_tbl_offset, gb_unicode_tbl_size;

    if (argc != 12) {
        printf("use defalut address!\n"); 
		in_file_addr = FILE_IN_ADDR;
		in_file_size = FILE_IN_SIZE;
        tone_addr = TONE_START;
        tone_size = TONE_SIZE;
        ch_font_addr = CH_FONT_START;
        ch_font_size = CH_FONT_SIZE;
		tbl_addr = TBL_START;
		tbl_size = TBL_SIZE;
		user_addr = USER_START;
		user_size = USER_SIZE;
		sysdata_addr = SYSDATA_START;
		sysdata_size = SYSDATA_SIZE;
		wifibin_addr = WIFIBIN_START;
		wifibin_size = WIFIBIN_SIZE;
		gb_unicode_map_offset = GB_UNICODE_MAP_OFFSET;
		gb_unicode_map_size = GB_UNICODE_TBL_OFFSET;
		gb_unicode_tbl_offset = GB_UNICODE_TBL_OFFSET;
    }
    else {
        parse_flash_info(argv[1], &boot_addr, &boot_size);
        parse_flash_info(argv[2], &btconf_addr, &btconf_size);
        parse_flash_info(argv[3], &in_file_addr, &in_file_size);
        parse_flash_info(argv[4], &tone_addr, &tone_size);
        parse_flash_info(argv[5], &ch_font_addr, &ch_font_size);
        parse_flash_info(argv[6], &tbl_addr, &tbl_size);
        parse_flash_info(argv[7], &user_addr, &user_size);
        parse_flash_info(argv[8], &sysdata_addr, &sysdata_size);
        parse_flash_info(argv[9], &wifibin_addr, &wifibin_size);
		gb_unicode_map_offset = strtol(argv[10], NULL, 16);
		gb_unicode_tbl_offset = strtol(argv[11], NULL, 16);
		gb_unicode_map_size = gb_unicode_tbl_offset;
		btconf_addr = btconf_addr - boot_addr;
		in_file_addr = in_file_addr - boot_addr;
		user_addr = user_addr - boot_addr;
		sysdata_addr = sysdata_addr - boot_addr;
		wifibin_addr = wifibin_addr - boot_addr;
		tone_addr = tone_addr - boot_addr;
		ch_font_addr = ch_font_addr - boot_addr;
		tbl_addr = tbl_addr - boot_addr;
    }
	gb_unicode_tbl_size = tbl_size-gb_unicode_tbl_offset;
	printf("btconf_addr:0x%x,			btconf_size:0x%x\n", btconf_addr, btconf_size);
	printf("in_file_addr:0x%x,			in_file_size:0x%x\n", in_file_addr, in_file_size);
	printf("sysdata_addr:0x%x,			sysdata_size:0x%x\n", sysdata_addr, sysdata_size);
	printf("wifibin_addr:0x%x,			wifibin_size:0x%x\n", wifibin_addr, wifibin_size);
	printf("user_addr:0x%x,				user_size:0x%x\n", user_addr, user_size);
    printf("tone_addr:0x%x,				tone_size:0x%x\n", tone_addr, tone_size);
	printf("ch_font_addr:0x%x,			ch_font_size:0x%x\n", ch_font_addr, ch_font_size);
	printf("tbl_addr:0x%x,				tbl_size:0x%x\n", tbl_addr, tbl_size);
	printf("gb_unicode_map_offset:0x%x, gb_unicode_map_size:0x%x\n", gb_unicode_map_offset, gb_unicode_map_size);
	printf("gb_unicode_tbl_offset:0x%x, gb_unicode_tbl_size:0x%x\n",  gb_unicode_tbl_offset, gb_unicode_tbl_size);

    fout = fopen(FILE_OUT_NAME,"w+");
    if (NULL == fout) {
        printf("open file failed:%s\n", FILE_OUT_NAME); 
		return -1;
    }
    data = (char *)malloc(LEN * sizeof(char));
    if (NULL == data) {
        printf("malloc failed.\n"); 
        goto close_out;
    }
	check_file(FILE_IN_NAME, &in_file_size);
	check_file(FILE_IN_USER, &user_size);
	check_file(FILE_IN_TONE_NAME, &tone_size);
	check_file(FILE_IN_CH_NAME, &ch_font_size);
	check_file(GB_UNICODE_MAP_NAME, &gb_unicode_map_size);
	check_file(GB_UNICODE_TBL_NAME, &gb_unicode_tbl_size);
	printf("in_file_size:0x%x,			user_size:0x%x\ntone_size:0x%x,				ch_font_size:0x%x\ngb_unicode_map_size:0x%x,	gb_unicode_tbl_size:0x%x\n",\
			in_file_size, user_size, tone_size, ch_font_size, gb_unicode_map_size, gb_unicode_tbl_size);

	ret = copy_file(FILE_IN_NAME, fout, data, in_file_size);

    fseek(fout, sysdata_addr, SEEK_SET);
	ret = copy_file(FILE_IN_SYSDATA, fout, data, sysdata_size);

    fseek(fout, wifibin_addr, SEEK_SET);
	ret = copy_file(FILE_IN_WIFIBIN, fout, data, wifibin_size);

    fseek(fout, user_addr, SEEK_SET);
	ret = copy_file(FILE_IN_USER, fout, data, user_size);

	if (0 != tone_size) {
		fseek(fout, tone_addr, SEEK_SET);
		memset(data, 0, LEN);
		strcpy(data, TONE_LOGO);
		fwrite(data, strlen(TONE_LOGO), 1, fout);
		ret = copy_file(FILE_IN_TONE_NAME, fout, data, tone_size);
	}

    fseek(fout, tbl_addr + gb_unicode_map_offset, SEEK_SET);
	ret = copy_file(GB_UNICODE_MAP_NAME, fout, data, gb_unicode_map_size);

    fseek(fout, tbl_addr + gb_unicode_tbl_offset, SEEK_SET);
	ret = copy_file(GB_UNICODE_TBL_NAME, fout, data, gb_unicode_tbl_size);

    fseek(fout, ch_font_addr, SEEK_SET);
	ret = copy_file(FILE_IN_CH_NAME, fout, data, ch_font_size);

    free(data);

close_out:
    fclose(fout);
    return 0;
}
