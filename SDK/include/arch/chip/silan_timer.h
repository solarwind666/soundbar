/*
 * silan_timer.h
 *
 *  Created on: 2013-1-17
 *      Author: Junbo_Wu
 */

#ifndef _SILAN_TIMER_H_
#define _SILAN_TIMER_H_
//#include <silan.h>
#include "silan_resources.h"
#include "silan_irq.h"
#include <nuttx/config.h>

typedef volatile unsigned int    SL_REG;
typedef volatile unsigned short  SL_SREG;
typedef void (*timer_callback_t)(void) ;

#if CONFIG_CKCPU_MMU
#define SILAN_TIMER_BASE          SILAN_TIMER1_BASE
#else
#define SILAN_TIMER_BASE          SILAN_TIMER1_PHY_BASE
#endif

#if CONFIG_CKCPU_MMU
#define SILAN_TIMER_2_BASE          SILAN_TIMER2_BASE
#else
#define SILAN_TIMER_2_BASE          SILAN_TIMER2_PHY_BASE
#endif

#if CONFIG_CKCPU_MMU
#define SILAN_TIMER_3_BASE          SILAN_TIMER3_BASE
#else
#define SILAN_TIMER_3_BASE          SILAN_TIMER3_PHY_BASE
#endif

#if CONFIG_CKCPU_MMU
#define SILAN_TIMER_4_BASE          SILAN_TIMER4_BASE
#else
#define SILAN_TIMER_4_BASE          SILAN_TIMER4_PHY_BASE
#endif

typedef struct CKS_TIMER {
    SL_REG    TxCurrentValue;  /*  Timer Current Value of Timer */
    SL_REG    TxLoadCount;     /*  Timer Value to be loaded into Timer */
    SL_REG    TxControl;       /* Timer Control Register for Timer */
    SL_REG    TxClkSel;       /* Timer Control Register for Timer */
} CKStruct_TIMER,* PCKPStruct_TIMER;


/*
 *  define the bits for TxControl
 */
#define TIMER_EN(x)           ((x) << 7)
#define TIMER_MODE(x)         ((x) << 6)
#define TIMER_INT_EN(x)       ((x) << 5)
#define TIMER_PRE(x)          ((x) << 2)
#define TIMER_SIZE(x)         ((x) << 1)
#define TIMER_ONE_SHOT(x)     ((x))


typedef struct CKS_TIMER_CON {
    SL_REG    IntStatus;        /*  Contains the interrupt status of all
                                 *  timers in the component.
                                 */
    SL_REG    EOI;              /*  Returns all zeroes (0) and clears all
                                 *  active interrupts.
                                 */
    SL_REG    RawIntStatus;     /*  Contains the unmasked interrupt status
                                 *  of all timers in the component.
                                 */

} CKStruct_TIMER_CON,* PCKStruct_TIMER_CON;

/* Functions Declare */

/* inititial timer */
int silan_timer_initialize(int timerid, int us, timer_callback_t callback);

/* stop timer */
void silan_timer_stop(int timerid);
/* timer delay for us */
int silan_timer_delay_us(int timerid, int us);
#endif /* _SILAN_TIMER_H_ */
