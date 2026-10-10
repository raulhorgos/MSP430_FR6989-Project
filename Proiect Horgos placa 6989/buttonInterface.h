/*
 * buttonInterface.h
 *
 * Created on: Jan 20, 2026
 * Description: Header for Button S1 (P1.1)
 */

#ifndef BUTTONINTERFACE_H_
#define BUTTONINTERFACE_H_

#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

/* Global Flag: true = Alarm On, false = Alarm Muted */
extern volatile bool g_systemArmed;

void initButton(void);
void taskButton(void);

#endif /* BUTTONINTERFACE_H_ */
