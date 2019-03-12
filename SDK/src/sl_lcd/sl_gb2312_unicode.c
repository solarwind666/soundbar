#include <stdio.h>
#include <string.h>
#include "sl_lcd.h"
#include "sl_gb2312_unicode.h"

static int gb2312_unicode_map_len = 7445;
static FILE* tbl_fp = NULL;

int tbl_init(char *name)
{
	tbl_fp = fopen(name, "r");
	if (NULL == tbl_fp) {
		printf("open file %s failed!\n", name);	
		return -1;
	}
	return 0;
}

static u8 TestIsBigEndian(void)
{
	u16 temp=0x1234;
	u8 *pChar=(u8 *)&temp;
	if(*pChar==0x12) return 1;
	else return 0;
}

static u16 GetUnicode(u16 gb2312){
	int first = 0;
	int end = gb2312_unicode_map_len - 1;
	GB2312_UNICODE  gb_unicode;
	int mid = 0;
	if (NULL == tbl_fp) {
		printf("%s %d not open file\n", __func__, __LINE__);	
		return 0;
	}
	if(TestIsBigEndian() == 0){
		gb2312 = ((gb2312)>>8 &0x00ff) | ((gb2312)<<8 &0xff00);
	}
	while(first <= end){
		mid = (first + end) / 2;
		fseek(tbl_fp, GB_UNICODE_MAP_OFFSET + mid*sizeof(GB2312_UNICODE), SEEK_SET);
		fread(&gb_unicode, sizeof(GB2312_UNICODE), 1, tbl_fp);
		if (gb_unicode.gb2312 == gb2312){
			return gb_unicode.unicode;
		}
		if(gb_unicode.gb2312 > gb2312){
			end = mid - 1;
		}else{
			first = mid + 1;
		}
	}
	return 0;
}

static u16 enc_unicode_to_utf8_one(u16 unic, char *pOutput, int outSize){
    if ( unic <= 0x007F ){
        // * U-00000000 - U-0000007F:  0xxxxxxx
        *pOutput     = (unic & 0x7F);
        return 1;
    }
    else if ( unic >= 0x0080 && unic <= 0x07FF ){
        // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
        *(pOutput+1) = (unic & 0x3F) | 0x80;
        *pOutput     = ((unic >> 6) & 0x1F) | 0xC0;
        return 2;
    }
    else if ( unic >= 0x0800 && unic <= 0xFFFF ){
        // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
        *(pOutput+2) = (unic & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >>  6) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 12) & 0x0F) | 0xE0;
        return 3;
    }

    return 0;
}

int gb2312_to_utf8(char *src,int src_len, char *dst){
	u16 *ps = (u16 *)src;
	u16 t;
	u16 tmp_val = *ps;
	int c=0;
	
	while(tmp_val<<8>>8 != 0){
		t = GetUnicode(tmp_val);
		if(t != 0){
			char tmp[10];
            memset(tmp, 0, 10);
			t = enc_unicode_to_utf8_one(t, tmp, 10);
			strncpy(&dst[c], tmp, t);
			c+=t;
			ps++;
		}
        else {
			u8 *ns = (u8 *)ps;
			dst[c] = (char)*ns;
			c+=1;
			ps = (u16 *)(ns + 1);
		}
        if ((unsigned int)ps % 2) {
            tmp_val = 0; 
            t = *((u16 *)((u8 *)ps-1));
            t = t & 0xff00;
            t = t >> 8;
            tmp_val = t;
            t = *((u16 *)((u8 *)ps+1));
            t = t & 0x00ff;
            t = t << 8;
            tmp_val += t;
        }
        else
            tmp_val = (*ps);
	}

	return c;
}

static int utf8_to_unicode(unsigned char *src, int src_len, unsigned char *dst, int dst_maxlen)
{
    unsigned char tmp;
    int i, j, k, bytes, dst_len = 0;

    for (j = 0; j < src_len;) {
        tmp = *src;
        for (i = 0; i < 8; i ++) {
            k = (tmp & 0x80) >> 7;
            if (k == 0)
                break;
            tmp = tmp << 1;
        }

        if (i == 0)
            bytes = 1;
        else
            bytes = i;

        switch (bytes) {
            case 1:
                *dst = 0;
                *(dst + 1) = *src;
                break;
            case 2:
                *(dst + 1) = *(src + 1) & 0x3f;
                tmp = *src & 0x3;
                tmp = tmp << 6;
                *(dst + 1) |= tmp;
                *dst = *src & 0xf;
                break;
            case 3:
                *(dst + 1) = *(src + 2) & 0x3f;
                tmp = *(src + 1) & 0x3;
                tmp = tmp << 6;
                *(dst + 1) |= tmp;

                *dst = *(src + 1) & 0x3f;
                *dst = *dst >> 2;
                tmp = *src & 0xf;
                tmp = tmp << 4;
                *dst |= tmp;
                break;
            default:
                printf("utf8_to_unicode err,can not support change \n");
                *dst = 0x20;
                *(dst + 1) = 0x20;
                break;
        }
        dst += 2;
        dst_len += 2;
        src += bytes;
        j += bytes;
        if (dst_len + 2 >= dst_maxlen)
            break;
    }

    *dst = 0;
    *(dst + 1) = 0;
    return dst_len;
}

static int unicode_to_gb2312(unsigned char *src, int src_len, unsigned char *dst, int dst_maxlen)
{
    int i, num, code, mb, lb, dst_len = 0;

	if (NULL == tbl_fp) {
		printf("%s %d not open file\n", __func__, __LINE__);	
		memset(dst, 0, dst_maxlen);
		return 0;
	}
    for (i = 0; i < src_len; i += 2, src += 2)
    {
        mb = *src;
        lb = *(src + 1);
        code = (mb << 8) | lb;
        if (mb) {
            if (code >= 0x4E00 && code <= 0x9FA5) {
				fseek(tbl_fp, GB_UNICODE_TBL_OFFSET + (code - 0x4E00) * sizeof(int), SEEK_SET);
				fread(&code, sizeof(int), 1, tbl_fp);
                if (code == 0)
                    *dst = *(dst + 1) = 0x20;
                else {
                    code |= 0x8080;
                    *dst = (unsigned char)(code >> 8);
                    *(dst + 1) = (unsigned char)(code & 0x00ff);
                }
            }
            else
                *dst = *(dst + 1) = 0x20;
            num = 2;
        }
        else {
            *dst = lb;
            num = 1;
        }
        dst += num;
        dst_len += num;
        if (dst_len + 2 >= dst_maxlen)
            break;
    }
    *dst = 0;
    *(dst + 1) = 0;
    return dst_len;
}

int utf8_to_gb2312(unsigned char *src, int src_len, unsigned char *dst, int dst_maxlen)
{
    int len;
    unsigned char buf[MAX_STRING_LEN];

    len = utf8_to_unicode(src, src_len, buf, MAX_STRING_LEN);
    return unicode_to_gb2312(buf, len, dst, dst_maxlen);
}

