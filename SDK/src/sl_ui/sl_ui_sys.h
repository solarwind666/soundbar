#ifndef __SL_UI_SYS_H__
#define __SL_UI_SYS_H__
#include <nuttx/config.h>

#ifdef CONFIG_WIRELESS
enum ui_sys_net_stat_e {
	SL_UI_SYS_NET_STAT_NULL = -1,
	SL_UI_SYS_NET_STAT_CONNECT,
	SL_UI_SYS_NET_STAT_DISCONNECT,
};

enum ui_sys_wifi_sig_e {
	SL_UI_SYS_WIFI_SIG_NULL = -1,
	SL_UI_SYS_WIFI_SIG_I,
	SL_UI_SYS_WIFI_SIG_II,
	SL_UI_SYS_WIFI_SIG_III,
	SL_UI_SYS_WIFI_SIG_IIII,
	SL_UI_SYS_WIFI_SIG_IIIII,
};
#endif

#ifdef CONFIG_SYSTEM_AVS
enum ui_sys_cloud_stat_e {
	SL_UI_SYS_CLOUD_NULL = -1,
	SL_UI_SYS_CLOUD_CONNECT,
	SL_UI_SYS_CLOUD_DISCONNECT,
};
#endif

enum ui_sys_sd_stat_e {
	SL_UI_SYS_SD_NULL = -1,
	SL_UI_SYS_SD_CONNECT,
	SL_UI_SYS_SD_DISCONNECT,
};

typedef struct sys_info_s {
#ifdef CONFIG_WIRELESS
    int net_stat;
	int wifi_sig;
#endif
#ifdef CONFIG_SYSTEM_AVS
	int cloud_stat;
#endif
	int sd_stat;
}sys_info_t;

#endif
