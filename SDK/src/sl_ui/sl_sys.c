/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <arch/chip/silan_timer.h>
#include <fcntl.h> /* For O_* constants */
#include <nuttx/audio/silan_audio_api.h>
#include <nuttx/config.h>
#include <nuttx/sys_conf.h>
#include <nxplayer.h>
#include <mqueue.h>
#include <player_cmd.h>
#include "sl_ui_cmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> /* For mode constants */
#include "tone_data.h"
#include "sl_ui_handle.h"
#include <apps/builtin.h>
#include "sl_bsp.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#ifdef CONFIG_WIRELESS
#ifdef CONFIG_BOARD_SHENZHEN
#define GPIO2_13_ 45
#define GPIO2_7_ 39
#define GPIO2_8_ 40
#define CONFIG_MHD_IRQ_PIN_ 43
#define CONFIG_MHD_RESET_PIN_ 40
#else

#define GPIO1_2 2
#define GPIO1_3 3
#define GPIO1_4 4
#endif
#endif
 
#if defined(CONFIG_CHIP_SC6138)
	const char *g_product_version = "product_version_6138A-1-0";
#elif defined(CONFIG_BOARD_AP_8835C)
	const char *g_product_version = "product_version_8835C-1-0";
#elif defined(CONFIG_BOARD_AP_5864B)
	const char *g_product_version = "product_version_5864B-1-0";
#elif defined(CONFIG_BOARD_AP_5864B_2)
	const char *g_product_version = "product_version_5864B-2-0";
#endif

#define PARTITION_LEN 64
static char flash_part[CONFIG_MTD_PARTITIONS][PARTITION_LEN] = {   
#if CONFIG_CHIP_SC6138
#if CONFIG_FLASH_4M
    "boot,     0x00000000, 0x00008000",
	"btupdate1,0x00008000, 0x00001000",
	"btupdate2,0x00009000, 0x00001000",
    "btconf,   0x0000a000, 0x00008000",
    "image2,   0x00012000, 0x00200000",
    "sysconf1, 0x00212000, 0x00001000",
    "sysconf2, 0x00213000, 0x00001000",
	"sysdata,  0x00214000, 0x00001000",
	"wifibin,  0x00215000, 0x00070000",
    "fs,       0x00285000, 0x00001000",
    "userspace,0x00286000, 0x00001000",
    "tonespace,0x00287000, 0x00030000",
    "table,    0x002b7000, 0x00012000",
    "chfnt,    0x002c9000, 0x000f5000",
	"backup,   0x003be000, 0x00320000"
#else
    "boot,     0x00000000, 0x00008000",
	"btupdate1,0x00008000, 0x00001000",
	"btupdate2,0x00009000, 0x00001000",
    "btconf,   0x0000a000, 0x00008000",
    "image2,   0x00012000, 0x00300000",
    "sysconf1, 0x00312000, 0x00001000",
    "sysconf2, 0x00313000, 0x00001000",
	"sysdata,  0x00314000, 0x00001000",
	"wifibin,  0x00315000, 0x00070000",
    "fs,       0x00385000, 0x00001000",
    "userspace,0x00386000, 0x00023000",
    "tonespace,0x003a9000, 0x00030000",		//128K
    "table,    0x003d9000, 0x00012000",		//72K
    "chfnt,    0x003eb000, 0x000f5000",		//979K
	"backup,   0x004e0000, 0x00320000"
#endif
#elif CONFIG_CHIP_AP1508
    "boot,     0x00020000, 0x00008000",
	"btupdate1,0x00028000, 0x00001000",
	"btupdate2,0x00029000, 0x00001000",
    "btconf,   0x0002a000, 0x00008000",
    "image2,   0x00032000, 0x00200000",
    "sysconf1, 0x00232000, 0x00001000",
    "sysconf2, 0x00233000, 0x00001000",
	"sysdata,  0x00234000, 0x00001000",
	"wifibin,  0x00235000, 0x00070000",
	"fs,       0x002a5000, 0x00001000",
    "userspace,0x002a6000, 0x00001000",
    "tonespace,0x002a7000, 0x00030000",
    "table,    0x002d7000, 0x00012000",
    "chfnt,    0x002e9000, 0x000f5000",
	"backup,   0x003de000, 0x00422000"
#endif
};

struct tone_data datas[] = {
    {0, 31138},
    {31138, 8882},
    {40020, 15569},
    {55589, 18913},
    {74502, 16091},
    {90593, 3840},
    {94433, 36448}};

static struct ui_s *ui_mq = NULL;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/
extern void player_paramter_set_init(AUDIO_OUT_MODE outMode, AUDIO_IN_MODE inMode, int arg1, int arg2);
extern void set_flash_partition_info(char info[][64]);

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: check_is_playing_sd
 *
 * Description:
 *    ????2??|??o??????y???22???????SD???????2????Y
 *
 * Parameters:
 * 
 * Returned Value:
 *    true  ?y???22???????SD???????2????Y
 *    false 2???o??y???22???????SD???????2????Y
 * 
 * Assumptions:
 *
 ****************************************************************************/
bool check_is_playing_sd(void)
{
	if (ui_source_select == SOURCE_SELECT_SD)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

/****************************************************************************
 * Name: check_is_playing_usb
 *
 * Description:
 *    ????2??|??o??????y???22???????U???????2????Y
 *
 * Parameters:
 * 
 * Returned Value:
 *    true  ?y???22???????U???????2????Y
 *    false 2???o??y???22???????U???????2????Y
 *  
 * Assumptions:
 *
 ****************************************************************************/
bool check_is_playing_usb(void)
{
	if (ui_source_select == SOURCE_SELECT_USB)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}
/****************************************************************************
 * Name: send_cmd_2_ui
 *
 * Description:
 *    ?????UI??????????????D?????????a??????
 *
 * Parameters:
 *    ui_cmd    ????a?????????a|?????????
 * 
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void send_cmd_2_ui(ui_cmd_t *ui_cmd)
{
    if (NULL != ui_mq)
    {
        if (mq_send(ui_mq->mq, (FAR const char *)ui_cmd, sizeof(ui_cmd_t), CONFIG_UI_MSG_PRIO))
        {
            printf("%s mq_send error:%d\n", __func__, errno);
        }
    }
}

/****************************************************************************
 * Name: sys_early_init
 *
 * Description:
 *    ?a???2?|????a33???o?????3???D????
 *
 * Parameters:
 *
 * Returned Value:
 *    ?????1??o?0
 * 
 * Assumptions:
 *
 ****************************************************************************/
int sys_early_init(void)
{
    set_flash_partition_info(flash_part);

    return 0;
}

/****************************************************************************
 * Name: ui_cmd_init
 *
 * Description:
 *    ui???1???????????????????D3???o?????
 *
 * Parameters:
 *
 * Returned Value:
 *
 * Assumptions:
 *
 ****************************************************************************/
void ui_cmd_init(void)
{
    struct mq_attr attr;
    ui_mq = (struct ui_s *)malloc(sizeof(struct ui_s));
    if (NULL == ui_mq)
    {
        printf("mq malloc failed\n");
    }
    else
    {
        memset(ui_mq, 0, sizeof(struct ui_s));
        attr.mq_maxmsg = 64;
        attr.mq_msgsize = sizeof(ui_cmd_t);
        attr.mq_curmsgs = 0;
        attr.mq_flags = 0;
        sprintf(ui_mq->mqname, "mq_common");
        //snprintf(Ui->mqname, sizeof(Ui->mqname), "/tmp/%0lx", (unsigned long)((uintptr_t)Ui));
        ui_mq->mq = mq_open(ui_mq->mqname, O_RDWR | O_CREAT | O_NONBLOCK, 0644, &attr);
        if (ui_mq->mq < 0)
        {
            printf("mq_open error!\n");
        }
    }
//	printf("->>>>>>>>>>>>%s", __func__);
}

/****************************************************************************
 * Name: user_early_init
 *
 * Description:
 *    ?a???2????????3???o?????3???D????
 *
 * Parameters:
 *
 * Returned Value:
 *    ?????1??o?0
 *
 * Assumptions:
 *
 ****************************************************************************/
int user_early_init(void)
{
    printf("%s %d\n", __func__, __LINE__);
	
#if (BYPASS_MODE || INNERADC_MODE)
    player_paramter_set_init(AUDIO_INNER_CODEC_OUT, AUDIO_INNER_IN, 2, 0); 
#else
    #if (MIX_6_CH_MIC)
    	player_paramter_set_init(AUDIO_EXTRA_CODEC_MASTER_OUT, AUDIO_EXTRA_MASTER_IN, 6, 4);
    #else
		//arg1¡êo ¨º?3?¨¦¨´¦Ì¨¤   		arg2: spdif¨ª¡§¦Ì¨¤
    	player_paramter_set_init(AUDIO_EXTRA_CODEC_SLAVE_OUT, AUDIO_EXTRA_SLAVE_IN, 2, 0); 
    #endif
#endif

	bsp_init();
    return 0;
}

/****************************************************************************
 * Name: user_late_init
 *
 * Description:
 *    ?a???2????????3???o?????3???D????
 *
 * Parameters:
 *
 * Returned Value:
 *    ?????1??o?0
 *
 * Assumptions:
 *
 ****************************************************************************/
int user_late_init(void)
{
    return 0;
}

/****************************************************************************
 * Name: user_timer_isr
 *
 * Description:
 *    ????o??????????????D?????t????|???Dsa3???D????
 *
 * Parameters:
 *
 * Returned Value:
 *
 * Assumptions:
 *
 ****************************************************************************/
void user_timer_isr(void)
{
    
}

bool sl_appentry_module_switch(enum appentry_module_e app_module)
{
	switch(app_module) {
		case APPENTRY_MODULE_CEC:
			return true;
		default:
			return false;
	}
}



