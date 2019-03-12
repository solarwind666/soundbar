/****************************************************************************
 * include/nuttx/audio/asr.h
 *
 *   Copyright (C) 2016-2017 Hang Xu. All rights reserved.
 *   Authors: Hang Xu <xuhang@silan.com.cn>
 * 
 ****************************************************************************/

#ifndef ___INCLUDE_NUTTX_AUDIO_ASR_H
#define ___INCLUDE_NUTTX_AUDIO_ASR_H

/****************************************************************************
 * Public Type Declarations
 ****************************************************************************/

/* ASR configuration */
typedef struct {
	int sample_rate;
	int chs;
	int bits;
} asr_info;

/* Call back */
typedef void (*asr_callback_f)(int sz);

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Name: asr_init
 *
 * Description:
 *   Init the asr module
 *
 * Input Parameters:
 *   asr_cb - The call back function will be called
 *
 * Returned Value:
 *   OK - Succeed
 *   <0 - Error occurred
 *
 ****************************************************************************/

int asr_init(asr_callback_f asr_cb);

/****************************************************************************
 * Name: asr_reset
 *
 * Description:
 *   Reset the asr module with new configuration provided by 'info'
 *
 * Input Parameters:
 *   info - The new configuration to be used
 *
 * Returned Value:
 *   OK - Succeed
 *   <0 - Error occurred
 *
 ****************************************************************************/

int asr_reset(asr_info *info);

/****************************************************************************
 * Name: asr_get_cont_data
 *
 * Description:
 *   Read data of audio in
 *
 * Input Parameters:
 *   buf    - The buffer to which data will be written
 *   req_sz - Bytes to be read
 *
 * Returned Value:
 *   >0 - Bytes have been read actually
 *   =0 - No data can be read
 *   <0 - Error occurred
 *
 ****************************************************************************/

int asr_get_cont_data(uint16_t *buf, uint32_t req_sz);

int asr_get_cont_size(int req_sz);

/****************************************************************************
 * Name: asr_get_info
 *
 * Description:
 *   Get the current configuration of asr module
 *
 * Input Parameters: None
 *
 * Returned Value:
 *   NULL  - Unable to get the current configuration
 *   !NULL - The current configuration
 *
 ****************************************************************************/

asr_info * asr_get_info(void);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif  /* ___INCLUDE_NUTTX_AUDIO_ASR_H */

