/*
 * libadsp_aec.h
 */

#ifndef __SILAN_LIBADSP_AEC_H__
#define __SILAN_LIBADSP_AEC_H__

#define LIBADSP_AEC_OUTPUT_BYTES     256

int aec_init();
int aec_open();
int aec_close();
int aec_input_x(short *buf, int samples);
int aec_input_d(short *buf, int samples);
short * aec_output();

int aec_config(unsigned char *cmd);
int aec_mesg();       // 1s print for debug.

#endif
