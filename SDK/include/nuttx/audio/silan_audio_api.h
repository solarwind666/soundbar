/*
 * sladsp.h
 * 	includes:
 * 	  - DECODER
 * 	  - RECODER
 * 	  - POST
 * 	  - IISIN & IISOUT
 * 	  - SWAP
 * 	  - DSP CTRL
 */

#ifndef __SILAN_ADSP_H__
#define __SILAN_ADSP_H__

/****** DECODER *****************************************************/

#define DEC_NUM          2

typedef struct {
	int        status;
	int        type;
	int        in_rate;
	int        in_channels;
	int        in_bits;
	int        out_rate;
	int        out_channels;
	int        out_bits;
	int        decode_one_frame;
	int       *inbuf;
	int       *outbuf;
}decoder_t;

/****** RECODER *****************************************************/

#define REC_BUF_NUM       3
typedef struct {
	int        status;
	int        type;
	int        in_rate;
	int        in_channels;
	int        in_bits;
	int        out_rate;
	int        out_channels;
	int        out_bits;
	int       *recbuf;
}recorder_t;

/****** POST ********************************************************/

typedef enum {
	SLADSP_ALGOR_POST          = 0x00,
	SLADSP_ALGOR_VBASS         = 0x01,
	SLADSP_ALGOR_ECHO          = 0x02,
	SLADSP_ALGOR_PTS           = 0x03,
	SLADSP_ALGOR_PTS_old1      = 0x04,      /* For compatibility */
	SLADSP_ALGOR_PTS_old2      = 0x05,      /* For compatibility */
	SLADSP_RESERVED_1          = 0x06,      /* For compatibility */     
	SLADSP_ALGOR_VOC           = 0x07,
	SLADSP_ALGOR_AFC           = 0x08,
	SLADSP_ALGOR_EQ            = 0x0a,
	SLADSP_ALGOR_LDRC          = 0x0b,
	SLADSP_ALGOR_SEPBASS       = 0x0c,
	SLADSP_ALGOR_REVERB        = 0x0d,
	SLADSP_ALGOR_VOLC          = 0x0f,
	SLADSP_ALGOR_DELAY         = 0x10,
	SLADSP_ALGOR_3D            = 0x11,
	SLADSP_ALGOR_NOISEGATE     = 0x12,
	SLADSP_ALGOR_NHS           = 0x13,
	SLADSP_ALGOR_CA_BASSBOOST  = 0x14,
	SLADSP_ALGOR_ALC           = 0x15,
	SLADSP_ALGOR_ENERGY        = 0x16,
	SLADSP_ALGOR_DIRECT_SOUND  = 0x17,     /* Do not use */
}algor_type;

int sladsp_set_ae(algor_type algor, char *params);

/****** DSP MOUNT DEV ************************************** *********/
#define 	SLADSP_MOUNT_NULL               0x00
#define 	SLADSP_MOUNT_SPI_FLASH          0x01
#define 	SLADSP_MOUNT_USB                0x02

/****** IISIN & IISOUT **********************************************/


/****** DSP CTRL ****************************************************/
/*iis_stat
 * 0 : mic inner master + aux inner master + out 2.0 inner master
 * 1 : mic inner master + aux inner master + out 2.0 extra master
 * 2 : mic inner master + aux inner master + out 5.1 extra master
 * */
typedef struct {
	int        cmd;
	int        ret;
	int        status;
	int       *dsp_swap;
	int        dsp_exc;
	int        dsp_stat;
	int        risc_stat;
	int        wdev_stat;
	int        mount_stat;
	int        iis_stat;
}dsp_ctrl_t;

typedef struct {
	int mode;
	int vol[6];
}algor_vol_t;

/****** POST ALGOR - EQ *********************************************/
/*
typedef struct {
	char       config;
	char       plist;
	char       ftype;
	int        gain;
	int        fc;
	int        q;
	int        chn;
}algor_eq_t;*/
typedef struct {
	int flt_id;
	int type;
	int on;
	int gain;
	int fc;
	int q;
	int ch;
}algor_eq_t;
/****** POST ALGOR - ECHO *******************************************/
/*
typedef struct {
	char       config;
	char       list;               // [0, 4]                    
	short      delay;              // mS, [0, 300]              
	short      gain;               // 0.01dB, [-3000, -1]       
}algor_echo_t;
*/
typedef struct{
	int type;   // (0) regular 1 - bouncing ball 2 - reverse of 1
	int gain;   // (-6) -30 to 1 dB, 0.1 unit
	int delay;  // (300) 0 - 5000 (ms)
	int stype;  // shift type 0 - Pitch/Time, 1 - Pitch only
	int shift;  // (0) -24 to 24 (0.5 to 2 times shifting)
	int number; // (5), 1 to 30, number of echo paths
}algor_echo_t;

typedef struct{
	int cmd;
	int fc;
	int q_width;
	int gain;
}algor_btr_t;


/****** POST ALGOR - POST *******************************************/
typedef struct _pFormat {
	char  channels;
	int   sampleRate;
	char  bits;
}pFormat;

typedef enum {
	DEFAULT_STEREO,
	DEFAULT_CH5P1,
}overlay_mode_t;

typedef struct {
	int           pts_level;
	algor_vol_t   ae_vol;
	algor_vol_t   ae_alc;
	algor_eq_t    ae_eq;
	algor_eq_t    ae_eq_mode[6];
	algor_eq_t    ae_record[12];
	algor_echo_t  ae_echo;
	algor_btr_t   ae_btr;
	algor_btr_t   ae_btr_record[2];
    int           energy[6];
    int           duration;
	int           delay[6];
	int           noise_gate[2];
	int           revb_type;
	int           revb_custom[9];
	int           revb_para[6];
	pFormat       informat;
	pFormat       outformat;
}post_t;

/**************** DSP SWAP      *************************************/
typedef struct {
	int           dspctrl;
	decoder_t     decoder[DEC_NUM];
	post_t        post[7];
	int          *iisin[3];
	int          *iisout[3];
	recorder_t    recorder[REC_BUF_NUM];
	char          args[256];
	int          *info;
	int          *buf_info;
	int          *rec_info[3];
	int           gde_busy;
	int          *vice_info;
	int          *vice_buf;
	int           print_switch;
	int          overlay_mode;
}dsp_swap_t;

typedef enum {
	VICE_UNKNOWN,
	VICE_MP3,
	VICE_PCM,
	VICE_MAX
}VICE_TYPE;



/****** Old sladsp.h ************************************************/

#define DMA_I2S_OUT		2
#define DMA_I2S_IN		1
#define DMA_SPDIF_OUT	0
#define DMA_SPDIF_IN	3
#define DMA_DUP_I2SIN   4
#define DMA_LLI_LENGTH  (384*2)
#define DMA_LLI_CNT     30

/*=====================================================================
//AUDIO_INNER_CODEC_OUT               inner out mode
//AUDIO_EXTRA_CODEC_MASTER_OUT        extra out mode, 6136 as master
//AUDIO_EXTRA_CODEC_SLAVE_OUT         extra out mode, 6136 as slave
//AUDIO_SPDIF_OUT                     spdif only out mode
//AUDIO_INNER_SPDIF_OUT               spdif and inner out mode
//AUDIO_EXTRA_SPDIF_OUT               spdif and extra out mode
//=====================================================================*/
typedef enum {
	AUDIO_INNER_CODEC_OUT,
	AUDIO_EXTRA_CODEC_MASTER_OUT,
	AUDIO_EXTRA_CODEC_SLAVE_OUT,
	AUDIO_SPDIF_OUT,
	AUDIO_INNER_SPDIF_OUT,
	AUDIO_EXTRA_SPDIF_OUT,
}AUDIO_OUT_MODE;

/*=====================================================================
//AUDIO_INNER_IN              inner in mode
//AUDIO_EXTRA_MASTER_IN       extra in mode, 6136 as master
//AUDIO_EXTRA_SLAVE_IN        extra in mode, 6136 as slave
//=====================================================================*/
typedef enum {
	AUDIO_INNER_IN,
	AUDIO_EXTRA_MASTER_IN,
	AUDIO_EXTRA_SLAVE_IN,
}AUDIO_IN_MODE;

/*=====================================================================
//INTRA_CODEC_ADC              CODEC inner adc mode
//INTRA_CODEC_DAC              CODEC inner dac mode
//EXTRA_CODEC_ADC_SLAVE        CODEC extra adc mode, 6136 as slave
//EXTRA_CODEC_DAC_SLAVE        CODEC extra dac mode, 6136 as slave
//EXTRA_CODEC_ADC_MASTER       CODEC extra adc mode, 6136 as master
//EXTRA_CODEC_DAC_MASTER       CODEC extra dac mode, 6136 as master
//=====================================================================*/
typedef enum {
	INTRA_CODEC_ADC,
	INTRA_CODEC_DAC,
	EXTRA_CODEC_ADC_SLAVE,
	EXTRA_CODEC_DAC_SLAVE,
	EXTRA_CODEC_ADC_MASTER,
	EXTRA_CODEC_DAC_MASTER,
}AUDIO_CODEC_MODE;

typedef enum {
	DSP_IDLE = 0,
	DSP_DECODE_ERROR,
	DSP_DATA_END,
	DSP_DECODE_FLUSH,
	DSP_DECODE_END,
	DSP_PLAY_END,
}DECODE_STATUS;

typedef enum {
	AUDIO_UNKNOWN,
	AUDIO_MP3,
	AUDIO_ALAC,
	AUDIO_AAC,
	AUDIO_WMA,
	AUDIO_FLAC,
	AUDIO_APE,
	AUDIO_AC3,
	AUDIO_DTS,
	AUDIO_WAV,
	AUDIO_OGG,
	AUDIO_SPDAC3,
	AUDIO_SPDDTS,
	AUDIO_PCM,
	AUDIO_MAX
}AUDIO_TYPE;

typedef enum {
	OUTPUT_UNKNOW = 0,
	OUTPUT_ONLY_MIC,
	OUTPUT_ONLY_DEC,
	OUTPUT_MIX
}OUTPUT_OPTION;

typedef enum {
	RECORD_UNKONW = 0,
	RECORD_ONLY_MIC,
	RECORD_POST_MIC,
	RECORD_ONLY_DEC,
	RECORD_MIX
}RECORD_OPTION;

typedef enum {
	SPK_UNKNOW = 0,
	SPK_ONLY_MIC,
	SPK_ONLY_DEC,
	SPK_MIX
}SPK_OPTION;

typedef enum {
	NONE_USED,
	USE_I2SDMA,
	USE_SPDDMA
}I2SIN_OPTION;

typedef enum {
    DEF_I2SIN_CH,
    USE_I2SIN_CH1,
    USE_I2SIN_CH2,
}I2SIN_CH;

typedef enum {
    SLADSP_AUDIO_EQ = 0,
    SLADSP_MIC_EQ,
    SLADSP_LINEIN_EQ,
    SLADSP_ECHO,
    SLADSP_VC,
    SLADSP_PTS,
    SLADSP_LDRC,
    SLADSP_FBC,
}SLADSP_AE_MODE;

typedef enum {
    SLADSP__LIST_DEC,
    SLADSP__LIST_ADC0,
    SLADSP__LIST_ADC1,
    SLADSP__LIST_ADC2,
    SLADSP__LIST_MIX
}SLADSP_AE_LIST;

typedef enum {
	SWA_AE_MOD_EQ      =  0,    /* Equalizer */
	SWA_AE_MOD_VC,              /* Voice Cancel */
	SWA_AE_MOD_EQ_AUDIO,        /* Audio Equalizer */
	SWA_AE_MOD_EQ_MIC,          /* MIC Equalizer */
	SWA_AE_MOD_EQ_LINEIN,       /* Line-In Equalizer */
	SWA_AE_MOD_ECHO,            /* Echo */
	SWA_AE_MOD_FBC,             /* FBC */
	SWA_AE_MOD_LDRC,            /* LDRC */
	SWA_AE_MOD_VBASS,           /* VBASS */
	SWA_AE_MOD_PITCHSHIFT,      /* Pitch-Shift */
	SWA_AE_MOD_TIMESCALE,       /* Time-Scale */
	SWA_AE_MOD_AEC,             /* AEC */
	SWA_AE_MOD_LMT,             /* Limit for ae mode */
}swa_ae_mode_t;

typedef enum {
	AUDIO_HARDWARE_MIC,
	AUDIO_HARDWARE_LINE,
	AUDIO_HARDWARE_MIX,
}AUDIO_HARDWARE_VOL;

int swa_audio_decode_init(void);
void swa_audio_set_reqformat(int type, int samplerate, int channels, int bits, int file_size);
void swa_audio_get_pcminfo(int* samplerate, int* channels, int* bits);
int swa_audio_set_param(int name, int samplerate, int channels, int bits);
int swa_audio_init(int name);
int swa_audio_start(int name, AUDIO_CODEC_MODE mode);
int swa_audio_play(int name);
int swa_audio_pause(int name);
int swa_audio_stop(int name);
int swa_audio_get_inbuf_fullness(void);
int swa_audio_get_info_status(void);
int swa_audio_set_info_status(int status);
int swa_audio_already_decode_one_frame(void);
int swa_audio_get_time_position(AUDIO_OUT_MODE out_mode);
void swa_audio_update_cur_pos(AUDIO_OUT_MODE out_mode, int seekwhere);
int swa_audio_record_on(RECORD_OPTION record_opt);
int swa_audio_record_off(void);
int swa_audio_record_buf_fullness(void);
int swa_audio_record_buf_addr(void);
void swa_audio_record_buf_update(int len);
char* swa_audio_record_read(int *len);
//int swa_audio_player_getcurfrm(int *cur_frm, int *cur_offset, int *buf_frm);
char* swa_audio_get_inbuf_addr(int *read_size);
void swa_audio_inbuf_update(int len);
/*eg :in_mode = 0,(0 inner,1:extra)out_mode = AUDIO_INNER_CODEC_OUT,output_opt = OUTPUT_ONLY_DEC*/
int swa_audio_set_mode(AUDIO_IN_MODE in_mode, AUDIO_OUT_MODE out_mode, OUTPUT_OPTION output_opt);
int swa_audio_set_mode_up(AUDIO_IN_MODE in_mode, AUDIO_OUT_MODE out_mode, OUTPUT_OPTION output_opt);
int swa_audio_decode_close(void);
int swa_audio_decode_reset(void);
int swa_audio_decode_flush(void);
int swa_audio_get_totaltime(void);
void swa_audio_codec_initial(int tmcnt1, int tmcnt2);
void swa_audio_codec_init(void);
void swa_audio_linein_init(int rate, int ch, int bits);
void swa_audio_lineout_init(int rate, int ch, int bits, int dac);
void swa_audio_micin_init(int rate, int ch, int bits);
void swa_audio_micout_init(int rate, int ch, int bits, int dac);
int swa_audio_decode_stop(void);
int swa_audio_time_2_pos(int seek_time, int total_time, int file_size);
void swa_audio_ctrl_init(void);
void swa_silan_dsp_firmware_load_init(void);
int swa_audio_set_hardware_vol(AUDIO_HARDWARE_VOL mode ,int vol);
/* return number of bytes in inbuf */
int swa_audio_get_inbuf_fullness(void);
int swa_audio_inringbuf_size(void); /* return inbuf size */
void swa_audio_decode_deinit(void);
int swa_audio_stop_output(void);
int swa_audio_check_playing(void);  /* check if dma already play */
int swa_audio_decpause(int opt);
void swa_audio_set_pcmformat(int samplerate, int channels, int bits);
AUDIO_TYPE swa_audio_get_audiotype(void);
int swa_audio_delay_start(int delay_ms);
int swa_audio_get_outbuf_fullness(void);
int swa_audio_outringbuf_size(void);
void swa_audio_mark_spdifin(void);
int swa_printf_fillout_zero(void );
int swa_audio_gde_get_echo(int argc[][6]);
int swa_aduio_gde_get_reverb(int *argc);
int swa_audio_gde_get_volume(int argc[][6],int mode[5]);
int swa_audio_gde_get_delay(int argc[][6]);
int swa_audio_gde_get_eq(int argc[][7][7],int argc1[][2][4]);

int swa_audio_spk_mic_on(void);
int swa_audio_spk_on(void);
int swa_audio_spk_off(void);
int swa_audio_spk_buf_fullness(void);
void swa_audio_spk_buf_update(int len);
char* swa_audio_spk_read(int *len);
int swa_audio_set_scale(int sc);//set scale effects for stream pcm after decode

/*************************** SPDIF/I2S Interface *************************/


/**************************************SPDIF PAD***************************
 * 0:GPIO1_9, 
 * 1:GPIO1_10,  
 * 2:GPIO1_11, 
 * 3:GPIO1_12, 
 * 4:GPIO2_13,
 * 5:GPIO2_14,
 * 6:GPIO2_15,
 * 7:GPIO2_16,
 */
typedef struct{
	int pad;   /* 0 ~ 7 (0:reserve) */   
}swa_spdif_in_t;

typedef struct{
	int pin_chan;    /* 1:pin chan1 2:pin chan2 */
	int sound_chan;  /*(2) 2:2 sound chan 6:6 sound chan */
	int pad;  	     /*  0 ~ 2 */
}swa_i2s_in_t;

typedef struct{
	int sound_chan;  /*(6) 2:2 sound chan 6:6 sound chan  */
	int pad;  	     /* 0 */
}swa_i2s_out_t;

int swa_spdif_in_set(swa_spdif_in_t *config);
int swa_i2s_in_set(swa_i2s_in_t *config);
int swa_i2s_out_set(swa_i2s_out_t *config);

typedef struct{
	SLADSP_AE_LIST list;
	SLADSP_AE_MODE ae_mode;
	int data[64];
}swa_sladsp_ae_t;
int sladsp_ae_set(swa_sladsp_ae_t *config);
int swa_ae_config(swa_ae_mode_t mod, void *cfg);
/*
 * libsladsp errno
 */
enum {
	SLADSP_EERROR            =  1,  /* Default error */
	SLADSP_EINVAL            =  2,  /* Invalid argument */
	SLADSP_EFAULT            =  3,  /* Bad address */
	SLADSP_ENOMEM            =  4,  /* Out of memory */
	SLADSP_ENOSPC            =  5,  /* No space left on device */
	SLADSP_EIO               =  6,  /* I/O error */
	SLADSP_EFBIG             =  7,  /* File too large */
	SLADSP_EBUSY             =  8,  /* Resource or device busy */
	SLADSP_EAGAIN            =  9,  /* Try again */
	SLADSP_ENODEV            = 10,  /* No such device */
	SLADSP_EACCES            = 11,  /* Permission denied */
	SLADSP_ENOENT            = 12,  /* No such file or directory */
	SLADSP_EUNSUP            = 13,  /* Unsupported */
};

/*
 * sladsp_setvol
 * type  : ADC, DAC, MIC, LINEIN, AUDIO/AUDIO_51, MIX/MIX_51
 * val   = volumes of each channel, see below
 * is_db = VOL_LINEAR or VOL_DB
 *
 * Type, Number Of Channels, Value Range
 * SLADSP_VOLC_ADC,      2(0-Left,1-Right)               [0,31] DB, Unsupport Linear.
 * SLADSP_VOLC_DAC,      1(0-Both)                       [-31,0] DB or [0,100]% (Linear)
 * SLADSP_VOLC_MIC,      2(0-Left,1-Right)               [-64,6] DB or [0,100]% (Linear)
 * SLADSP_VOLC_LINEIN,   2(0-Left,1-Right)               [-64,6] DB or [0,100]% (Linear)
 * SLADSP_VOLC_AUDIO,    2(0-Left,1-Right)               [-64,6] DB or [0,100]% (Linear)
 * SLADSP_VOLC_AUDIO_51, 6(0-L,1-R,2-C,3-SL,4-SR,5-LFE)  [-64,6] DB or [0,100]% (Linear)
 * SLADSP_VOLC_MIX,      2(0-Left,1-Right)               [-64,6] DB or [0,100]% (Linear)
 * SLADSP_VOLC_MIX_51,   6(0-L,1-R,2-C,3-SL,4-SR,5-LFE)  [-64,6] DB or [0,100]% (Linear)
 */

typedef enum {
	SLADSP_VOLC_NULL           =  0,
	SLADSP_VOLC_ADC,                  /* val: 0-Left,1-Right */
	SLADSP_VOLC_DAC,                  /* val: 0-Both */
	SLADSP_VOLC_MIC,                  /* val: 0-Left,1-Right */
	SLADSP_VOLC_LINEIN,               /* val: 0-Left,1-Right */
	SLADSP_VOLC_AUDIO,                /* val: 0-Left,1-Right */
	SLADSP_VOLC_AUDIO_51,             /* val: 0-L,1-R,2-C,3-SL,4-SR,5-LFE */
	SLADSP_VOLC_MIX,                  /* val: 0-Left,1-Right */
	SLADSP_VOLC_MIX_51,               /* val: 0-L,1-R,2-C,3-SL,4-SR,5-LFE */
	SLADSP_VOLC_ADC0,				  /* val: 0-Left,1-Right */
	SLADSP_VOLC_ADC1,				  /* val: 0-Left,1-Right */
	SLADSP_VOLC_ADC2,				  /* val: 0-Left,1-Right */
	SLADSP_VOLC_LMT,
}sladsp_volc_t;

typedef enum {
	ITU_755 = 0,
	CA_MIX,
	BDC_755,
	BDC_721,
}sladsp_mix_mode;

typedef enum {
	LR_DEFAULT = 0,//l=l,r=r
	LR_MIX,        //l=r=l+r
	LR_EXCHANGE,   //l=r,r=l
}sladsp_overlay_mode;

void sladsp_getvol();
int swa_audio_spdin_delay(int time_ms);
int swa_audio_set_mixmode(sladsp_mix_mode mode);
void swa_audio_get_mediainfo(int* samplerate, int* channels, int* bits);
int swa_audio_get_curtime_ms(AUDIO_OUT_MODE out_mode);
void swa_audio_update_curtime_ms(AUDIO_OUT_MODE out_mode, int curtime);
int swa_audio_mark_i2sin(I2SIN_OPTION opt);
int swa_audio_get_i2sin_chan(void);
int swa_audio_set_i2sin_chan(I2SIN_CH i2s_ch);
int swa_audio_set_adc_channel(int channel);
int swa_audio_set_adc1_mode(int mode);
int swa_audio_set_adc0_mode(int mode);
int swa_audio_read_dsp_status(void);
int swa_audio_set_cur_frame_number(int num);
int swa_audio_dsp_printf_off(int printf_off);
int swa_audio_nuttx_printf_off(int printf_off);
int swa_audio_downsample(void);
int swa_audio_set_overlay_mode(sladsp_overlay_mode mode);

/*
 * Functions for porting
 */
typedef void (*sladsp_irq_hdl_f)(int param);
int sladsp_port_reqirq(sladsp_irq_hdl_f irq_hdl);
void sladsp_port_printf (const char *fmt, ...);
/*
 * Function for ap ringbuf
 */
char *ap_inbuf_wr_addr(void);
void ap_inbuf_wr_update(int val);
int ap_inbuf_fullness(void);
int ap_inbuf_wr_to_end(void);
int ap_inbuf_size(void);
char *ap_inbuf_start_addr(void);
int ap_inbuf_space(void);

int ap_get_dec_status(void);
/*
 * Function for ap vice ringbuf
 */
char *ap_vice_inbuf_wr_addr(void);
void ap_vice_inbuf_wr_update(int val);
int ap_vice_inbuf_fullness(void);
int ap_vice_inbuf_wr_to_end(void);
int ap_vice_inbuf_size(void);
char *ap_vice_inbuf_start_addr(void);
int ap_vice_inbuf_space(void);
int ap_get_vice_status(void);
/*
 * Function for ap record buf
 */
int ap_recbuf_rd_addr(int buf_num);
void ap_recbuf_rd_update(int buf_num,int val);
int ap_recbuf_fullness(int buf_num);
int ap_recbuf_rd_to_end(int buf_num);
int ap_recbuf_size(int buf_num);
int ap_recbuf_start_addr(int buf_num);


void ap_set_pcmformat(int samplerate, int channels, int bits);
void ap_set_reqformat(int type, int samplerate, int channels, int bits, int file_size);
int ap_send_dec_play(void);
int ap_send_dec_pause(void);
int ap_send_dec_stop(void);
int ap_send_record_on(void);
int ap_send_record_off(void);
int ap_send_vice_play(void);
int ap_send_vice_pause(void);
int ap_send_vice_stop(void);

void ap_get_mediainfo(int* rate, int* channels, int* bits);
void ap_get_pcminfo(int* rate, int* channels, int* bits);
int ap_already_decode_one_frame(void);
int ap_get_audio_type(void);
int ap_set_info_status(int status);
int ap_vice_set_info_status(int status);
void ap_vice_set_pcmformat(int samplerate, int channels, int bits);
void ap_vice_set_reqformat(int type, int samplerate, int channels, int bits, int file_size);
int ap_vice_get_info_status(void);
int ap_set_overlay_mode(overlay_mode_t mode);
int ap_send_spdifin_play(void);
int ap_send_spdifin_stop(void);
#endif
