#include "sl_ui_struct.h"
#include "sl_ui_show.h"
#include "sl_ui_local.h"
#include "sl_ui_post.h"
#include "sl_ui_action.h"

struct dialog_info dialog_mode_tbl[SL_UI_DIALOG_TYPE_MODE_MAX] =
{
	{"mode_source", 	NULL,   show_dialog_name, 	NULL, 	NULL,		NULL,   SL_UI_DIALOG_TYPE_MODE_MAX,     true,   false,  false},	
	{"mode_play", 		NULL,   show_dialog_name, 	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_MODE_MAX,     true,   false,  false},	
#ifdef CONFIG_WIRELESS
	{"mode_net", 		NULL,   show_dialog_name, 	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_MODE_MAX,     true,   false,  false},	
#endif
#ifdef CONFIG_PM
	{"mode_lpm", 		NULL,   show_dialog_name, 	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_MODE_MAX,     true,   false,  false},	
	{"mode_freq", 		NULL,   show_dialog_name, 	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_MODE_MAX,     true,   false,  false},	
	{"mode_power", 		NULL,   show_dialog_name, 	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_MODE_MAX,     true,   false,  false},	
#endif
#ifdef CONFIG_RTC
	{"mode_alarm",		NULL,   show_dialog_name, 	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_MODE_MAX,     true,   false,  false},	
#endif
#ifdef CONFIG_SYSTEM_AVS
	{"mode_avs",		NULL,   show_dialog_name, 	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_MODE_MAX,     true,   false,  false},	
#endif
};

struct dialog_info dialog_source_tbl[SL_UI_DIALOG_TYPE_SOURCE_MAX] =
{
	{"source_local", 	NULL,   show_dialog_name, 	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_SOURCE_MAX,       true,   false,  false},	
	{"source_linein", 	NULL,   show_dialog_name, 	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_SOURCE_MAX,       true,   false,  false},	
#ifdef CONFIG_SPDIFIN
	{"source_spdifin", 	NULL,   show_dialog_name, 	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_SOURCE_MAX,       true,   false,  false},	
#endif
#ifdef CONFIG_CEC
	{"source_hdmi", 	NULL,   show_dialog_name, 	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_SOURCE_MAX,       true,   false,  false},	
#endif
#ifdef CONFIG_WIRELESS
	{"source_radio", 	NULL,   show_dialog_name, 	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_SOURCE_MAX,       true,   false,  false},	
#endif
#ifdef CONFIG_SYSTEM_UI_ROMFS
	{"source_mix", 		NULL,   show_dialog_name, 	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_SOURCE_MAX,       true,   false,  false},	
#endif
};

struct dialog_info dialog_linein_tbl[SL_UI_DIALOG_TYPE_LINEIN_MAX] = 
{
	{"linein_on", 	NULL,   show_dialog_name,	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_LINEIN_MAX,     true,   false,   false},
	{"linein_off", 	NULL,   show_dialog_name,	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_LINEIN_MAX,     true,   false,   false},
};

struct dialog_info dialog_lineinon_tbl[SL_UI_DIALOG_TYPE_LINEINON_MAX] = 
{
	{"lineinon", 	NULL,  show_tmp_dialog_name,	action_linein_on,   NULL,		NULL,   SL_UI_DIALOG_TYPE_LINEINON_MAX,     true,   true,   false},
};

struct dialog_info dialog_lineinoff_tbl[SL_UI_DIALOG_TYPE_LINEINOFF_MAX] = 
{
	{"lineinoff", 	NULL,   show_tmp_dialog_name,	action_linein_off,   NULL,		NULL,   SL_UI_DIALOG_TYPE_LINEINOFF_MAX,     true,   true,   false},
};

#ifdef CONFIG_SPDIFIN
struct dialog_info dialog_spdifin_tbl[SL_UI_DIALOG_TYPE_SPDIFIN_MAX] = 
{
	{"spdifin_on", 	NULL,   show_dialog_name,	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_SPDIFIN_MAX,     true,   false,   false},
	{"spdifin_off",	NULL,   show_dialog_name,	NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_SPDIFIN_MAX,     true,   false,   false},
};

struct dialog_info dialog_spdifinon_tbl[SL_UI_DIALOG_TYPE_SPDIFINON_MAX] = 
{
	{"spdifinon", 	NULL,   show_tmp_dialog_name,		action_spdifin_on,   NULL,		NULL,   SL_UI_DIALOG_TYPE_SPDIFINON_MAX,     true,   true,   false},
};

struct dialog_info dialog_spdifinoff_tbl[SL_UI_DIALOG_TYPE_SPDIFINOFF_MAX] = 
{
	{"spdifinoff", 	NULL,   show_tmp_dialog_name,		action_spdifin_off,   NULL,		NULL,   SL_UI_DIALOG_TYPE_SPDIFINOFF_MAX,     true,   true,   false},
};
#endif

#ifdef CONFIG_CEC
struct dialog_info dialog_hdmi_tbl[SL_UI_DIALOG_TYPE_HDMI_MAX] = 
{
	{"hdmi_on", 	NULL,   show_dialog_name,		NULL,   NULL,	NULL,   SL_UI_DIALOG_TYPE_HDMI_MAX,     true,   false,   false},
	{"hdmi_off",	NULL,   show_dialog_name,		NULL,   NULL,   NULL,   SL_UI_DIALOG_TYPE_HDMI_MAX,     true,   false,   false},
       {"hdmi_standby",	NULL,   show_dialog_name,	NULL,   NULL,   NULL,   SL_UI_DIALOG_TYPE_HDMI_MAX,     true,   false,   false},
       {"hdmi_pwron",	NULL,   show_dialog_name,	NULL,   NULL,   NULL,   SL_UI_DIALOG_TYPE_HDMI_MAX,     true,   false,   false},
};

struct dialog_info dialog_hdmion_tbl[SL_UI_DIALOG_TYPE_HDMION_MAX] = 
{
	{"hdmion", 	NULL,   show_tmp_dialog_name,		action_hdmi_on,   NULL,		NULL,   SL_UI_DIALOG_TYPE_HDMION_MAX,     true,   true,   false},
};

struct dialog_info dialog_hdmioff_tbl[SL_UI_DIALOG_TYPE_HDMIOFF_MAX] = 
{
	{"hdmioff", NULL,   show_tmp_dialog_name,	    action_hdmi_off,   NULL,	NULL,   SL_UI_DIALOG_TYPE_HDMIOFF_MAX,     true,   true,   false},
};

struct dialog_info dialog_hdmistby_tbl[SL_UI_DIALOG_TYPE_HDMISTANDBY_MAX] = 
{
	{"hdmistby", 	NULL,   show_tmp_dialog_name,		action_hdmi_standby,   NULL,		NULL,   SL_UI_DIALOG_TYPE_HDMISTANDBY_MAX,     true,   true,   false},
};

struct dialog_info dialog_hdmipowon_tbl[SL_UI_DIALOG_TYPE_HDMIPOWERON_MAX] = 
{
	{"hdmipwron", NULL,   show_tmp_dialog_name,	    action_hdmi_poweron,   NULL,	NULL,   SL_UI_DIALOG_TYPE_HDMIPOWERON_MAX,     true,   true,   false},
};
#endif

#ifdef CONFIG_WIRELESS
struct dialog_info dialog_radio_tbl[SL_UI_DIALOG_TYPE_RADIO_MAX] = 
{
	{"radio_on", 	NULL,   show_dialog_name,		NULL,   NULL,	NULL,   SL_UI_DIALOG_TYPE_RADIO_MAX,     true,   false,   false},
	{"radio_off",	NULL,   show_dialog_name,		NULL,   NULL,   NULL,   SL_UI_DIALOG_TYPE_RADIO_MAX,     true,   false,   false},
};

struct dialog_info dialog_radioon_tbl[SL_UI_DIALOG_TYPE_RADIOON_MAX] = 
{
	{"radioon", 	NULL,   show_tmp_dialog_name,		action_radio_on,   NULL,		NULL,   SL_UI_DIALOG_TYPE_RADIOON_MAX,     true,   true,   false},
};

struct dialog_info dialog_radiooff_tbl[SL_UI_DIALOG_TYPE_RADIOOFF_MAX] = 
{
	{"radiooff",    NULL,   show_tmp_dialog_name,	    action_radio_off,   NULL,	    NULL,   SL_UI_DIALOG_TYPE_RADIOOFF_MAX,     true,   true,   false},
};
#endif

#ifdef CONFIG_SYSTEM_UI_ROMFS
struct dialog_info dialog_mix_tbl[SL_UI_DIALOG_TYPE_MIX_MAX] = 
{
	{"mix_play_on", 	NULL,   show_dialog_name,		NULL,   NULL,	NULL,   SL_UI_DIALOG_TYPE_MIX_MAX,     true,   false,   false},
	{"mix_play_off",	NULL,   show_dialog_name,		NULL,   NULL,   NULL,   SL_UI_DIALOG_TYPE_MIX_MAX,     true,   false,   false},
};

struct dialog_info dialog_mixon_tbl[SL_UI_DIALOG_TYPE_MIXON_MAX] = 
{
	{"mixplayon", 	NULL,   show_dialog_name,		action_mix_on,   NULL,		NULL,   SL_UI_DIALOG_TYPE_MIXON_MAX,     true,   false,   false},
};

struct dialog_info dialog_mixoff_tbl[SL_UI_DIALOG_TYPE_MIXOFF_MAX] = 
{
	{"mixplayoff", 	NULL,   show_tmp_dialog_name,	    	action_mix_off,   NULL,		NULL,   SL_UI_DIALOG_TYPE_MIXOFF_MAX,     true,   true,   false},
};
#endif

#ifdef CONFIG_FAT32_FILELIST
struct dialog_info dialog_local_mode_tbl[SL_UI_DIALOG_TYPE_LOCAL_MODE_MAX] =
{
#ifdef CONFIG_SC6138_SD
	{"local_sd", 	NULL,   show_dialog_name,		action_local_sd, 	NULL, 			NULL,   SL_UI_DIALOG_TYPE_LOCAL_MODE_MAX,       true,   false,  false},	
#endif
#ifdef CONFIG_SILAN_USBHS
	{"local_usb", 	NULL,   show_dialog_name, 		action_local_usb,   NULL, 			NULL,   SL_UI_DIALOG_TYPE_LOCAL_MODE_MAX,       true,   false,  false},	
#endif
};

#ifdef CONFIG_SC6138_SD
struct dialog_info dialog_local_sd_tbl[SL_UI_DIALOG_TYPE_SD_MODE_MAX] =
{
	{"sd_file", 	NULL,   show_dialog_name, 		NULL, 	NULL, 			NULL,   SL_UI_DIALOG_TYPE_SD_MODE_MAX,       true,   false,  false},	
	{"sd_folder", 	NULL,   show_dialog_name, 		NULL,   NULL, 			NULL,   SL_UI_DIALOG_TYPE_SD_MODE_MAX,       true,   false,  false},	
};
#endif

#ifdef CONFIG_SILAN_USBHS
struct dialog_info dialog_local_usb_tbl[SL_UI_DIALOG_TYPE_USB_MODE_MAX] =
{
	{"usb_file", 	NULL,   show_dialog_name, 		NULL, 	NULL, 			NULL,   SL_UI_DIALOG_TYPE_USB_MODE_MAX,       true,   false,  false},	
	{"usb_folder", 	NULL,   show_dialog_name, 		NULL,   NULL, 			NULL,   SL_UI_DIALOG_TYPE_USB_MODE_MAX,       true,   false,  false},	
};
#endif
#endif

struct dialog_info dialog_play_tbl[SL_UI_DIALOG_TYPE_PLAY_MAX] =
{
	{"play_repeat_once", 	NULL,   show_dialog_name,	    NULL, 		NULL,		NULL,   SL_UI_DIALOG_TYPE_PLAY_MAX,     true,   false,  false},
	{"play_repeat_all", 	NULL,   show_dialog_name,	    NULL,		NULL, 		NULL,   SL_UI_DIALOG_TYPE_PLAY_MAX,     true,   false,  false},
};

#ifdef CONFIG_WIRELESS
struct dialog_info dialog_net_tbl[SL_UI_DIALOG_TYPE_NET_MAX] =
{
	{"net", 	NULL,   show_tmp_dialog_name,	    action_net, 		NULL,		NULL,   SL_UI_DIALOG_TYPE_NET_MAX,     true,   true,  false},
};
#endif

#ifdef CONFIG_PM
struct dialog_info dialog_lpm_tbl[SL_UI_DIALOG_TYPE_LPM_MAX] =
{
	{"lpm", 	NULL,   show_tmp_dialog_name,	    action_lpm, 		NULL,		NULL,   SL_UI_DIALOG_TYPE_LPM_MAX,     true,   true,  false},
};

struct dialog_info dialog_freq_tbl[SL_UI_DIALOG_TYPE_FREQ_MAX] =
{
	{"freq", 	NULL,   show_tmp_dialog_name,	    action_freq, 		NULL,		NULL,   SL_UI_DIALOG_TYPE_FREQ_MAX,     true,   true,  false},
};

struct dialog_info dialog_power_tbl[SL_UI_DIALOG_TYPE_POWER_MAX] =
{
	{"power", 	NULL,   show_tmp_dialog_name,	    action_power, 		NULL,		NULL,   SL_UI_DIALOG_TYPE_POWER_MAX,     true,   true,  false},
};
#endif

#ifdef CONFIG_RTC
struct dialog_info dialog_alarm_tbl[SL_UI_DIALOG_TYPE_ALARM_MAX] = 
{
	{"alarm_on", 	NULL,   show_dialog_name,		NULL,   NULL,	NULL,   SL_UI_DIALOG_TYPE_ALARM_MAX,     true,   false,   false},
	{"alarm_off",	NULL,   show_dialog_name,		NULL,   NULL,   NULL,   SL_UI_DIALOG_TYPE_ALARM_MAX,     true,   false,   false},
};

struct dialog_info dialog_alarmon_tbl[SL_UI_DIALOG_TYPE_ALARMON_MAX] = 
{
	{"alarmon", 	NULL,   show_tmp_dialog_name,		action_alarm_on,   NULL,		NULL,   SL_UI_DIALOG_TYPE_ALARMON_MAX,     true,   true,   false},
};

struct dialog_info dialog_alarmoff_tbl[SL_UI_DIALOG_TYPE_ALARMOFF_MAX] = 
{
	{"alarmoff", NULL,   show_tmp_dialog_name,	    action_alarm_off,   NULL,	NULL,   SL_UI_DIALOG_TYPE_ALARMOFF_MAX,     true,   true,   false},
};
#endif

#ifdef CONFIG_SYSTEM_AVS
struct dialog_info dialog_avs_tbl[SL_UI_DIALOG_TYPE_AVS_MAX] = 
{
	{"avs", 	NULL,   show_tmp_dialog_name,		action_avs,   NULL,		NULL,   SL_UI_DIALOG_TYPE_AVS_MAX,     true,   true,   false},
};

#endif

#ifdef CONFIG_WIRELESS
struct dialog_info dialog_wireless_tbl[SL_UI_DIALOG_TYPE_WIRE_MAX] = 
{
	{"wireless", 	NULL,   show_wireless,		NULL,   reset_music,		NULL,   SL_UI_DIALOG_TYPE_WIRE_MAX,     true,   false,   true},
};
#endif

struct dialog_info dialog_stop_tbl[SL_UI_DIALOG_TYPE_STOP_MAX] = 
{
	{"stop", 	NULL,   show_tmp_dialog_name,		NULL,   NULL,		NULL,   SL_UI_DIALOG_TYPE_STOP_MAX,     true,   true,   false},
};

struct dialog_info dialog_next_tbl[SL_UI_DIALOG_TYPE_NEXT_MAX] = 
{
	{"next", 	NULL,   NULL,		action_next,   reset_music,		NULL,   SL_UI_DIALOG_TYPE_NEXT_MAX,     true,   false,   true},
};

struct dialog_info dialog_prev_tbl[SL_UI_DIALOG_TYPE_PREV_MAX] = 
{
	{"prev", 	NULL,   NULL,		action_prev,   reset_music,		NULL,   SL_UI_DIALOG_TYPE_PREV_MAX,     true,   false,   true},
};

struct dialog_info dialog_pause_tbl[SL_UI_DIALOG_TYPE_PAUSE_MAX] = 
{
	{"pause", 	NULL,   show_tmp_dialog_name,		action_pause,   NULL,		NULL,   SL_UI_DIALOG_TYPE_PAUSE_MAX,     true,   true,   false},
};

struct dialog_info dialog_resume_tbl[SL_UI_DIALOG_TYPE_RESUME_MAX] = 
{
	{"resume", 	NULL,   show_tmp_dialog_name,		action_resume,   NULL,		NULL,   SL_UI_DIALOG_TYPE_RESUME_MAX,     true,   true,   false},
};

//post
struct dialog_info dialog_vol_up_tbl[SL_UI_DIALOG_TYPE_VOL_UP_MAX] = 
{
	{"volume_up", 	NULL,   show_volume_up,				action_volume_up,   NULL,		NULL,   SL_UI_DIALOG_TYPE_VOL_UP_MAX,     true,   true,   false},
};

struct dialog_info dialog_vol_dn_tbl[SL_UI_DIALOG_TYPE_VOL_DN_MAX] = 
{
	{"volume_dn", 	NULL,   show_volume_dn,				action_volume_dn,   NULL,		NULL,   SL_UI_DIALOG_TYPE_VOL_DN_MAX,     true,   true,   false},
};

struct dialog_info *get_mode_tbl(void)
{
	return dialog_mode_tbl;
}

struct dialog_info *get_play_tbl(void)
{
	return dialog_play_tbl;
}

#ifdef CONFIG_WIRELESS
struct dialog_info *get_net_tbl(void)
{
	return dialog_net_tbl;
}
#endif

#ifdef CONFIG_PM
struct dialog_info *get_lpm_tbl(void)
{
	return dialog_lpm_tbl;
}

struct dialog_info *get_freq_tbl(void)
{
	return dialog_freq_tbl;
}

struct dialog_info *get_power_tbl(void)
{
	return dialog_power_tbl;
}
#endif

#ifdef CONFIG_RTC
struct dialog_info *get_alarm_tbl(void)
{
	return dialog_alarm_tbl;
}

struct dialog_info *get_alarmon_tbl(void)
{
	return dialog_alarmon_tbl;
}

struct dialog_info *get_alarmoff_tbl(void)
{
	return dialog_alarmoff_tbl;
}
#endif

#ifdef CONFIG_SYSTEM_AVS
struct dialog_info *get_avs_tbl(void)
{
	return dialog_avs_tbl;
}
#endif

struct dialog_info *get_source_tbl(void)
{
	return dialog_source_tbl;
}

struct dialog_info *get_linein_tbl(void)
{
	return dialog_linein_tbl;
}

struct dialog_info *get_lineinon_tbl(void)
{
	return dialog_lineinon_tbl;
}

struct dialog_info *get_lineinoff_tbl(void)
{
	return dialog_lineinoff_tbl;
}

#ifdef CONFIG_SPDIFIN
struct dialog_info *get_spdifin_tbl(void)
{
	return dialog_spdifin_tbl;
}

struct dialog_info *get_spdifinon_tbl(void)
{
	return dialog_spdifinon_tbl;
}

struct dialog_info *get_spdifinoff_tbl(void)
{
	return dialog_spdifinoff_tbl;
}
#endif

#ifdef CONFIG_CEC
struct dialog_info *get_hdmi_tbl(void)
{
	return dialog_hdmi_tbl;
}

struct dialog_info *get_hdmion_tbl(void)
{
	return dialog_hdmion_tbl;
}

struct dialog_info *get_hdmioff_tbl(void)
{
	return dialog_hdmioff_tbl;
}

struct dialog_info *get_hdmistby_tbl(void)
{
	return dialog_hdmistby_tbl;
}

struct dialog_info *get_hdmipowon_tbl(void)
{
	return dialog_hdmipowon_tbl;
}
#endif

#ifdef CONFIG_SYSTEM_UI_ROMFS
struct dialog_info *get_mix_tbl(void)
{
	return dialog_mix_tbl;
}

struct dialog_info *get_mixon_tbl(void)
{
	return dialog_mixon_tbl;
}

struct dialog_info *get_mixoff_tbl(void)
{
	return dialog_mixoff_tbl;
}
#endif

#ifdef CONFIG_WIRELESS
struct dialog_info *get_radio_tbl(void)
{
	return dialog_radio_tbl;
}

struct dialog_info *get_radioon_tbl(void)
{
	return dialog_radioon_tbl;
}

struct dialog_info *get_radiooff_tbl(void)
{
	return dialog_radiooff_tbl;
}
#endif

#ifdef CONFIG_FAT32_FILELIST
struct dialog_info *get_local_mode_tbl(void)
{
	return dialog_local_mode_tbl;
}
 
#ifdef CONFIG_SC6138_SD
struct dialog_info *get_local_sd_tbl(void)
{
	return dialog_local_sd_tbl;
}
#endif

#ifdef CONFIG_SILAN_USBHS
struct dialog_info *get_local_usb_tbl(void)
{
	return dialog_local_usb_tbl;
}
#endif
#endif

#ifdef CONFIG_WIRELESS
struct dialog_info *get_wireless_tbl(void)
{
	return dialog_wireless_tbl;
}
#endif

struct dialog_info *get_stop_tbl(void)
{
	return dialog_stop_tbl;
}

struct dialog_info *get_next_tbl(void)
{
	return dialog_next_tbl;
}

struct dialog_info *get_prev_tbl(void)
{
	return dialog_prev_tbl;
}

struct dialog_info *get_pause_tbl(void)
{
	return dialog_pause_tbl;
}

struct dialog_info *get_resume_tbl(void)
{
	return dialog_resume_tbl;
}

struct dialog_info *get_vol_up_tbl(void)
{
	return dialog_vol_up_tbl;
}

struct dialog_info *get_vol_dn_tbl(void)
{
	return dialog_vol_dn_tbl;
}

static int dialog_tbl_member_free(struct dialog_info *ui_dialog)
{
	if (NULL != ui_dialog->param) {
		free(ui_dialog->param);
		ui_dialog->param = NULL;
	}
	if (NULL != ui_dialog->item_info) {
		free(ui_dialog->item_info);
		ui_dialog->item_info = NULL;
	}
}

int dialog_tbl_free(void)
{
	dialog_tbl_member_free(dialog_mode_tbl);
	dialog_tbl_member_free(dialog_source_tbl);
#ifdef CONFIG_FAT32_FILELIST
	dialog_tbl_member_free(dialog_local_mode_tbl);
#endif
	dialog_tbl_member_free(dialog_play_tbl);
	return 	SL_UI_ERROR_NULL;
}
