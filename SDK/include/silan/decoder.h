/********************************************************************************
*Copyright (c) 2005， 杭州士兰有限公司光存储事业部
*All right  reserved.
*
*文件名称：decoder.h
*文件标识：见配置管理计划书 
*摘    要：
*
*当前版本：1.0.sunxw.2
*作    者：孙熙文
*完成日期：2005年7月13日
*
*取代版本：
*原来作者：
*完成日期：
********************************************************************************/

#ifndef _DECODER_H_
#define  _DECODER_H_
#include "file_io.h"


#ifndef WIN32    
#define WAVE_TARGET_UBOOT_ARM                  //my
#endif

// 解码器选项
/* copyed from  wmaudio.h */

#define DECOPT_CHANNEL_DOWNMIXING      0x00000001
#define DECOPT_DRC                     			0x00000002
#define DECOPT_INTERPOLATED_DOWNSAMPLE 0x00000004
#define DECOPT_HALF_TRANSFORM          	0x00000008
#define DECOPT_HALF_UP_TRANSFORM       0x00000010
#define DECOPT_2X_TRANSFORM            	0x00000020
#define DECOPT_REQUANTTO16             		0x00000040
#define DECOPT_DOWNSAMPLETO44OR48     0x00000080
#define DECOPT_LTRTDOWNMIX             	0x00000100



#define MAX_WMA_SAMPLES 16384  
#define MAX_MP3_SAMPLES 1152  


// 在定义PCM 缓冲区大小时，必须同时兼顾MP3 和WMA 
//#define PCM_BUF_SIZE  	 ( 16384 * 2  /*sizeof(short )*/* 2 /* 2 channel*/)
//#define PCM_BUF_SIZE  	 ( 16384 * 4)	//sie
#define PCM_BUF_SIZE	2048*4	//sie 2005-11-11

#define MP3_ENCODE_BUF_SIZE	1152*24	//sie 2005-11-11
// 解码结果
#define  DECODE_OK  			1
#define  DECODE_ERROR		2
#define  DECODE_OK_FINISH	3
#define  DECODE_SKIP		4

#define SEEK_BY_MS				0
#define SEEK_BY_MS_OFFSET		1
#define SEEK_BY_MS_GET_FILE_POS	2
#define SEEK_MS_BY_FILE_POS	3

#define GET_DURATION_MS	0
#define GET_CHANNELS	1
#define GET_SAMPLERATE	2
#define GET_BITSPERSAMPLE	3
#define GET_BITRATE		4
#define GET_CUR_TIME_MS	5
#define GET_MEG_LAYER	6

#define MAX_ID3_INFO_LEN		64

#define	MUSIC_TAG_TITLE_LEN		MAX_ID3_INFO_LEN
#define	MUSIC_TAG_ARTIST_LEN	MAX_ID3_INFO_LEN
#define	MUSIC_TAG_ALBUM_LEN		MAX_ID3_INFO_LEN
#define	MUSIC_TAG_YEAR_LEN		4
#define	MUSIC_TAG_COMMENT_LEN	MAX_ID3_INFO_LEN

struct mp3tag {
    char        tag[3];
    char        title[30];
    char        artist[30];
    char        album[30];
    char        year[4];
    char        comments[30];
    unsigned char   genre;
};

struct MusicTag {
	char		title[MUSIC_TAG_TITLE_LEN];
	char		artist[MUSIC_TAG_ARTIST_LEN];
	char		album[MUSIC_TAG_ALBUM_LEN];
	char		year[MUSIC_TAG_YEAR_LEN];
	char		comments[MUSIC_TAG_COMMENT_LEN];
	unsigned char	genre;
	unsigned char	tag_char_code;
};

typedef struct MusicTag		MusicTag_t;

#define TAG_TITLE		0
#define TAG_ARTIST		1
#define TAG_ALBUM		2
#define TAG_YEAR		3
#define TAG_COMMENTS	4

#define CHAR_CODE_ASCII		0
#define CHAR_CODE_UNICODE	1
#define CHAR_CODE_UTF8		2



typedef struct decoder_func{
	int (*create_dec)(char * file_path,  FILE_IO * fio);
	void (*destroy_dec)(void);
	int (*dec_next_frm)(void * pcm_out);
	int (*seek)(int ms, int opt, int * file_pos);
	int (*get_info)(int info);
	MusicTag_t * (*get_tag)(void);
} decoder_func_t;

extern const decoder_func_t aac_dec_if;
extern const decoder_func_t m4a_dec_if;
extern const decoder_func_t ts_dec_if;

#endif
