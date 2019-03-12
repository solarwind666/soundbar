#ifndef __SL_UI_TABLE_H__
#define __SL_UI_TABLE_H__

#include "sl_ui_struct.h"

extern struct dialog_info *g_dialog_local_usb_tbl;

struct dialog_info *get_mode_tbl();
struct dialog_info *get_play_tbl();
struct dialog_info *get_source_tbl();
struct dialog_info *get_local_tbl();
struct dialog_info *get_local_usb_tbl_template();
int dialog_tbl_free(void);
#endif
