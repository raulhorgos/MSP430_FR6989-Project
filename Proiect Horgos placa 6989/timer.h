/*
 * timer.h
 *
 *  Created on: Oct 22, 2025
 *      Author: cosmi
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <msp430.h>
#include <stdint.h>

void timer_init();
void timer_stop();
void timer_start();

#ifdef DEBUG_SCHEDULER

void timer_init_task_statistics();

static inline void timer_start_task_statistics()
{
    TA1CTL |= TACLR;
    TA1CTL |= MC__CONTINUOUS;
}

static inline uint16_t timer_stop_task_statistics()
{
    TA1CTL &= ~MC_3;
    return TA1R;
}

#endif

#endif /* TIMER_H_ */
