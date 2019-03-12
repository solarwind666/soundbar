#ifndef __SL_UI_STRUCT_H__
#define __SL_UI_STRUCT_H__
#include <stdio.h>

#include "sl_lcd.h"
#include "sl_ui_old.h"
#include "sl_ui_def.h"
#include "sl_ui_sys.h"

typedef struct dialog_item {
	void *userdata;
	struct dialog_item *parent;
	struct dialog_item *child;
	struct dialog_item *prev;
	struct dialog_item *next;
}DIALOG_ITEM;

typedef struct dialog_info {
	char *e_name;
	void *param;
	int (*show)(struct dialog_info *);
	int (*action)(struct dialog_info *); // devide into 3 type cmd interface given by nxplayer
	int (*reset)(struct dialog_info *);
	struct dialog_item *item_info;
	int max_member;
	bool should_show;
	bool should_tempo_show;
	bool should_const_show;
}DIALOG_INFO;

struct display_info {
	WORD *value_pos;
	WORD value[INFO_LEN];
	int line;
	int mode;
	int len;
}DISPLAY_INFO;

typedef struct normal_dialog_param {
	int cur_normal_idx;
};

struct local_dialog_param {
	int cur_normal_idx;
	char *name;
	struct dialog_info *dialog;
	pthread_t tid;
};

typedef struct music_dialog_param {
	int cur_music_idx;
	int total_music;
	bool is_get_tag;
	bool is_get_pcm_info;
};

typedef struct file_dialog_param {
	int file_start_idx;
	int file_end_idx;
	int cur_file_idx;
};

typedef struct folder_dialog_param {
	int cur_folder_idx;
};

struct send_cmd_s {
	int cmd;
	void *param;	//parameter for cmd such url etc
	int arg;
};

struct  ui_context_s {
	char player_url[CONTEXT_URL_LEN];
	int player_pos;
};

typedef struct button_info {
	//int cur_state_machine;
	//int player_cmd;
	//void *param;	//action paramter deliver from CMD_FUNC
	struct send_cmd_s player_forced;
	struct send_cmd_s player_post;
	struct send_cmd_s player_process;
	//int (*action)(struct dialog_info *); //copy from struct dialog_info action
	DIALOG_INFO	*prev_dialog;
	DIALOG_INFO	*cur_dialog;

	struct display_info line_info[LIST_LINE_MAX];
	int show_delay_cnt;
	int line_pos[LIST_LINE_MAX];
	ui_info_t   player_info;
	sys_info_t  sys_info;
	mqd_t		mq;
	char		mqname[16];
	int		state_machine;
#ifdef CONFIG_RTC
	int			alarm_stat;
	struct tm	alarm_time;
	pthread_t   alarm_pid;
	bool		alarm_is_playing;
#endif
	struct ui_context_s context;
}BUTTON_INFO;	//only one for UI

#endif
