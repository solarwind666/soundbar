/************************************************************************************
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

#ifndef _SILAN_COMMON_H_
#define _SILAN_COMMON_H_

typedef enum{
	SILAN_MODULE_SPDIF = 0,
	SILAN_MODULE_SDMMC,
	SILAN_MODULE_SDIO,
	SILAN_MODULE_OTP,
	SILAN_MODULE_CODEC1,
	SILAN_MODULE_CODEC2,
	SILAN_MODULE_PWM,
	SILAN_MODULE_ADC,
	SILAN_MODULE_TIMER,
	SILAN_MODULE_RTC,
	SILAN_MODULE_USBFS,
	SILAN_MODULE_PDB,
	SILAN_MODULE_UART1,
	SILAN_MODULE_UART2,
	SILAN_MODULE_UART3,
	SILAN_MODULE_UART4
}silan_misc_clk_t;
#endif /* _SILAN_COMMON_H_ */
