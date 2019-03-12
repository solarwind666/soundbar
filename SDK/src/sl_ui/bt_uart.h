#ifndef __BT_UART_H__
#define __BT_UART_H__

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <stdbool.h>
/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Types
 ****************************************************************************/
enum
{
    BT_POWER,
    BT_MODE,
    AUX_MODE,
    FM_MODE,
    BT_PRV,
    BT_NEXT,
    BT_VOL_DOWN,
    BT_VOL_UP,
    BT_PAIRE,
    BT_DIS_PAIRE,
    BT_AUTO_CONNECT,
    BT_DIS_CONNECT,
    BT_PAUSE,
    BT_PLAY,
    BT_STOP,
    FM_SEARCH,
    FM_STOP,
    FM_GET_FQ,
    SD_MODE,
    COM_IQ,
    BT_AT_AUX,
    BT_AT_DECODE,
    BT_AT_BT,
    BT_AT_PWROFF,
} BT_CMD;


enum
{
	AT_CMD_START = -1,
	AT_CMD_POWER,	
	AT_CMD_MUTE,
	
	AT_CMD_RCA,
	AT_CMD_HDMI,
	AT_CMD_AUX,
	AT_CMD_OPT,
	AT_CMD_BT,
	
	AT_CMD_EQ_MUSIC,
	AT_CMD_EQ_MOVIE,
	AT_CMD_EQ_DIALOG,
	
	AT_CMD_BASS_DOWN,
	AT_CMD_BASS_UP,
	AT_CMD_TREBLE_DOWN,
	AT_CMD_TREBLE_UP,
	
	AT_CMD_BT_PREV,
	AT_CMD_BT_OK,
	AT_CMD_BT_NEXT,
	
	AT_CMD_MODE,
	AT_CMD_BT_CONNECTED,
	AT_CMD_BT_DISCONECT,

	AT_CMD_BT_VOL_INC,
	AT_CMD_BT_VOL_DEC,

	AT_CMD_SET_48K,
	AT_CMD_SET_44K,

	AT_CMD_SET_VOL,
	AT_CMD_MAX
}AT_CMD_S;


/****************************************************************************
 * Public Data
 ****************************************************************************/

 /****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: bt_read
 *
 * Description:
 *    通过串口读取蓝牙模块反馈的信息
 * 
 * Parameters:
 *    buf_receive 接收数据用的buf
 *
 * Returned Value:
 *    -1 获取数据失败， 0 获取数据成功
 * 
 * Assumptions:
 *
 ****************************************************************************/
//int bt_read(char *buf_receive);
//int bt_chk_AT_cmd(char *cmd, int *pVal);

int bt_read(char *buf, int buf_szie);
/****************************************************************************
 * Name: bt_uart_init
 *
 * Description:
 *    初始化与蓝牙通信的串口，波特率9600
 * 
 * Parameters:
 *
 * Returned Value:
 *    true 初始化成功， false 初始化失败
 * 
 * Assumptions:
 *
 ****************************************************************************/
bool bt_uart_init(void);

/****************************************************************************
 * Name: bt_uart_close
 *
 * Description:
 *    关闭蓝牙设备句柄
 * 
 * Parameters:
 *
 * Returned Value:
 *    true 初始化成功， false 初始化失败
 * 
 * Assumptions:
 *
 ****************************************************************************/
bool bt_uart_close(void);

 /****************************************************************************
 * Name: handle_bt_cmd
 *
 * Description:
 *    通过串口向蓝牙模块发送命令
 * 
 * Parameters:
 *    cmd 要发送的命令
 *
 * Returned Value:
 *    0 发送成功， -1 发送失败失败
 * 
 * Assumptions:
 *
 ****************************************************************************/
int handle_bt_cmd(int cmd);
int handle_bt_vol(int vol);
 
#endif
