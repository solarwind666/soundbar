#include <stdlib.h>
#include <string.h>
#include "sl_ui_def.h"
#include "sl_ui_table.h"

extern struct button_info	*g_ui_button;

static int dialog_prev_2_cur(void)
{
	g_ui_button->cur_dialog = g_ui_button->prev_dialog;
	g_ui_button->prev_dialog = NULL;
	return 	SL_UI_ERROR_NULL;
}

int dialog_temporary_out_check(void)
{
	if (g_ui_button->cur_dialog) {
		if (g_ui_button->cur_dialog->should_tempo_show) {
			dialog_prev_2_cur();  
			return 	SL_UI_ERROR_NULL;
		}
	}
	return 	-SL_UI_ERROR_NO_SWITCH;
}

int dialog_temporary_in_check(struct dialog_info *ui_dialog)
{
	dialog_temporary_out_check();
	if (NULL != ui_dialog) {
		if (ui_dialog->should_tempo_show) {
			g_ui_button->prev_dialog = g_ui_button->cur_dialog;
			if (NULL != g_ui_button->cur_dialog) {
				if (NULL != g_ui_button->cur_dialog->reset)
					g_ui_button->cur_dialog->reset(g_ui_button->cur_dialog);
				g_ui_button->cur_dialog = ui_dialog;
				if (NULL != g_ui_button->cur_dialog->reset)
					g_ui_button->cur_dialog->reset(g_ui_button->cur_dialog);
			}
		}
		else  {
			g_ui_button->cur_dialog = ui_dialog;
			if (NULL != g_ui_button->cur_dialog->reset)
				g_ui_button->cur_dialog->reset(g_ui_button->cur_dialog);
		}
		/*
		 * Note: handle_dn & handle_up cause problem!
		 if (!ui_dialog->should_tempo_show)
		 show_list_val_init(ui_dialog->max_member);
		 */
	}
	else {
		g_ui_button->cur_dialog = ui_dialog;
	}
	return 	SL_UI_ERROR_NULL;
}

struct dialog_info	*ui_dialog_find_tail(struct dialog_info *ui_dialog)
{
	struct dialog_item *child;
	struct dialog_item *item;
	if (NULL == ui_dialog) {
		printf("%s %d parameter failed!\n", __func__, __LINE__); 
		return 	NULL;
	}
	item = ui_dialog->item_info;
	child = item->child;
	while(child != NULL) {
		item = child;
		child = item->child;
	}
	return item->userdata;
}

struct dialog_item	*ui_dialog_item_list_add_tail(int item_num, struct dialog_info	*ui_dialog, struct dialog_info	*parent_dialog)
{
	int i=0, max;
	struct dialog_item *ui_dialog_item;
	struct dialog_item *parent;
	struct dialog_item *brother;

	if(NULL == parent_dialog) {
		printf("%s %d parent is NULL %s\n", __func__, __LINE__, ui_dialog->e_name);
		return NULL;
	}
	max = ui_dialog->max_member;
	ui_dialog_item = malloc(item_num * sizeof(struct dialog_item));	
	if (NULL == ui_dialog_item) {
		printf("%s %d malloc child failed %s\n", __func__, __LINE__, ui_dialog->e_name);
		return NULL;
	}
#ifdef SL_UI_DBG
	printf("mmmmmmmmm %s %d 0x%x\n", __func__, __LINE__, ui_dialog_item);
#endif
	memset(ui_dialog_item, NULL, item_num * sizeof(struct dialog_item));

	parent = parent_dialog->item_info;
	brother = parent->child;
	for (i=0; i<max-1; ++i) {
		brother = brother->next;
	}
	for (i=0; i<item_num; ++i) {
		ui_dialog_item[i].parent = parent;
		ui_dialog_item[i].userdata = &ui_dialog[i];
		ui_dialog[i].item_info =  &ui_dialog_item[i];
		if (i < (item_num - 1)) {
			ui_dialog_item[i].next = &ui_dialog_item[i + 1];
			ui_dialog_item[i + 1].prev = &ui_dialog_item[i];
		}
		else if (i == (item_num - 1)) {
			ui_dialog_item[i].next = brother;
			brother->prev = &ui_dialog_item[i];
		}
	}
}

struct dialog_item	*ui_dialog_item_list_init(int item_num, struct dialog_info	*ui_dialog, struct dialog_info	*parent_dialog)
{
	int i=0;
	struct dialog_item *ui_dialog_item;
	struct dialog_item *parent;

	ui_dialog_item = malloc(item_num * sizeof(struct dialog_item));	
	if (NULL == ui_dialog_item) {
		printf("%s %d malloc child failed %s\n", __func__, __LINE__, ui_dialog->e_name);
		return NULL;
	}
#ifdef SL_UI_DBG
	printf("mmmmmmmmm %s %d 0x%x\n", __func__, __LINE__, ui_dialog_item);
#endif
	memset(ui_dialog_item, NULL, item_num * sizeof(struct dialog_item));
	if (parent_dialog) {
		parent = parent_dialog->item_info;
		parent->child = ui_dialog_item;	
	}
	for (i=0; i< item_num; ++i) {

		ui_dialog_item[i].parent = parent;
		ui_dialog_item[i].userdata = &ui_dialog[i];
		ui_dialog[i].item_info =  &ui_dialog_item[i];
		if (i < (item_num - 1)) {
			ui_dialog_item[i].next = &ui_dialog_item[i + 1];
			ui_dialog_item[i + 1].prev = &ui_dialog_item[i];
		}
		else if (i == (item_num - 1)) {
			ui_dialog_item[i].next = &ui_dialog_item[0];
			ui_dialog_item[0].prev = &ui_dialog_item[i];
		}
	}
	return ui_dialog_item;
}

int dialog_music_param_init(int max, struct dialog_info *ui_dialog)
{
	int i;
	struct music_dialog_param *param;
	param = (struct music_dialog_param *)malloc(max * sizeof(struct normal_dialog_param));
	if (NULL == param) {
		printf("%s %d malloc music_param failed!\n", __func__, __LINE__); 
		return 	-SL_UI_ERROR_MALLOC;
	}
#ifdef SL_UI_DBG
	printf("mmmmmmmmm %s %d 0x%x\n", __func__, __LINE__, param);
#endif
	for (i=0; i<max; ++i) {
		param[i].cur_music_idx = i;
		param[i].is_get_tag = false;
		param[i].is_get_pcm_info = false;
		ui_dialog[i].param = &param[i];
	}
	return 	SL_UI_ERROR_NULL;

}

int dialog_norm_param_init(int max, struct dialog_info *ui_dialog)
{
	int i;
	struct normal_dialog_param *param;
	param = (struct normal_dialog_param *)malloc(max * sizeof(struct normal_dialog_param));
	if (NULL == param) {
		printf("%s %d malloc norm_param failed!\n", __func__, __LINE__); 
		return 	-SL_UI_ERROR_MALLOC;
	}
#ifdef SL_UI_DBG
	printf("mmmmmmmmm %s %d 0x%x\n", __func__, __LINE__, param);
#endif
	for (i=0; i<max; ++i) {
		param[i].cur_normal_idx = i;
		ui_dialog[i].param = &param[i];
	}
	return 	SL_UI_ERROR_NULL;
}

int dialog_local_param_init(int max, struct dialog_info *ui_dialog)
{
	int i;
	struct local_dialog_param *param;
	param = (struct local_dialog_param *)malloc(max * sizeof(struct local_dialog_param));
	if (NULL == param) {
		printf("%s %d malloc norm_param failed!\n", __func__, __LINE__); 
		return 	-SL_UI_ERROR_MALLOC;
	}
#ifdef SL_UI_DBG
	printf("mmmmmmmmm %s %d 0x%x\n", __func__, __LINE__, param);
#endif
	for (i=0; i<max; ++i) {
		param[i].cur_normal_idx = i;
		param[i].tid = 0;
		param[i].name = NULL;
		param[i].dialog = NULL;
		ui_dialog[i].param = &param[i];
	}
	return 	SL_UI_ERROR_NULL;
}

int dialog_init()
{
	int i = 0, item_num = 0;
	struct dialog_info	*ui_dialog;
	struct dialog_info	*parent_dialog;
	struct dialog_item	*ui_dialog_item;

	ui_dialog = get_mode_tbl();
	item_num = SL_UI_DIALOG_TYPE_MODE_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, NULL);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_source_tbl();
	parent_dialog = get_mode_tbl();
	item_num = SL_UI_DIALOG_TYPE_SOURCE_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_MODE_SOURCE]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

#ifdef CONFIG_FAT32_FILELIST
	ui_dialog = get_local_mode_tbl();
	parent_dialog = get_source_tbl();
	item_num = SL_UI_DIALOG_TYPE_LOCAL_MODE_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_SOURCE_LOCAL]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

#ifdef CONFIG_SC6138_SD
	ui_dialog = get_local_sd_tbl();
	parent_dialog = get_local_mode_tbl();
	item_num = SL_UI_DIALOG_TYPE_SD_MODE_MAX;
	dialog_local_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_LOCAL_MODE_SD]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}
#endif

#ifdef CONFIG_SILAN_USBHS
	ui_dialog = get_local_usb_tbl();
	parent_dialog = get_local_mode_tbl();
	item_num = SL_UI_DIALOG_TYPE_USB_MODE_MAX;
	dialog_local_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_LOCAL_MODE_USB]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}
#endif
#endif

	ui_dialog = get_linein_tbl();
	parent_dialog = get_source_tbl();
	item_num = SL_UI_DIALOG_TYPE_LINEIN_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_SOURCE_LINEIN]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_lineinon_tbl();
	parent_dialog = get_linein_tbl();
	item_num = SL_UI_DIALOG_TYPE_LINEINON_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_LINEIN_ON]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_lineinoff_tbl();
	parent_dialog = get_linein_tbl();
	item_num = SL_UI_DIALOG_TYPE_LINEINOFF_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_LINEIN_OFF]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

#ifdef CONFIG_SPDIFIN
	ui_dialog = get_spdifin_tbl();
	parent_dialog = get_source_tbl();
	item_num = SL_UI_DIALOG_TYPE_SPDIFIN_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_SOURCE_SPDIFIN]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_spdifinon_tbl();
	parent_dialog = get_spdifin_tbl();
	item_num = SL_UI_DIALOG_TYPE_SPDIFINON_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_SPDIFIN_ON]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_spdifinoff_tbl();
	parent_dialog = get_spdifin_tbl();
	item_num = SL_UI_DIALOG_TYPE_SPDIFINOFF_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_SPDIFIN_OFF]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}
#endif

#ifdef CONFIG_CEC
	ui_dialog = get_hdmi_tbl();
	parent_dialog = get_source_tbl();
	item_num = SL_UI_DIALOG_TYPE_HDMI_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_SOURCE_HDMI]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_hdmion_tbl();
	parent_dialog = get_hdmi_tbl();
	item_num = SL_UI_DIALOG_TYPE_HDMION_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_HDMI_ON]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_hdmioff_tbl();
	parent_dialog = get_hdmi_tbl();
	item_num = SL_UI_DIALOG_TYPE_HDMIOFF_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_HDMI_OFF]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_hdmistby_tbl();
	parent_dialog = get_hdmi_tbl();
	item_num = SL_UI_DIALOG_TYPE_HDMISTANDBY_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_HDMI_STANDBY]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_hdmipowon_tbl();
	parent_dialog = get_hdmi_tbl();
	item_num = SL_UI_DIALOG_TYPE_HDMIPOWERON_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_HDMI_POWERON]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}
#endif

#ifdef CONFIG_SYSTEM_UI_ROMFS
	ui_dialog = get_mix_tbl();
	parent_dialog = get_source_tbl();
	item_num = SL_UI_DIALOG_TYPE_MIX_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_SOURCE_MIX]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_mixon_tbl();
	parent_dialog = get_mix_tbl();
	item_num = SL_UI_DIALOG_TYPE_MIXON_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_MIX_ON]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_mixoff_tbl();
	parent_dialog = get_mix_tbl();
	item_num = SL_UI_DIALOG_TYPE_MIXOFF_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_MIX_OFF]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}
#endif

#ifdef CONFIG_WIRELESS
	ui_dialog = get_radio_tbl();
	parent_dialog = get_source_tbl();
	item_num = SL_UI_DIALOG_TYPE_RADIO_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_SOURCE_RADIO]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_radioon_tbl();
	parent_dialog = get_radio_tbl();
	item_num = SL_UI_DIALOG_TYPE_RADIOON_MAX;
	dialog_music_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_RADIO_ON]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_radiooff_tbl();
	parent_dialog = get_radio_tbl();
	item_num = SL_UI_DIALOG_TYPE_RADIOOFF_MAX;
	dialog_music_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_RADIO_OFF]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_net_tbl();
	parent_dialog = get_mode_tbl();
	item_num = SL_UI_DIALOG_TYPE_NET_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_MODE_NET]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}
#endif

#ifdef CONFIG_PM
	ui_dialog = get_lpm_tbl();
	parent_dialog = get_mode_tbl();
	item_num = SL_UI_DIALOG_TYPE_LPM_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_MODE_LPM]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_freq_tbl();
	parent_dialog = get_mode_tbl();
	item_num = SL_UI_DIALOG_TYPE_FREQ_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_MODE_FREQ]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_power_tbl();
	parent_dialog = get_mode_tbl();
	item_num = SL_UI_DIALOG_TYPE_POWER_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_MODE_POWER]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}
#endif

#ifdef CONFIG_RTC
	ui_dialog = get_alarm_tbl();
	parent_dialog = get_mode_tbl();
	item_num = SL_UI_DIALOG_TYPE_ALARM_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_MODE_ALARM]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_alarmon_tbl();
	parent_dialog = get_alarm_tbl();
	item_num = SL_UI_DIALOG_TYPE_ALARMON_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_ALARM_ON]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_alarmoff_tbl();
	parent_dialog = get_alarm_tbl();
	item_num = SL_UI_DIALOG_TYPE_ALARMOFF_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_ALARM_OFF]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}
#endif

#ifdef CONFIG_SYSTEM_AVS
	ui_dialog = get_avs_tbl();
	parent_dialog = get_mode_tbl();
	item_num = SL_UI_DIALOG_TYPE_AVS_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_MODE_AVS]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}
#endif

	ui_dialog = get_play_tbl();
	parent_dialog = get_mode_tbl();
	item_num = SL_UI_DIALOG_TYPE_PLAY_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, &parent_dialog[SL_UI_DIALOG_TYPE_MODE_PLAY]);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

#ifdef CONFIG_WIRELESS
	ui_dialog = get_wireless_tbl();
	item_num = SL_UI_DIALOG_TYPE_WIRE_MAX;
	dialog_music_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, NULL);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}
#endif

	ui_dialog = get_next_tbl();
	item_num = SL_UI_DIALOG_TYPE_NEXT_MAX;
	dialog_music_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, NULL);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_prev_tbl();
	item_num = SL_UI_DIALOG_TYPE_PREV_MAX;
	dialog_music_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, NULL);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_pause_tbl();
	item_num = SL_UI_DIALOG_TYPE_PAUSE_MAX;
	dialog_music_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, NULL);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_resume_tbl();
	item_num = SL_UI_DIALOG_TYPE_RESUME_MAX;
	dialog_music_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, NULL);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_vol_up_tbl();
	item_num = SL_UI_DIALOG_TYPE_VOL_UP_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, NULL);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	ui_dialog = get_vol_dn_tbl();
	item_num = SL_UI_DIALOG_TYPE_VOL_DN_MAX;
	dialog_norm_param_init(item_num, ui_dialog);
	ui_dialog_item  = ui_dialog_item_list_init(item_num, ui_dialog, NULL);
	if (NULL == ui_dialog_item) {
		printf("error malloc %s %d\n", __func__, __LINE__);
		goto error_out;
	}

	return 	SL_UI_ERROR_NULL;

error_out:
	return 	-SL_UI_ERROR_MALLOC;
}
