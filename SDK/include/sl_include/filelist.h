#ifndef __FS_FILE_LIST__
#define __FS_FILE_LIST__
#define MAX_DIR_NUM	  512//512  //2000
#define MAX_FILE_NUM  2000  //5000
#define MAX_FILE_NAME_LEN	128//8//48
#define MAX_DIR_NAME_LEN	256//MAX_FILE_NAME_LEN//48

typedef struct dir_elmt{
	char path_name[MAX_DIR_NAME_LEN];
	short parent_index;
	short child_index;
	short file_index;
	short file_num;
	short dir_num;
}dir_elmt_t;

#define MUSIC_FILE_UNSUPPORT  	0	/* unsupport file */
#define MUSIC_FILE_MP3        	1	/* "*.mp3" file */
#define MUSIC_FILE_WMA        	2	/* "*.wma" and "*.asf" file */
#define MUSIC_FILE_WAVE       	3	/* "*.wav" file */
#define MUSIC_FILE_AAC			4	/* "*.aac" file*/
#define MUSIC_FILE_M4A			5	/* "*.m4a" file*/
#define MUSIC_FILE_FLAC			6	/*"*.flac" file*/
#define MUSIC_FILE_APE			7	/*"*.ape" file*/
#define MUSIC_FILE_OGG			8

#define SUM_SUFFIX		12

enum Codecs_ID{
    CODEC_UNSUPPORT=0,
    CODEC_MP1 = 1,
    CODEC_MP3,
    CODEC_MP2,
    CODEC_APE,
    CODEC_FLAC,
    CODEC_AAC,
    CODEC_WMA,
    CODEC_WAV,
    CODEC_DTS,
    CODEC_AC3
};

static char * music_suffixs[SUM_SUFFIX]={"mp1","mp3","mp2","ape","flac","aac","wma","wav", "dts", "ac3", "ogg", "m4a"};
static enum Codecs_ID music_codecs[SUM_SUFFIX]={CODEC_MP1, CODEC_MP3, CODEC_MP2, CODEC_APE, CODEC_FLAC, CODEC_AAC, CODEC_WMA, CODEC_WAV, CODEC_DTS, CODEC_AC3};

typedef struct music_file{
	char file_name[MAX_FILE_NAME_LEN];
	short parent_dir_index;
	unsigned char type;
}music_file_t;


typedef struct cur_index{
	short dir_index;
	short file_index;
}fs_lst_cur_idx_t;

typedef struct play_list_item{
    char path[MAX_DIR_NAME_LEN+MAX_FILE_NAME_LEN+2];
    char name[MAX_FILE_NAME_LEN];
    short dir_index;
    short file_index;
}play_list_item_t;

struct play_list{
	struct music_file music_list[MAX_FILE_NUM];
	int file_total;
	int start_file_idx;
	struct dir_elmt dir_list[MAX_DIR_NUM];
	int dir_total;
	fs_lst_cur_idx_t line_dir_list[MAX_DIR_NUM];
	int valid_dir_num;
};
typedef struct play_list play_list_t;

int playlist_init(void);
int file_music_enumate(const char *dirpath, int start_file_idx);
void set_cur_file_position(unsigned short music_no);
void fs_list_create_liner_list_for_fat(void);
int play_list_get_file_total();
int play_list_get_valid_dir_num();
int play_list_get_dir_total();
unsigned short get_cur_dir_index();
unsigned short get_cur_file_index();
dir_elmt_t *  play_list_get_cur_direlm();
dir_elmt_t *  play_list_get_direlm_byindex(unsigned int num);
int play_list_get_cur_name(play_list_item_t * item);
int play_list_get_file_byindex(play_list_item_t * item, unsigned int num);
int play_list_get_next_name(play_list_item_t * item);
int play_list_get_prev_name( play_list_item_t * item);

#endif
