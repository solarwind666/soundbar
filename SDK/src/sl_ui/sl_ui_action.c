#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <nuttx/config.h>
#include <nuttx/input.h>
#ifdef CONFIG_CEC
#include <silan_cec.h>
#endif
#ifdef CONFIG_PM
#include <nuttx/power/pm.h>
#endif
#ifdef CONFIG_WIRELESS
#include <nuttx/sys_conf.h>
#endif
#ifdef CONFIG_SYSTEM_UI_ROMFS
#include <nuttx/fs/ramdisk.h>
#include <nuttx/binfmt/binfmt.h>
#include "romfs.h"
#endif
#include "nxplayer.h"
#include "player_cmd.h"
#include "sl_ui_def.h"
#include "sl_ui_cmd.h"
#include "sl_ui_struct.h"
#include "sl_ui_action.h"
#include "sl_ui_sys.h"

struct button_info	*g_ui_button;


int action_linein_on(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	set_sl_ui_cmd(NP_CMD_LINEIN_ON, NULL, 0);
	return SL_UI_ERROR_NULL;
}

int action_linein_off(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	set_sl_ui_cmd(NP_CMD_LINEIN_OFF, NULL, 0);
	return SL_UI_ERROR_NULL;
}

#ifdef CONFIG_SPDIFIN
int action_spdifin_on(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	set_sl_ui_cmd(NP_CMD_SPDIFIN_START, NULL, 4);
	return SL_UI_ERROR_NULL;
}

int action_spdifin_off(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	set_sl_ui_cmd(NP_CMD_SPDIFIN_STOP, NULL, 0);
	return SL_UI_ERROR_NULL;
}
#endif

#if 0
#ifdef CONFIG_CEC
int action_hdmi_on(struct dialog_info *ui_dialog)
{
    int cec_cmd_gpio = 0;  //GPIO1_0
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
     
    cec_process_cmd(CEC_CMD_ARC_INIT,&cec_cmd_gpio);
	cec_process_cmd(CEC_CMD_ARCON, NULL);
	set_sl_ui_cmd(NP_CMD_SPDIFIN_START, NULL, 0);
	return SL_UI_ERROR_NULL;
}

int action_hdmi_off(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
      
	cec_process_cmd(CEC_CMD_ARCOFF, NULL);
	set_sl_ui_cmd(NP_CMD_SPDIFIN_STOP, NULL, 0);
	return SL_UI_ERROR_NULL;
}
int action_hdmi_standby(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
       
	cec_process_cmd(CEC_CMD_STANDBY, NULL);
	set_sl_ui_cmd(NP_CMD_SPDIFIN_STOP, NULL, 0);
	return SL_UI_ERROR_NULL;
}
int action_hdmi_poweron(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
       
    cec_process_cmd(CEC_CMD_ARCON, NULL);
	cec_process_cmd(CEC_CMD_POWERON, NULL);
	
	return SL_UI_ERROR_NULL;
}
#endif

#endif
#ifdef CONFIG_WIRELESS
#define RADIO_URL_LEN_MAX 128
#define RADIO_CHANNEL_MAX 6
static char radio_info[RADIO_CHANNEL_MAX][RADIO_URL_LEN_MAX];

int action_radio_on(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	struct music_dialog_param *param = (struct music_dialog_param *)(ui_dialog->param);
	int i;
	param->total_music = RADIO_CHANNEL_MAX;
	char url_config_info[15];
	if (0 != zhuque_sys_conf_get(SYS_CONF_RADIO_SESSION, url_config_info, RADIO_URL_LEN_MAX, SYS_CONF_STRING, radio_info[0])) {
		char data_in[RADIO_CHANNEL_MAX][RADIO_URL_LEN_MAX] = {
			"http://fdfs.xmcdn.com/group5/M0A/65/9E/wKgDtVTCAKqzIRL2AEatpVPIimM849.mp3",
			"http://fdfs.xmcdn.com/group5/M01/0D/3D/wKgDtVN1Zk2wc0V8AFILd87o9jo558.mp3",
			"http://fdfs.xmcdn.com/group3/M06/C3/90/wKgDslLZK_PiFhB4AEzMIsr2dro787.mp3",
			"http://fdfs.xmcdn.com/group5/M00/4E/2A/wKgDtlOi8MKT8LwbAIJr_8vbwhk908.mp3",
			"http://fdfs.xmcdn.com/group6/M09/26/56/wKgDhFTcBquQDvifABEkV6kY0Mc360.mp3",
			"http://fdfs.xmcdn.com/group1/M00/0C/F0/wKgDrVEqmSjQ-GKnAUBJihIQgJ8955.mp3",
		};
		for (i=0; i<RADIO_CHANNEL_MAX; i++) {
			sprintf(url_config_info, "radio_url%d", i);
			zhuque_sys_conf_set(SYS_CONF_RADIO_SESSION, url_config_info,
					SYS_CONF_STRING, data_in[i]);
		}
	}
	param->cur_music_idx = 0;
	for (i=0; i< RADIO_CHANNEL_MAX; i++) {
		sprintf(url_config_info, "radio_url%d", i);
		zhuque_sys_conf_get(SYS_CONF_RADIO_SESSION, url_config_info,
				RADIO_URL_LEN_MAX, SYS_CONF_STRING, radio_info[i]);
	}
	//player_process_cmd(NP_CMD_PLAY, radio_info[radio_idx], 0, NULL, NULL);
	g_ui_button->player_info.ui_media = MEDIA_RADIO;
	set_sl_ui_cmd(NP_CMD_PLAY, radio_info[param->cur_music_idx], 0);
	return SL_UI_ERROR_NULL;
}

int action_radio_off(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	set_sl_ui_cmd(NP_CMD_STOP, NULL, 0);
	return SL_UI_ERROR_NULL;
}
#endif

#ifdef CONFIG_SYSTEM_UI_ROMFS
static bool first_open = true;
int mp3_idx = 0;
char *music_name[MP3_NAME_NUM] = {"/media/flash/001.mp3", "/media/flash/002.mp3", "/media/flash/003.mp3", "/media/flash/004.mp3", "/media/flash/005.mp3"};

static int dj_start(void)
{

	int ret;
	if (first_open) {
		/* Create a ROM disk for the ROMFS filesystem */
		printf("Registering romdisk\n");

		ret = ramdisk_register(0, (uint8_t*)romfs_img, NSECTORS(romfs_img_len), SECTORSIZE, RDFLAG_WRENABLED);
		if (ret < 0)
		{
			printf("ERROR: romdisk_register failed: %d\n", ret);
			return -1;
		}

		/* Mount the ROMFS file system */

		printf("Mounting ROMFS filesystem at target=%s with source=%s\n",
				ROMFS_MOUNTPT, ROMFSDEV);

		ret = mount(ROMFSDEV, ROMFS_MOUNTPT, "romfs", 0, NULL);
		if (ret < 0)
		{
			printf("ERROR: mount(%s,%s,romfs) failed: %d\n",
					ROMFSDEV, ROMFS_MOUNTPT, errno);
			return -1;
		}
		first_open = false;
	}
	sladsp_mix_channel(1);
	swa_audio_set_i2sin_chan(USE_I2SIN_CH1);
	sladsp_mix_play(NULL, 1, &music_name[mp3_idx]);
}

int action_mix_on(struct dialog_info *ui_dialog)
{
	dj_start();
	g_ui_button->player_info.ui_media = MEDIA_ROMFS;
}

int action_mix_off(struct dialog_info *ui_dialog)
{
	g_ui_button->player_info.ui_media = MEDIA_UNKNOWN;
}
#endif

#ifdef CONFIG_WIRELESS
int action_net(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	input_add_event_ext(EV_SYS, CODE_EASYSETUP, VALUE_NULL);
	return SL_UI_ERROR_NULL;
}
#endif

#ifdef CONFIG_PM
#include <sys/mount.h>
#define STANDBY_DELAY_SEC             10

int action_lpm(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	g_ui_button->state_machine = SL_UI_STATE_MACHINE_LPM;
	set_sl_ui_cmd(NP_CMD_STOP, NULL, 0);

	return SL_UI_ERROR_NULL;
}

int enter_lpm(void)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	int ret, fd;

	ret = SL_UI_ERROR_NULL;
	if (player_is_busy()) {
		printf("%s %d player is busy!!\n", __func__, __LINE__);
		return SL_UI_ERROR_BUSY;
	}
	fd = open(CONFIG_PM_DEV_PATH, O_RDWR);
	if (fd < 0) {
		printf("open /dev/pm error\n");
		return SL_UI_ERROR_OPEN;
	}

#ifdef CONFIG_SILAN_USBHS
	usb_manual_disconnect();
	sysfs_usb_umount();
	silan_usb_task_del();
#endif

	ret = ioctl(fd, PMIOC_ENTERLPM, PM_STANDBY);

	/* update time throld to 60s */
	if (ret != 0) {
		pm_sync(STANDBY_DELAY_SEC);
		close(fd);
	}
	else {
		close(fd);
	}

#ifdef CONFIG_SILAN_USBHS
	//silan_usb_reset();
	silan_usb_initialize();
#endif
	return ret;
}

int action_freq(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	g_ui_button->state_machine = SL_UI_STATE_MACHINE_FREQ;
	set_sl_ui_cmd(NP_CMD_STOP, NULL, 0);

	return SL_UI_ERROR_NULL;
}

int enter_freq(void)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	int ret, fd;
	int freq;

	ret = SL_UI_ERROR_NULL;
	if (player_is_busy()) {
		printf("%s %d player is busy!!\n", __func__, __LINE__);
		return SL_UI_ERROR_BUSY;
	}
	fd = open(CONFIG_PM_DEV_PATH, O_RDWR);
	if (fd < 0) {
		printf("open /dev/pm error\n");
		return SL_UI_ERROR_OPEN;
	}

#ifdef CONFIG_SILAN_USBHS
	usb_manual_disconnect();
	sysfs_usb_umount();
	silan_usb_task_del();
#endif
	
	freq = get_silan_cpuclk();
	printf("%s %d freq:%d\n", __func__, __LINE__, freq);
	if (freq == 300*1000*1000)
		freq = 6*1000*1000;
	else if (freq == 6*1000*1000)
		freq = 300*1000*1000;
	printf("%s %d freq:%d\n", __func__, __LINE__, freq);
	ret = ioctl(fd, PMIOC_DYNAMICFREQ, freq);

printf(",,,,,ret:%d\n", ret);
	/* update time throld to 60s */
	if (ret != 0) {
		pm_sync(STANDBY_DELAY_SEC);
		close(fd);
	}
	else {
		close(fd);
	}

#ifdef CONFIG_SILAN_USBHS
	//silan_usb_reset();
	silan_usb_initialize();
#endif
	return ret;
}

int action_power(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	pm_request(PM_POWEROFF);
}
#endif

#ifdef CONFIG_RTC
static int sl_ui_read_rtc(struct tm *tmtime)
{
    int fd;
    fd = open(RTC_PATH, O_RDWR);
    if (fd < 0)
    {
        printf("open %s error\n", RTC_PATH);
        return SL_UI_ERROR_OPEN;
    }
    ioctl(fd, RTC_RD_TIME, tmtime);

	tmtime->tm_year += 1900;
	tmtime->tm_mon += 1;
	tmtime->tm_hour += 8;
	tmtime->tm_min += 0;

	close(fd);
	return SL_UI_ERROR_NULL;
}

static void user_alarm_player(void)
{
	printf("---------------- %s %d\n", __func__, __LINE__);
	g_ui_button->alarm_is_playing = true;
	em_player_tone(1);
	while (g_ui_button->alarm_is_playing)
		usleep(1000);
	printf("alarm player is done\n");
}

static void user_alarm_process(void)
{
	//user do it .
	user_alarm_player();
}

static pthread_addr_t alarm_process(pthread_addr_t argc)
{
	save_ui_context();
	user_alarm_process();
	g_ui_button->alarm_pid = 0;
	g_ui_button->alarm_stat = SL_UI_ALARM_STAT_NULL;
	restore_ui_context();
}

int check_alarm(void)
{
	struct tm tmtime;
	int ret;
	sl_ui_read_rtc(&tmtime);
#ifdef SL_UI_DBG
    printf("%d/%d/%d %d:%d:%d\n", tmtime.tm_year, tmtime.tm_mon, tmtime.tm_mday, tmtime.tm_hour, tmtime.tm_min, tmtime.tm_sec);
#endif
	if ((g_ui_button->alarm_time.tm_hour == tmtime.tm_hour) && (g_ui_button->alarm_time.tm_min == tmtime.tm_min)) {
		if (g_ui_button->alarm_stat == SL_UI_ALARM_STAT_SET) {
			if (g_ui_button->alarm_pid != 0) {
				restore_ui_context();
				pthread_cancel(g_ui_button->alarm_pid);
			}
			ret = pthread_create(&g_ui_button->alarm_pid, NULL, alarm_process, NULL);
			ret = pthread_detach(g_ui_button->alarm_pid);
			g_ui_button->alarm_stat = SL_UI_ALARM_STAT_EXEC;
		}
	}
	else if ((g_ui_button->alarm_time.tm_hour == tmtime.tm_hour) && ((g_ui_button->alarm_time.tm_min + 1) == tmtime.tm_min)) {
		if (g_ui_button->alarm_stat == SL_UI_ALARM_STAT_EXEC) {
			g_ui_button->alarm_stat = SL_UI_ALARM_STAT_SET;
		}
	}
	return SL_UI_ERROR_NULL;
}

int action_alarm_on(struct dialog_info *ui_dialog)
{
	struct tm tmtime;
	sl_ui_read_rtc(&tmtime);
    printf("%s %d %d/%d/%d %d:%d:%d\n", __func__, __LINE__, tmtime.tm_year, tmtime.tm_mon, tmtime.tm_mday, tmtime.tm_hour, tmtime.tm_min, tmtime.tm_sec);

	g_ui_button->alarm_stat = SL_UI_ALARM_STAT_SET;
	g_ui_button->alarm_time.tm_hour = tmtime.tm_hour;
	g_ui_button->alarm_time.tm_min = tmtime.tm_min+1;
	g_ui_button->alarm_time.tm_sec = tmtime.tm_sec;

	return SL_UI_ERROR_NULL;
}

int action_alarm_off(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	if (g_ui_button->alarm_pid != 0) {
		restore_ui_context();
		pthread_cancel(g_ui_button->alarm_pid);
		g_ui_button->alarm_pid = 0;
		g_ui_button->alarm_stat = SL_UI_ALARM_STAT_NULL;
	}
	return SL_UI_ERROR_NULL;
}
#endif


#ifdef CONFIG_SYSTEM_AVS
#include "avs.h"
int action_avs(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	sys_info_t sys_info;
	sl_ui_get_sys_info(&sys_info);
	printf("%s %d net_stat:%d ", __func__, __LINE__, sys_info.net_stat);
	printf("wifi_sig:%d ", sys_info.wifi_sig);
	printf("cloud_stat:%d ", sys_info.cloud_stat);
	printf("sd_stat:%d\n", sys_info.sd_stat);
#ifndef AVS_PROTO_OLD
	struct avs_cmd_opt_ctrl_s data;
	data.cmd = AVS_OPT_CTRL_ONLINE_PLAY;
	avs_send_cmd(AVS_CMD_OPT_CTRL, &data);
#endif
	return SL_UI_ERROR_NULL;
}
#endif

int action_next(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	set_sl_ui_cmd(NP_CMD_NEXT, NULL, 0);
	return SL_UI_ERROR_NULL;
}

int action_prev(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	set_sl_ui_cmd(NP_CMD_PREV, NULL, 0);
	return SL_UI_ERROR_NULL;
}

int action_pause(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	set_sl_ui_cmd(NP_CMD_PAUSE, NULL, 0);
	return SL_UI_ERROR_NULL;
}

int action_resume(struct dialog_info *ui_dialog)
{
#ifdef SL_UI_DBG
	printf("%s %d\n", __func__, __LINE__);
#endif
	set_sl_ui_cmd(NP_CMD_RESUME, NULL, 0);
	return SL_UI_ERROR_NULL;
}

int reset_music(struct dialog_info *ui_dialog)
{
	((struct music_dialog_param *)(ui_dialog->param))->is_get_tag = false;
	((struct music_dialog_param *)(ui_dialog->param))->is_get_pcm_info = false;
}

