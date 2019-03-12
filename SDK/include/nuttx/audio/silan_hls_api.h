#ifndef __HLS_DownLoad__hls__
#define __HLS_DownLoad__hls__

#include <stdbool.h>

#define MASTER_PLAYLIST 0
#define MEDIA_PLAYLIST 1

#define ENC_AES_SAMPLE 0x02
#define ENC_AES128 0x01
#define ENC_NONE 0x00

#define KEYLEN 16

#define MAX_URL_SIZE    1024

struct ByteBuffer {
    uint8_t *data;
    int len;
    int pos;
};

struct enc_aes128 {
    bool iv_is_static;
    uint8_t iv_value[KEYLEN];
    uint8_t key_value[KEYLEN];
};

enum KeyType {
    KEY_NONE,
    KEY_AES_128,
    KEY_SAMPLE_AES
};

typedef enum {
    ST_HLS_FINISH = 0,
    ST_HLS_WAIT_UPDATE_PLAYLIST,
    ST_HLS_PARSE_PLAYLIST,
    ST_HLS_READ_SEGMENT,
}HLS_ST;

struct segment {
    int64_t duration;
    int64_t url_offset;
    int64_t size;
    char *url;
    int sequence_number;
    enum KeyType key_type;
    struct enc_aes128 enc_aes;
    int sockfd;
};

#define AV_TIME_BASE            1000000
struct hls_playlist {
    char *url;
    char *source;
    int source_total;
    int source_len;
    unsigned int bitrate;
    bool encryption;
    int encryptiontype;
    int count;
    struct segment *media_segment;
    struct enc_aes128 enc_aes;
    int cur_seq_no;
    int start_seq_no;
    int finished;
    int64_t target_duration;
    int64_t last_load_time;
    int64_t cur_seg_offset;

    int state; /* for uv api. */
    int first_read;
};

struct hls_master_playlist {
    char *url;
    char *source;
    int count;
    struct hls_playlist *media_playlist;
};

int hls_read_data(struct hls_playlist *pls, char *buf, int buflen);
int hls_read_playlist(struct hls_playlist *me);
int hls_read_segment(struct hls_playlist *me, char **url);
bool hls_probe(char *buf);
void hls_update_cur_seqno(struct hls_playlist *pls);
int hls_read_header(void *arg, char *buf, int buflen, int total_size);
void hls_set_state(void *data, int state);
void hls_close(void *data);
#endif /* defined(__HLS_DownLoad__hls__) */
