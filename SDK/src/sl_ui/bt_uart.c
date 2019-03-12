/****************************************************************************
 * Included Files
 ****************************************************************************/
#include "bt_uart.h"
#include <fcntl.h>
#include <silan_resources.h>
#include <silan_addrspace.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <zhuque_bsp_gpio.h>



/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define BT_DEBUG    1
#define UART_TX_PIN 13
#define UART_RX_PIN 14

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/
/*与蓝牙模块通信的字符串*/
const char AUX_mode[] = "COM+MAX\n";
const char BT_auto_connect[] = "BT+AC\r\n";
const char BT_dis_connect[] = "BT+DC\r\n";
const char BT_dis_paire[] = "AT+CA\r\n";
const char BT_mode[] = "COM+MBT\n";
const char BT_next[] = "AT+PV\r\n";
const char BT_prv[] = "AT+PN\r\n";
const char BT_paire[] = "AT+PR\r\n";
const char BT_pause[] = "AT+PU\r\n";
const char BT_play[] = "AT+PA\n";
const char BT_power[] = "AT+CP\r\n";
const char BT_stop[] = "AT+MC\r\n";
const char BT_vol_down[] = "AT+CL\r\n";
const char BT_vol_up[] = "AT+CK\r\n";
const char COM_iq[] = "AT+MO\r\n";
const char COM_sd[] = "COM+MSD\n";
const char FM_get_fq[] = "FM+GF\n";
const char FM_mode[] = "COM+MFM\n";
const char FM_search[] = "FM+SC\n";
const char FM_stop[] = "FM+ST\n";
//
const char BT_CMD_AUX[] = "AT+AUX\n";
const char BT_CMD_DECODE[] = "AT+D8836\n"; //8836输入的音源
const char BT_CMD_BT[] = "AT+BT\n";
const char BT_CMD_PWROFF[] = "AT+PWROFF\n";





/*与蓝牙模块通信串口文件描述符*/
int bt_fd = 0;

const char * AT_CMDS[] = {
	"T+IDLE",
	"T+MU",
	
	"T+LINE",
	"T+HDMI",
	"T+AUX",
	"T+OPT",
	"T+BT",
	
	"T+EQ",
	"T+EQ2",
	"T+EQ3",		
	"T+BASSDOWN",
	"T+BASSUP",
	"T+TREBDOWN",
	"T+TREBUP",
	
	"T+PE",	//PREV
	"T+PA",	//PAUSE
	"T+PD",	//NEXT	
	"T+MODE",   //MODE
	"T+C1",
	"T+C0",

	"T+VOL_UP",
	"T+VOL_DOWN",

	"T+48K",
	"T+44K",

	"T+VOL+",
};


/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: bt_chk_AT_cmd
 *
 * Description:
 *    检测不带参数的AT命令
 *
 * Parameters:
 *    cmd 命令字符串
 *    val 返回的值
 *
 * Returned Value:
 *    -1不是AT命令，命令对就的序号
 * 
 * Assumptions:
 *
 ****************************************************************************/
int bt_chk_AT_cmd(char *cmd, int *pVal)
{
    const int cmds_num = AT_CMD_MAX;
    int ret = AT_CMD_START;
    int i;
    char * ptr = NULL;
	int val = 0;
    for(i=0;i<cmds_num;++i)
    {
        if ((ptr = strstr(cmd, AT_CMDS[i])) != NULL)
        {//蓝牙连接
            int j = 0;
            int len = strlen(AT_CMDS[i]);
            if(i < AT_CMD_MAX)
            {
                //清除字符串中的命令
                for(j=0;j<len;++j)
                {
                    ptr[j]=' ';
                }
                ret = i;

				if('0' <= ptr[len] && ptr[len] <= '9')
				{
					val = 10 * (ptr[len] - '0');
				}

				if('0' <= ptr[len+1] && ptr[len+1] <= '9')
				{
					val += (ptr[len+1] - '0');
				}

				*pVal = val;
            }
            else
            {
            	/*
                //计算参数值
                for(j=len;j<len+2;++j)
                {
                    if('0' <= ptr[j] && ptr[j] <= '9')
                    {
                        val *= 10;
                        val += ptr[j] - '0';
                    }
                    else
                    {
                        break;
                    }
                }

                if(ptr[j]==0)
                {//数据未读完
                }
                else if(j == len || ptr[j] != '\n')
                {//无效命令
                    ++j;
                    for(;j>=0;--j)
                    {
                        ptr[j]=' ';
                    }
                }
                else if(ptr[j] == '\n')
                {//有效命令
                    //清除字符串中的命令
                    ++j;
                    for(;j>=0;--j)
                    {
                        ptr[j]=' ';
                    }
                    ret = i;
                    *pVal = val;
                }
                */
            }
            break;
        }
    }

    return ret;
}

/****************************************************************************
 * Name: bt_read
 *
 * Description:
 *    通过串口读取蓝牙模块反馈的信息
 * 
 * Parameters:
 *    buf 接收数据用的buf
 *    buf_szie 缓存的大小
 *
 * Returned Value:
 *    -1 获取数据失败， >= 0 获取数据成功
 * 
 * Assumptions:
 *    buf的长度必须大于等于buf_szie
 *
 ****************************************************************************/
int bt_read(char *buf, int buf_szie)
{
    int ret = -1;
    
    if (bt_fd < 0)
    {   //无效串口文件描述符
		#if BT_DEBUG
        printf("%s:UART is not open\n", __func__);
		#endif
    }
    else if(NULL == buf)
    {
        #if BT_DEBUG
        printf("%s:error buffer\n", __func__);
        #endif
    }
    else
    {
        fd_set fds;
        struct timeval tm;

        FD_ZERO(&fds);
        FD_SET(bt_fd, &fds);
        tm.tv_sec = 0;
        tm.tv_usec = 2500;


        if(select(bt_fd + 1, &fds, NULL, NULL, &tm) < 0)
        {
            #if BT_DEBUG
           // printf("%s:select err or timeout\n", __func__);
            #endif
        }
        else
        {
            if (FD_ISSET(bt_fd, &fds) > 0)
            {   ///有数据可以从串口读取
                memset(buf, 0, buf_szie);
                int count = read(bt_fd, buf, buf_szie);
                if (count <= 0)
                {   //串口中没有数据
                    #if BT_DEBUG
                  //  printf("%s:Read nothing from UART\n", __func__);
                    #endif
                    ret = 0;
                }
                else
                {   //从串口读到了数据
                    ret = count;
					#if BT_DEBUG
					{
					  	printf("%s:buf_rev %s count:%d\r\n", __func__, buf, count);
					}
					#endif
                }
            }
            else
            {   //串口中无数据可读
                #if BT_DEBUG
                //printf("%s:Nothing can be read from UART\n", __func__);
                #endif
            }
        }
        
        
    }

    return ret;
}

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
bool bt_uart_init(void)
{
    bool ret = false;
    unsigned long value;
    //设置UART3的IO口状态
    zhuque_bsp_gpio_set_mode(UART_TX_PIN, GPIO_OUT, PULLING_HIGH);
    zhuque_bsp_gpio_set_value(UART_TX_PIN, GPIO_VALUE_LOW);
    zhuque_bsp_gpio_set_mode(UART_RX_PIN, GPIO_IN, PULLING_HIGH);
    zhuque_bsp_gpio_set_value(UART_RX_PIN, GPIO_VALUE_LOW);
    //设置UART3的对应的IO口功能
    value = REG32(KSEG1(SILAN_PADMUX_CTRL));
    value |= (1 << SILAN_PADMUX_UART3_1);
	value &= ~(1 << SILAN_PADMUX_UART3_2);
    REG32(KSEG1(SILAN_PADMUX_CTRL)) = value;

    //打开UART3设备
    bt_fd = open("/dev/ttyS2", O_RDWR | O_NDELAY);
    if (bt_fd > 0)
    {   //UART3打开成功
        struct termios term;
        bzero(&term, sizeof(struct termios));
        tcgetattr(bt_fd, &term);
        cfsetispeed(&term, B115200);
        cfsetospeed(&term, B115200);
        tcsetattr(bt_fd, TCSANOW, &term);
        ret = true;
    }
    else
    {
        printf("open ttys2 fail\n");
    }
    
    return ret;
}

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
bool bt_uart_close(void)
{
//    unsigned long value;
//    if(bt_fd > 0)
//    {   //UART3已经打开
//        //关闭UART3
//        close(bt_fd);
//    }
//    //清除设备句柄
//    bt_fd = -1;

//    //关闭UART3的IO口功能
//    value = REG32(KSEG1(SILAN_PADMUX_CTRL));
//    value &= ~(1 << SILAN_PADMUX_UART1);
//    REG32(KSEG1(SILAN_PADMUX_CTRL)) = value;
//    //输出低
//    zhuque_bsp_gpio_set_mode(UART_TX_PIN, GPIO_OUT, PULLING_DOWN);
//    zhuque_bsp_gpio_set_value(UART_TX_PIN, GPIO_VALUE_LOW);
//    zhuque_bsp_gpio_set_mode(UART_RX_PIN, GPIO_OUT, PULLING_DOWN);
//    zhuque_bsp_gpio_set_value(UART_RX_PIN, GPIO_VALUE_LOW);
    return true;
}

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
int handle_bt_cmd(int cmd)
{
    int ret = -1;
    char buf[12] = {0};

    if (bt_fd < 0)
    {
        printf("%s:UART for bluetooth is not open\n", __func__);
    }
    else
    {
        switch (cmd)
        {
            case BT_POWER:
                strcpy(buf, BT_power);
                break;
            case BT_MODE:
                strcpy(buf, BT_mode);
                break;
            case AUX_MODE:
                strcpy(buf, AUX_mode);
                break;
            case FM_MODE:
                strcpy(buf, FM_mode);
                break;
            case BT_PRV:
                strcpy(buf, BT_prv);
                break;
            case BT_NEXT:
                strcpy(buf, BT_next);
                break;
            case BT_VOL_DOWN:
                strcpy(buf, BT_vol_down);
                break;
            case BT_VOL_UP:
                strcpy(buf, BT_vol_up);
                break;
            case BT_PAIRE:
                strcpy(buf, BT_paire);
                break;
            case BT_DIS_PAIRE:
                strcpy(buf, BT_dis_paire);
                break;
            case BT_AUTO_CONNECT:
                strcpy(buf, BT_auto_connect);
                break;
            case BT_DIS_CONNECT:
                strcpy(buf, BT_dis_connect);
                break;
            case BT_PAUSE:
                strcpy(buf, BT_pause);
                break;
            case BT_PLAY:
                strcpy(buf, BT_play);
                break;
            case BT_STOP:
                strcpy(buf, BT_stop);
                break;
            case FM_SEARCH:
                strcpy(buf, FM_search);
                break;
            case FM_STOP:
                strcpy(buf, FM_stop);
                break;
            case FM_GET_FQ:
                strcpy(buf, FM_get_fq);
                break;
            case SD_MODE:
                strcpy(buf, COM_sd);
                break;
            case COM_IQ:
                strcpy(buf, COM_iq);
                break;
			//
			case BT_AT_AUX:
				strcpy(buf, BT_CMD_AUX);
				break;
			case BT_AT_DECODE:
				strcpy(buf, BT_CMD_DECODE);
				break;
			case BT_AT_BT:
				strcpy(buf, BT_CMD_BT);
				break;
			case BT_AT_PWROFF:
				strcpy(buf, BT_CMD_PWROFF);
				break;
            default:
                break;
        }
    
        write(bt_fd, buf, 12);

        printf("%s: buf:%s\n", __func__, buf);

        ret = 0;
    }

    return ret;
}

int handle_bt_vol(int vol)
{
    int ret = -1;
    char buf[12] = {0};

    if (bt_fd < 0)
    {
        printf("%s:UART for bluetooth is not open\n", __func__);
    }
    else
    {
    	sprintf(buf, "AT+VOL+%02d\n", vol);
        write(bt_fd, buf, 12);

        printf("%s: buf:%s\n", __func__, buf);

        ret = 0;
    }
    return ret;
}



