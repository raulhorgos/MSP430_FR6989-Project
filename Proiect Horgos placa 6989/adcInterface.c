/*
 * adcInterface.c
 *
 * Created on: 10 Dec 2025
 * Author: Raul Horgos
 */

#include "adcInterface.h"

/* Define the global variable here */
volatile int16_t g_adcResult = 0;

// Port Init ADC
void adcPortInit(){
    P8SEL1 |= BIT4;                    // Enable A/D channel A0 (Check if P8.4 is A7 on your datasheet)
    P8SEL0 |= BIT4;
}

// ADC Init
// Configure ADC12
void adcInit(){
    ADC12CTL0 = ADC12ON | ADC12SHT0_2;        // Turn on ADC12, set sampling time
    ADC12CTL1 = ADC12SHP | ADC12SSEL1_L;      // Use sampling timer
    ADC12MCTL0 |= ADC12INCH_7;                // Input Channel 7 (Matches P8.4 usually)
    ADC12CTL0 |= ADC12ENC;                    // Enable conversions
}

// Start ADC
void adcStart(){
    ADC12CTL0 |= ADC12SC;
}

// Task ADC
void adcTask(){
    // Check if conversion is finished (Interrupt Flag BIT0 set)
    if ((ADC12IFGR0 & BIT0) == 1)
    {
        // Store result in GLOBAL variable so you can see it in Expressions View
        g_adcResult = ADC12MEM0;

        // Start the next conversion
        adcStart();
    }
}
