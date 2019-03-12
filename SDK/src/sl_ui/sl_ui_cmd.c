#include <stdio.h>

#include "nxplayer.h"
#include "player_cmd.h"
#include "sl_ui_cmd.h"
#include "sl_ui_struct.h"
#include "sl_ui_handle.h"

extern struct button_info	*g_ui_button;
extern void player_get_info(ui_info_t *info);

struct ui_cmd_func ui_cmd_tbl[] =
{
/*
	{   NP_CMD_SUPPER_START,            NULL                   },
	{   NP_CMD_STOP,                    sl_ui_handle_show_stop },
	{   NP_CMD_RESET,                   NULL                   },
	{   NP_CMD_SUPPER_END,              NULL                   },

	{   NP_CMD_PROCESS_START,           NULL                   },
	{   NP_CMD_PLAY,                    sl_ui_handle_play      },
	{   NP_CMD_RESUME,                  NULL                   },
	{   NP_CMD_PAUSE,                   NULL                   },
	{   NP_CMD_RECORD_ON,               NULL                   },
	{   NP_CMD_RECORD_OFF,              NULL                   },
	{   NP_CMD_SEEK,                    NULL                   },
#ifdef CONFIG_WIRELESS
	{   NP_CMD_BT_START,                sl_ui_handle_bt_start  },
	{   NP_CMD_BT_FINISH,               sl_ui_handle_show_stop },
	{   NP_CMD_BT_MODEOFF,              NULL                   },
	{   NP_CMD_AIRPLAY_START,           sl_ui_handle_airplay_start},
	{   NP_CMD_AIRPLAY_STOP,            sl_ui_handle_show_stop },
	{   NP_CMD_DLNA_START,              NULL                   },
	{   NP_CMD_DLNA_PLAY,               sl_ui_handle_dlna_start},
	{   NP_CMD_DLNA_FINISH,             sl_ui_handle_show_stop },
	{   NP_CMD_BT_HFP_START,            NULL                   },
	{   NP_CMD_BT_HFP_FINISH,           NULL                   },
#endif
	{   NP_CMD_UPDATE_PLAY_POS,         NULL                   },
	{   NP_CMD_GET_PLAY_POS,            NULL                   },
	{   NP_CMD_NEXT,                    NULL                   },
	{   NP_CMD_PREV,                    NULL                   },
	{   NP_CMD_PCM_DATA,                NULL                   },
	{   NP_CMD_PCM_END,                 NULL                   },
	{   NP_CMD_LINEIN_ON,               NULL                   },
	{   NP_CMD_LINEIN_OFF,              sl_ui_handle_show_stop },
	{   NP_CMD_SPDIFIN_START,           NULL                   },
	{   NP_CMD_SPDIFIN_STOP,            sl_ui_handle_show_stop },
	{   NP_CMD_SET_CHANNELS,            NULL                   },
	{   NP_CMD_SET_OUTMODE,             NULL                   },
	{   NP_CMD_PROCESS_END,             NULL                   },

	{   NP_CMD_AUDIO_POST_START,        NULL                   },
	{   NP_CMD_VOLUME_UP,               NULL                   },
	{   NP_CMD_VOLUME_DOWN,             NULL                   },
	{   NP_CMD_MUTE,                    NULL                   },
	{   NP_CMD_VOLUME_SET,              NULL                   },
	{   NP_CMD_AUDIO_POST_END,          NULL                   },

	{   UI_CMD_NULL,					NULL                   },
	{   UI_CMD_BT_UP,					sl_ui_handle_up        },
	{   UI_CMD_BT_DOWN, 	            sl_ui_handle_dn        },
	{   UI_CMD_BT_NEXT, 	            sl_ui_handle_next      },
	{   UI_CMD_BT_PREV, 	            sl_ui_handle_prev      },
	{   UI_CMD_BT_OK,					sl_ui_handle_ok        },
	{   UI_CMD_BT_MODE, 	            sl_ui_handle_mode      },
	{   UI_CMD_BT_FUNC,                 sl_ui_handle_func      },
	{   UI_CMD_BT_EQ,                   NULL                   },

	{   UI_CMD_USB_IN,                  NULL                   },
	{	UI_CMD_USB_OUT,					sl_ui_handle_local_out },
	{   UI_CMD_USB_UNLOAD,              sl_ui_handle_usb_out   },
	{   UI_CMD_SD_IN,                   NULL                   },
	{   UI_CMD_SD_UNLOAD,               sl_ui_handle_sd_out    },
	{	UI_CMD_SD_OUT,					sl_ui_handle_local_out },
#ifdef CONFIG_WIRELESS
	{	UI_NET_STA_SUCCESS,				sl_ui_handle_sta_success },
	{	UI_NET_STA_FAIL,				sl_ui_handle_sta_fail },
#endif

	{   UI_CMD_PLAYER_FINISH,           sl_ui_handle_player_finish },
	{   UI_CMD_PLAYER_TONE_FINISH,      sl_ui_handle_tone_finish },
	{   UI_CMD_BUFFERING,               NULL                   },

	{   UI_CMD_DOPLAY,                  sl_ui_handle_do_play   },
	{   UI_CMD_MUTE,                    sl_ui_handle_mute      },
	{   UI_CMD_UNMUTE,                  sl_ui_handle_unmute    },
	{   UI_CMD_RESUME,                  sl_ui_handle_resume    },
	{   UI_CMD_PAUSE,                   sl_ui_handle_pause     },
	{   UI_CMD_STOP,                    sl_ui_handle_stop      },
#ifdef CONFIG_CEC	
    {   UI_CEC_INACTIVE_SOURCE,sl_ui_handle_cec_inactive_source},
    {   UI_CEC_ACTIVE_SOURCE,   sl_ui_handle_cec_active_source},
#endif
*/
};

struct ui_cmd_func *sl_ui_parse_cmd(int cmd)
{
	int i;
	for (i=0; i<(sizeof(ui_cmd_tbl)/sizeof(struct ui_cmd_func)); i++) {
		if (cmd == ui_cmd_tbl[i].cmd)
			return &(ui_cmd_tbl[i]);
	}
	return NULL;
}

static bool is_forced_cmd(int cmd)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	if ((cmd > NP_CMD_SUPPER_START)  && (cmd < NP_CMD_SUPPER_END))
		return true;
	else
		return false;
}

static bool is_post_cmd(int cmd)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	if ((cmd > NP_CMD_AUDIO_POST_START)  && (cmd < NP_CMD_AUDIO_POST_END))
		return true;
	else
		return false;
}

static bool is_processing_cmd(int cmd)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	if ((cmd > NP_CMD_PROCESS_START)  && (cmd < NP_CMD_PROCESS_END))
		return true;
	else
		return false;
}

bool is_processing_done(void)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	return true;
}

static int set_nxplayer_terminate(void)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
}

int forced_action(void)
{
#ifdef SL_UI_DBG
	printf("%s %d, cmd:%d\n", __func__, __LINE__, g_ui_button->player_process.cmd);
#endif
	set_nxplayer_terminate();
	player_process_cmd(g_ui_button->player_forced.cmd, g_ui_button->player_forced.param, g_ui_button->player_forced.arg, NULL, NULL);
	if (NULL != g_ui_button->player_forced.param) {
		free(g_ui_button->player_forced.param);
	}
	g_ui_button->player_forced.cmd = NP_CMD_NONE;
	g_ui_button->player_forced.param = NULL;
	return SL_UI_ERROR_NULL;	
}

static int post_action(void)
{
#ifdef SL_UI_DBG
	printf("%s %d, cmd:%d\n", __func__, __LINE__, g_ui_button->player_process.cmd);
#endif
	player_process_cmd(g_ui_button->player_post.cmd, g_ui_button->player_post.param, g_ui_button->player_post.arg, NULL, NULL);
	if (NULL != g_ui_button->player_post.param) {
		free(g_ui_button->player_post.param);
	}
	g_ui_button->player_post.cmd = NP_CMD_NONE;
	g_ui_button->player_post.param = NULL;
	return SL_UI_ERROR_NULL;	
}

int processing_action(void)
{
#ifdef SL_UI_DBG
	printf("%s %d, cmd:%d\n", __func__, __LINE__, g_ui_button->player_process.cmd);
#endif
	player_process_cmd(g_ui_button->player_process.cmd, g_ui_button->player_process.param, g_ui_button->player_process.arg, NULL, NULL);
	if (NULL != g_ui_button->player_process.param)
		free(g_ui_button->player_process.param);
	g_ui_button->player_process.cmd = NP_CMD_NONE;
	g_ui_button->player_process.param = NULL;
	return SL_UI_ERROR_NULL;	
}

int set_sl_ui_cmd(int cmd, void *param, int arg)
{
#ifdef SL_UI_DBG
	printf("%s %d, cmd:%d\n", __func__, __LINE__, cmd);
#endif
	if (is_forced_cmd(cmd)) {
		g_ui_button->player_forced.cmd = cmd;
		if (NULL != g_ui_button->player_forced.param) {
			free(g_ui_button->player_forced.param); 
			g_ui_button->player_forced.param = NULL;
		}
		if (param != NULL)
			g_ui_button->player_forced.param = strdup(param);
		g_ui_button->player_forced.arg = arg;

	}
	else if (is_post_cmd(cmd)) {
		g_ui_button->player_post.cmd = cmd;
		if (NULL != g_ui_button->player_post.param) {
			free(g_ui_button->player_post.param); 
			g_ui_button->player_post.param = NULL;
		}
		if (param != NULL)
			g_ui_button->player_post.param = strdup(param);
		g_ui_button->player_post.arg = arg;
		post_action();
	}
	else if (is_processing_cmd(cmd)) {
		g_ui_button->player_process.cmd = cmd;
		if (NULL != g_ui_button->player_process.param) {
			free(g_ui_button->player_process.param); 
			g_ui_button->player_process.param = NULL;
		}
		if (param != NULL)
			g_ui_button->player_process.param = strdup(param);
		g_ui_button->player_process.arg = arg;
	}
	return SL_UI_ERROR_NULL;	
}

ui_info_t get_all_play_info(void)
{
	ui_info_t   *player_info = &(g_ui_button->player_info);
	player_get_info(player_info);
	return g_ui_button->player_info;
}
