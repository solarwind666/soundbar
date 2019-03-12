#ifndef __AVS_INCLUDE_H__
#define __AVS_INCLUDE_H__
#include <nuttx/config.h>

//#define AVS_DBG	1
//#define AVS_PROTO_OLD 1
#ifdef AVS_PROTO_OLD
#define AVS_CMD_SEND_READY 0x1
#define AVS_CMD_RECV_READY 0x2
#define AVS_CMD_RECV_CODE  0x3
#define AVS_CMD_SEND_CODE  0x4
#define AVS_CMD_SEND_CTRL  0x7
#define AVS_CMD_RECV_CTRL  0x8
#define AVS_CMD_RECV_ERROR 0x9
#define AVS_CMD_SEND_ERROR 0xa

#define AVS_CMD_PACKET_TAG  0
#define AVS_CMD_PACKET_HEAD 0xffff

#define AVS_CODE_WAKEUP        0
#define AVS_CODE_WAKEDOWN      1
#define AVS_CODE_VOLUP         2
#define AVS_CODE_VOLDOWN       3
#define AVS_CODE_VOLMAX        4
#define AVS_CODE_VOLMIN        5
#define AVS_CODE_PLAYRESUME    6
#define AVS_CODE_PLAYPAUSE     7
#define AVS_CODE_REPEATLIST    8
#define AVS_CODE_REPEATONE     9
#define AVS_CODE_PLAYNEXT      10
#define AVS_CODE_PLAYPREV      11

enum button
{
    VOLUMEDOWN = 0,
    VOLUMEUP = 1,
    FBPREVIOUS = 2,
    STBYFUNCTION = 3,
    FFNEXT = 4,
    PLAYPAUSE = 5,
    NETRADIO1 = 6,
    NETRADIO2 = 7,
    STOP = 8,
    SMARTCONFIG = 9,
    EQ = 10,
    REPEAT = 11,
    NETRADIO1_STORE = 32+6,
    NETRADIO2_STORE = 32+7,
};

struct avs_key
{
    int key;
    int code;
};

struct avs_cmd_s
{
    unsigned short head;
    unsigned short len;
    unsigned char cmd;
    unsigned char num;
    unsigned short tag;
    unsigned char code;
    unsigned char checksum;
};
#else
#define PROTO_HEAD_LEN			2
#define PROTO_LENGTH_LEN		2
#define PROTO_CMD_LEN			1
#define PROTO_SEQ_LEN			1
#define PROTO_CHECKSUM_LEN		1

#define AVS_QUERY_CLOUD_CONNECT			1
#define AVS_QUERY_CLOUD_DISCONNECT		0
#define AVS_QUERY_WIFI_SIG_I			0x1
#define AVS_QUERY_WIFI_SIG_II			0x2
#define AVS_QUERY_WIFI_SIG_III			0x3
#define AVS_QUERY_WIFI_SIG_IIII			0x4
#define AVS_QUERY_WIFI_SIG_IIIII		0x5
#define AVS_QUERY_SD_OK					1
#define AVS_QUERY_SD_ERROR				0

#define AVS_PLAY_CTRL_VOL_UP			0x1
#define AVS_PLAY_CTRL_VOL_DN			0x2
#define AVS_PLAY_CTRL_PAUSE				0x3
#define AVS_PLAY_CTRL_RESUME			0x4
#define AVS_PLAY_CTRL_STOP				0x5
#define AVS_PLAY_CTRL_REPEAT			0x6
#define AVS_PLAY_CTRL_NET_DISCON		0x7
#define AVS_PLAY_CTRL_NET_CONNECT		0x8
#define AVS_PLAY_CTRL_PREV				0x9
#define AVS_PLAY_CTRL_NEXT				0xa
#define AVS_PLAY_CTRL_FF				0xb
#define AVS_PLAY_CTRL_FR				0xc
#define AVS_PLAY_CTRL_VOL_MAX			0xd
#define AVS_PLAY_CTRL_VOL_MIN			0xe

#define AVS_LOCAL_CONTENT_FILE_PLAY				0x1
#define AVS_LOCAL_CONTENT_FILE_OPEN_ERROR		0x2
#define AVS_LOCAL_CONTENT_FILE_FORMAT_ERROR		0x3

#define AVS_OPT_CTRL_ONLINE_PLAY	0x1
#define AVS_OPT_CTRL_PERMIT			0x55
#define AVS_OPT_CTRL_FORBID			0xaa

#define AVS_NOTIFY_LOCAL_PLAY_DONE		0x1
#define AVS_NOTIFY_ONLINE_PLAY_DONE		0x2
#define AVS_NOTIFY_NET_CONNECT			0x3
#define AVS_NOTIFY_NET_DISCONNECT		0x4
#define AVS_NOTIFY_SD_INSERT			0x5
#define AVS_NOTIFY_SD_REMOVE			0x6
#define AVS_NOTIFY_WIFI_SIG_I			0x1
#define AVS_NOTIFY_WIFI_SIG_II			0x2
#define AVS_NOTIFY_WIFI_SIG_III			0x3
#define AVS_NOTIFY_WIFI_SIG_IIII		0x4
#define AVS_NOTIFY_WIFI_SIG_IIIII		0x5

#define AVS_REPEAT_DELAY	200

struct avs_cmd_query_s {
	unsigned char cloud_stat;
	unsigned char wifi_sig;
	unsigned char sd_stat;
};

struct avs_cmd_local_content_s {
	unsigned char stat;
};

struct avs_cmd_opt_ctrl_s {
	unsigned char cmd;
};

struct avs_cmd_notify_s {
	unsigned char local_stat;
	unsigned char wifi_sig;
};

enum process_sm_e {
	PROCESS_SM_NULL,
	PROCESS_SM_R_START,
	PROCESS_SM_T_START,
};

enum avs_cmd_type_e{
	AVS_CMD_NULL = 0x0,
	AVS_CMD_QUERY = 0x1,
	AVS_CMD_PLAY_CTRL = 0x2,
	AVS_CMD_LOCAL_CONTENT =	0x3,
	AVS_CMD_OPT_CTRL = 0x4,
	AVS_CMD_NOTIFY = 0x5,
};

struct avs_cmd_s
{
    unsigned short head;
    unsigned short len;
    unsigned char cmd;
    unsigned char seq;
	unsigned char *playload;
    unsigned char checksum;
};

int avs_send_cmd(enum avs_cmd_type_e type, void *data);
#endif
#endif
