#include <stdio.h>

#include "nxplayer.h"
#include "player_cmd.h"
#include "sl_ui_def.h"
#include "sl_ui_cmd.h"
#include "sl_ui_struct.h"
#include "sl_ui_post.h"

extern struct button_info	*g_ui_button;

static int show_volume(struct dialog_info *ui_dialog)
{
	char txt_info [VALUE_LEN];
	ui_info_t   *player_info = &(g_ui_button->player_info);
	player_get_info(player_info);
	sprintf(txt_info, "%s %d", ui_dialog->e_name, player_info->volume);
	display_line_info(MEDIA_LINE, txt_info, 0, false);
	return SL_UI_ERROR_NULL;
}

int show_volume_up(struct dialog_info *pre_ui_dialog)
{
	show_volume(pre_ui_dialog);
	return SL_UI_ERROR_NULL;
}

int action_volume_up(struct dialog_info *ui_dialog)
{
	set_sl_ui_cmd(NP_CMD_VOLUME_UP, NULL, VOLUME_ADJ_STEP);
	return SL_UI_ERROR_NULL;
}

int show_volume_dn(struct dialog_info *pre_ui_dialog)
{
	show_volume(pre_ui_dialog);
	return SL_UI_ERROR_NULL;
}

int action_volume_dn(struct dialog_info *ui_dialog)
{
	set_sl_ui_cmd(NP_CMD_VOLUME_DOWN, NULL, VOLUME_ADJ_STEP);
	return SL_UI_ERROR_NULL;
}
