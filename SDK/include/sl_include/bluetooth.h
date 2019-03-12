#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#define BT_EXT_CMD_SWITCH_FG    1
#define BT_EXT_CMD_SWITCH_BG    2
#define BT_EXT_CMD_PAUSE        3
#define BT_EXT_CMD_STOP         4
#define BT_EXT_CMD_PREV         5
#define BT_EXT_CMD_NEXT         6
#define BT_EXT_CMD_PLAY         7
#define BT_EXT_CMD_ANSWER       8
#define BT_EXT_CMD_HUNG         9
#define BT_EXT_CMD_DISCONNECT   10
#define BT_EXT_CMD_CONNECT      11

#ifdef CONFIG_BLUETOOTH
int bt_process_cmd(int cmd);
#else
int bt_process_cmd(int cmd) {
    return 0;
}
#endif
#endif
