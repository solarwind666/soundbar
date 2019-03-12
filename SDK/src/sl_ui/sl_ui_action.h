#ifndef SL_UI_ACTION_H__
#define SL_UI_ACTION_H__

int action_linein_on(struct dialog_info *ui_dialog);
int action_linein_off(struct dialog_info *ui_dialog);
#ifdef CONFIG_SPDIFIN
int action_spdifin_on(struct dialog_info *ui_dialog);
int action_spdifin_off(struct dialog_info *ui_dialog);
#endif
#ifdef CONFIG_CEC
int action_hdmi_on(struct dialog_info *ui_dialog);
int action_hdmi_off(struct dialog_info *ui_dialog);
int action_hdmi_standby(struct dialog_info *ui_dialog);
int action_hdmi_poweron(struct dialog_info *ui_dialog);
#endif
#ifdef CONFIG_WIRELESS
int action_radio_on(struct dialog_info *ui_dialog);
int action_radio_off(struct dialog_info *ui_dialog);
#endif
#ifdef CONFIG_SYSTEM_UI_ROMFS
int action_mix_on(struct dialog_info *ui_dialog);
int action_mix_off(struct dialog_info *ui_dialog);
#endif
#ifdef CONFIG_WIRELESS
int action_net(struct dialog_info *ui_dialog);
#endif
#ifdef CONFIG_PM
int action_lpm(struct dialog_info *ui_dialog);
int action_freq(struct dialog_info *ui_dialog);
int action_power(struct dialog_info *ui_dialog);
#endif
#ifdef CONFIG_RTC
int action_alarm_on(struct dialog_info *ui_dialog);
int action_alarm_off(struct dialog_info *ui_dialog);
#endif
#ifdef CONFIG_SYSTEM_AVS
int action_avs(struct dialog_info *ui_dialog);
#endif
int action_next(struct dialog_info *ui_dialog);
int action_prev(struct dialog_info *ui_dialog);
int action_pause(struct dialog_info *ui_dialog);
int action_resume(struct dialog_info *ui_dialog);
int reset_music(struct dialog_info *ui_dialog);

#endif
