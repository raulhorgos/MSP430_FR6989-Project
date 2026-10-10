/*
 * clcksystem.c
 *
 *  Created on: Oct 29, 2025
 *      Author: cosmi
 */

#include "clksystem.h"



void initClkPort()
{
    PJSEL1 &= ~BIT4;
    PJSEL0 |= BIT4;
}

void initClkSystem()
{
    CSCTL0_H = CSKEY >> 8;                  // Unlock CS registers
    CSCTL1 &= ~(DCORSEL_L | DCOFSEL_7);     // Setez registru in 0
    CSCTL1 |= DCORSEL_L | DCOFSEL_3;        // Set DCO to 8MHz
    CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__1 | DIVS__2 | DIVM__1;   /* ACLK = 32768 Hz,  SMCLK = 4 MHz, MCLK = 8 MHz */
    CSCTL4 |= LFXTDRIVE_3;
    CSCTL4 &= ~(LFXTOFF);

    do
    {
        CSCTL5 &= ~(LFXTOFFG);       // Clear XT1
        SFRIFG1 &= ~OFIFG;
    }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

    CSCTL0_H = 0;                             // Lock CS registers
}


