/****************************************************************************
 * Included Files
 ****************************************************************************/
#ifdef CONFIG_BLUETOOTH
#include "bluetooth.h"
#endif
#include "bt_uart.h"
#include <errno.h>
#include <fcntl.h>
#include <nuttx/power/pm.h>
#include <nxplayer.h>
#include "player_cmd.h"
#include <pthread.h>
#include <silan_gpio.h>
#include <silan_addrspace.h>
#include <silan_resources.h>
#include <nuttx/audio/sladsp_ae.h>
#include "filelist.h"
#include "sl_lcd.h"
#include "sl_ui_cmd.h"
#include "sl_ui_handle.h"
#include "sl_ui_local.h"
#include <string.h>
#include <sys/ioctl.h>
#include "4052.h"
#include "sl_bsp.h"
#include "vol_ctrl.h"
#include <silan_cec.h>
#include "led_api.h"

int eq_sel = 0;
bool need_reload_eq = false;

bool frist_hdmi_init = false;
WDOG_ID wdtimer_hdmion_send = NULL;

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
/*??????????*/
#define SL_UI_DBG
/*????standby*/
#define STANDBY_DELAY_SEC 10

/****************************************************************************
 * Public Types
 ****************************************************************************/
/*??????*/
enum
{
    PLAY_START = -1,
    PLAY,
    STOP,
    PLAY_END,
} UI_SELECT_PLAY;

/****************************************************************************
 * Public Data
 ****************************************************************************/
/*??*/
extern int ui_source_select;
extern int ui_source_ir_select;
/*???*/
/*????*/
/*???????????*/
static const char aux_str[] = "aux";
static const char bt_str[] = "bluetooth";
static const char opti_str[] = "spdifin";
static const char power_off_str[] = "power off";
static const char power_on_str[] = "Silan";
static const char sd_str[] = "sd";
static const char usb_str[] = "usb";

/*????*/
/*??????????*/
bool bt_connected = false;
bool bt_force_disconnect = false;

/*????mute????*/
static int bt_mute_last_state = 0;
/*?????????????????*/
static sem_t bt_start_check_sem;
/*????????????*/
static sem_t bt_state_sem;
/*????????????ID*/
static pthread_t bt_state_tid = -1;
/*bypass??????*/
static float bypass_in_vol = -12;
/*bypass????????*/
static float bypass_vol_offset = 0;
/*????????*/
static int cur_freq = 300000000;
/*?????????*/
static bool is_volume_mode = false;
/*mix????*/
static float mix_vol = 60; //

static bool is_movie_mode = false;


/*????????*/
static unsigned char set_vol = 16;
/*?????????*/
static int mute_state = 0;
static int stop_state = 0;
static int bt_pause_state = 0;
static int aux_pause_state = 0;
/*SD????��??????????*/
static int sd_last_file_index = -1;
/*SD???????????????????*/
static int sd_last_folder_num = -1;
/*SD???????????*/
static int sd_last_total_num = -1;
/*???????*/
static int sd_playtime = 0;
/*USB????��??????????*/
static int usb_last_file_index = -1;
/*USB???????????????????*/
static int usb_last_folder_num = -1;
/*USB???????????*/
static int usb_last_total_num = -1;
/*???????*/
static int usb_playtime = 0;
/*??????????????????*/
static WDOG_ID wdtimer_goback_mode;
/*??????????????????????*/
static WDOG_ID wdtimer_vol_longpress = NULL;
/*???????��?????*/
static WDOG_ID wdtimer_vesion;


unsigned short ui_select_fm_freq = 0;	//

/*???*/
/*??????????*/
#ifdef CONFIG_PM
pthread_cond_t stop_cond = PTHREAD_COND_INITIALIZER;
#endif
/*???????*/
int ui_power = POWER_START;

int ADC2_MAX_VOLUME = 100; 
int DECODER_MAX_VOLUME = 40;

/*Flash????��*/
#define FLASH_PAGE_SIZE (256)
/*Flash???????????????*/
#define FLASH_USER_SPACE_ADDR     (0x00286100)

/*???TREBLE????*/
static int treble_level = 0;
/*???BASS????*/
static int bass_level = 0;
/* adc ??????*/
/*BASS/TREBLE�����*/
//*�ü�����������vol    �ü�������gain����*/
static const int bass_treble_gains[][2] = {
    {50, 300},  //300
    {60, 300}, 
    {70, 300}, 
    {80, 300}, 
    {90, 300},
};
static const int bass_treble_gains_size = (sizeof(bass_treble_gains)/sizeof(bass_treble_gains[0]));

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/
/*??*/
extern int fat_get_unicode_size(WORD *ustr);
extern int fat_utf8_to_unicode(const char* str, WORD *ustr, int len);
extern void send_cmd_2_ui(ui_cmd_t *ui_cmd);
extern void sysfs_sd_umount(void);
extern void sysfs_usb_umount(void);
extern void time2str(int curtime, int totaltime, char *str);
extern void usb_manual_disconnect(void);

/*???*/
static void lcd_display_set_source(int num);
static void lcd_display_str(const char *dis_str, const int line);
static void ui_process_vol_dec(void);
static void ui_process_vol_inc(void);

bool update_params_2_flash(void);
bool update_params_from_flash(void);

bool hdmi_on_flag = false;
bool hdmi_det_online= false;


/****************************************************************************
 * Name: bt_chk_and_disp
 *
 * Description:
 *    ????????????��???
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void bt_chk_and_disp(void)
{
    static bool isDisp = true;
	static bool isMuteFlash = true;
	static uint32_t ioval = 0;
    if(ui_source_select == SOURCE_SELECT_BT) 
    {
    	if (is_volume_mode == false)
    	{
	        if(bt_connected)
	        {
	            if(!isDisp)
	            {
					isDisp = true;
	            }
				ui_led_disp_mode(SOURCE_SELECT_BT);
	        }
	        else
	        {
	            if(!isDisp)
	            {
					ui_led_disp_mode(SOURCE_SELECT_BT);
	                isDisp = true;
	            }
	            else
	            {
					ui_led_clear();
	                isDisp = false;
	            }
	        }
    	}

    }
	
	if (mute_state == MUTE)
	{	
		if (isMuteFlash==0)	ui_led_disp_volume(0);
		else ui_led_clear();
		isMuteFlash = isMuteFlash?0:1;		
	}
	
	ui_led_update_display();
}

/****************************************************************************
 * Name: bt_init_sem
 *
 * Description:
 *    ?????????????????
 *
 * Parameters:
 *    en 1-????0-????
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void bt_init_sem(void)
{
    //?????????????????????
    sem_init(&bt_state_sem, 0, 1);
    //??????????????????????
    sem_init(&bt_start_check_sem, 0, 1);
}


/****************************************************************************
 * Name: bt_cmd_translate
 *
 * Description:
 *    ״AT����ת��־UI����
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
enum ui_cmd_e bt_cmd_translate(int cmd)
{
    const int UI_CMDS[] = {
		UI_CMD_BT_POWER,	
		UI_CMD_NULL, //UI_CMD_BT_MUTE,

		UI_CMD_IR_AUX_MODE, //UI_CMD_IR_RCA_MODE
		UI_CMD_IR_HDMI_MODE,
		UI_CMD_IR_RCA_MODE, //UI_CMD_IR_AUX_MODE
		UI_CMD_IR_OPT_MODE,
		UI_CMD_IR_BT_MODE,
		
		UI_CMD_EQ_MUSIC,
		UI_CMD_NULL, //UI_CMD_EQ_MOVIE,
		UI_CMD_NULL, //UI_CMD_EQ_DIALOG,
		
		UI_CMD_NULL, //UI_CMD_BASS_DOWN,
		UI_CMD_NULL, //UI_CMD_BASS_UP,
		UI_CMD_NULL, //UI_CMD_TREBLE_DOWN,
		UI_CMD_NULL, //UI_CMD_TREBLE_UP,

		UI_CMD_NULL, //UI_CMD_BT_PREV,
		UI_CMD_BT_OK,
		UI_CMD_NULL, //UI_CMD_BT_NEXT,

		UI_CMD_BT_MODE,
		UI_CMD_NULL,
		UI_CMD_NULL,

		UI_CMD_BT_UP,
		UI_CMD_BT_DOWN,

		UI_CMD_SET_48K,
		UI_CMD_SET_44K,
		
		UI_CMD_SET_VOL,
    };

    if(AT_CMD_START < cmd && cmd < AT_CMD_MAX)
    {
        return UI_CMDS[cmd];
    }

    return UI_CMD_NULL;
}

/****************************************************************************
 * Name: bt_read_state
 *
 * Description:
 *    ����״̬����߳���ں���
 *
 * Parameters:
 *    en 1-ʹ�ܣ�0-����
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void bt_read_state(void)
{
    const int buf_szie = 20;
    int ret;
    char buf_recv[20] = {0};
    char * ptr = buf_recv;

    while (1)
    {
        if(ui_power == POWER_ON)
        {
        	//memset(buf_recv, 0, sizeof(buf_recv));
            ret = bt_read(ptr, 20);
            
            ui_cmd_t cmd = {0};
            cmd.cmd = UI_CMD_NULL;
            int value = 0;
            int index = bt_chk_AT_cmd(buf_recv, &value);
            if(index > AT_CMD_START && index < AT_CMD_MAX)
            {
                int ui_cmd = bt_cmd_translate(index); 
				if (index == AT_CMD_SET_VOL)
				{
					printf("index:%d value:%d\n", index, value);
                    cmd.cmd = ui_cmd;
					cmd.arg2 = value;
                    send_cmd_2_ui(&cmd);
				}
                else if(ui_cmd != UI_CMD_NULL)
                {
                    cmd.cmd = ui_cmd;
                    send_cmd_2_ui(&cmd);
                }
				
				if (index == AT_CMD_BT_CONNECTED)
				{
					bt_connected = true;
				}
				else if (index == AT_CMD_BT_DISCONECT)
				{
					bt_connected = false;
				}
				
            }

            if (ret > 0)
            {
                //printf("uart buffer: %s\n", buf_recv);
                
                ptr += ret;
                if(buf_recv - ptr + buf_szie < 16)
                {   //������ǰ�洢��Χ
                    ptr = buf_recv;
                    memset(buf_recv, 0, buf_szie);
                }
            }
    
            usleep(1000);
        }
        else
        {
            bt_uart_close();
            sem_wait(&bt_start_check_sem);
            printf("%s:Recover from semaphore\n", __func__);
            bt_uart_init();
            usleep(100000);
        }
    }
}


void bt_pthread_start(void)
{
	if (bt_state_tid < 0)
	{
		if(pthread_create(&bt_state_tid, NULL, (pthread_startroutine_t)bt_read_state, NULL) == 0)
		{
			printf("%s:Create check bluetooth connect state thread success\n", __func__);
		}
		else
		{
			printf("%s:Create check bluetooth connect state thread fail\n", __func__);
		}
	}
	else
	{
		printf("%s:pid = %d\n", __func__, bt_state_tid);
	}
	
	usleep(100);

}


/****************************************************************************
 * Name: bt_power
 *
 * Description:
 *    ?????????????
 *
 * Parameters:
 *    en 1-????0-????
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void bt_power(bool en)
{
    //zhuque_bsp_gpio_set_mode(16, GPIO_OUT, PULLING_HIGH);
    //zhuque_bsp_gpio_set_value(16, en?1:0);
}

/****************************************************************************
 * Name: display_volume
 *
 * Description:
 *    ????????
 * 
 * Parameters:
 *    vol ???????????
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void display_volume(float vol)
{
    int vol_i = vol;
    char volume[10] = {0};
    sprintf(volume, "Vol %d", vol_i);

    //????????????
    //lcd_display_str(volume, MEDIA_LINE);

//	ui_led_disp_volume(vol_i);
//	ui_led_update_display();
	
    //????????????????????
//    ui_goback_source(900);
}

#ifdef CONFIG_PM
/****************************************************************************
 * Name: enter_dynamic
 *
 * Description:
 *    ????��?????
 *
 * Parameters:
 *    arg ??????
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static pthread_addr_t enter_dynamic(pthread_addr_t arg)
{
    int fd, ret = 0;

    fd = open(CONFIG_PM_DEV_PATH, O_RDWR);
    if (fd < 0)
    {
        printf("%s:open /dev/pm error\n", __func__);
    }
    else
    {   
        if (cur_freq == 300000000)
        {
            cur_freq = 6000000;
            ret = ioctl(fd, PMIOC_DYNAMICFREQ, 6000000);

            printf("%s:Switch to 6 MHz freq\n", __func__);
        }
        else if (cur_freq == 6000000)
        {
            cur_freq = 300000000;
            ret = ioctl(fd, PMIOC_DYNAMICFREQ, 300000000);

            printf("%s:Switch to 300 MHz freq\n", __func__);
        }
    
        /* update time throld to 60s */
        if (ret != 0)
        {
            printf("%s:Switch freq fail\n", __func__);

            pm_sync(STANDBY_DELAY_SEC);
        }
    
        close(fd);
        
    }
    return NULL;
}

/****************************************************************************
 * Name: handle_mode_dynamic
 *
 * Description:
 *    ?????????????��?????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void handle_mode_dynamic(void)
{
    int ret;
    pthread_t tid;
    ret = pthread_create(&tid, NULL, enter_dynamic, NULL);
    ret = pthread_detach(tid);
}
#endif

/****************************************************************************
 * Name: lcd_display_clear_line
 *
 * Description:
 *    ???????��????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static void lcd_display_clear_line(int line)
{
    WORD show[INFO_LEN];
    memset(show, 0, INFO_LEN*sizeof(WORD));
    lcd_display(0, line, show, 0, INFO_LEN);
}

/****************************************************************************
 * Name: lcd_display_set_source
 *
 * Description:
 *    ???????????
 *
 * Parameters:
 *    num ??????
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static void lcd_display_set_source(int num)
{
    printf(" >>>>>> %s:%d\n", __func__, num);
    lcd_clear();

    switch (num)
    {
        case SOURCE_SELECT_BT:
            lcd_display_str(bt_str, MEDIA_LINE);
            break;
//        case SOURCE_SELECT_SPDIFIN:
//            lcd_display_str(opti_str, MEDIA_LINE);
//            break;
        case SOURCE_SELECT_LINEIN:
            lcd_display_str(aux_str, MEDIA_LINE);
            break;
        case SOURCE_SELECT_USB:
            lcd_display_str(usb_str, MEDIA_LINE);
            break;
        case SOURCE_SELECT_SD:
            lcd_display_str(sd_str, MEDIA_LINE);
            break;
    }
}

/****************************************************************************
 * Name: lcd_display_str
 *
 * Description:
 *    ????????
 *
 * Parameters:
 *    dis_str ???????????????
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void lcd_display_str(const char *dis_str, const int line)
{
    if (dis_str != NULL)
    {
        WORD show[INFO_LEN];
        memset(show, 0, INFO_LEN*sizeof(WORD));
	    fat_utf8_to_unicode(dis_str, show, MAX_STRING_LEN);
        lcd_display(0, line, show, 0, fat_get_unicode_size(show)/2);
    }
}

int hdmisend_count = 0;
int hdmi_deinit_count = 0;
void ui_hdmion_send(void)
{

	static int send_count1=0,send_count2=0;
	ui_cmd_t cmd;

	if(NULL != wdtimer_hdmion_send)
	{
		wd_start(wdtimer_hdmion_send, 900, ui_hdmion_send, 0);
	}

	if (swa_audio_check_playing())
	{
		printf("\n---------->>>>>>>>>>>>hdmi is playing ! cancel hdmi send\n");
		cmd.cmd = UI_CMD_HDMION_SEND;
		send_cmd_2_ui(&cmd);

		wd_cancel(wdtimer_hdmion_send);

	}
	else 
	{
		hdmi_deinit_count++;
		if (hdmi_deinit_count >= 10)
		{
			hdmi_deinit_count = 0;
			cmd.cmd = UI_CMD_HDMION_DEINIT;
			send_cmd_2_ui(&cmd);
		}
	}
	
    #ifdef SL_UI_DBG
    printf("%s\n",__func__);
    #endif

}

int iis_sample_rate = IIS_SAMP_44K;
void sl_ui_set_samp(bool on_off )
{
	char *samp_str;
	samp_str = "0 2 2 44100 44100";		
	iis_sample_rate = IIS_SAMP_44K;
	player_process_cmd(NP_CMD_SET_SAMPLE, samp_str, 0, NULL, NULL); 
	usleep(1000);
	player_process_cmd(NP_CMD_SET_REQRATE, NULL, 44100, NULL, NULL); 
	usleep(1000);

	printf("\n%s %s \n", __func__, samp_str);
}

void sl_ui_set_reqrate(void)
{
	player_process_cmd(NP_CMD_SET_REQRATE, NULL, 44100, NULL, NULL); 
	usleep(1000);

}


void ui_handle_set_samp(bool flag)
{
	if (ui_source_select == SOURCE_SELECT_BT)
	{
 		char *samp_str;
		if (flag) //48k
		{
			if (iis_sample_rate != IIS_SAMP_48K)
			{

				samp_str = "0 2 2 48000 48000";
				iis_sample_rate = IIS_SAMP_48K;
				
				player_process_cmd(NP_CMD_SET_SAMPLE, samp_str, 0, NULL, NULL); 
				usleep(1000);
					
				player_process_cmd(NP_CMD_SET_REQRATE, NULL, 48000, NULL, NULL); 
				usleep(1000);
				
				player_process_cmd(NP_CMD_I2SIN_CLOSE, NULL, 1, NULL, NULL);
				usleep(1000);
				player_process_cmd(NP_CMD_I2SIN_OPEN, NULL, 1, NULL, NULL);
				usleep(1000);			
				printf("\n set samp 48000 \n");
			}
		}
		else 
		{
			if (iis_sample_rate != IIS_SAMP_44K)
			{

				samp_str = "0 2 2 44100 44100";
				iis_sample_rate = IIS_SAMP_44K;
				
				player_process_cmd(NP_CMD_SET_SAMPLE, samp_str, 0, NULL, NULL); 
				usleep(1000);
					
				player_process_cmd(NP_CMD_SET_REQRATE, NULL, 44100, NULL, NULL); 
				usleep(1000);
				
				player_process_cmd(NP_CMD_I2SIN_CLOSE, NULL, 1, NULL, NULL);
				usleep(1000);
				player_process_cmd(NP_CMD_I2SIN_OPEN, NULL, 1, NULL, NULL);
				usleep(1000);			
				printf("\n set samp 44100 \n");
			}
		}
		printf("%s, %d , %d", __func__, __LINE__, iis_sample_rate);

 	}
}

/****************************************************************************
 * Name: set_golr_gain
 *
 * Description:
 *    设置hdmi增益
 * 
 * Parameters:
 *    增益值 取值范围【0，31】, 对应【+6，-25db], step 为1db
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
#define GOL_GAIN_ADDR		(0xba0e0030)
#define GOR_GAIN_ADDR		(0xba0e0034)
void set_golr_gain(int gain)
{
	REG32(KSEG1(GOL_GAIN_ADDR)) = gain;
	REG32(KSEG1(GOR_GAIN_ADDR)) = gain;
	
}

/****************************************************************************
 * Name: play_local
 *
 * Description:
 *    ????��????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
 bool is_set_spdif = false;
int clear_sdf_pad_cnt = 0;
static int play_local(void)
{
#ifdef SL_UI_DBG
    printf("%s.....\n", __func__);
#endif
	
    switch (ui_source_select)
    {
        case SOURCE_SELECT_SPDIFIN:
        {            
			printf(">>>>>>>>>> opt mode <<<<<<<<<<\n");
			player_paramter_set_init(AUDIO_EXTRA_CODEC_SLAVE_OUT , AUDIO_INNER_IN, 2, 0);  //AUDIO_EXTRA_CODEC_SLAVE_OUT
			usleep(1000);
			sem_wait(&bt_state_sem);
			handle_bt_cmd(BT_AT_DECODE);
			sem_post(&bt_state_sem);
			usleep(200000);
			/*
			//发送音量
			sem_wait(&bt_state_sem);
			handle_bt_vol(set_vol);
			sem_post(&bt_state_sem);
			*/
			
			DECODER_MAX_VOLUME = 40;
			set_decoder_vol(DECODER_MAX_VOLUME);
			
			sl_ui_set_reqrate();

			if (mute_state != MUTE)	Hw_Amp_UnMute();		
			player_process_cmd(NP_CMD_VOLUME_SET, NULL, (int)mix_vol, NULL, NULL);
            player_process_cmd(NP_CMD_SPDIFIN_STOP, NULL, 0, NULL, NULL);
            usleep(1000);
            player_process_cmd(NP_CMD_SPDIFIN_START, NULL, 0, NULL, NULL);
            usleep(1000);

        }
		break;

        case SOURCE_SELECT_HDMI:
        {            
			printf(">>>>>>>>>> hdmi mode <<<<<<<<<<\n");
			
			if(frist_hdmi_init == true)
			{
				usleep(2000000);
				frist_hdmi_init = false;
			}
			
			player_paramter_set_init(AUDIO_EXTRA_CODEC_SLAVE_OUT, AUDIO_INNER_IN, 2, 2); 
			usleep(1000);
			sem_wait(&bt_state_sem);
			handle_bt_cmd(BT_AT_DECODE);
			sem_post(&bt_state_sem);
			usleep(20000);
			/*
			//发送音量
			sem_wait(&bt_state_sem);
			handle_bt_vol(set_vol);
			sem_post(&bt_state_sem);
			*/
			DECODER_MAX_VOLUME = 40;
			set_decoder_vol(DECODER_MAX_VOLUME);
			
			sl_ui_set_reqrate();

			if (mute_state != MUTE)	Hw_Amp_UnMute();	
			player_process_cmd(NP_CMD_VOLUME_SET, NULL, (int)mix_vol, NULL, NULL);
			usleep(100000);
			//��HDMI
			action_hdmi_on();
			usleep(1000);

			/*
			if(frist_hdmi_init == true)
			{
				frist_hdmi_init = false;
				hdmisend_count = 0;
				if(wdtimer_hdmion_send == NULL)
				{
					wdtimer_hdmion_send = wd_create();
				}
				wd_start(wdtimer_hdmion_send, 900, ui_hdmion_send, 0);
			}
			else
			{
				if(NULL != wdtimer_hdmion_send)
				{
					wd_cancel(wdtimer_hdmion_send);
				}
			}
			*/
        }
		break;
		
        case SOURCE_SELECT_BT:
        {
			printf(">>>>>>>>>> bluetooth mode <<<<<<<<<<\n");
			player_process_cmd(NP_CMD_I2SIN_CHAN, NULL, 2, NULL, NULL);//////////adc2
			usleep(1000);	
			player_paramter_set_init(AUDIO_EXTRA_CODEC_SLAVE_OUT, AUDIO_EXTRA_SLAVE_IN, 2, 0); 
			usleep(10000);
			sem_wait(&bt_state_sem);
			handle_bt_cmd(BT_AT_BT);
			sem_post(&bt_state_sem);
			usleep(200000);
			/*
			//发送音量
			sem_wait(&bt_state_sem);
			handle_bt_vol(set_vol);
			sem_post(&bt_state_sem);
			*/
			
			ADC2_MAX_VOLUME = 100;
			set_adc2_vol(ADC2_MAX_VOLUME);

			//usleep(100000);		
			//???????mute?????????????
			bt_mute_last_state = 0;
			//switch_4052_function(BT_4052);
			//if (mute_state != MUTE)	Hw_Amp_UnMute();	
			player_process_cmd(NP_CMD_VOLUME_SET, NULL, (int)mix_vol, NULL, NULL);
			is_volume_mode = false;

			sl_ui_set_samp(0);
			player_process_cmd(NP_CMD_I2SIN_CLOSE, NULL, 1, NULL, NULL);
			usleep(1000);
			player_process_cmd(NP_CMD_I2SIN_OPEN, NULL, 1, NULL, NULL);
			usleep(1000);
			
        }
		break;
		
        case SOURCE_SELECT_LINEIN:
        {
			printf(">>>>>>>>>> aux mode <<<<<<<<<<\n");
			
			player_process_cmd(NP_CMD_I2SIN_CHAN, NULL, 2, NULL, NULL);//////////adc2
			usleep(1000);	
			player_paramter_set_init(AUDIO_EXTRA_CODEC_SLAVE_OUT, AUDIO_EXTRA_SLAVE_IN, 2, 0); 
			usleep(10000);
			
			switch_4052_function(AUX_4052);
			
			sem_wait(&bt_state_sem);
			handle_bt_cmd(BT_AT_AUX);
			sem_post(&bt_state_sem);
			usleep(200000);
			/*
			//发送音量
			sem_wait(&bt_state_sem);
			handle_bt_vol(set_vol);
			sem_post(&bt_state_sem);
			*/

			ADC2_MAX_VOLUME = 100;
			set_adc2_vol(ADC2_MAX_VOLUME);
			
			player_process_cmd(NP_CMD_VOLUME_SET, NULL, (int)mix_vol, NULL, NULL);
			
			sl_ui_set_samp(0);
			player_process_cmd(NP_CMD_I2SIN_CLOSE, NULL, 1, NULL, NULL);
            usleep(1000);
			player_process_cmd(NP_CMD_I2SIN_OPEN, NULL, 1, NULL, NULL);
            usleep(1000);
        }
		break;
		
        case SOURCE_SELECT_LINEIN1:
        {
			printf(">>>>>>>>>> rca mode <<<<<<<<<<\n");
			
			player_process_cmd(NP_CMD_I2SIN_CHAN, NULL, 2, NULL, NULL);//////////adc2
			usleep(1000);	
			player_paramter_set_init(AUDIO_EXTRA_CODEC_SLAVE_OUT, AUDIO_EXTRA_SLAVE_IN, 2, 0); 
			usleep(10000);
			
			switch_4052_function(RCA_4052);
			
			sem_wait(&bt_state_sem);
			handle_bt_cmd(BT_AT_AUX);
			sem_post(&bt_state_sem);
			usleep(200000);
			/*
			//发送音量
			sem_wait(&bt_state_sem);
			handle_bt_vol(set_vol);
			sem_post(&bt_state_sem);
			*/
			
			ADC2_MAX_VOLUME = 100;
			set_adc2_vol(ADC2_MAX_VOLUME);
			
			player_process_cmd(NP_CMD_VOLUME_SET, NULL, (int)mix_vol, NULL, NULL);
			
			sl_ui_set_samp(0);
			player_process_cmd(NP_CMD_I2SIN_CLOSE, NULL, 1, NULL, NULL);
            usleep(1000);
			player_process_cmd(NP_CMD_I2SIN_OPEN, NULL, 1, NULL, NULL);
            usleep(1000);
			
        }		
		break;
		/*
        case SOURCE_SELECT_USB:
        {
        	printf("\n>>>>>>>>>> usb mode <<<<<<<<<< \n");
			
			player_paramter_set_init(AUDIO_EXTRA_CODEC_SLAVE_OUT, AUDIO_INNER_IN, 2, 0); 
			usleep(1000);

			DECODER_MAX_VOLUME = 65;
			set_decoder_vol(DECODER_MAX_VOLUME);
			
			player_process_cmd(NP_CMD_VOLUME_SET, NULL, 60, NULL, NULL); //18
            usleep(1000);
			
			sem_wait(&bt_state_sem);
			handle_bt_cmd(BT_AT_DECODE);
			sem_post(&bt_state_sem);
			usleep(20000);
			//player_process_cmd(NP_CMD_SET_REQRATE, NULL, 44100, NULL, NULL); 
			//usleep(1000);
			
            //usb加载
            handle_local(SEARCH_USB_NAME);
        }
		break;
		*/

    }
    return 0;
}

/****************************************************************************
 * Name: save_sd_play_time
 *
 * Description:
 *    ????SD????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static void save_sd_play_time(void)
{
    //????????????
    ui_info_t player_info;
    player_get_info(&player_info);
    if (ui_source_select == SOURCE_SELECT_SD)
    {
        //??????????
        sd_playtime=player_info.curtime;
    }
}

/****************************************************************************
 * Name: save_usb_play_time
 *
 * Description:
 *    ????USB????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static void save_usb_play_time(void)
{
    //????????????
    ui_info_t player_info;
    player_get_info(&player_info);
    if (ui_source_select == SOURCE_SELECT_USB)
    {
        //??????????
        usb_playtime=player_info.curtime;
    }
}

/****************************************************************************
 * Name: ui_display_source
 *
 * Description:
 *    ??????????
 *
 * Parameters:
 *    argc ????????????????
 *    arg1 ???????????1
 *    ...  ???????????
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
 static int wdt_enter_times = 0;
static bool wdt_led_flash = false;
static void ui_display_source(int argc, wdparm_t arg1, ...)
{
    if(NULL != wdtimer_goback_mode)
    {
        wd_cancel(wdtimer_goback_mode);
    }

	ui_led_disp_mode(ui_source_select);
	
    is_volume_mode = false;
}

/****************************************************************************
 * Name: ui_goback_source
 *
 * Description:
 *    ?????????????
 *
 * Parameters:
 *    delay ????????
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_goback_source(int delay)
{
    if (wdtimer_goback_mode == NULL)
    {
        wdtimer_goback_mode = wd_create();
    }
    else
    {
        wd_cancel(wdtimer_goback_mode);
    }
    
    if (wdtimer_goback_mode != NULL)
    {
        wd_start(wdtimer_goback_mode, delay, ui_display_source, 0);
    }

    #ifdef SL_UI_DBG
    printf("%s\n",__func__);
    #endif
}

void set_reg_spec(void)
{
	REG32(KSEG1(0xba000044)) = 0;
	printf("%s set reg 0xba000044 0 \n");
}

/****************************************************************************
 * Name: ui_handle_down
 *
 * Description:
 *    ?????????????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_down(void)
{
/*
    if (mute_state == MUTE)
    {
        //ui_handle_mute();
	    mute_state = UNMUTE;
    }   
*/	
    ui_process_vol_dec();
#ifdef SL_UI_DBG
    printf("%s, volume down\n", __func__);
#endif
//	set_reg_spec();

}

/****************************************************************************
 * Name: ui_handle_file_load
 *
 * Description:
 *    ???????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_file_load(int total_num, int folder_num)
{
	printf(">>>>>>>>>>>>>>>>>>>> %d total:%d fold:%d sd_total:%d sd_fold:%d usd_total:%d usb_fold:%d\n",
		ui_source_select, total_num, folder_num, sd_last_total_num, sd_last_folder_num, 
		usb_last_total_num, usb_last_folder_num);
    if(ui_source_select == SOURCE_SELECT_USB)
    {
		is_usb_load = true;
        if(usb_last_total_num != total_num || usb_last_folder_num != folder_num)
        {
            usb_last_file_index = 0;
            usb_playtime = 0;
        }
        usb_last_total_num = total_num;
        usb_last_folder_num = folder_num;
        //??????��??EEPROM
        //update_params_2_eeprom();
        handle_local_music_play(usb_last_file_index, usb_playtime);
    }
    else if(ui_source_select == SOURCE_SELECT_SD)
    {
		is_sd_load = true;
        if(sd_last_total_num != total_num || sd_last_folder_num != folder_num)
        {
            sd_last_file_index = 0;
            sd_playtime = 0;
        }
        sd_last_total_num = total_num;
        sd_last_folder_num = folder_num;
        //update_params_2_eeprom();
        handle_local_music_play(sd_last_file_index, sd_playtime);
    }
}

/****************************************************************************
 * Name: ui_handle_load_sd
 *
 * Description:
 *    SD????��???????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_load_sd(void)
{
    if(ui_source_select == SOURCE_SELECT_SD)
    {   //sd??
        //????USB????��?
        handle_local(SEARCH_SD_NAME);
    }
    printf("%s:load\n", __func__);
	
	is_sd_load = true;
}

/****************************************************************************
 * Name: ui_handle_load_usb
 *
 * Description:
 *    USB????��???????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_load_usb(void)
{
    if(ui_source_select == SOURCE_SELECT_USB)
    {   //usb??
        //????USB????��?
        handle_local(SEARCH_USB_NAME);
    }
    printf("%s:load\n", __func__);
	is_usb_load = true;
}

void sync_dsp_startup(void)
{
	int dsp_on = -1;
	while(1)
	{
		dsp_on = swa_audio_decode_init();
		if (dsp_on == 0 || dsp_on == 1)
		{
			break;
		}
		usleep(1);
	}
	
}

/****************************************************************************
 * Name: update_bass_treble
 *
 * Description:
 *    ????bass??treble???
 *
 * Parameters:
 *    pLevel ????????????????
 *    bass_or_treble true?????BASS??false?????TREBLE
 *
 * Returned Value:
 *
 * Assumptions:
 *
 ****************************************************************************/
static bool loaded = false;

static int treble_gain_tab[15] = {
	-1200, -1028, -857, -685, -514, -342, -170, 0, 
	170, 342, 514, 685, 857, 1028, 1200
};

static int bass_gain_tab[15] = {
	-1200, -1028, -857, -685, -514, -342, -170, 0, 
	170, 342, 514, 685, 857, 1028, 1200
	
};

static void update_bass_treble(int * pLevel, bool bass_or_treble)
{   
	int temp1 = 0, temp2 = 0;
    if (bass_level == 0 && treble_level == 0)
    {//???bass??treble
        if (loaded)
        {
            int para[7] = {0, 0, 0, 0, 0, 0, 6};
            int i;
            //??????EQ???
            for(i=0;i<2;++i)
            {
                para[0] = i+1;
                swa_audio_audproc_eq(AUDPROC_LIST_MIX, (ae_eq_para *)para);
                swa_audio_audproc_set(AUDPROC_LIST_MIX, AUDPROC_EQ);
            }
            //????EQ???
            swa_audio_audproc_unload(AUDPROC_LIST_MIX, AUDPROC_EQ);
            loaded = false;
        }
    }
    else
    {//??bass??treble
        //filter_id=?, eq_type=0, on_off=1, gain=?, fc=?, q=300, ch=6
        int para[7] = {1, 0, 1, 0, 180, 200, 6};

		/*
        if (*pLevel <= 0)
        {
            para[3] = ((*pLevel) * BASS_TREBLE_GAIN_STEP);
        }
        else
        {
            int i;
            int gain_max = BASS_TREBLE_GAIN_MAX;
            for(i=0;i<bass_treble_gains_size;++i)
            {
                if (mix_vol <= bass_treble_gains[i][0])
                {
                    gain_max = bass_treble_gains[i][1];
                    printf("%d,%d\n", bass_treble_gains, i);
//                    if(update_params_2_flash())
//                    {
//                        printf("write params 2 flash success\n");
//                    }
                    break;
                }
            }
            printf("gain_max=%d,i=%d\n", gain_max, i);
            
            para[3] = ((*pLevel) * (gain_max / BASS_TREBLE_LEVEL));
        }
		*/

		if (!bass_or_treble)
			para[3] = treble_gain_tab[*pLevel + 7];
		else 
			para[3] = bass_gain_tab[*pLevel + 7];

		if (para[3] > 0 && para[3]/100)
		{
			temp1 = para[3]/100;
			temp2 = temp1*(100.0f/64);
			if (ui_source_select == SOURCE_SELECT_HDMI || 
				ui_source_select == SOURCE_SELECT_SPDIFIN)
			{
				set_decoder_vol(DECODER_MAX_VOLUME - temp2);
				printf("set dec vol %d \n", DECODER_MAX_VOLUME - temp2);
			}
			else 
			{
				set_adc2_vol(ADC2_MAX_VOLUME - temp2);
				printf("set adc2 vol %d \n", ADC2_MAX_VOLUME - temp2);
			}
		}
        //????EQ?
        //if(!loaded)
        {
            loaded = true;
            //????EQ???
            printf("set trebass\n");
            swa_audio_audproc_load(AUDPROC_LIST_MIX, AUDPROC_EQ);
        }

        //filter_id=?, eq_type=0, on_off=1, gain=?, fc=?, q=300, ch=6
        para[0] = bass_or_treble?6:7;
        para[4] = bass_or_treble?90:12000;
		para[5] = bass_or_treble?100:300;
        swa_audio_audproc_eq(AUDPROC_LIST_MIX, (ae_eq_para *)para);
        swa_audio_audproc_set(AUDPROC_LIST_MIX, AUDPROC_EQ);

    }

	if (!need_reload_eq)
	{
		if (bass_or_treble) //bass
		{
			ui_led_disp_trebass(SET_DISP_BASS, bass_level);
		}
		else 
		{
			ui_led_disp_trebass(SET_DISP_TREBLE, treble_level);
		}
		ui_led_update_display();
		is_volume_mode = true;
		
		ui_goback_source(900);
	}
	
}

/****************************************************************************
 * Name: handle_bass_treble
 *
 * Description:
 *    ???EQ???????BASS??TREBLE
 *
 * Parameters:
 *    
 *
 * Returned Value:
 *
 * Assumptions:
 *
 ****************************************************************************/
void handle_bass_treble(int mode)
{
    //?????????????
	if (is_movie_mode) return;
	
    const bool bass_or_treble = (mode > 1);
    const bool is_up = (mode % 2 == 0);
    const int level_step = ((is_up)?BASS_TREBLE_STEP:-BASS_TREBLE_STEP);
    int *pLevel = (bass_or_treble?&bass_level:&treble_level);

    if((*pLevel > -BASS_TREBLE_LEVEL && !is_up) || (*pLevel < BASS_TREBLE_LEVEL && is_up))
    {
        //???????????
        *pLevel += level_step;
        //????BASS??TREBLE???
        update_bass_treble(pLevel, bass_or_treble);
    }
}

void handle_bt_dispair(void)
{
	sem_wait(&bt_state_sem);
	handle_bt_cmd(BT_DIS_PAIRE);
	sem_post(&bt_state_sem);
	printf("%s %d", __func__, __LINE__);
}

/****************************************************************************
 * Name: ui_handle_mode
 *
 * Description:
 *    ???��?????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_mode(void)
{
	Hw_Amp_Mute();			

#ifdef SL_UI_DBG
    printf("%s.....%d\n", __func__, ui_source_select);
#endif	

    if (ui_source_select == SOURCE_SELECT_BT)
    {
    	if (!bt_force_disconnect)
    	{
        	Bt_Power_Off();
    	}
		bt_connected = 0;
    }
	else if (ui_source_select == SOURCE_SELECT_HDMI)
	{
		if (hdmi_det_online)
		{
			//�ر�hdmi
			action_hdmi_off();
			usleep(1000);
		}
	}
	hdmi_on_flag = false;
    //player_process_cmd(NP_CMD_LINEIN_OFF, NULL, 0, NULL, NULL);
	//usleep(1000);
    player_process_cmd(NP_CMD_SPDIFIN_STOP, NULL, 0, NULL, NULL);
	usleep(1000);
    player_process_cmd(NP_CMD_STOP, NULL, 0, NULL, NULL);
	usleep(1000);
	player_process_cmd(NP_CMD_I2SIN_CLOSE, NULL, 1, NULL, NULL);
	usleep(1000);
	
	if (ui_source_ir_select >= 0)
	{
		ui_source_select = ui_source_ir_select;	    
		ui_source_ir_select = -1;
	}
	else
	{
		//?��???
	    if (ui_source_select < SOURCE_SELECT_END - 1)
	    {
	        ui_source_select++;
	    }
	    else
	    {
	        ui_source_select = SOURCE_SELECT_START + 1;
	    }
	}	
		
    if(NULL != wdtimer_goback_mode)
    {
        wd_cancel(wdtimer_goback_mode);
    }

	if( NULL != wdtimer_hdmion_send)
	{
		wd_cancel(wdtimer_hdmion_send);
	}

	
	is_set_spdif = false;
	
/*
	if (update_params_2_flash())
	{
		printf("write 2 flash success !\n");
	}
	else 
	{
		printf("write 2 flash fail !\n");
	}
*/
	ui_led_disp_mode(ui_source_select);

    play_local();
}

/****************************************************************************
 * Name: ui_handle_mute
 *
 * Description:
 *    ???????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_mute(void)
{
    printf("\n%s\n", __func__);
    if (mute_state == UNMUTE) //????
    {
		Hw_Amp_Mute();
		player_process_cmd(NP_CMD_VOLUME_SET, NULL, 0, NULL, NULL);
		
		mute_state = MUTE;
		
    }
    else						//???????
    {
		player_process_cmd(NP_CMD_VOLUME_SET, NULL, (int)mix_vol, NULL, NULL);
        mute_state = UNMUTE;
		
		Hw_Amp_UnMute();
		ui_led_disp_mode(ui_source_select);
		
    }
}

/****************************************************************************
 * Name: ui_handle_prev
 *
 * Description:
 *    ?????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_prev(void)
{
    if (ui_source_select == SOURCE_SELECT_BT)
    {   //??????
		int semval;
		sem_getvalue(&bt_state_sem, &semval);
		printf("%s %d semval :%d \n", __func__, __LINE__, semval);
        sem_wait(&bt_state_sem);
        handle_bt_cmd(BT_PRV);
        sem_post(&bt_state_sem);
    }
    else if (ui_source_select == SOURCE_SELECT_USB ||
             ui_source_select == SOURCE_SELECT_SD)
    {
        int *p_index = (ui_source_select == SOURCE_SELECT_USB?&usb_last_file_index:&sd_last_file_index);
        int *p_playtime = (ui_source_select == SOURCE_SELECT_USB?&usb_playtime:&sd_playtime);
        int total = get_file_total();
        if (total > 0)
        {
            if(--(*p_index) < 0)
            {
                *p_index = total-1;
            }
        }
        else
        {
            *p_index = 0;
        }
        *p_playtime = 0;
        handle_local_music_play(*p_index, *p_playtime);

		//????��??EEPROM
		//update_params_2_eeprom();
		
    }
	else if(ui_source_select == SOURCE_SELECT_FM)
	{
	
	}

    printf("%s", __func__);
}


/****************************************************************************
 * Name: ui_handle_finish
 *
 * Description:
 *    ???????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_finish(void)
{
    if (ui_source_select == SOURCE_SELECT_USB ||
             ui_source_select == SOURCE_SELECT_SD)
    {
        int *p_index = (ui_source_select == SOURCE_SELECT_USB?&usb_last_file_index:&sd_last_file_index);
        int *p_playtime = (ui_source_select == SOURCE_SELECT_USB?&usb_playtime:&sd_playtime);
        int total = get_file_total();
        if (total > 0)
        {
            if(++(*p_index) >= total)
            {
                *p_index = 0;
            }
	        *p_playtime = 0;
            handle_local_music_play(*p_index, *p_playtime);
			//????��??EEPROM
			//update_params_2_eeprom();
        }

    }
	else 
	{
		ui_handle_next();
	}
}

/****************************************************************************
 * Name: ui_handle_next
 *
 * Description:
 *    ?????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
unsigned char  ui_test_setvolume=0;
void ui_handle_next(void)
{
    if (ui_source_select == SOURCE_SELECT_BT)
    {
    	int val;
		sem_getvalue(&bt_state_sem, &val);
		printf("value :%d\n", val);
        sem_wait(&bt_state_sem);
        handle_bt_cmd(BT_NEXT);
        sem_post(&bt_state_sem);
		printf("%s sempost  :%d\n",__func__, val);
    }
    else if (ui_source_select == SOURCE_SELECT_USB ||
             ui_source_select == SOURCE_SELECT_SD)
    {
        int *p_index = (ui_source_select == SOURCE_SELECT_USB?&usb_last_file_index:&sd_last_file_index);
        int *p_playtime = (ui_source_select == SOURCE_SELECT_USB?&usb_playtime:&sd_playtime);
        int total = get_file_total();
        if (total > 0)
        {
            if(++(*p_index) >= total)
            {
                *p_index = 0;
            }
            *p_playtime = 0;
            handle_local_music_play(*p_index, *p_playtime);

			//????��??EEPROM
			//update_params_2_eeprom();
        }
    }
	else if(ui_source_select == SOURCE_SELECT_FM)
	{
	}

    printf("%s", __func__);
}

/****************************************************************************
 * Name: ui_handle_next_long_pressdown
 *
 * Description:
 *    FM????NEXT??????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_next_long_pressdown(void)
{

}

/****************************************************************************
 * Name: ui_handle_prev_long_pressdown
 *
 * Description:
 *    FM????prev??????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_prev_long_pressdown(void)
{

}

/****************************************************************************
 * Name: ui_handle_pause_play
 *
 * Description:
 *    ??????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_pause_play(void)
{
    printf("\n%s\n", __func__);

    if ((ui_source_select == SOURCE_SELECT_LINEIN) ||
		(ui_source_select == SOURCE_SELECT_LINEIN1) ||
		(ui_source_select == SOURCE_SELECT_HDMI) ||
        (ui_source_select == SOURCE_SELECT_SPDIFIN))
    {
    	if (aux_pause_state) //????
    	{
			player_process_cmd(NP_CMD_VOLUME_SET, NULL, (int)mix_vol, NULL, NULL);
			Hw_Amp_UnMute();			
			aux_pause_state = 0;
		}
		else 				//pause
		{
			player_process_cmd(NP_CMD_VOLUME_SET, NULL, 0, NULL, NULL);
			Hw_Amp_Mute();			
			aux_pause_state = 1;
		}
    }
    else if(ui_source_select == SOURCE_SELECT_BT)
    {   //??????
		int semval;
		sem_getvalue(&bt_state_sem, &semval);
		printf("%s %d semval :%d \n", __func__, __LINE__, semval);
        //???????????????????????
        if (bt_pause_state == 0) //???????
        {        
			//player_process_cmd(NP_CMD_VOLUME_SET, NULL, 0, NULL, NULL);
			//Hw_Amp_Mute();			
			bt_pause_state = 1;
			sem_wait(&bt_state_sem);
			handle_bt_cmd(BT_PLAY);
			sem_post(&bt_state_sem);
        }
		else 					//???????
		{
			//player_process_cmd(NP_CMD_VOLUME_SET, NULL, (int)mix_vol, NULL, NULL);
			//Hw_Amp_UnMute();			
			bt_pause_state = 0;
			sem_wait(&bt_state_sem);
			handle_bt_cmd(BT_PLAY);
			sem_post(&bt_state_sem);
		}	
		stop_state = 0;
	}
	/*
    else if(ui_source_select == SOURCE_SELECT_USB ||
            ui_source_select == SOURCE_SELECT_SD)
    {
        //?????????
        ui_info_t player_info;
        memset(&player_info, 0, sizeof(ui_info_t));
        player_get_info(&player_info);
        if (player_info.player_stat == 2)
        {   //???????
            //??????????????
            player_process_cmd(NP_CMD_PAUSE, NULL, 0, NULL, NULL);
        }
        else if (player_info.player_stat == 3)
        {   //???????
            //??????????????
            player_process_cmd(NP_CMD_RESUME, NULL, 0, NULL, NULL);
			usleep(20000);
			Hw_Amp_UnMute();			
        }
		
        if (stop_state) //else if (player_info.player_stat == 0)	
        {   
			Hw_Amp_UnMute();			
			if (ui_source_select == SOURCE_SELECT_USB)
			{
				handle_local_music_play(usb_last_file_index, usb_playtime);
			}
			else 
			{
				handle_local_music_play(sd_last_file_index, sd_playtime);
			}
			stop_state = 0;
        }
		//printf("player_stat %d", player_info.player_stat);
    }
	*/

}


/****************************************************************************
 * Name: ui_handle_pause_play
 *
 * Description:
 *    ?????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_stopplay(void)
{
    printf("\n%s\n", __func__);

	Hw_Amp_Mute();			
    if (ui_source_select == SOURCE_SELECT_LINEIN ||
        ui_source_select == SOURCE_SELECT_LINEIN1 ||
        ui_source_select == SOURCE_SELECT_SPDIFIN ||
        ui_source_select == SOURCE_SELECT_BT)
    {
		player_process_cmd(NP_CMD_VOLUME_SET, NULL, 0, NULL, NULL);
		aux_pause_state = 1;
    }
    else if(ui_source_select == SOURCE_SELECT_BT)
    {   //??????
        //???????????????????????
        if (stop_state == 0 && bt_pause_state == 0) //??????????????
        {
			int semval;
			sem_getvalue(&bt_state_sem, &semval);
			printf("%s %d semval :%d \n", __func__, __LINE__, semval);
	        sem_wait(&bt_state_sem);
	        handle_bt_cmd(BT_PAUSE);
	        sem_post(&bt_state_sem);			
			bt_pause_state = 1;
        }
    }
    else if(ui_source_select == SOURCE_SELECT_USB)
    {
        //??????????????
        player_process_cmd(NP_CMD_STOP, NULL, 0, NULL, NULL);
		usb_playtime = 0;
    }
	else if(ui_source_select == SOURCE_SELECT_SD)
	{
		//??????????????
		player_process_cmd(NP_CMD_STOP, NULL, 0, NULL, NULL);
		sd_playtime = 0;
	}
//	Digital_Disp_Status(DISP_STOP);
	stop_state = 1;			
}



/****************************************************************************
 * Name: ui_handle_power
 *
 * Description:
 *    ?????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/

void ui_handle_power(void)
{
	int ret;
	uint32_t  value = 0xFF;	
    if (ui_power < POWER_END - 1)
    {
        ui_power++;
    }
    else
    {
        ui_power = POWER_START + 1;
    }

    if (ui_power == POWER_ON)
    {   
        if (cur_freq == 6000000)
        {
            //enter_dynamic(NULL);
            printf("out of low power\n");
            //usb???
            //silan_usb_reset();
        }		
				
        if(sem_post(&bt_start_check_sem) == 0)
        {
            int value = 0;
            sem_getvalue(&bt_start_check_sem, &value);
            printf("%s,%d:Send semaphore to continue bluetooth check state success\n", __func__, value);
        }
        else
        {
            printf("%s:Send semaphore to continue bluetooth check state fail\n", __func__);
        }
		/*
		if (update_params_from_flash())
		{
			printf("read flash success !\n");
		}	
		else 
		{
			printf("read flash fail !\n");
		}
		*/
		zhuque_bsp_gpio_set_mode(HW_HDMI_DET_PIN, GPIO_IN, PULLING_HIGH);
		zhuque_bsp_gpio_get_value(HW_HDMI_DET_PIN, &value);

		if (value == 0)
		{
			usleep(20000);
			value = 0xff;
			zhuque_bsp_gpio_get_value(HW_HDMI_DET_PIN, &value);
			if (value == 0)
			{
				hdmi_det_online = true;
				printf("\n[HDMI] detected hdmi insert");
				ui_source_select = SOURCE_SELECT_HDMI - 1;
			}
		}
		else 
		{
			if (ui_source_select <= SOURCE_SELECT_START || ui_source_select >= SOURCE_SELECT_END)
			{
	        	ui_source_select = SOURCE_SELECT_START;
			}
		}
		
		//set_golr_gain(0);
		
		/*0到100对应  -64到0db*/

		set_adc0_vol(0);
		set_adc1_vol(0);
		set_adc2_vol(ADC2_MAX_VOLUME);
		set_decoder_vol(DECODER_MAX_VOLUME);
			
		//sl_ui_set_samp(0);
		
        ui_handle_mode();

		/*
		if (ui_source_select == SOURCE_SELECT_HDMI)
		{
			action_hdmi_poweron();
		}
  		*/
	}
    else
    {	    	
    	printf("power down ! %d\n", ui_power);
		
		Hw_Amp_Mute();			

		ui_led_clear();
		//led_clear_buffer();
		//led_timer_stop();
		
		player_process_cmd(NP_CMD_VOLUME_SET, NULL, 0, NULL, NULL);
		
        player_process_cmd(NP_CMD_STOP, NULL, 0, NULL, NULL);
        usleep(1000);

        #if BYPASS_MODE
        silan_set_linebypass_disable();
        usleep(100);
        #endif

        #if (BYPASS_MODE || INNERADC_MODE)
        player_process_cmd(NP_CMD_LINEIN_OFF, NULL, 0, NULL, NULL);
        usleep(100);
        #else
        player_process_cmd(NP_CMD_I2SIN_CLOSE, NULL, 1, NULL, NULL);
        usleep(1000);
        #endif

        player_process_cmd(NP_CMD_SPDIFIN_STOP, NULL, 0, NULL, NULL);
        usleep(1000);

		//ͨ通知电视进入待机
		//action_hdmi_standby();
		
        //?????????????????
        if (wdtimer_goback_mode != NULL)
        {
            wd_cancel(wdtimer_goback_mode);
        }

        //????????????
        bt_connected = false;

        ui_source_select = SOURCE_SELECT_START;

		/*
        if (cur_freq == 300000000)
        {
            //???usb
            //usb_manual_disconnect();
            //sysfs_usb_umount();

            //???sd??
            //sysfs_sd_umount();

            printf("enter low power\n");
            //enter_dynamic(NULL);
        }
		Bt_Power_Off();
		*/
		//通知蓝牙关机
		sem_wait(&bt_state_sem);
		handle_bt_cmd(BT_AT_PWROFF);
		sem_post(&bt_state_sem);

		
		if (hdmi_on_flag)
		{
			hdmi_on_flag = false;
			action_hdmi_off();
			//usleep(1000);
			//action_hdmi_standby();
		}
		printf("go to sleep ...\n");
		while(1) usleep(1000);
    }   
}


void ui_handle_hdmi_poweroff(void)
{
	printf("hdmi power down ! %d\n", ui_power);
	
	ui_power = POWER_OFF;
	
	Hw_Amp_Mute();			
	led_clear_buffer();
	led_timer_stop();
	
	player_process_cmd(NP_CMD_VOLUME_SET, NULL, 0, NULL, NULL);
	usleep(1000);
	player_process_cmd(NP_CMD_STOP, NULL, 0, NULL, NULL);
	usleep(1000);
	
	//if (hdmi_det_online)
	//{
		//action_hdmi_off();
		//usleep(1000);
		//action_hdmi_standby();
	//}
	
#if BYPASS_MODE
	silan_set_linebypass_disable();
	usleep(100);
#endif
	
#if (BYPASS_MODE || INNERADC_MODE)
	player_process_cmd(NP_CMD_LINEIN_OFF, NULL, 0, NULL, NULL);
	usleep(100);
#else
	player_process_cmd(NP_CMD_I2SIN_CLOSE, NULL, 1, NULL, NULL);
	usleep(1000);
#endif
	
	player_process_cmd(NP_CMD_SPDIFIN_STOP, NULL, 0, NULL, NULL);
	usleep(1000);
	
	//ͨ通知电视进入待机
	//action_hdmi_standby();
	
	//?????????????????
	if (wdtimer_goback_mode != NULL)
	{
		wd_cancel(wdtimer_goback_mode);
	}
	
	//????????????
	bt_connected = false;
	
	ui_source_select = SOURCE_SELECT_START;
	
	/*
	if (cur_freq == 300000000)
	{
		//???usb
		//usb_manual_disconnect();
		//sysfs_usb_umount();
	
		//???sd??
		//sysfs_sd_umount();
	
		//printf("enter low power\n");
		//enter_dynamic(NULL);
	}
	*/
	
	//Bt_Power_Off();
	
	//通知蓝牙关机
	sem_wait(&bt_state_sem);
	handle_bt_cmd(BT_AT_PWROFF);
	sem_post(&bt_state_sem);
	
	while(1) usleep(1000);
}

/****************************************************************************
 * Name: ui_handle_sd_unload
 *
 * Description:
 *    SD??��?????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_sd_unload(void)
{
    if(ui_source_select == SOURCE_SELECT_SD)
    {
        player_process_cmd(NP_CMD_STOP, NULL, 0, NULL, NULL);
        usleep(100);
    }

    if(ui_source_select != SOURCE_SELECT_USB)
    {
        //????????��?
        reset_playlist();
    }
	
	is_sd_load = false;
}



/****************************************************************************
 * Name: ui_handle_up
 *
 * Description:
 *    ?????????????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_up(void)
{
/*
    if (mute_state == MUTE)
    {
        ui_handle_mute();
    }
*/
    ui_process_vol_inc();

#ifdef SL_UI_DBG
    printf("%s, volume_up\n", __func__);
#endif
}

static void ui_post_event(int code, int value)
{
	struct input_event ui_event;
	memset(&ui_event, 0, sizeof(struct input_event));
	ui_event.type = EV_UI;
	ui_event.value = value;
	ui_event.code = code;
	input_add_event(&ui_event);
}

/****************************************************************************
 * Name: ui_handle_usb_out
 *
 * Description:
 *    USB?��????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_usb_out(void)
{
    if(ui_source_select == SOURCE_SELECT_USB)
    {
        player_process_cmd(NP_CMD_STOP, NULL, 0, NULL, NULL);
        usleep(100);
		ui_post_event(CODE_UI_UPDATE_DONE, 0);
    }

    if(ui_source_select != SOURCE_SELECT_SD)
    {
        //????????��?
        reset_playlist();
    }
	
	is_usb_load = false;
}

/****************************************************************************
 * Name: ui_handle_vol_dec_long_press
 *
 * Description:
 *    ?????????????????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_vol_dec_long_press(void)
{
    if (NULL == wdtimer_vol_longpress)
    { //??????
        wdtimer_vol_longpress = wd_create();
    }
    else
    { //???????????
        wd_cancel(wdtimer_vol_longpress);
    }

    //???????????????
    ui_cmd_t cmd;
    cmd.cmd = UI_CMD_BT_DOWN;
    send_cmd_2_ui(&cmd);

    if (NULL != wdtimer_vol_longpress)
    { //??��??????????
        //????????????????
        wd_start(wdtimer_vol_longpress, CLOCKS_PER_SEC / 4, (wdentry_t)ui_handle_vol_dec_long_press, 0);
    }
}

/****************************************************************************
 * Name: ui_handle_vol_inc_long_press
 *
 * Description:
 *    ???????????????????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_vol_inc_long_press(void)
{
    if (NULL == wdtimer_vol_longpress)
    { //??????
        wdtimer_vol_longpress = wd_create();
    }
    else
    { //???????????
        wd_cancel(wdtimer_vol_longpress);
    }

    //???????????????
    ui_cmd_t cmd;
    cmd.cmd = UI_CMD_BT_UP;
    send_cmd_2_ui(&cmd);

    if (NULL != wdtimer_vol_longpress)
    { //??��??????????
        //????????????????
        wd_start(wdtimer_vol_longpress, CLOCKS_PER_SEC / 4, (wdentry_t)ui_handle_vol_inc_long_press, 0);
    }
}

/****************************************************************************
 * Name: ui_handle_vol_long_press_up
 *
 * Description:
 *    ?????????????????????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void ui_handle_vol_long_press_up(void)
{
    if (NULL != wdtimer_vol_longpress)
    { //???????????
        wd_cancel(wdtimer_vol_longpress);
    }
}

/****************************************************************************
 * Name: ui_process_vol_dec
 *
 * Description:
 *    ??????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static void ui_process_vol_dec(void)
{
	int vol_temp=0;
	if (set_vol >= VOL_STEP) set_vol -= VOL_STEP;
	else   set_vol = 0;
	
	/*
    //??????????
    //display_volume(set_vol);
    mix_vol = set_vol * (100.0f/32) ;
    player_process_cmd(NP_CMD_VOLUME_SET, NULL, (int)mix_vol, NULL, NULL);
	usleep(100);
	ui_led_disp_volume(set_vol);
	is_volume_mode = true;
	ui_goback_source(900);
	*/
	
	sem_wait(&bt_state_sem);
	handle_bt_vol(set_vol);
	sem_post(&bt_state_sem);
	
	
    #if 0 //BYPASS_MODE
    bypass_in_vol -= BYPASS_VOL_IN_STEP;
    if(bypass_in_vol <= BYPASS_VOL_IN_MIN || mix_vol < VOL_STEP)
    {
        bypass_in_vol = BYPASS_VOL_IN_MIN;
        if(ui_source_select != SOURCE_SELECT_SPDIFIN)
        {
            silan_set_linebypass_disable();
        }
    }
    else
    {
        if(ui_source_select != SOURCE_SELECT_SPDIFIN)
        {
            float vol = bypass_in_vol + bypass_vol_offset;
            silan_set_hardware_gilr_volume(vol, vol);
        }
    }
    printf("%s:bypass_in_vol=%d\n", __func__, bypass_in_vol);
    #endif
}

/****************************************************************************
 * Name: ui_process_vol_inc
 *
 * Description:
 *    ???????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static void ui_process_vol_inc(void)
{
    set_vol += VOL_STEP;
    if(set_vol > 32)
    {
        set_vol = 32;
    }
    //??????????
    //display_volume(set_vol);
	/*
    mix_vol = set_vol * (100.0f/32) ;
    player_process_cmd(NP_CMD_VOLUME_SET, NULL, (int)mix_vol, NULL, NULL);
	usleep(1000);
	
	ui_led_disp_volume(set_vol);
	is_volume_mode = true;
	//ui_goback_source(900);
	*/
	sem_wait(&bt_state_sem);
	handle_bt_vol(set_vol);
	sem_post(&bt_state_sem);
	
    #if 0//BYPASS_MODE
    if(bypass_in_vol == BYPASS_VOL_IN_MIN)
    {
        if(ui_source_select != SOURCE_SELECT_SPDIFIN)
        {
            silan_set_linebypass_enable();
        }
    }

    bypass_in_vol += BYPASS_VOL_IN_STEP;
    if(bypass_in_vol > BYPASS_VOL_IN_MAX || mix_vol > 100)
    {
        bypass_in_vol = BYPASS_VOL_IN_MAX;
        if(ui_source_select != SOURCE_SELECT_SPDIFIN)
        {
            float vol = bypass_in_vol + bypass_vol_offset;
            silan_set_hardware_gilr_volume(vol, vol);
        }
    }	
    else
    {
        if(ui_source_select != SOURCE_SELECT_SPDIFIN)
        {
            float vol = bypass_in_vol + bypass_vol_offset;
            silan_set_hardware_gilr_volume(vol, vol);
        }
    }
    printf("%s:bypass_in_vol=%d\n", __func__, bypass_in_vol);
    #endif
}

void ui_handle_bt_set_vol(int value)
{
	set_vol = value;
	printf("%s %d\n", __func__, set_vol);
}

/****************************************************************************
 * Name: ui_update_music_time
 *
 * Description:
 *    ??????????
 *
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static int recorddatacnt=0;
static int dispdelaycnt=0;
static bool flashcol=false;
void ui_update_music_time(void)
{
    if(((is_usb_load && ui_source_select == SOURCE_SELECT_USB) ||
        (is_sd_load && ui_source_select == SOURCE_SELECT_SD)) &&
        ui_power == POWER_ON )
    {
		static bool showed = true;
		ui_info_t player_info;
		//????????????
		player_get_info(&player_info);

		if (player_info.player_stat == 2 ||
		   (player_info.player_stat == 3 && !showed))
		{   //????????????????????
		   int * seek_time_p = (ui_source_select == SOURCE_SELECT_USB?&usb_playtime:&sd_playtime);
		   int curtime = player_info.curtime;
		   //???seek?????????��???????
		   if(curtime < *seek_time_p)
		   {
			   curtime = *seek_time_p;
		   }
		   else 
		   {
			   if (curtime < *seek_time_p + 5)
			   {
			   	   *seek_time_p = curtime;
		   		   if (++recorddatacnt >= 2)
				   {
					   recorddatacnt = 0;
					   //??????��??
//					   if(update_params_2_eeprom())
//					   {
//						   //update_params_from_eeprom();
//					   }
//					   else
//					   {
//						   printf("write params to EEPROM fail\n");
//					   }
				   }
			   }
		   }

		   if (!is_volume_mode && mute_state != MUTE && !stop_state)
		   {
//           	   ui_led_disp_music_time(curtime);
//			   if (flashcol == false) ui_led_disp_col2(1);
//			   else ui_led_disp_col2(0);
			   flashcol = flashcol?0:1;
//			   if (showed==false) ui_led_disp_col2(1);
			   showed = true;
//			   ui_led_update_display();
		   	}
		}
		else if (player_info.player_stat == 3 && showed)
		{   //????????
		   showed = false;
//		   ui_led_clear();
//		   ui_led_update_display();
		}
    }

}

void ui_handle_mic_pair(void)
{

}


#define eq_set_ch		6 
/*
* - standard
1,	   0,	   1,	   0,	   100,    100,	 
2,	   0,	   1,	   0,	   300,    100,	 
3,	   0,	   1,	   0,	   1000,   300,	 
4,	   0,	   1,	   0,	   3000,   300,	 
5,	   0,	   1,	   0,	   8000,   300

*
* - class
1,	   0,	   1,	   0,	   100,    100,
2,	   0,	   1,	   -500,   300,    100,
3,	   0,	   1,	   -1200,  1000,   300,
4,	   0,	   1,	   -1000,  3000,   300,
5,	   0,	   1,	   -500,   8000,   300

*
* - jazz
1,	   0,	   1,	   -1200,  100,    100, 
2,	   0,	   1,	   -800,   300,    100,
3,	   0,	   1,	   -140,   1000,   300,
4,	   0,	   1,	   0,	   3000,   300,
5,	   0,	   1,	   -800,   8000,   300

*
* - rock
1,	   0,	   1,	   0,	   100,    100,
2,	   0,	   1,	   -400,   300,    100,
3,	   0,	   1,	   -1200,  1000,   300,
4,	   0,	   1,	   -1200,  3000,   300,
5,	   0,	   1,	   -400,   8000,   300

*		
* - pop
1,	   0,	   1,	   -200,   100,    100,
2,	   0,	   1,	   0,	   300,    100,
3,	   0,	   1,	   -1100,  1000,   300,
4,	   0,	   1,	   -1200,  3000,   300,
5,	   0,	   1,	   -1100,  8000,   300
*/
const int eq_jazz[]={
//flt_id, type,  onoff,  gain,      fc,      q,    ch 
	1,	   0,	   1,	   -1200,  100,    100, 	eq_set_ch,
	2,	   0,	   1,	   -800,   300,    100,	 	eq_set_ch,	
	3,	   0,	   1,	   -140,   1000,   300, 	eq_set_ch,
	4,	   0,	   1,	   0,	   3000,   300, 	eq_set_ch,
	5,	   0,	   1,	   -800,   8000,   300, 	eq_set_ch
};

//movie
const int eq_pop[]={
	//flt_id, type, onoff, gain, fc, q
	1,	   0,	   1,	   -200,   100,    100, 	eq_set_ch,
	2,	   0,	   1,	   0,	   300,    100, 	eq_set_ch,
	3,	   0,	   1,	   -1100,  1000,   300, 	eq_set_ch,
	4,	   0,	   1,	   -1200,  3000,   300, 	eq_set_ch,
	5,	   0,	   1,	   -1100,  8000,   300, 	eq_set_ch
};

const int eq_classic[]={
	//flt_id, type, onoff, gain, fc, q
	1,	   0,	   1,	   0,	   100,    100, 	eq_set_ch,
	2,	   0,	   1,	   -500,   300,    100, 	eq_set_ch,
	3,	   0,	   1,	   -1200,  1000,   300, 	eq_set_ch,
	4,	   0,	   1,	   -1000,  3000,   300, 	eq_set_ch,
	5,	   0,	   1,	   -500,   8000,   300, 	eq_set_ch

};
	
const int eq_flat[]={
	//flt_id, type, onoff, gain, fc, q
	1,	   0,	   1,	   0,	   100,    100, 	eq_set_ch,  
	2,	   0,	   1,	   0,	   300,    100, 	eq_set_ch,  
	3,	   0,	   1,	   0,	   1000,   300, 	eq_set_ch,  
	4,	   0,	   1,	   0,	   3000,   300, 	eq_set_ch,  
	5,	   0,	   1,	   0,	   8000,   300, 	eq_set_ch

};

const int eq_rock[]={
	//flt_id, type, onoff, gain, fc, q
	1,	   0,	   1,	   0,	   100,    100, 	eq_set_ch,
	2,	   0,	   1,	   -400,   300,    100, 	eq_set_ch,
	3,	   0,	   1,	   -1200,  1000,   300, 	eq_set_ch,
	4,	   0,	   1,	   -1200,  3000,   300, 	eq_set_ch,
	5,	   0,	   1,	   -400,   8000,   300, 	eq_set_ch
};

void ui_handle_eq_jazz(void)
{
	int i,j;
	char set_eq_text[64];
	swa_audio_audproc_load(AUDPROC_LIST_MIX, AUDPROC_EQ);
	usleep(100);
	for (i = 0, j = 0; i < 5; i++, j += 7)
	{
		swa_audio_audproc_eq(AUDPROC_LIST_MIX, (ae_eq_para *)&eq_jazz[j]);
		swa_audio_audproc_set(AUDPROC_LIST_MIX, AUDPROC_EQ);
	}		

	printf("%s \n", __func__);
	/*
	if (!need_reload_eq)
	{
		ui_led_disp_state(2);
		is_volume_mode = true;
		ui_goback_source(900);
	}
	
	is_movie_mode = false;
	*/
}

void ui_handle_eq_pop(void)
{
	int i,j;
	char set_eq_text[64];
	swa_audio_audproc_load(AUDPROC_LIST_MIX, AUDPROC_EQ);
	usleep(100);
	for (i = 0, j = 0; i < 5; i++, j += 7)
	{
		swa_audio_audproc_eq(AUDPROC_LIST_MIX, (ae_eq_para *)&eq_pop[j]);
		swa_audio_audproc_set(AUDPROC_LIST_MIX, AUDPROC_EQ);
	}		
	printf("%s \n", __func__);

	/*
	if (!need_reload_eq)
	{
		ui_led_disp_state(2);
		is_volume_mode = true;
		ui_goback_source(900);
	}
	
	is_movie_mode = false;
	*/

}

void ui_handle_eq_class(void)
{
	int i,j;
	char set_eq_text[64];
	swa_audio_audproc_load(AUDPROC_LIST_MIX, AUDPROC_EQ);
	usleep(100);
	for (i = 0, j = 0; i < 5; i++, j += 7)
	{
		swa_audio_audproc_eq(AUDPROC_LIST_MIX, (ae_eq_para *)&eq_classic[j]);
		swa_audio_audproc_set(AUDPROC_LIST_MIX, AUDPROC_EQ);
	}		
	printf("%s \n", __func__);

	/*
	if (!need_reload_eq)
	{
		ui_led_disp_state(2);
		is_volume_mode = true;
		ui_goback_source(900);
	}
	
	is_movie_mode = false;
	*/

}

void ui_handle_eq_flat(void)
{
	int i,j;
	char set_eq_text[64];
	swa_audio_audproc_load(AUDPROC_LIST_MIX, AUDPROC_EQ);
	usleep(100);
	for (i = 0, j = 0; i < 5; i++, j += 7)
	{
		swa_audio_audproc_eq(AUDPROC_LIST_MIX, (ae_eq_para *)&eq_flat[j]);
		swa_audio_audproc_set(AUDPROC_LIST_MIX, AUDPROC_EQ);
	}		
	printf("%s \n", __func__);

	/*
	if (!need_reload_eq)
	{
		ui_led_disp_state(2);
		is_volume_mode = true;
		ui_goback_source(900);
	}
	
	is_movie_mode = false;
	*/

}

void ui_handle_eq_rock(void)
{
	int i,j;
	char set_eq_text[64];
	swa_audio_audproc_load(AUDPROC_LIST_MIX, AUDPROC_EQ);
	usleep(100);
	for (i = 0, j = 0; i < 5; i++, j += 7)
	{
		swa_audio_audproc_eq(AUDPROC_LIST_MIX, (ae_eq_para *)&eq_rock[j]);
		swa_audio_audproc_set(AUDPROC_LIST_MIX, AUDPROC_EQ);
	}		
	printf("%s \n", __func__);

	/*
	if (!need_reload_eq)
	{
		ui_led_disp_state(2);
		is_volume_mode = true;
		ui_goback_source(900);
	}
	
	is_movie_mode = false;
	*/

}

void ui_handle_eq(void)
{
	static int eq_sel = 0;

	eq_sel++;
	if (eq_sel > 5)
	{
		eq_sel = 1;;
	}
	
	switch(eq_sel)
	{
		case 1:
			ui_handle_eq_jazz();
		break;

		case 2:
			ui_handle_eq_pop();
		break;

		case 3:
			ui_handle_eq_class();
		break;

		case 4:
			ui_handle_eq_flat();
		break;

		case 5:
			ui_handle_eq_rock();
		break;	
	}
/*
	swa_audio_audproc_load(AUDPROC_LIST_MIX, AUDPROC_EQ); 
		
	//设置第一个通道的drc参数,attack=100,release=200,threshold=0,ratio=1,channel=0
	int drc_parameter[5] = {100, 200, 0, 1, 0};
	swa_audio_audproc_drc(AUDPROC_LIST_MIX, drc_parameter);
	swa_audio_audproc_set(AUDPROC_LIST_MIX, AUDPROC_COMPRESSOR);
	
	//设置第二个通道的drc参数,attack=100,release=200,threshold=-6,ratio=1,channel=1
	drc_parameter[4] = 1;
	swa_audio_audproc_drc(AUDPROC_LIST_MIX, drc_parameter);
	swa_audio_audproc_set(AUDPROC_LIST_MIX, AUDPROC_COMPRESSOR);
*/
}

void ui_handle_reload_eq(int sel)
{
	if (sel == 1)
	{
		ui_handle_eq_music();
	}
	else if (sel == 2)
	{
		ui_handle_eq_movie();
	}
	else if (sel == 3)
	{
		ui_handle_eq_dialog();
	}
	usleep(100);
    update_bass_treble(&bass_level, false);
	usleep(100);
    update_bass_treble(&treble_level, true);
	usleep(100);
	need_reload_eq = false;

	printf("%s %d\n", __func__, sel);
}


#ifdef AUDIO_ENERGY_DEBUG	
int energy[6];
int det_energy_cnt=0;
bool is_det_need_mute = true;
#endif

void get_energy_init(void)
{
#ifdef AUDIO_ENERGY_DEBUG	
	int err = swa_audio_audproc_load(AUDPROC_LIST_MIX, AUDPROC_ENERGY);
	printf("swa_audio_audproc_load: %d \n", err);
	err = swa_audio_audproc_energy(AUDPROC_LIST_MIX, 30);
	printf("swa_audio_audproc_energy :%d \n", err);
#endif
}

void ui_source_detect_handle(void)
{
	static int cont = 0;
	if (ui_power == POWER_ON)// && ui_source_select != SOURCE_SELECT_BT)
	{
#ifdef AUDIO_ENERGY_DEBUG
			if (cont++ >= 4)
			{
				cont = 0;
				swa_audio_audproc_get_energy(AUDPROC_LIST_MIX, &energy);
				printf("swa_audio_audproc_get_energy %d %d \n", energy[0], energy[1]);
			}
#endif
/*
			if (energy[0] > 500 || energy[1] > 500)
			{
				if (++det_energy_cnt >= 10) 
				{
					det_energy_cnt = 0;
					is_det_need_mute = false;
				}
			}
			else 
			{
				det_energy_cnt = 0;
				is_det_need_mute = true;
			}
			if (mute_state == UNMUTE) 
			{
				if (!is_det_need_mute)
				{
					Hw_Amp_UnMute();
				}
				else	//����Դʱ����
				{
					Hw_Amp_Mute(); 
				}
			}
			*/
	}
	
}

static int bt_mute_det_cnt = 0;
static int bt_unmute_det_cnt = 0;
void ui_bt_mute_handle(void)
{
	uint32_t ioval = 0;
    if(ui_source_select == SOURCE_SELECT_BT && ui_power == POWER_ON) 
    {
		//������Դ״̬
		if (mute_state == UNMUTE) 
		{
			zhuque_bsp_gpio_get_value(HW_BT_MUTE_PIN, &ioval);
			if (ioval)
			{
				bt_unmute_det_cnt = 0;
				if (++bt_mute_det_cnt >= 30)
				{
					Hw_Amp_UnMute();
					bt_mute_det_cnt = 0;
				}
			}
			else 
			{
				bt_mute_det_cnt = 0;
				if (++bt_unmute_det_cnt >= 5)
				{
					bt_unmute_det_cnt = 0;
					Hw_Amp_Mute();
				}
			}	
		}
    }
}

void ui_handle_hdmi_det(void)
{
		static int count1,count2;
		uint32_t   det_value = 0xFF;
		ui_cmd_t cmd;
	
		zhuque_bsp_gpio_set_mode(HW_HDMI_DET_PIN, GPIO_IN, PULLING_HIGH);
		zhuque_bsp_gpio_get_value(HW_HDMI_DET_PIN, &det_value);
	
	/////////////////////////////////////////////////////
	
		if(det_value == 0)
		{
			count2=0;
			if(count1<100)
			{
				count1++;
				if(count1>20)
				{
					count1=200;
					hdmi_det_online=true;
	
					cmd.cmd = UI_CEC_HDMI_INSERT;
					send_cmd_2_ui(&cmd);
	
				}
			}
		}
		else
		{
			count1=0;	
			if(count2<100)
			{
				count2++;
				if(count2>20)
				{
					count2=200;
					hdmi_det_online=false;
	
					cmd.cmd = UI_CEC_HDMI_PULL_OUT;
					send_cmd_2_ui(&cmd);
	
				}	
			}
		}
	
	
	////////////////////////////////////
	

}


#ifdef CONFIG_CEC
int action_hdmion_send(void)
{
	cec_process_cmd(CEC_CMD_ARCON, NULL);
	usleep(100);
}

int action_hdmi_poweron_init(void)
{
    int cec_cmd_gpio = HW_HDMI_CEC_PIN;  
	printf("%s %d\n", __func__, __LINE__);
    cec_process_cmd(CEC_CMD_ARC_INIT, &cec_cmd_gpio);
	usleep(1000);
	cec_process_cmd(CEC_CMD_ARCON, NULL);
	usleep(1000);
	cec_process_cmd(CEC_CMD_POWERON, NULL);
	usleep(1000);
}

int action_hdmi_on(void)
{
    int cec_cmd_gpio = HW_HDMI_CEC_PIN;  
	printf("%s %d\n", __func__, __LINE__);
     
    cec_process_cmd(CEC_CMD_ARC_INIT, &cec_cmd_gpio);
	usleep(1000);
	cec_process_cmd(CEC_CMD_ARCON, NULL);
	usleep(1000);
	player_process_cmd(NP_CMD_SPDIFIN_STOP, NULL, 0, NULL, NULL);
	usleep(1000);
	player_process_cmd(NP_CMD_SPDIFIN_START, NULL, 0, NULL, NULL);
	usleep(1000);

	hdmi_on_flag = true;
	return SL_UI_ERROR_NULL;
}

int action_hdmi_off(void)
{
	printf("%s %d\n", __func__, __LINE__);
      
	cec_process_cmd(CEC_CMD_ARCOFF, NULL);
	usleep(1000);
	//player_process_cmd(NP_CMD_SPDIFIN_STOP, NULL, 0, NULL, NULL);
	//usleep(1000);
	return SL_UI_ERROR_NULL;
}

int action_hdmi_standby(void)
{
	printf("%s %d\n", __func__, __LINE__);
       
	cec_process_cmd(CEC_CMD_STANDBY, NULL);
	usleep(1000);
	//player_process_cmd(NP_CMD_SPDIFIN_STOP, NULL, 0, NULL, NULL);
	return SL_UI_ERROR_NULL;
}

int action_hdmi_poweron(void)
{
	printf("%s %d\n", __func__, __LINE__);
       
    //cec_process_cmd(CEC_CMD_ARCON, NULL);
	//usleep(1000);
	cec_process_cmd(CEC_CMD_POWERON, NULL);
	usleep(1000);
	return SL_UI_ERROR_NULL;
}

//���ӿ�soundbar
void ui_handle_cec_active_source(void)
{
	if (ui_source_select != SOURCE_SELECT_HDMI)
	{
		ui_source_ir_select = SOURCE_SELECT_HDMI;
		ui_handle_mode();
	}
}



//���ӹ�soundbar
void ui_handle_cec_inactive_source(void)
{
	if (ui_source_select == SOURCE_SELECT_HDMI)
	{
//		ui_source_ir_select = SOURCE_SELECT_BT;
//		ui_handle_mode();
		
		ui_handle_hdmi_poweroff();
	}
}

void ui_handle_cec_insert(void)
{
	//if (ui_source_select != SOURCE_SELECT_HDMI)
	{
		ui_source_ir_select = SOURCE_SELECT_HDMI;
		ui_handle_mode();
	}
}

void ui_handle_cec_pull_out(void)
{
	if (ui_source_select == SOURCE_SELECT_HDMI)
	{
		action_hdmi_off();
	}
}


#endif

int for_test_state = 0;
void juset_for_test(void)
{


	if (for_test_state == 0)
	{
		ui_handle_eq_music();
	}
	else if (for_test_state == 1) 
	{
		ui_handle_eq_movie();
	}
	else if (for_test_state == 2) 
	{
		ui_handle_eq_dialog();
	}

	for_test_state++;
	if (for_test_state >= 3)
	{
		for_test_state = 0;
	}

}



void ui_handle_check_playing(void)
{
	int ret;
	ret = swa_audio_check_playing();
	printf("%s %d \n", __func__, ret);
//	if (ret == 1)	
//	{
//	
//		ui_cmd_t cmd;
//		cmd.cmd = UI_CMD_EQ_RELOAD;
//		send_cmd_2_ui(&cmd);
//		
//	}

}

int set_gor_gain = 50;
void ui_handle_balence_vol(int flag)
{
	if (flag)
	{
		if (set_gor_gain < 100)
		set_gor_gain++;
	}
	else 
	{
		if (set_gor_gain > 0)
			set_gor_gain--;
	}
	
	if (ui_source_select == SOURCE_SELECT_HDMI ||
		ui_source_select == SOURCE_SELECT_SPDIFIN)
	{
		set_decoder_vol(set_gor_gain);
	}
	else 
	{
		set_adc2_vol(set_gor_gain);
	}
	
	ui_led_disp_volume(set_gor_gain);
	is_volume_mode = true;
	ui_goback_source(900);

}


/****************************************************************************
 * Name: update_params_2_flash
 *
 * Description:
 *    写数据到flash
 *
 * Parameters:
 *
 * Returned Value: ture : success   false : fail
 * 
 * Assumptions:
 *
 ****************************************************************************/
bool update_params_2_flash(void)
{

    bool ret = false;
    int buf[0x100] = {1, (int)(ui_source_select - 1),  0};
    yunos_bsp_flash_erase(FLASH_USER_SPACE_ADDR, 0xd8);
    int i = 0;
    for(i=0;i<2;++i)
    {
        if(zhuque_bsp_flash_page_program(FLASH_USER_SPACE_ADDR, sizeof(buf), (int)buf) == 0)
        {
            break;
        }
    }

    if (i < 2)
    {
        ret = true;
    }
    return ret;

}

/****************************************************************************
 * Name: update_params_from_flash
 *
 * Description:
 *    从flash读取数据
 *
 * Parameters:
 *
 * Returned Value: ture : success   false : fail
 * 
 * Assumptions:
 *
 ****************************************************************************/
bool update_params_from_flash(void)
{
    bool ret = false;
    int i;
    int buf[0x100] = {0};
    int length = sizeof(buf);
    zhuque_bsp_flash_read(FLASH_USER_SPACE_ADDR, length, (unsigned char *)buf);
	printf("%s read buf\n", __func__);
    for(i=0;i<20;++i)
    {
       printf(" buf[%d]=%x ", i, buf[i]);
    }

    if(buf[0] == 1)
    {		
        ui_source_select = buf[1];
		printf("------>>>>%s, ui_source_select:%d \n", __func__, ui_source_select);
		ret = true;
    }
    else
    {
        if(update_params_2_flash())
        {
            printf("write params 2 flash success\n");
        }
    }
    return ret;


}

void ui_handle_usb_emu_timeout(void)
{
#ifdef CONFIG_SILAN_USBHS
	printf("\n%s %d", __func__, __LINE__);
	usb_manual_disconnect();
	sysfs_usb_umount();
	silan_usb_task_del();
	silan_usb_initialize();
#endif	
}


