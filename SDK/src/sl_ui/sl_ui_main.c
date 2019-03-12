/****************************************************************************
 * Included Files
 ****************************************************************************/
#include "bt_uart.h"
#include <fcntl.h>
#include <nuttx/module.h>
#include <nuttx/audio/silan_audio_api.h>
#include <nxplayer.h>
#include <mqueue.h>
#include <player_cmd.h>
#include "sl_lcd.h"
#include "sl_ui_cmd.h"
#include "sl_ui_handle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef CONFIG_SYSTEM_AIRPLAY
#include "swa_airplay_api.h"
#endif
#include <termios.h>
#include "vol_ctrl.h"
#include "silan_resources.h"
#include "silan_addrspace.h"
#include <nuttx/audio/sladsp_ae.h>
#include "sl_bsp.h"
#include <silan_adc.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
/*??????????????*/
#define SL_UI_DBG
/*??????*/
#define SLEEP_COUNT 50
#define UI_UPDATE_COUT 5
/*Check sum?????*/
//#define SLUI_MEM_CHECK 1
#define ADC_DETECT_COUT 1
#define EN_ADC_COUT		20
#define TIME_COUNT_100MS  10
/****************************************************************************
 * Public Types
 ****************************************************************************/
/*??§Ü??????????*/
typedef void (exec_func_t)(void);  

/****************************************************************************
 * Public Data
 ****************************************************************************/
//??????????
#ifdef SLUI_MEM_CHECK
static int mem_cnt = 0;
#endif
/*?????????????*/
static bool should_exec = true;
/*?????§á????ID*/
static WDOG_ID wdtimer_exec;
/*ui???????*/
static struct ui_s *Ui = NULL;

//??????
/*??????????*/
int ui_source_select = -1;
int ui_source_ir_select = -1;
/* ???ADC??? ?????????????*/
bool en_adc_detect_flag = false;


//??????
/**/
#ifdef CONFIG_PM
extern pthread_cond_t stop_cond;
#endif
/*??????????????????ID*/
extern WDOG_ID wdtimer_source;
bool is_usb_load=false;
bool is_sd_load=false;


/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/
/*lcd?????????*/
extern int lcd_main(void);
/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: sc6138_exec_handle
 *
 * Description:
 *    ?????§Þ??
 *
 * Parameters:
 *    argc  ????????
 *    arg1  ?????§Ò?
 *    ....  ?????????§Ò?
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static void sc6138_exec_handle(int argc, wdparm_t arg1, ...)
{
    should_exec = true;
    wd_cancel(wdtimer_exec);
}

/****************************************************************************
 * Name: ui_check_on_off_before_exec
 *
 * Description:
 *    ???????????????????§Ø??????
 *
 * Parameters:
 *    func ???§Ö?????????
 *    func_name ???§Ö??????????
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static void ui_check_on_off_before_exec(exec_func_t func, const char * func_name)
{
    if(ui_power == POWER_ON)
    {
        if(NULL != func)
        {
            func();
        }
        else
        {
            printf("%s:No function to be execute\n", __func__);
        }
    }
    else
    {
        printf("%s:Is power off\n", (NULL != func_name)?func_name:__func__);
    }
}

/****************************************************************************
 * Name: ui_handle_cmd
 *
 * Description:
 *    UI?????????
 *
 * Parameters:
 *    cmd  ??????UI????
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static void ui_handle_cmd(ui_cmd_t *cmd)
{
    printf("-------------------- %s:cmd:%d, arg2:%d\n", __func__, cmd->cmd, cmd->arg2);

#ifdef SL_UI_DBG
    printf("%s:ui_power:%d\n", __func__, ui_power);
#endif

    switch (cmd->cmd)
    {
    case UI_CMD_STOP:
#ifdef CONFIG_PM
        pthread_cond_signal(&stop_cond);
#endif
        break;
    case UI_CMD_PLAYER_TONE_FINISH:
        break;
    case UI_CMD_BUFFERING:
        break;
    case UI_CMD_BT_UP:
        ui_check_on_off_before_exec(ui_handle_up, "ui_handle_up");
        break;
    case UI_CMD_BT_DOWN:
        ui_check_on_off_before_exec(ui_handle_down, "ui_handle_down");
        break;
    case UI_CMD_PLAYER_FINISH:
        ui_handle_finish();
		break;
    case UI_CMD_BT_NEXT:
        ui_check_on_off_before_exec(ui_handle_next, "ui_handle_next");
        break;
	case UI_CMD_BT_NEXT_LONG_DOWN:
        ui_check_on_off_before_exec(ui_handle_next_long_pressdown, "ui_handle_next_long_pressdown");
		break;
	case UI_CMD_BT_PREV_LONG_DOWN:
        ui_check_on_off_before_exec(ui_handle_prev_long_pressdown, "ui_handle_prev_long_pressdown");
		break;	
    case UI_CMD_BT_PREV:
        ui_check_on_off_before_exec(ui_handle_prev, "ui_handle_prev");
        break;
    case UI_CMD_BT_OK:
        ui_check_on_off_before_exec(ui_handle_pause_play, "ui_handle_pause_play");
        break;
    case UI_CMD_BT_PLAY_LONG_DOWN:
        //ui_check_on_off_before_exec(ui_handle_fm_seek_auto_init, "ui_handle_fm_seek_auto_init");
        break;
    case UI_CMD_BT_PLAY_LONG_UP:
        //ui_check_on_off_before_exec(ui_handle_fm_seek_auto, "ui_handle_fm_seek_auto");
        break;
	case UI_CMD_BT_STOP:
		ui_check_on_off_before_exec(ui_handle_stopplay, "ui_handle_stopplay");
		break;
    case UI_CMD_BT_MODE:  
        ui_check_on_off_before_exec(ui_handle_mode, "ui_handle_mode");
        break;
    case UI_CMD_BT_POWER:
        ui_handle_power();
        break;
    case UI_CMD_BT_MUTE:
        ui_check_on_off_before_exec(ui_handle_mute, "ui_handle_mute");
        break;
    case UI_CMD_VOLUME_INC_DOWN:
        ui_check_on_off_before_exec(ui_handle_vol_inc_long_press, "ui_handle_vol_inc_long_press");
        break;
    case UI_CMD_VOLUME_INC_UP:
        ui_check_on_off_before_exec(ui_handle_vol_long_press_up, "ui_handle_vol_long_press_up");
        break;
    case UI_CMD_VOLUME_DEC_DOWN:
        ui_check_on_off_before_exec(ui_handle_vol_dec_long_press, "ui_handle_vol_dec_long_press");
        break;
    case UI_CMD_VOLUME_DEC_UP:
        ui_check_on_off_before_exec(ui_handle_vol_long_press_up, "ui_handle_vol_long_press_up");
        break;
	case UI_CMD_SET_VOL:
        ui_handle_bt_set_vol(cmd->arg2);
		break;
	case UI_CMD_BT_PAIR:
		if (ui_source_select != SOURCE_SELECT_BT)
		{
			break;
		}
		bt_connected = false;	
		//bt_force_disconnect = true;
		handle_bt_dispair();
		break;
	case UI_CMD_IR_BT_MODE:
		if (ui_source_select != SOURCE_SELECT_BT)
		{
			ui_source_ir_select = SOURCE_SELECT_BT;
			ui_handle_mode();
		}
		break;
	case UI_CMD_IR_OPT_MODE:
		if (ui_source_select != SOURCE_SELECT_SPDIFIN)
		{
			ui_source_ir_select = SOURCE_SELECT_SPDIFIN;
			ui_handle_mode();
		}
		break;
	case UI_CMD_IR_AUX_MODE:
		if (ui_source_select != SOURCE_SELECT_LINEIN)
		{
			ui_source_ir_select = SOURCE_SELECT_LINEIN;
			ui_handle_mode();
		}
		break;
	case UI_CMD_IR_RCA_MODE:
		if (ui_source_select != SOURCE_SELECT_LINEIN1)
		{
			ui_source_ir_select = SOURCE_SELECT_LINEIN1;
			ui_handle_mode();
		}
		break;
	case UI_CMD_IR_HDMI_MODE:
		if (ui_source_select != SOURCE_SELECT_HDMI)
		{
			ui_source_ir_select = SOURCE_SELECT_HDMI;
			ui_handle_mode();
		}
		break;
	case UI_CMD_BT_MIC_PAIR:
        //ui_check_on_off_before_exec(ui_handle_mic_pair, "ui_handle_mic_pair");
		break;
	case UI_CMD_EQ_MUSIC:		
        ui_check_on_off_before_exec(ui_handle_eq, "ui_handle_eq");
		break;
		
	case UI_CMD_USB_EMU_TIMEOUT:
        //ui_check_on_off_before_exec(ui_handle_usb_emu_timeout, "ui_handle_usb_emu_timeout");
		break;
		
	case UI_CMD_BASS_DOWN:
	case UI_CMD_BASS_UP:
	case UI_CMD_TREBLE_DOWN:
	case UI_CMD_TREBLE_UP:
		//handle_bass_treble(cmd->cmd - UI_CMD_TREBLE_UP);
		break;
    case UI_CMD_USB_LOAD:
        //ui_check_on_off_before_exec(ui_handle_load_usb, "ui_handle_load_usb");
        break;
    case UI_CMD_USB_OUT:
        //ui_check_on_off_before_exec(ui_handle_usb_out, "ui_handle_usb_out");
        break;
    case UI_CMD_SD_IN:
	case UI_CMD_SD_LOAD:
		//ui_check_on_off_before_exec(ui_handle_load_sd, "ui_handle_load_sd");
		break;
    case UI_CMD_SD_OUT:
    case UI_CMD_SD_UNLOAD:
        //ui_check_on_off_before_exec(ui_handle_sd_unload, "ui_handle_sd_unload");
        break;
    case UI_CMD_FILES_IS_LOAD:
		/*
        if(ui_power == POWER_ON)
        {   
            ui_handle_file_load(cmd->arg2, cmd->mode);
        }
        */
        break;
	
#ifdef CONFIG_CEC
	case UI_CEC_INACTIVE_SOURCE:
        ui_check_on_off_before_exec(ui_handle_cec_inactive_source, "ui_handle_cec_inactive_source");
		break;
    case UI_CEC_ACTIVE_SOURCE:
        ui_check_on_off_before_exec(ui_handle_cec_active_source, "ui_handle_cec_active_source");
		break;
	case UI_CEC_HDMI_PULL_OUT:
		ui_handle_cec_pull_out();
		break;
	case UI_CEC_HDMI_INSERT:
		ui_handle_cec_insert();
		break;
	case UI_CMD_HDMION_SEND:
		action_hdmion_send();
		break;	
	case UI_CMD_HDMION_DEINIT:
		action_hdmi_on();
		break;
#endif
	case UI_CMD_SET_48K:
		ui_handle_set_samp(true);
		break;
	case UI_CMD_SET_44K:
		ui_handle_set_samp(false);
		break;	
	case UI_CMD_EQ_RELOAD:
		//ui_handle_reload_eq(eq_sel);
		break;
    default:
        break;
    }
}

/****************************************************************************
 * Name: ui_thread
 *
 * Description:
 *    UI??????????
 *
 * Parameters:
 *    argc  ????????
 *    argv  ?????§Ò?
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
//#define AUDIO_ENERGY_DEBUG
int adc_fd;
unsigned short Adc_Read_Buf[6];
static int sl_ui_thread(void)
{
    struct mq_attr attr;
    int msgsize, prio;
    int count = 0;
	int cxmode_count = 0;
	int uicount = 0;
	int update_cout = 0;
	int en_adc_cout=0;
	int mci_count=0;
	int delay_disp_cout=0;
	int det_energy_cnt=0;
	bool is_rhy_bre_mode = false;
    bool running = true;
    ui_cmd_t cmdq;
    int ret = 0;
    int handle_wd_delay;
	bool cplfalg = false;
	int energy_old = 0;
	int energy_cur = 0;
	int energy_temp = 0;
	
	sync_dsp_startup();
#ifdef CONFIG_CEC
	cec_entry();
#endif
	bsp_init();	
	get_energy_init();
	//?????????
    Ui = (FAR struct ui_s *)malloc(sizeof(struct ui_s));
    if (Ui == NULL)
    {
        printf("%s:Allocate memery for UI error\n",__func__);
    }
    else
    {
        printf("%s:Allocate memery for UI success\n",__func__);

        memset(Ui, 0, sizeof(struct ui_s));

        //??????????????
        attr.mq_maxmsg = 64;
        attr.mq_msgsize = sizeof(ui_cmd_t);
        attr.mq_curmsgs = 0;
        attr.mq_flags = 0;
        sprintf(Ui->mqname, "mq_common");
        //?????????
        Ui->mq = mq_open(Ui->mqname, O_RDWR | O_CREAT | O_NONBLOCK, 0644, &attr);
        if (Ui->mq < 0)
        { //??????§Õ????
            printf("%s:Open message queue for UI fail\n", __func__);
        }
        else
        {
            printf("%s:Open message queue for UI success\n", __func__);

			
            if(bt_uart_init())
            {
                printf("%s:UART for bluetooth open success\n", __func__);
            }
            else
            {
                printf("%s:UART for bluetooth open fail\n", __func__);
            }

            //???????????????????????????????
            bt_init_sem();
			bt_pthread_start();
			
            //??§á???????
            ui_handle_power();
			
			//UI?????
            while (running)
            {
                //????????§Ø?????
                msgsize = mq_receive(Ui->mq, (char *)&cmdq, sizeof(ui_cmd_t), &prio);
				//printf("size %d msg %d \n", msgsize, cmdq.cmd);
                if (msgsize == sizeof(ui_cmd_t))
                {   //??§¹???
                    if ((cmdq.cmd == UI_CMD_BT_MODE) || (cmdq.cmd == UI_CMD_BT_POWER))
                    {   //???????????????
                        if(should_exec)
                        {   //???????????????
                            if (cmdq.cmd == UI_CMD_BT_MODE)
                            {
                                handle_wd_delay = 200;
                            }
                            else if (cmdq.cmd == UI_CMD_BT_POWER)
                            {
                                handle_wd_delay = 800;
							}
							else 
                            {
                                handle_wd_delay = 150;
                            }

                            if (wdtimer_exec != NULL)
                            {
                                wd_cancel(wdtimer_exec);
                            }
                            else
                            {
                                wdtimer_exec = wd_create();
                            }
							
                            should_exec = false;
                            wd_start(wdtimer_exec, handle_wd_delay, sc6138_exec_handle, 0);
                            //???????
                            ui_handle_cmd(&cmdq);
                        }
                        else
                        {
                            printf("%s:cmd %d is be ignored\n", __func__, cmdq.cmd);
                        }
                    }
                    else
                    {   //???????????????????????????????
                        ui_handle_cmd(&cmdq);
                    }
                }
                else if(msgsize >= 0)
                {   //?????§³????
                    printf("%s:Message size error\n", __func__);
                }
                if (++count >= SLEEP_COUNT)
                {
                    //???????????????????????
                    bt_chk_and_disp();
					
					//????SB??SD??
					//chk_usb_sd_disp();
                    //???2?????????
                    //ui_update_music_time();
					
                    ui_source_detect_handle();

					
					count = 0;
                }
				if (++update_cout >= 10)
				{
					ui_update_disp();
					update_cout = 0;
				}
				if (++uicount >= UI_UPDATE_COUT)
				{
					ui_handle_hdmi_det();
					uicount = 0;
				}				
				//ui_bt_mute_handle();
                usleep(6000);
            }
            //??????????
            mq_close(Ui->mq);
        }
        //??????????
        free(Ui);
    }
    return ret;
}

/****************************************************************************
 * Name: ui_main
 *
 * Description:
 *    ???UI????
 *
 * Parameters:
 *    argc  ????????
 *    argv  ?????§Ò?
 *
 * Returned Value:
 *    ????0
 * 
 * Assumptions:
 *
 ****************************************************************************/
#include <nuttx/module.h>
int sl_ui_main(int argc, char *argv)
{
	int ret;
	ret = task_create("sl_ui", 100, 16384, sl_ui_thread, NULL);
	if (ret <= 0) {
		printf("%s %d task_create failed!\n", __func__, __LINE__);
		return SL_UI_ERROR_INIT;
	}
	return	SL_UI_ERROR_NULL;
}
app_entry(sl_ui_main);



int sl_lcd_main(void)
{

}

