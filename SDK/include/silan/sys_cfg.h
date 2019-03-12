/******************************************************************
*sys_cfg.h
*2006-05-16
******************************************************************/

#ifndef __SYS_CFG__
#define __SYS_CFG__
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define AUDIO_BIT_PER_SAMPLE		16

#if		(AUDIO_BIT_PER_SAMPLE == 16)
#define ds_atype	short
#define ds_datype	int
#define aint_t 		short
#elif 	(AUDIO_BIT_PER_SAMPLE == 24)
#define ds_atype	int
#define ds_datype	int
#define aint_t 		int
#elif 	(AUDIO_BIT_PER_SAMPLE == 32)
#define ds_atype	int
#define ds_datype	long long
#define aint_t 		int
#endif

#define __SUPPORT_AAC_DEC__

#ifndef _ASSEMBLE_
#include "type_def.h"
#endif

#endif
