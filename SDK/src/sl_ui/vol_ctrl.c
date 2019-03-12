/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <nuttx/compiler.h>
#include <nuttx/audio/sladsp_ae.h>
#include <nuttx/audio/silan_audio_api.h>

#include <nxplayer.h>
#include "player_cmd.h"
#include <stdio.h>
#include <string.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/
extern int player_get_indival_volume(AUDPROC_LIST src, int mode);

/****************************************************************************
 * Public Functions
 ****************************************************************************/


/****************************************************************************
 * Name: getADC0Vol
 *
 * Description:
 *    打印ADC0通道音量
 * 
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void getADC0Vol(void)
{
    int *tmp_vol;
    int vol;
    char data[64];
    memset(data, 0, 64);

    tmp_vol = (int *)player_get_indival_volume(AUDPROC_LIST_ADC0, 0);
    vol = tmp_vol[0];
    sprintf(data, "%d %d %d %d %d %d %d %d", AUDPROC_LIST_ADC0, 0, vol, vol, vol, vol, vol, vol);
    printf("data:%s\n", data);
}

void set_decoder_vol(int vol)
{
    int val[6] = {0}; /* 6 channels */

    if (vol > 100) {
        vol = 100;
    }
	else if (vol < 0)
	{
		vol = 0;
	}
    val[0] = vol; 
    val[1] = vol; 
    val[2] = vol; 
    val[3] = vol; 
    val[4] = vol; 
    val[5] = vol; 
	
    swa_audio_audproc_load(AUDPROC_LIST_DEC, AUDPROC_VOLUMECTL);
    swa_audio_audproc_vol(AUDPROC_LIST_DEC, 0, val);
    swa_audio_audproc_set(AUDPROC_LIST_DEC, AUDPROC_VOLUMECTL);

}

/****************************************************************************
 * Name: setADC0Vol
 *
 * Description:
 *    设置ADC0通道音量
 * 
 * Parameters:
 *    vol 要设置的音量值
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void set_adc0_vol(int vol)
{
    int val[6] = {0}; /* 6 channels */

    if (vol > 100) {
        vol = 100;
    }
	else if (vol < 0)
	{
		vol = 0;
	}
    val[0] = vol; 
    val[1] = vol; 
    val[2] = vol; 
    val[3] = vol; 
    val[4] = vol; 
    val[5] = vol; 
	
    //swa_audio_audproc_unload(AUDPROC_LIST_ADC0, AUDPROC_VOLUMECTL);
    swa_audio_audproc_load(AUDPROC_LIST_ADC0, AUDPROC_VOLUMECTL);
    swa_audio_audproc_vol(AUDPROC_LIST_ADC0, 0, val);
    swa_audio_audproc_set(AUDPROC_LIST_ADC0, AUDPROC_VOLUMECTL);

}
/****************************************************************************
 * Name: setADC1Vol
 *
 * Description:
 *    设置ADC1通道音量
 * 
 * Parameters:
 *    vol 要设置的音量值
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void set_adc1_vol(int vol)
{
	int val[6] = {0}; /* 6 channels */

	if (vol > 100) {
		vol = 100;
	}
	else if (vol < 0)
	{
		vol = 0;
	}
	val[0] = vol; 
	val[1] = vol; 
	val[2] = vol; 
	val[3] = vol; 
	val[4] = vol; 
	val[5] = vol; 

	//swa_audio_audproc_unload(AUDPROC_LIST_ADC1, AUDPROC_VOLUMECTL);
	swa_audio_audproc_load(AUDPROC_LIST_ADC1, AUDPROC_VOLUMECTL);
	swa_audio_audproc_vol(AUDPROC_LIST_ADC1, 0, val);
	swa_audio_audproc_set(AUDPROC_LIST_ADC1, AUDPROC_VOLUMECTL);

}

void set_adc2_vol(int vol)
{
	int val[6] = {0}; /* 6 channels */

	if (vol > 100) {
		vol = 100;
	}
	else if (vol < 0)
	{
		vol = 0;
	}
	val[0] = vol; 
	val[1] = vol; 
	val[2] = vol; 
	val[3] = vol; 
	val[4] = vol; 
	val[5] = vol; 

	//swa_audio_audproc_unload(AUDPROC_LIST_ADC1, AUDPROC_VOLUMECTL);
	swa_audio_audproc_load(AUDPROC_LIST_ADC2, AUDPROC_VOLUMECTL);
	swa_audio_audproc_vol(AUDPROC_LIST_ADC2, 0, val);
	swa_audio_audproc_set(AUDPROC_LIST_ADC2, AUDPROC_VOLUMECTL);

}


void setMixVol(int vol)
{
    int val[6] = {0}; /* 6 channels */

    if (vol > 100) {
        vol = 100;
    }
    val[0] = vol; 
    val[1] = vol; 
    val[2] = vol; 
    val[3] = vol; 
    val[4] = vol; 
    val[5] = vol; 
	
    swa_audio_audproc_unload(AUDPROC_LIST_DEC, AUDPROC_VOLUMECTL);
    swa_audio_audproc_load(AUDPROC_LIST_DEC, AUDPROC_VOLUMECTL);
    swa_audio_audproc_vol(AUDPROC_LIST_DEC, 0, val);
    swa_audio_audproc_set(AUDPROC_LIST_DEC, AUDPROC_VOLUMECTL);
	
//	usleep(2000);
//	// 设置叠加L+R
//	player_process_cmd(NP_CMD_SET_OVERLAY_MODE, NULL, LR_MIX, NULL, NULL); 
//	usleep(2000);
} 

#define LINEIN_REG_BASE_ADDR 0xBA0E0000
#define GCR8_OFFSET 		 0x13*4
#define GCR9_OFFSET			 0x14*4
void set_linein_gain(unsigned char leftchan, unsigned char rightchan)
{
	(*(volatile unsigned int  *)(LINEIN_REG_BASE_ADDR + GCR8_OFFSET)) &= 0xFFFFFFE0;
	(*(volatile unsigned int  *)(LINEIN_REG_BASE_ADDR + GCR9_OFFSET)) &= 0xFFFFFFE0;

	(*(volatile unsigned int  *)(LINEIN_REG_BASE_ADDR + GCR8_OFFSET)) |= leftchan;
	(*(volatile unsigned int  *)(LINEIN_REG_BASE_ADDR + GCR9_OFFSET)) |= rightchan;
}

/****************************************************************************
 * Name: setDECVol
 *
 * Description:
 *    设置DECODE通道音量
 * 
 * Parameters:
 *    vol 要设置的音量值
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void setDECVol(int vol)
{
    /*
    char data[64];
    memset(data, 0, 64);

    sprintf(data, "%d %d %d %d %d %d %d %d", AUDPROC_LIST_DEC, VOL_LINEAR, vol, vol, vol, vol, vol, vol);
    printf("%s data:%s\n", __func__, data);
    player_process_cmd(NP_CMD_POSTVOL, data, 0, NULL, NULL);
    */
    int val[6] = {0}; /* 6 channels */

    if (vol > 100) {
        vol = 100;
    }
    val[0] = vol; 
    val[1] = vol; 
    val[2] = vol; 
    val[3] = vol; 
    val[4] = vol; 
    val[5] = vol; 

//    swa_audio_audproc_unload(AUDPROC_LIST_DEC, AUDPROC_VOLUMECTL);
    swa_audio_audproc_load(AUDPROC_LIST_DEC, AUDPROC_VOLUMECTL);
    swa_audio_audproc_vol(AUDPROC_LIST_DEC, 0, val);
    swa_audio_audproc_set(AUDPROC_LIST_DEC, AUDPROC_VOLUMECTL);
}



