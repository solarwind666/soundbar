/*
 *  Copyright (C) 2015 YunOS Project. All rights reserved.
 */

#ifndef __SE_INTERFACE_H__
#define __SE_INTERFACE_H__

/* Definitions */
#define SE_DRIVER_VERSION 1

/* structors */

/* functions declare */

extern int DeviceOpen(void **handle);
extern int DeviceTransmit(void *handle, unsigned char *input, int input_len,
                    unsigned char *output, int *output_len);
extern int DeviceClose(void *handle);
extern int GetDeviceVersion(char *deviceVersion);
#endif
