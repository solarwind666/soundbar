/****************************************************************************
 * apps/system/airplay/audio.h
 *
 * Developed by:
 *
 *   Copyright (C) 2016 Silan Microelectronics co., ltd. All rights reserved.
 *   Author: Jiang WeiHong <jiangweihong@silan.com.cn>
 *
 ****************************************************************************/

#ifndef __APPS_SYSTEM_AIRPLAY_SWA_AIRPLAY_API_H
#define __APPS_SYSTEM_AIRPLAY_SWA_AIRPLAY_API_H

#define CMD_STATUS           1  /* update status */
#define CMD_VOLUME           2
#define CMD_UPDATE_INFO      3
#define CMD_UPDATE_POS       4

#define AIRPLAY_DACP_PAUSE   1
#define AIRPLAY_DACP_VOLUP   2
#define AIRPLAY_DACP_VOLDOWN 3
#define AIRPLAY_DACP_PREV    4
#define AIRPLAY_DACP_NEXT    5
#define AIRPLAY_DACP_PLAY    6
#define AIRPLAY_DACP_STOP    7
#define AIRPLAY_DACP_PLAYPAUSE    8

typedef void (*update_status_callback)(void *cls, int cmd, int param, char *data);

typedef struct {
    int status;
    int volume;
    int totaltime;
    char trackinfo[512]; /* title;artist;album;*/
}saplay_info_t;

typedef struct {
    int msgid;
    saplay_info_t  info;
    update_status_callback update_status;
} saplay_options_t;

int swa_airplay_init(char*deviceid, char* devicename, update_status_callback update_status);
int swa_airplay_shutdown(void);
void swa_airplay_ipchange(void);
void swa_airplay_setapname( char* apname);
int swa_airplay_getstatus(void);
int swa_airplay_gettotaltime(void);
char* swa_airplay_gettrackinfo(void);
int swa_airplay_getvolume(void);
int swa_airplay_dacp_command(int command);

#endif /* __APPS_SYSTEM_AIRPLAY_SWA_AIRPLAY_API_H */
