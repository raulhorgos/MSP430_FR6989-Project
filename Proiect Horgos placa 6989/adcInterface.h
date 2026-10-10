/*
 * adcInterface.h
 *
 * Created on: 10 Dec 2025
 * Author: Horgos Raul
 */

#ifndef ADCINTERFACE_H_
#define ADCINTERFACE_H_

#include "stdint.h"
#include "msp430.h"

/* GLOBAL VARIABLE for Debugging/Viewing */
extern volatile int16_t g_adcResult;

void adcPortInit();
void adcInit();

// start ADC
void adcStart();

// task ADC
void adcTask();

#endif /* ADCINTERFACE_H_ */
