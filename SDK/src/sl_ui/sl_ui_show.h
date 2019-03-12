#ifndef __SL_UI_SHOW_H__
#define __SL_UI_SHOW_H__

#include "sl_ui_struct.h"

extern char *logo_name;
extern int g_list_max;
extern int g_list_cur;

int sl_ui_show_init(void);
int show_dialog_name(struct dialog_info *pre_ui_dialog);
int show_tmp_dialog_name(struct dialog_info *ui_dialog);
int show_wireless(struct dialog_info *pre_ui_dialog);
int show_logo();
int show_list_val_init(int max);

#endif
