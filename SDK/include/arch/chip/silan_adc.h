/************************************************************************************
 *arch/cskyv1/src/silan_adc.h
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
 ************************************************************************************/

#ifndef __ARCH_CSKV1_SRC_SILAN_ADC_H
#define __ARCH_CSKV1_SRC_SILAN_ADC_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#define ADC_MAX_CH_NUM  7
#ifdef CONFIG_BOARD_SHENZHEN
#define ADC_MAX_CH_VAL  8
#else
#define ADC_MAX_CH_VAL  9
#endif

#define _IO(a, b)          ((a<<8)|b)
#define ADC_IOCTL_MAGIC    'A'
#define CMD_ADC_SET_CHANNEL _IO(ADC_IOCTL_MAGIC, 0x1)

#define ADC_DEV_NAME "/dev/silan-adc"

extern void silan_adc_probe(void);
/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/


#endif /* __ARCH_CSKV1_SRC_SILAN_ADC_H */
