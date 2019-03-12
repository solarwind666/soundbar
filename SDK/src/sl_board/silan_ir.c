#include <nuttx/config.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <semaphore.h>
#include <errno.h>
#include <debug.h>
#include <nuttx/io.h>
#include <arch/board/board.h>
#include <nuttx/arch.h>
#include <nuttx/module.h>
#include <nuttx/input.h>
#include <silan_resources.h>
#include "zhuque_bsp_gpio.h"

//#define IR_DEBUG

#define TIMER_COUNTER 0
#define TIMER_COMPARE 4
#define TIMER_CONTROL 8

#define LEADER_MIN   1330*10  //us
#define LEADER_MAX   1370*10
#define DATA_1_MIN   205*10
#define DATA_1_MAX   245*10
#define DATA_0_MIN   92*10
#define DATA_0_MAX   132*10
#define REPEAT_MIN   1100*10
#define REPEAT_MAX   1150*10

#define cpuclk 10
#define CLK_LEADER_MIN  (cpuclk * 1300)  /* Leader minimum */
#define CLK_LEADER_MAX  (cpuclk * 1390)  /* Leader maximum */
#define CLK_DATA_1_MIN  (cpuclk * 195)   /* Data 1 minimum  */
#define CLK_DATA_1_MAX  (cpuclk * 255)   /* Data 1 maximum */
#define CLK_DATA_0_MIN  (cpuclk * 82)    /* Data 0 minimum */
#define CLK_DATA_0_MAX  (cpuclk * 142)   /* Data 0 maximum  */
#define CLK_REP_MIN     (cpuclk * 1000)  /* REP  0 minimum */
#define CLK_REP_MAX     (cpuclk * 1150)  /* REP  0 maximum  */

#define IR_BIT_NUM 32

static const struct
{
   unsigned char  ircode;
   int  keycode;
} ir_key_table[] =
{
};

#define CODENUM (sizeof(ir_key_table)/sizeof(ir_key_table[0]))

#define TIMER_BASE (SILAN_TIMER1_BASE+0x10*(CONFIG_SILAN_IR_TIMER-1))

static int ir_irq_num = CONFIG_SILAN_IR_GPIO;
static int ir_code_cnt = 0;
static int ir_code_tbl[IR_BIT_NUM] = {0};
static int ir_last_key = 0;

static int read_timer(void);
static void ir_produce(void);
extern unsigned int get_silan_busclk(void);

static int read_timer(void)
{
    int val, cnt, usec;

    val = readl(TIMER_BASE + TIMER_COUNTER);
    cnt = get_silan_busclk()/(1000000*get_silan_timer_div());
    //printf("busclk=%d\n", get_silan_cpuclk());
    usec = val/cnt;

    return usec;
}

static void ir_produce(void)
{
    unsigned int data = 0, i;
    unsigned char data1, check, key;
    struct input_event event;
    for (i = 0; i < IR_BIT_NUM; i++)
        data = ((data << 1) | ir_code_tbl[i]);
#ifdef IR_DEBUG
    printf("ir_produce data %x\n", data);
#endif
    data1 = data & 0xff;
    check = ~((data >> 8) & 0xff);
#ifdef IR_DEBUG
    printf("ir_produce data1 %x check %x\n", data1, check);
#endif
    if (data1 == check)
    {
        key = ~(data & 0xff);
        printf("keycode : 0x%x\n", key);
        ir_last_key = key;
        for (i = 0; i < CODENUM; i++)
        {
            if (key == ir_key_table[i].ircode)
            {
                event.type = EV_IR;
                event.code = CODE_IR_PRESS;
                event.value = key;
                //printf("keycode : %x\n", key);
            }
        }
    }

    ir_code_cnt = 0;
    memset(ir_code_tbl, 0, IR_BIT_NUM);
    silan_timer_stop(CONFIG_SILAN_IR_TIMER);
    silan_timer_initialize(CONFIG_SILAN_IR_TIMER, 0xffffffff, NULL);

    return;
}

static int ir_isr(int irq)
{
    unsigned int width, usec;
    static unsigned int prev_usec = 0;
    struct input_event event;

    if (ir_code_cnt >= IR_BIT_NUM)
        return 0;

    silan_timer_start(CONFIG_SILAN_IR_TIMER);
    usec = read_timer();
    if (prev_usec > usec)
        prev_usec = 0;

    width = usec - prev_usec;
    prev_usec = usec;
    if ((width >= CLK_DATA_1_MIN) && (width <= CLK_DATA_1_MAX))
        ir_code_tbl[ir_code_cnt++] = 1;
    else if ((width >= CLK_DATA_0_MIN) && (width <= CLK_DATA_0_MAX))
        ir_code_tbl[ir_code_cnt++] = 0;
    else if ((width >= CLK_LEADER_MIN) && (width <= CLK_LEADER_MAX))
    {
         ir_code_cnt = 0;
         ir_last_key = 0;
         memset(ir_code_tbl, 0, IR_BIT_NUM);
    }
    else if ((width >= CLK_REP_MIN) && (width <= CLK_REP_MAX))
    {
        if (ir_last_key > 0) {
            printf("repeat key 0x%x\n", ir_last_key);
            event.type = EV_IR;
            event.code = CODE_IR_LONG_PRESS;
            event.value = ir_last_key;
        }
    }

    if (ir_code_cnt >= IR_BIT_NUM)
        ir_produce();

    return 0;
}

int silan_ir_pin_set(int pin)
{
    ir_irq_num = pin;
    return 0;
}

static int silan_irinitialize(void)
{
    zhuque_bsp_gpio_set_mode(ir_irq_num, GPIO_IN, PULLING_NONE);
    zhuque_bsp_gpio_register_interrupt(ir_irq_num, FALLING_EDGE, ir_isr);

    silan_timer_initialize(CONFIG_SILAN_IR_TIMER, 0xffffffff, NULL);
    silan_timer_start(CONFIG_SILAN_IR_TIMER);
    return 0;
}
zhuque_device_init(silan_irinitialize);
