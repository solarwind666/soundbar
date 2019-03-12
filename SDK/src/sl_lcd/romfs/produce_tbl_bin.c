#include <stdio.h>
#include <string.h>
#include "sl_gb2312_unicode.h"

#define GB_UNICODE_MAP_NAME	"gb_unicode_map.bin"
extern int gb2312_unicode_map_len;
extern GB2312_UNICODE gb2312_unicode_map[];

#define GB_UNICODE_TBL_NAME	"gb_unicode_tbl.bin"
extern int unicode_gb2312_tbl_len;
extern unsigned short unicode_gb2312_tbl[];

#define DATA_LEN	1024

int produce_bin_file(char *name, char *data_in, int total_len)
{
	char data[DATA_LEN];
	int len, wr_len, offset_len;
	FILE *fout = NULL;

	printf("%s %d name: %s total_len:%d\n", __func__, __LINE__, name, total_len);
    fout = fopen(name, "w+");
	if (NULL == fout) {
		printf("open file error!\n", name);	
		return -1;
	}
	wr_len = 0;
	offset_len = 0;
	while (1) {
		if (total_len == offset_len)
			break;
		len = ((total_len-offset_len) > DATA_LEN) ? DATA_LEN : total_len-offset_len;
		memset(data, 0, DATA_LEN);
		memcpy(data, data_in+offset_len, len);		
        wr_len = fwrite(data, 1, len, fout);
		offset_len += wr_len;
	}
	fclose(fout);

	return 0;
}

int main(int argc, char **argv)
{
	char *data_in = NULL;
	int total_len;

	total_len = gb2312_unicode_map_len * sizeof(GB2312_UNICODE);
	data_in = (char *)gb2312_unicode_map;
	produce_bin_file(GB_UNICODE_MAP_NAME, data_in, total_len);

	total_len = unicode_gb2312_tbl_len * sizeof(unsigned short);
	data_in = (char *)unicode_gb2312_tbl;
	produce_bin_file(GB_UNICODE_TBL_NAME, data_in, total_len);
	return 0;
}
