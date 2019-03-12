#include <stdio.h>
#include <string.h>

#include "sl_ui_def.h"
#include "sl_ui_struct.h"
#include "sl_ui_table.h"

extern struct button_info	*g_ui_button;

char *logo_name = "Silan";
int g_list_max = 0;
int g_list_cur = 0;

static WORD song_show[INFO_LEN];

static void reserv_display(int line, WORD* show, int mode)
{
	memcpy(g_ui_button->line_info[line].value, show, fat_get_unicode_size(show));
	g_ui_button->line_info[line].value_pos = &g_ui_button->line_info[line].value[1];
	g_ui_button->line_info[line].line = line;
	g_ui_button->line_info[line].mode = mode;
	g_ui_button->line_info[line].len = fat_get_unicode_size(show)/2-1;
}
/*
 * format --0 GB2312/ASCII  --1 UTF8
 */
static bool display_name(int line, char *value, int mode, bool force)
{
	bool is_exceed;
	memset(song_show, 0, INFO_LEN*sizeof(WORD));
	fat_utf8_to_unicode(value, song_show, MAX_STRING_LEN);
	is_exceed = lcd_display(0, line, song_show, mode, fat_get_unicode_size(song_show)/2);
	if ((mode == 1 && is_exceed) || (force && is_exceed)) {
		reserv_display(line, song_show, mode);
	}
	else {
		g_ui_button->line_info[line].line = -1;
	}
}

bool display_line_info(int line, char *info, int mode, bool force)
{
	display_name(line, info, mode, force);
}

void display_clear(void)
{
	int i;
	for (i=0; i<LIST_LINE_MAX; ++i) {
		memset(g_ui_button->line_info[i].value, 0, INFO_LEN * sizeof(WORD));
		g_ui_button->line_info[i].value_pos = NULL;
		g_ui_button->line_info[i].line = -1;
	}
	lcd_clear();
}

int sl_ui_show_info()
{
	int i;
	char *string = NULL;

#if 0//def CONFIG_SYSTEM_AIRPLAY
	player_get_info(&player_info);
	do {
		if((player_info.ui_media == MEDIA_AIRPLAY) && (false == is_showing_list)) {
			char text[INFO_LEN];
			memset(text, 0, INFO_LEN);
			memcpy(text, swa_airplay_gettrackinfo(), strlen(swa_airplay_gettrackinfo()));
			memset(song_tag, 0, INFO_LEN);
			memcpy(song_tag, text, strlen(text));
			display_line_info(NAME_LINE, song_tag, 0, false);
		}
	}while(0);
#endif

	for (i=0; i<LIST_LINE_MAX; ++i) {
		if(g_ui_button->line_info[i].line == i) {
			lcd_display(0, g_ui_button->line_info[i].line, g_ui_button->line_info[i].value_pos, g_ui_button->line_info[i].mode, g_ui_button->line_info[i].len);
			(g_ui_button->line_info[i].value_pos)++;
			g_ui_button->line_info[i].len --;
			if (g_ui_button->line_info[i].len == 0) {
				g_ui_button->line_info[i].len = fat_get_unicode_size(g_ui_button->line_info[i].value)/2;
				g_ui_button->line_info[i].value_pos = g_ui_button->line_info[i].value;
			}
		}
	}

}

int sl_ui_show_init(void)
{
	int i = 0;
	for (i=0; i<LIST_LINE_MAX; ++i) {
		memset(g_ui_button->line_info[i].value, 0, INFO_LEN * sizeof(WORD));
		g_ui_button->line_info[i].value_pos = NULL;
		g_ui_button->line_info[i].line = -1;
		g_ui_button->line_info[i].mode = 0;
	}
}

int show_dialog_name(struct dialog_info *pre_ui_dialog)
{
	int i;
	struct dialog_info *tmp_ui_dialog = NULL;
	struct dialog_item *item = pre_ui_dialog->item_info;
	for (i=0; i<g_list_cur; ++i) {
		item = item->prev;  
	}
#ifdef SL_UI_DBG
	printf("%s %d dialog:0x%x\n", __func__, __LINE__, pre_ui_dialog);
#endif
	for (i=0; i<g_list_max; ++i) {
		if (NULL == item) {
			printf("%s %d item not match g_list_max:%d, i:%d\n", __func__, __LINE__, g_list_max, i); 
			return -SL_UI_ERROR_MAX_MATCH;
		}
		tmp_ui_dialog = (struct dialog_info *)item->userdata;
		if (g_list_cur == i)
			display_line_info(i, tmp_ui_dialog->e_name, 1, false);
		else 
			display_line_info(i, tmp_ui_dialog->e_name, 0, false);
		item = item->next;
	}
	return 	SL_UI_ERROR_NULL;
}

int show_tmp_dialog_name(struct dialog_info *ui_dialog)
{
	char txt_info [VALUE_LEN];
	sprintf(txt_info, "%s", ui_dialog->e_name);
	display_line_info(MEDIA_LINE, txt_info, 0, false);
	return SL_UI_ERROR_NULL;
}

int show_wireless(struct dialog_info *pre_ui_dialog)
{
	int ret;
	ret = show_normal_music(pre_ui_dialog, NULL);
	return ret;
}

int show_logo(void)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	display_clear();
	display_line_info(LOGO_LINE, logo_name, 0, false);
}

int show_list_val_init(int max)
{
	g_list_cur = 0;
	if(max < LIST_LINE_MAX)
		g_list_max = max;
	else
		g_list_max = LIST_LINE_MAX;

}
