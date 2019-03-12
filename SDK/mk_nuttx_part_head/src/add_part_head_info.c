#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "update_struct.h"

enum e_in_param {
	IN_IDX_NULL				=	0,
	IN_IDX_FILE_IN			=	1,
	IN_IDX_FILE_OUT			=	2,
	IN_IDX_START_ADDR		=	3,
	IN_IDX_LEN				=	4,
	IN_IDX_SYS_VERSION		=	5,
	IN_IDX_ARCH_VERSION 	=	6,
	IN_IDX_PRODUCT_VERSION	=	7,
	IN_IDX_ARCH_MAX			=	8,
};
static  int _calculate_checksum(unsigned char *data, int data_len)
{
    int checksum = 0;
    int i = 0;

    if ( data == NULL || data_len <= 0 )
    	return -1;

    for (i=0; i<data_len; i++ ) {
    	checksum += (data[i]&0xff);
    }

    return (checksum & 0xffffffff);
}

static int parse_arch_version(char *version_str)
{
	char *pos;
	pos = strstr(version_str, "csky-v");
	if (NULL == pos)
		return -1;
	else
		return (pos[6] - '0');
}

int main(int argc, char* argv[])
{
    FILE *fin, *fout;
	int total_size;
	char *data_in = NULL;
	struct part_head_info head;
	int addr, len;

	if (argc != IN_IDX_ARCH_MAX) {
		printf(" usage [add_part_head_info <file_in> <file_out> <start_addr> <len> <sys_version> <arch_version> <product_version>]\n");
		return -1;
	}

    addr = strtol(argv[IN_IDX_START_ADDR],NULL,16);
    len = strtol(argv[IN_IDX_LEN],NULL,16);
	fin= fopen(argv[IN_IDX_FILE_IN], "rb+");
	if (NULL == fin) {
		printf("open file_in %s error!\n", argv[IN_IDX_FILE_IN]);
		return -1;
	}
	fseek(fin, 0 , SEEK_END);
	total_size = ftell(fin);
	fseek(fin, 0 , SEEK_SET);
	printf("addr:0x%x, len:0x%x, total_size:0x%x\n", addr, len, total_size);
	if ((addr+len) > total_size) {
		printf("cut length error!\n");	
		fclose(fin);
		return -1;
	}
	fseek(fin, addr, SEEK_SET);
	data_in = malloc(len);
	if (NULL == data_in) {
		printf("malloc %d size falied!\n", total_size);
		fclose(fin);
		return -1;	
	}
	fread(data_in, len, 1, fin);
	fclose(fin);

	memset(&head, 0, sizeof(struct part_head_info));
	head.magic = 0x6138;
	strcpy(head.sys_version, argv[IN_IDX_SYS_VERSION]);
	strcpy(head.product_version, argv[IN_IDX_PRODUCT_VERSION]);
	head.arch_version = parse_arch_version(argv[IN_IDX_ARCH_VERSION]);
    head.len = len;
    head.update_start_addr = addr;
    head.update_length = len;
	head.checksum = _calculate_checksum(data_in, len);
printf("magic:0x%x, len:0x%x, checksum:0x%x sys_version:%s arch_version:%d board_version:%s\n", head.magic, head.len, head.checksum, head.sys_version, head.arch_version, head.product_version);
	fout= fopen(argv[IN_IDX_FILE_OUT], "w+");
	if (NULL == fout) {
		printf("open file_out %s error!\n", argv[IN_IDX_FILE_OUT]);
		return -1;
	}
	fwrite(&head, sizeof(struct part_head_info), 1, fout);
	fwrite(data_in, len, 1, fout);
	free(data_in);
	fclose(fout);
	return 0;
}
