/***********************************************************
描述：	用c语言写的一个如何从点阵字库中读取字符信息（像素宽 +点阵信息）
        至于容错性和效率方面还得使用者自行改善,谢谢您的参阅！

文件格式： 
		Unicode -- 文件头+数据段(section)+索引表+点阵信息
		MBCS_Ladin-文件头+索引表+点阵信息
		MBCS_CJK-- 文件头+点阵信息
		
作者：  wujianguo
日期： 	20090516
MSN:    wujianguo19@hotmail.com
qq：    9599598
*************************************************************/

#include "font.h"
#include "font_file.h"
#include "unicode.h"
#include "mbcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FL_HEADER _fl_header;
static DWORD g_dwCharInfo = 0;    // 存储当前字符的检索信息。  bit0～bit25：存放点阵信息的起始地址。 bit26～bit31：存放像素宽度。

static int ReadFontHeader(PFL_HEADER pfl_header)
{	
	font_file_read(pfl_header, sizeof(FL_HEADER) -4);

	//检测表示头
	if((_fl_header.magic[0] != 'U' && _fl_header.magic[0] != 'M')
		|| _fl_header.magic[1] != 'F' || _fl_header.magic[2] != 'L')
	{
		printf("Cann't support file format!\n");
		return 0;
	}

	if('U' == pfl_header->magic[0])     //unicode 编码
	{
		return font_read_sections();
	}

	return 1;	
}

static int OpenFontFile(char *pFontFile)
{
	if(!font_file_open(pFontFile))
	{
		printf("Cann't open : %s\n", pFontFile);
		return 0;
	}
		
	return 1;
}

/***************************************************************
功能： 初始化字体。 即打开字体文件，且读取信息头。
参数： pFontFile--字库文件名      
***************************************************************/
int font_init(char *pFontFile)
{
	memset(&_fl_header, 0, sizeof(FL_HEADER));

	if(OpenFontFile(pFontFile))
		return ReadFontHeader(&_fl_header);	
	else
		return 0;
}

void font_exit()
{
	if('U' == _fl_header.magic[0])     //unicode 编码
		font_release_sections();

	font_file_close();
}

BYTE font_get_ysize()
{
	return _fl_header.YSize;
}


/********************************************************************
功能： 获取当前字符的像素宽度, 且将索引信息存入一个全局变量：g_dwCharInfo。
        根据索引信息，即同时能获取当前字符的点阵信息的起始地址。
参数： wCode -- 当字库为unicode编码格式时，则将wCode当unicode编码处理。
                否则当内码（MBCS)处理。
********************************************************************/
int font_read_char_distX(WORD wCode)
{
	if('U' == _fl_header.magic[0])     // unicode 编码
		g_dwCharInfo = read_char_info_unicode(wCode);
	else  // MBCS
		g_dwCharInfo = read_char_info_mbcs(wCode);

	return GET_FONT_WIDTH(g_dwCharInfo);
}

/**********************************************************************
功能： 获取点阵信息
参数： wCode 在这里预留，主要是因为前面有保存一个全局的g_dwCharInfo，也就知道了该字符的相应信息(宽度+点阵信息的起始地址)。
       fontArray 存放点阵信息
	   bytesPerLine 每一行占多少个字节。
**********************************************************************/
int font_read_char_dot_array(WORD wCode, BYTE *fontArray, WORD *bytesPerLine)
{	
	*bytesPerLine= (WORD)((GET_FONT_WIDTH(g_dwCharInfo))+7)/PIXELS_PER_BYTE;	

	if(g_dwCharInfo > 0)
	{		
		DWORD nDataLen = *bytesPerLine * _fl_header.YSize;			
		DWORD  dwOffset = GET_FONT_OFFADDR(g_dwCharInfo);    //获取字符点阵的地址信息(低26位)
		
		font_file_seek(dwOffset);
		font_file_read(fontArray, nDataLen);	
		
		return 1;
	}
	
	return 0;
}
