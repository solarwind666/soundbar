#ifndef DEMUX_H_
#define DEMUX_H_

#include "types.h"
#include "error.h"

typedef enum _DmxInfoType {
    DMX_DURATION = 0,
    DMX_BITRATE,
    DMX_CHANNELS,
    DMX_SAMPLERATE,
    DMX_PROGRAMS,
    DMX_AUDIOTYPE,
    DMX_CUR_FRAME_NO,
    DMX_ALL
} DmxInfoType;

typedef enum _DmxOpenLevel {
    DMX_OPEN_NORMAL = 0,
    DMX_OPEN_FAST
} DmxOpenLevel;

typedef struct {
    char title[64];
    char album[64];
    char artist[64];
    char year[20];
    char genre[64];
    char description[100];
    int encoding_format;
}TagInfo;

void *demux_init(void);
int demux_open(void *dmx, const char *filename, void *stream, void *decoder, DmxOpenLevel level);
int demux_get_only_tag(void *dmx, const char *filename, void *stream);
int demux_seek(void *dmx, int64_t seek_timestamp, int direction);
int demux_get_frame(void *dmx, AVPacket *pkt);
int demux_get_info(void *dmx, DmxInfoType type);
int demux_deinit(void *dmx);
int demux_flush_buffer(void *dmx);
int demux_get_metadata(TagInfo **taginfo);
const char *demux_get_audio_type(void *dmx);

#endif /* DEMUX_H_ */

