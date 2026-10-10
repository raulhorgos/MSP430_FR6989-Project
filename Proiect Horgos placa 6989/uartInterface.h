/*
 * uartInterface.h
 *
 * Created on: Dec 3, 2025
 * Author: Horgos Raul
 */

#ifndef UARTINTERFACE_H_
#define UARTINTERFACE_H_

#include <msp430.h>
#include <stdio.h>  // Added for sprintf

void initUartPorts(void);
void initUartInterface(void);
void taskUart(void);

#endif /* UARTINTERFACE_H_ */
