#ifndef _UART_H_
#define _UART_H_

typedef enum _uart_port{
    HIGH_UART,
    NORMAL_UART1,
    NORMAL_UART2,
    NORMAL_UART3,
}UART_PORT;

int swa_uart_open(UART_PORT num);
int swa_uart_set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop);
int swa_uart_read(int fd, char *rbuf, int length);
int swa_uart_write(int fd, char *wbuf, int length);
int swa_uart_close(int fd);

#endif

