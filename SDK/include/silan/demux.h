#ifndef __DEMUX_H__
#define __DEMUX_H__


typedef struct demux_handle_struct{
	FILE_IO * fio;
    decoder_func_t * decoder;

}demux_hdl_t;


typedef struct demux_func{
	int (*open)(char * file_path, unsigned int opt, FILE_IO * fio);
	void (*close)(demux_hdl_t * hdl);
	int (*next_frm)(demux_hdl_t * hdl, void * pcm_out);
	int (*seek)(demux_hdl_t * hdl, int ms, int opt, int * file_pos);
	int (*get_info)(demux_hdl_t * hdl, int info);
	MusicTag_t *(*get_tag)(demux_hdl_t * hdl);
} demux_func_t;


extern const demux_func_t demux_if;


#define MUSIC_TYPE_WAV	0
#define MUSIC_TYPE_MP3	1
#define MUSIC_TYPE_AAC	2
#define MUSIC_TYPE_WMA	3
#define MUSIC_TYPE_OGG	4
#define MUSIC_TYPE_M4A	5
#define MUSIC_TYPE_FLAC	6
#define MUSIC_TYPE_APE	7
#define MUSIC_TYPE_AC3	8
#define MUSIC_TYPE_DTS	9
#define MUSIC_TYPE_OPUS	10
#define MUSIC_TYPE_LPCM	11
#define MUSIC_TYPE_TS	12

#endif /*__DEMUX_H__*/
