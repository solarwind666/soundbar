/****************************************************************************
 * apps/system/airplay/audio.h
 *
 * Developed by:
 *
 *   Copyright (C) 2016 Silan Microelectronics co., ltd. All rights reserved.
 *   Author: Jiang WeiHong <jiangweihong@silan.com.cn>
 *
 ****************************************************************************/

#ifndef __APPS_SYSTEM_AIRPLAY_AUDIO_H
#define __APPS_SYSTEM_AIRPLAY_AUDIO_H

typedef struct {
	void (*help)(void);
	char *name;

	// start of program
	int (*init)(int argc, char **argv);
	// at end of program
	void (*deinit)(void);

	//int (*start)(int sample_rate, int bits, int chans);
	int (*start)(int sample_rate);
	// block of samples
	void (*play)(char buf[], int size);
	void (*stop)(void);
	void (*samplerate)(int samples);
	void (*bitset)(int bits);
	void (*chanset)(int chans);
	// may be NULL, in which case soft volume is applied
	void (*volume)(int vol);
}audio_output;

audio_output *audio_get_output(char *name);
void audio_set_output(audio_output *ao);
void audio_ls_outputs(void);

#endif /* __APPS_SYSTEM_AIRPLAY_AUDIO_H  */
