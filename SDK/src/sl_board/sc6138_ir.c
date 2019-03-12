  /****************************************************************************
  * Included Files
  ****************************************************************************/
#include <arch/board/board.h>
#include <debug.h>
#include <errno.h>
#include "input_key.h"
#include <nuttx/arch.h>
#include <nuttx/config.h>
#include <nuttx/input.h>
#include <nuttx/io.h>
#include <nuttx/module.h>
#include <semaphore.h>
#include <silan_resources.h>
#include <silan_timer.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "zhuque_bsp_gpio.h"
 
#include <../sl_ui/led_driver.h>

 /****************************************************************************
  * Pre-processor Definitions
  ****************************************************************************/
//#define IR_DEBUG
 
#define TIMER_COUNTER 0
#define TIMER_COMPARE 4
#define TIMER_CONTROL 8
 
#define LEADER_MIN 1330 * 10 //us
#define LEADER_MAX 1370 * 10
#define DATA_1_MIN 205 * 10
#define DATA_1_MAX 245 * 10
#define DATA_0_MIN 92 * 10
#define DATA_0_MAX 132 * 10
#define REPEAT_MIN 1100 * 10
#define REPEAT_MAX 1150 * 10
 
#define cpuclk 10
#define CLK_LEADER_MIN (cpuclk * 1300) /* Leader minimum */
#define CLK_LEADER_MAX (cpuclk * 1390) /* Leader maximum */
#define CLK_DATA_1_MIN (cpuclk * 185)  /* Data 1 minimum  */
#define CLK_DATA_1_MAX (cpuclk * 275)  /* Data 1 maximum */
#define CLK_DATA_0_MIN (cpuclk * 72)   /* Data 0 minimum */
#define CLK_DATA_0_MAX (cpuclk * 152)  /* Data 0 maximum  */
#define CLK_REP_MIN (cpuclk * 1000)    /* REP  0 minimum */
#define CLK_REP_MAX (cpuclk * 1150)    /* REP  0 maximum  */
#define CLK_REPEAT_MIN (cpuclk * 1075) /* REPEAT  11.25 minimum */
#define CLK_REPEAT_MAX (cpuclk * 1175) /* REPEAT  11.25 maximum  */
#define CLK_REPEAT (cpuclk * 10800)    /* REPEAT  108 maximum  */
 
#define IR_BIT_NUM 32

//??????????€?0xCF10 1100 1111 0001 0000   ¨¨¡ì¡ê?????¡°??? 0xF308  0101 1000 -->  0001 1010
#define cust_code  0xF308
 
#define CODENUM (sizeof(ir_key_table) / sizeof(ir_key_table[0]))
 
#define TIMER_BASE (SILAN_TIMER1_BASE + 0x10 * (CONFIG_SC6138_IR_TIMER - 1))
 
 //?????¡ì?¨¦?D???|¡§??????¡§|?¡ìo?3??|¡§???¡ìo
#define REPEATE_TIMES 2
#define REPEATE_TIMES_SPEC  5

 /****************************************************************************
  * Public Types
  ****************************************************************************/
 
 /****************************************************************************
  * Public Data
  ****************************************************************************/
 static const struct
 {
	 unsigned char ircode;
	 int keycode;
 } ir_key_table[] =
 {
	 {0x30, CODE_POWER},	 
	 {0x96, CODE_BT_MODE},						  
	 {0xb0, CODE_MUTE}, 	  
	 {0x9c, CODE_OPT_MODE}, 	  
	 {0xdf, CODE_HDMI_MODE},	  
	 {0x61, CODE_AUX_MODE}, 	  
	 {0x1c, CODE_RCA_MODE}, 	 
	 {0x98, CODE_TREBLE_INC},		  
	 {0x5a, CODE_TREBLE_DEC},	  
	 {0xe8, CODE_BASS_INC}, 	  
	 {0x34, CODE_BASS_DEC}, 	 
	 {0x88, CODE_VOLUME_INC},	  //vol inc
	 {0xda, CODE_VOLUME_DEC},	  //voi dec   
	 {0x58, CODE_CHANNEL_PREV},   //prev
	 {0xdc, CODE_CHANNEL_NEXT},   //next
	 {0xa8, CODE_PLAY_PAUSE},	  //play or pause
 	 {0x18, CODE_EQ_MUSIC},
	 {0x68, CODE_EQ_MOVIE},
	 {0x08, CODE_EQ_DIALOG}
 };
 
 static int ir_irq_num = 38;
 static int ir_code_cnt = 0;
 static int ir_code_tbl[IR_BIT_NUM] = {0};
 static int ir_last_key = 0;
 
 static int repeat_timer = REPEATE_TIMES;
 static int repeat_timer_spec = REPEATE_TIMES_SPEC;
 /****************************************************************************
  * Public Function Prototypes
  ****************************************************************************/
 static int read_timer(void);
 static void ir_produce(void);
 
 extern unsigned int get_silan_busclk(void);
 extern void sc6138_timer_start(int timerNo);
 /****************************************************************************
  * Public Functions
  ****************************************************************************/
 
 /****************************************************************************
  * Name: ir_produce
  *
  * Description:
  *    o?¡ì??¡ìaa??¡ì??¡ìo?3?¡ì|1|??|?¡ì?¨¨?¡ìa3?¡ì?D?¡ì??
  *
  * Parameters:
  *
  * Returned Value:
  *
  * Assumptions:
  *
  ****************************************************************************/
 static void ir_produce(void)
 {
	 unsigned int data = 0, i;
	 unsigned char data1, check, key;
	 struct input_event key_event;
 
	 for (i = 0; i < IR_BIT_NUM; i++)
	 {
		 data = ((data << 1) | ir_code_tbl[i]);
	 }
#ifdef IR_DEBUG
	 printf("ir_produce data %x\n", data);
#endif
	 data1 = data & 0xff;
	 check = ~((data >> 8) & 0xff);
#ifdef IR_DEBUG
	 printf("ir_produce data1 %x check %x\n", data1, check);
	 printf("data H :%x\n", ((data >> 16) & 0xffff));
#endif
	 if ((data1 == check) && (((data >> 16) & 0xffff) == cust_code))
	 {
		 key = ~(data & 0xff);
#ifdef IR_DEBUG
		 printf("keycode : %x\n", key);
#endif
 
		 //ir_last_key = key;
		 for (i = 0; i < CODENUM; i++)
		 {
			 if (key == ir_key_table[i].ircode)
			 {
 
#ifdef IR_DEBUG
				 printf("keycode : %x\n", key);
#endif
				if (key != 0x96) //¨¦??BT MODE¨¦¡±?
				{
					 key_event.type = EV_IR;
					 key_event.code = ir_key_table[i].keycode;
					 key_event.value = 0; //key_priv.key_num;
	 
#ifdef IR_DEBUG
					 printf("sc6138 adkey push 0x%x\n", key_event.value);
#endif
					 input_add_event(&key_event);
				}
				 
				 //update last IR key value
				 ir_last_key = ir_key_table[i].keycode;
			 }
		 }
	 }
 
	 ir_code_cnt = 0;
	 memset(ir_code_tbl, 0, IR_BIT_NUM);
	 sc6138_timer_stop(CONFIG_SC6138_IR_TIMER);
	 sc6138_timer_initialize(CONFIG_SC6138_IR_TIMER, 0xffffffff, NULL);
 
	 return;
 }


 /****************************************************************************
  * Name: ir_produce
  *
  * Description:
  *    o?¡ì??¡ìaa?D????¨¨t??3?¡ì?D?¡ì??
  *
  * Parameters:
  *
  * Returned Value:
  *    ?¡§¡é?¡ì1?¡ìo?0
  * 
  * Assumptions:
  *
  ****************************************************************************/
 static int ir_isr(int irq)
 {
	 unsigned int width, usec;
	 static unsigned int prev_usec = 0;
	 //  struct input_event key_event;
 
	 int value;
 
	 zhuque_bsp_gpio_get_value(ir_irq_num, (uint32_t *)&value);
	 //  printf("ir_isr value:%d\r\n",value);
 
	 if (value > 0)
	 {
		 return 0;
	 }
 
	 if (ir_code_cnt >= IR_BIT_NUM)
	 {
		 return 0;
	 }
 
	 sc6138_timer_start(CONFIG_SC6138_IR_TIMER);
	 usec = read_timer();
	 if (prev_usec > usec)
	 {
		 prev_usec = 0;
	 }
 
	 width = usec - prev_usec;
 
#ifdef IR_DEBUG
	 printf("width:%ld\r\n", width);
#endif
	 prev_usec = usec;
	 if ((width >= CLK_DATA_1_MIN) && (width <= CLK_DATA_1_MAX))
	 {
		 ir_code_tbl[ir_code_cnt++] = 1;
	 }
	 else if ((width >= CLK_DATA_0_MIN) && (width <= CLK_DATA_0_MAX))
	 {
		 ir_code_tbl[ir_code_cnt++] = 0;
	 }
	 else if ((width >= CLK_LEADER_MIN) && (width <= CLK_LEADER_MAX))
	 {
		 ir_code_cnt = 0;
		 // ir_last_key = 0;
		 memset(ir_code_tbl, 0, IR_BIT_NUM);
		 // reset key repeat counter
		 repeat_timer = REPEATE_TIMES;
		 
		 ir_repeat_code_times = 0;
		 ir_repeat_wdtimer_start = 0;
		 ir_repeat_flag = 0;
	 }
	 else if ((width >= CLK_REPEAT_MIN) && (width <= CLK_REPEAT_MAX))
	 {
#ifdef IR_DEBUG
		 printf("xxxxxxxx11.5ms\n");
#endif
		 if (ir_last_key == CODE_BT_MODE)
		 {
			 ir_repeat_flag = 1;
			 if (ir_repeat_wdtimer_start == 0)
			 {
			 	 ir_repeat_wdtimer_start = 1;
			 }
		 }
		 else if (CODE_VOLUME_INC == ir_last_key || CODE_VOLUME_DEC == ir_last_key)
		 {
			 if (--repeat_timer == 0)
			 {
				 //send key event for long press
				 struct input_event key_event;
				 key_event.type = EV_IR;
				 key_event.code = ir_last_key;
				 key_event.value = 0;
				 input_add_event(&key_event);
				 // reset key repeat counter
				 repeat_timer = REPEATE_TIMES;
			 }
		 }
	 }
 //#ifdef IR_DEBUG
 //  printf("ir_code_cnt %d\n", ir_code_cnt);
 //#endif
	 if (ir_code_cnt >= IR_BIT_NUM)
	 {
#ifdef IR_DEBUG
		 printf("enter ir_produce !\n\n");
#endif
		 ir_produce();
	 }
 
	 return 0;
 }
 
 /****************************************************************************
  * Name: read_timer
  *
  * Description:
  *    ??¡ì?¨¦?¡ì?¡ì??¡ìo?¡§¡è???|¡§?
  *
  * Parameters:
  *
  * Returned Value:
  *    ??¡§|???¡ìoy
  * 
  * Assumptions:
  *
  ****************************************************************************/
 static int read_timer(void)
 {
	 int val, cnt, usec;
 
	 val = readl(TIMER_BASE + TIMER_COUNTER);
	 cnt = get_silan_busclk() / 1000000;
	 //printf("busclk=%d\n", get_silan_cpuclk());
	 usec = val / cnt;
 
	 return usec;
 }
 
 /****************************************************************************
  * Name: sc6138_ir_pin_set
  *
  * Description:
  *    ?¡ì|?¡ì?¡ì??o?¡ì??¡ìaa??¡ì??¡ìo??¡ìo1?¡ì??|¡§???¡ì??y??
  *
  * Parameters:
  *
  * Returned Value:
  *    ??¡§|???¡ìoy
  * 
  * Assumptions:
  *
  ****************************************************************************/
 int sc6138_ir_pin_set(int pin)
 {
	 ir_irq_num = pin;
	 return 0;
 }
 
 /****************************************************************************
  * Name: sc6138_irinitialize
  *
  * Description:
  *    o?¡ì??¡ìaa??¡ì??¡ìo???¡ì?2a3??¡ìo???¡ê¡è
  *
  * Parameters:
  *
  * Returned Value:
  *    ??¡§|???¡ìoy
  * 
  * Assumptions:
  *
  ****************************************************************************/
 static int sc6138_irinitialize(void)
 {
	 //printf(">>>>>>>>>>>>>>>sc6138_irinitialize !\n ");
	 zhuque_bsp_gpio_set_mode(ir_irq_num, GPIO_IN, PULLING_NONE);
	 zhuque_bsp_gpio_register_interrupt(ir_irq_num, FALLING_EDGE, ir_isr);
	 sc6138_timer_initialize(CONFIG_SC6138_IR_TIMER, 0xffffffff, NULL);
	 return 0;
 }
 //?¡ì|?¡ì?¡ì???a??¡ì2???DDo?¡ì??¡ìaa??¡ì?2?¡ì|3??¡ìo???¡ê¡è3?¡ì?D?¡ì??
 //zhuque_device_init(sc6138_irinitialize);
