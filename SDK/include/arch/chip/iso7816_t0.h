/*
 *  Copyright (C) 2015 YunOS Project. All rights reserved.
 */

#ifndef __ISO7816_T0_H__
#define __ISO7816_T0_H__

/* Definitions */
#define TLENGTH_MAX 20
#define HLENGTH_MAX 20
#define LC_MAX      300
#define MAX_ATR_LENGTH  40

#define PROTOCOL_T0 0x00

#define NO_ERROR        0
#define GETATR_ERROR    (-1)
#define TRANSMIT_ERROR  (-2)
#define RESPONSE_ERROR  1 
#define TIMEOUT_ERROR   2

/* ATR */
typedef struct {
    unsigned char TS;
    unsigned char T0;
    unsigned char T[TLENGTH_MAX];
    unsigned char H[HLENGTH_MAX];
    unsigned char Tlength;
    unsigned char Hlength;
}iso7816_atr_t;

/* apdu header */
typedef struct {
    unsigned char CLA;
    unsigned char INS;
    unsigned char P1;
    unsigned char P2;
}iso7816_header_t;

/* apdu body */
typedef struct {
    unsigned char LC;
    unsigned char Data[LC_MAX];
    unsigned char LE;
}iso7816_body_t;

/* apdu */
typedef struct {
    iso7816_header_t header;
    iso7816_body_t body;
}iso7816_apdu_command_t;

/* response */
typedef struct {
    unsigned char data[LC_MAX];
    unsigned char SW1;
    unsigned char SW2;
}iso7816_apdu_response_t;

/* functions declare */
extern void iso7816_pps_exchange(void);
extern int iso7816_start(void);
extern int iso7816_stop(void);
extern int iso7816_reset(void);
extern int t0_send_command_recv_status(iso7816_apdu_command_t *apdu, iso7816_apdu_response_t *response);
#endif
