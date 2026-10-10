/*
 * timer.c
 *
 *  Created on: Oct 22, 2025
 *      Author: cosmi
 */

#include "timer.h"
#include "scheduler.h"

void timer_init(){
    TA0CTL = MC__STOP;
    TA0CTL |= TASSEL__ACLK | ID__8;
    TA0CCTL0 |= CCIE;
}

void timer_stop(){
    TA0CTL &= ~MC_3;
    TA0CTL |= TACLR;
}

void timer_start(){
    TA0CCR0 = 4096;
    TA0CTL |= MC__UP;
}

// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    scheduler(); // lansare planificator
}

#ifdef DEBUG_SCHEDULER

    void timer_init_task_statistics(){
        TA1CTL = MC__STOP;
        TA1CTL |= TASSEL__SMCLK | ID__1;
        TA1CCTL0 &= ~CCIE;
    }

//    static inline void timer_start_task_statistics();
//    static inline uint16_t timer_stop_task_statistics();

#endif
