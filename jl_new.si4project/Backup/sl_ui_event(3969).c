#include <nuttx/config.h>
#include <nuttx/input.h>
#include <nuttx/module.h>
#include <pthread.h>
#include <stdio.h>

#include "nxplayer.h"
#include "player_cmd.h"
#include "sl_ui_struct.h"
#include "sl_ui_cmd.h"
#include "sl_ui_sys.h"

#ifdef CONFIG_BOARD_AP_5864B
#define	 CMD_UI_UP		(1<<4 | 1)
#define  CMD_UI_OK      (1<<4 | 2)
#define	 CMD_UI_DOWN	(1<<4 | 4)
#define  CMD_UI_REC     (1<<4 | 5)
#define  CMD_UI_POWER   (1<<4 | 6)
#else

#define  CMD_UI_VOL_INC 0
#define  CMD_UI_VOL_DEC 1
#define  CMD_UI_PLAY_PAUSE	2

#define  CMD_UI_UP      11
#define  CMD_UI_OK      21
#define  CMD_UI_DOWN    41
#define  CMD_UI_REC     51
#define  CMD_UI_FUNC    61
#define  CMD_UI_MODE    71
#define  CMD_UI_EQ      81
#define  CMD_UI_PREV    91
#define  CMD_UI_NEXT    92

#endif
bool is_start_to_update = false;

static void handle_ui_events_inner(struct input_event *event);

#define	UI_EVENT_BACKUP_MAX	4
extern struct button_info	*g_ui_button;
struct ui_input_event {
	bool should_resend;
	struct input_event event;
};
static struct ui_input_event ui_event_bk[UI_EVENT_BACKUP_MAX];

static int ui_eventbk_init(void)
{
	int i;
	for (i=0; i<UI_EVENT_BACKUP_MAX; i++) {
		ui_event_bk[i].should_resend = false;
	}
	return 0;
}

static bool ui_event_restore(struct input_event *event)
{
	int i;
	for (i=0; i<UI_EVENT_BACKUP_MAX; i++) {
		if(ui_event_bk[i].should_resend == true) {
			if ((event->type == ui_event_bk[i].event.type) && (event->code == ui_event_bk[i].event.code) && (event->value == ui_event_bk[i].event.value))
				break;
			else
				continue;
		}
	}
	if (i < UI_EVENT_BACKUP_MAX) {
		printf("ui event already backup%d %d %d\n", event->type, event->code, event->value);
		return false;
	}
	for (i=0; i<UI_EVENT_BACKUP_MAX; i++) {
		if(ui_event_bk[i].should_resend == false) {
			memcpy(&(ui_event_bk[i].event), event, sizeof(struct input_event));
			ui_event_bk[i].should_resend = true;
			break;
		}
	}
	if (i == UI_EVENT_BACKUP_MAX) {
		printf("ui event backup has full %d %d %d\n", event->type, event->code, event->value);
		return false;
	}
	else
		return true;
}

static void ui_event_check_done(void)
{
	int  i;
	struct input_event *event;
	for (i=0; i<UI_EVENT_BACKUP_MAX; i++) {
		if(ui_event_bk[i].should_resend == true) {
			ui_event_bk[i].should_resend = false;
			event = &(ui_event_bk[i].event);
			handle_ui_events_inner(event);
		}
	}
}

static ui_cmd_t ui_handle_click(int event_cmd)
{
	ui_cmd_t cmd;
    memset(&cmd, 0, sizeof(ui_cmd_t));
	cmd.cmd = UI_CMD_NULL;
	switch(event_cmd & 0x0f) {
		case  CMD_UI_VOL_INC:
			cmd.cmd = UI_CMD_BT_UP;
			break;
		case  CMD_UI_PLAY_PAUSE:
			cmd.cmd = UI_CMD_BT_MODE; //UI_CMD_BT_OK;
			break;
		case  CMD_UI_VOL_DEC:
			cmd.cmd = UI_CMD_BT_DOWN;
			break;
	}

	return cmd;
}

static ui_cmd_t ui_handle_long_press(int event_cmd)
{
	ui_cmd_t cmd;
    memset(&cmd, 0, sizeof(ui_cmd_t));
	cmd.cmd = UI_CMD_NULL;
    printf("%s %d event_cmd:%d\n", __func__, __LINE__, event_cmd);
    switch (event_cmd) {
		case  CMD_UI_UP:
			break;
		case  CMD_UI_DOWN:
			break;
		case  CMD_UI_OK:
			break;
		case  CMD_UI_REC:
			break;
#ifdef CONFIG_BOARD_AP_5864B
		case CMD_UI_POWER:
			cmd.cmd = UI_CMD_NET_JOIN;
			break;
#else
		case  CMD_UI_PREV:
			break;
		case  CMD_UI_NEXT:
			break;
		case  CMD_UI_FUNC:
			break;
		case  CMD_UI_MODE:
			break;
		case  CMD_UI_EQ:
			break;
#endif
    }
    return cmd;
}

#define CONFIG_AUTO_UPDATE

#ifdef CONFIG_AUTO_UPDATE
static bool is_updating = false;
static pthread_addr_t update_local(pthread_addr_t arg)
{
	int ret;
	bool reboot = false;	
	//ui_led_disp_upload(5);
	is_start_to_update = true;
	printf("%s %d\n", __func__, __LINE__);
	if (is_updating) {
		ret = silan_update_safe(reboot);
		is_start_to_update = false;
		//ui_led_disp_upload(0);
		/*
		if (0 == ret) {
			board_reset(0);
		}
		*/
	}
}
#endif

static void handle_ui_events_inner(struct input_event *event)
{
	ui_cmd_t cmd;
    memset(&cmd, 0, sizeof(ui_cmd_t));
#ifdef CONFIG_AUTO_UPDATE
	char name[32];
#endif
	cmd.cmd = UI_CMD_NULL;

	printf("%s %d 0x%x %d %d\n", __func__, __LINE__, event->type, event->code, event->value);
	if (EV_KEY == event->type) {
		switch (event->code) {
				case 0x8004:
				case CODE_KEY_UP:
					{
						int val = event->value & 0xff;
						if(val == CMD_UI_VOL_INC)
						{
							cmd.cmd = UI_CMD_VOLUME_INC_UP;
						}
						else if(val == CMD_UI_VOL_DEC)
						{
							cmd.cmd = UI_CMD_VOLUME_DEC_UP;
						}
					}
					break;
				case CODE_KEY_DOWN:
					{
						int val = event->value & 0xff;
						printf("press:%x\n", val);
						if(val == CMD_UI_VOL_INC)
						{
							cmd.cmd = UI_CMD_VOLUME_INC_DOWN;
						}
						else if(val == CMD_UI_VOL_DEC)
						{
							cmd.cmd = UI_CMD_VOLUME_DEC_DOWN;
						}

					}
					break;
				case CODE_KEY_CLICK:
					cmd = ui_handle_click(event->value);
					break;
			}

	}
	else if (EV_BT == event->type) {
		switch (event->code) {
			case CODE_BT_PHONE_IN: 
				cmd.cmd = UI_CMD_BT_PHONE_IN;
				break;
			case CODE_BT_VOICE_CONNECT:
				cmd.cmd = UI_CMD_BT_VOICE_CONNECT;
				break;
			case CODE_BT_VOICE_DISCONNECT:
				cmd.cmd = UI_CMD_BT_VOICE_DISCONNECT;
				break;
		}
	}
	else if (EV_PLAYER == event->type) {
		switch (event->code) {
			case CODE_PLAYER_PLAY_FINISH:
				cmd.cmd =UI_CMD_PLAYER_FINISH;
				break;
			case CODE_PLAYER_TONE_FINISH:
				cmd.cmd = UI_CMD_PLAYER_TONE_FINISH;
				break;
			case CODE_PLAYER_REPORT_VOLUME:
				cmd.cmd = NP_CMD_VOLUME_SET;
				cmd.arg2 = event->value;
				break;
			case CODE_PLAYER_BUFFER_LOW:
				cmd.cmd = UI_CMD_BUFFERING;
				break;
			case CODE_PLAYER_RECORD_ON:
				cmd.cmd = NP_CMD_RECORD_ON;
				break;
			case CODE_PLAYER_RECORD_OFF:
				cmd.cmd = NP_CMD_RECORD_OFF;
				break;
			case CODE_PLAYER_PLAY_STOP:
				cmd.cmd = NP_CMD_STOP;
				break;
		}
	}
	else if (EV_FSYS == event->type) {
		switch (event->code) {
			case CODE_FSYS_UPDATE_FILE:	
#ifdef CONFIG_AUTO_UPDATE
				if (is_updating) {
					if(event->value == VALUE_SUCCESS) { pthread_t tid;
						pthread_create(&tid, NULL, update_local, NULL);
						pthread_detach(tid);
					}
					else if (event->value == VALUE_FAIL) {
						printf("check update file failed\n");
						is_updating = false;
					}
				}
#endif
				break;
		}
	}
	else if (EV_USB == event->type) {
		switch (event->code) {
			/*
			case CODE_USB_IO_RESET:
				break;
			case CODE_USB_EMU_TIMEOUT:
				cmd.cmd = UI_CMD_USB_EMU_TIMEOUT;
				printf("silan usb enumrate error!\n");
				break;
				*/
		}
	}
	else if (EV_UI == event->type) {
		switch (event->code)  {
			case CODE_UI_SD_LOAD:
				if (event->value == VALUE_FAIL)
				{	//SD挂接失败
				}
				else if(event->value == VALUE_SUCCESS)
				{	//SD挂接成功
					cmd.cmd = UI_CMD_SD_LOAD;
				}

				break;
			case CODE_UI_SD_IN:
#ifdef CONFIG_AUTO_UPDATE
				is_updating = true;
				silan_check_update_file_save("/media/sd/sd00", "update.binary");
#endif
				cmd.cmd = UI_CMD_SD_IN;
				break;
			case CODE_UI_SD_UNLOAD:
				cmd.cmd = UI_CMD_SD_UNLOAD;

				break;
			case CODE_UI_USB_LOAD:
				if (event->value == VALUE_FAIL)
					;
				else if(event->value == VALUE_SUCCESS)
				{
					cmd.cmd = UI_CMD_USB_LOAD;
				}
				break;
			case CODE_UI_USB_IN:
#ifdef CONFIG_AUTO_UPDATE
				memset(name, 0, 32);
				sprintf(name, "/media/usb/usb0%d", event->value);
				is_updating = true;
				silan_check_update_file_save(name, "update.binary", false);
#endif
				cmd.cmd = UI_CMD_USB_IN;
				cmd.arg2 = event->value;
				break;
			case CODE_UI_USB_UNLOAD:
				if (event->value == VALUE_FAIL)
					cmd.cmd = UI_CMD_USB_OUT;
				break;
			default:
				break;
		}
	}

	if (cmd.cmd != UI_CMD_NULL)
		send_cmd_2_ui(&cmd);
}

static void handle_ui_events(struct input_event *event, void *cb_para)
{
	handle_ui_events_inner(event);
	ui_event_check_done();
}

static int init_sl_ui_event(void)
{
	printf("%s %d\n", __func__, __LINE__);
	ui_eventbk_init();
	ui_cmd_init();
	idjs_event_register(handle_ui_events, NULL);
	return 0;
}
app_entry(init_sl_ui_event)
