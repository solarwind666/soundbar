#ifndef __SL_UI_OLD_H__
#define __SL_UI_OLD_H__

#include "sl_ui_def.h"
#include <nuttx/audio/silan_audio_api.h>
#include <nuttx/audio/libadsp_demux.h>

// adapt to old version
typedef struct ui_cmd_s {
	int 	cmd;
	union {
		void *payload;
		char *url;
	}arg;
	int 	arg2;	//volume
	int 	mode;
}ui_cmd_t;

typedef struct ui_info_s {
	int player_media;
	int volume;
	int player_stat;
    int curtime;
    int totaltime;
    int ui_media;
    int bits;
    int samplerate;
    int channels;
    char tag_info[INFO_LEN];
    AUDIO_TYPE audiotype;
    TagInfo tag;
}ui_info_t;

#endif
