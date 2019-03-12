/****************************************************************************
 * hardware/id.bsp/configs/sc6138a-xj-1/src/sc6138_adckey.c
 *
 * Copyright (C) 2015 The YunOS Open Source Project
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *      http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
 *
 ****************************************************************************/

 /****************************************************************************
 * Included Files
 ****************************************************************************/
#include <arch/board/board.h>
#include <fcntl.h>
#include "input_key.h"
#include <nuttx/arch.h>
#include <nuttx/clock.h>
#include <nuttx/config.h>
#include <nuttx/input.h>
#include <nuttx/module.h>
#include <poll.h>
#include <silan_adc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include "../sl_ui/sl_ui_cmd.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
/*ADC???????*/
#define ADC_KEY_CHANNEL  0x40

/*ADC???????????*/
#define SC6138_ADCKEY_TIMEOUT 1 //10ms


/*??????????????????*/
#define KEY_DEBUG
/*ADC??Χ???*/
#define KEY_RANGE(a, b) (((a > b - 100) && (a < b + 100)) ? 1 : 0)
/*???????????*/
#ifdef KEY_DEBUG
#define PRINTF printf
#else
#define PRINTF(fmt, arg...)
#endif


// ADC????????
#define SC6138_ADCDETECT_TIMEOUT	1 //10ms

/****************************************************************************
 * Public Types
 ****************************************************************************/
struct s_key
{
    WDOG_ID wdog_id;
    int level_value;
    int level_detect_number;
    int ch_num;
    int key_num;
    int fd;
    pid_t adc_pid;
};

/****************************************************************************
 * Public Data
 ****************************************************************************/
static struct s_key key_priv;
static int key_value_tbl[] = {0x7, 0x3a5, 0x5aa};
/*电源/输入源切换*/
//#define POWER_SOURCE_BUTTON		13//	

static WDOG_ID adc_wdt;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/
//???????
static void key_detect_low_level(int argc, uint32_t irq_num, ...);
static void key_detect_reset(void);
static int key_num_translate(int key_num);

//??????
extern void button_add_event(struct input_event *event);
extern void msleep(int ms);
extern void silan_adc_read(int fd, char* buf, int size);
extern void silan_adc_ioctl(int fd, int cmd, int channel);
/****************************************************************************
 * Public Functions
 ****************************************************************************/
 static void Adc_Get_Value(void);

 static int Key_detect_power_pin(void)
 {

 }

 /****************************************************************************
 * Name: adc_stop
 *
 * Description:
 *    ???ADC????
 * 
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
int adc_stop(void)
{
    int ret;
    ret = wd_cancel(key_priv.wdog_id);
    if (ret == ERROR)
    {
        printf("wd_cancel failed.\n");
    }
    wd_delete(key_priv.wdog_id);
    key_priv.wdog_id = NULL;
    ret = close(key_priv.fd);
    if (ret < 0)
    {
        printf("close adc fd failed.\n");
    }
    key_priv.fd = -1;
    task_delete(key_priv.adc_pid);
    return ret;
}

/****************************************************************************
 * Name: key_detect_channel
 *
 * Description:
 *    ??????????????
 * 
 * Parameters:
 *
 * Returned Value:
 *    0-???￡?1-????
 * 
 * Assumptions:
 *
 ****************************************************************************/
static int key_detect_channel(void)
{
    int m;
    unsigned short buf[ADC_MAX_CH_NUM];
    char * p = (char *)buf;
    //?????ADC?????????
    memset(p, 0xff, ADC_MAX_CH_NUM * 2);
    //????????????ADC?
    silan_adc_read(key_priv.fd, p, ADC_MAX_CH_NUM * 2);
	
    //????????а???
    m = KEY_RANGE(buf[key_priv.ch_num], key_value_tbl[key_priv.key_num]);// | Key_detect_power_pin();
    if (m)
    {   //?а???
        return 0;
    }
    else
    {   //??а???
        return 1;
    }
}

/****************************************************************************
 * Name: key_find_channel
 *
 * Description:
 *    ?????????????????ADC???????????????е????
 * 
 * Parameters:
 *
 * Returned Value:
 *    -1 ????????????????????-1???????????
 * 
 * Assumptions:
 *
 ****************************************************************************/
static int key_find_channel(void)
{
    int i, j, k, m;
    unsigned short buf[ADC_MAX_CH_NUM];	
    char *p = (char *)buf;
    //???????????
    memset(p, 0xff, ADC_MAX_CH_NUM * 2);
    //??????ADC????
    silan_adc_read(key_priv.fd, p, ADC_MAX_CH_NUM * 2);
	
    for (i = 0; i < ADC_MAX_CH_NUM; i++)
    {
        j = (ADC_KEY_CHANNEL >> i) & 0x01;
        if (j)
        {   //????????ADC???
            //??鵱?ADC??????????趨??????Χ??
			//printf("0x%x\n", buf[i]);
            for (k = 0; k < ADC_MAX_CH_VAL; k++)
            {
                m = KEY_RANGE(buf[i], key_value_tbl[k]);
                if (m)
                {   //?????ADC???????趨????Χ??
                    //?????????
                    key_priv.key_num = k;
                    break;
                }
            }
            if (key_priv.key_num != -1)
            {   //?а???
                //????ADC?????
                key_priv.ch_num = i;
                //???????
                return 0;
            }
        }
    }
    //??м??????
    return -1;
}

/****************************************************************************
 * Name: key_detect_high_level
 *
 * Description:
 *    ????????????????????????????????????
 * 
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static void key_detect_high_level(int argc, uint32_t irq_num, ...)
{
    int value;
    struct input_event key_event;
    int tmp_key_num = 0;

    //???°????????
    value = key_detect_channel();
    key_priv.level_value = key_priv.level_value << 1;
    key_priv.level_value |= value;
    //????????
    key_priv.level_detect_number++;

    if ((key_priv.level_value & 0xf) == 0xf)
    {   //???????????????
        //???????????
        key_event.type = EV_KEYDRV;
        //???e???????????
        key_event.code = SILAN_INPUTKEY_CODE_BUTTON_UP;
        //????????
        tmp_key_num = key_num_translate(key_priv.key_num);
        //???e????
        key_event.value = (key_priv.ch_num << 4) | tmp_key_num;
        //?????????????
        button_add_event(&key_event);
        //??????λ
        key_detect_reset();
        //??????????????????????
        wd_start(key_priv.wdog_id, SC6138_ADCKEY_TIMEOUT, key_detect_low_level, 1, 0);
        return;
    }

    //??????????????????????
    wd_start(key_priv.wdog_id, SC6138_ADCKEY_TIMEOUT, key_detect_high_level, 1, 0);
}

/****************************************************************************
 * Name: key_detect_low_level
 *
 * Description:
 *    ????????????????????????????????????
 * 
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static void key_detect_low_level(int argc, uint32_t irq_num, ...)
{
    int value;
    struct input_event key_event;
    int tmp_key_num = 0;

    if (key_priv.ch_num == -1)
    {   //???????
        //???????а???
        value = key_find_channel();
        if (value == -1)
        {   //??а???
            //????????????????
            wd_start(key_priv.wdog_id, SC6138_ADCKEY_TIMEOUT, key_detect_low_level, 1, 0);
            return;
        }
    }

    //?а???
    //???°????????
    value = key_detect_channel();
    key_priv.level_value = key_priv.level_value << 1;
    key_priv.level_value |= !value;
    //???????????
    key_priv.level_detect_number++;
    if (key_priv.level_detect_number > 32)
    {   //???????????
        //???????λ
        key_detect_reset();
        //?????????????
        wd_start(key_priv.wdog_id, SC6138_ADCKEY_TIMEOUT, key_detect_low_level, 1, 0);
        return;
    }

    if ((key_priv.level_value & 0xf) == 0xf)
    {   //????8??=8*2=16ms????????
        //??λ?????
        key_priv.level_value = 0;
        //??λ????????
        key_priv.level_detect_number = 0;
        //???????????
        key_event.type = EV_KEYDRV;
        //???e???????????
        key_event.code = SILAN_INPUTKEY_CODE_BUTTON_DOWN;
        //??????
        tmp_key_num = key_num_translate(key_priv.key_num);
        //???ü??
        key_event.value = (key_priv.ch_num << 4) | tmp_key_num;
		printf("key_event.value:%d", key_event.value);
        //????????????????
        button_add_event(&key_event);
        //??????????????????????
        wd_start(key_priv.wdog_id, SC6138_ADCKEY_TIMEOUT, key_detect_high_level, 1, 0);
        return;
    }

    //???????δ??????????????????
    wd_start(key_priv.wdog_id, SC6138_ADCKEY_TIMEOUT, key_detect_low_level, 1, 0);
}

/****************************************************************************
 * Name: key_detect_reset
 *
 * Description:
 *    ??????鸴λ
 * 
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static void key_detect_reset(void)
{
    key_priv.level_value = 0;
    key_priv.level_detect_number = 0;
    key_priv.ch_num = -1;
    key_priv.key_num = -1;
}

/****************************************************************************
 * Name: key_num_translate
 *
 * Description:
 *    ??????????
 * 
 * Parameters:
 *     key_num ???????
 *
 * Returned Value:
 *    0-?????????????????0-???????
 * 
 * Assumptions:
 *
 ****************************************************************************/
static int key_num_translate(int key_num)
{
    return key_num;
}

 /****************************************************************************
 * Name: adc_main
 *
 * Description:
 *    ADC???????????????ADC????????????????????
 * 
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
static int adc_main(int argc, FAR char *argv[])
{
    //??ADC?豸
    key_priv.fd = open(ADC_DEV_NAME, O_RDONLY);

    if (key_priv.fd < 0)
    {   //ADC?豸?????
        return -1; 
    }
    //????ADC????
    silan_adc_ioctl(key_priv.fd, CMD_ADC_SET_CHANNEL, ADC_KEY_CHANNEL); //ADC_CHANNEL ADC_KEY_CHANNEL
    //???????λ
    key_detect_reset();
    //??????????????????????
    key_priv.wdog_id = wd_create();
    //?????????????鰴??????
    wd_start(key_priv.wdog_id, SC6138_ADCKEY_TIMEOUT, key_detect_low_level, 1, 0);
//	//ADC??????
//	adc_wdt = wd_create();
//    //??????????????ADC?
//    wd_start(adc_wdt, SC6138_ADCDETECT_TIMEOUT, Adc_Get_Value, 1, 0);
	printf("%s adc init ", __func__);
    //?????????
    while (1)
    {
        msleep(10);
    }
    return 0;
}

 /****************************************************************************
 * Name: adc_start
 *
 * Description:
 *    ???ADC????
 * 
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void adc_start(void)
{
    key_priv.adc_pid = task_create("adckey", 5, 8192, adc_main, NULL);
    if (key_priv.adc_pid < 0)
    {
        LOGE("ADC", "Failed to start task (%d)", errno);
    }
}

/****************************************************************************
 * Name: sc6138_adcinitialize
 *
 * Description:
 *    ADC???????????
 * 
 * Parameters:
 *
 * Returned Value:
 *    ????OK
 * 
 * Assumptions:
 *
 ****************************************************************************/
static int sc6138_adcinitialize(void)
{
    //adc?????
    silan_adc_probe();
    //???ADC??????????
    #if (MIX_6_CH_MIC)
    #else
    key_priv.adc_pid = task_create("adckey", 5, 8192, adc_main, NULL);
    if (key_priv.adc_pid < 0)
    {
        LOGE("ADC", "Failed to start task (%d)", errno);
        return -errno;
    }
    #endif

    return OK;
}
//??????????ADC???????????
zhuque_device_init(sc6138_adcinitialize);

static void Adc_Get_Value(void)
{
//	char *p = (char *)Adc_Read_Buf;	
//  	silan_adc_read(key_priv.fd, p, ADC_MAX_CH_NUM * 2);
//	
//    wd_start(adc_wdt, SC6138_ADCDETECT_TIMEOUT, Adc_Get_Value, 1, 0);
}






