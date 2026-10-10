/*
 * led.c
 *
 *  Created on: Nov 12, 2025
 *      Author: cosmi
 */


#include "led.h"

void led_toggle_led1(){

#ifdef DEBUG_SCHEDULER
    static uint8_t index = 0;
    uint16_t i;
    ++index;
#endif

    P1OUT ^= BIT0;

#ifdef DEBUG_SCHEDULER
    if(index % 2){
        for(i = 0; i < 10000; ++i) { __no_operation; }
    }
#endif
}

void led_toggle_led2(){
    P9OUT ^= BIT7;
}
/* Control LED2 directly. state: 1=ON, 0=OFF */
void led2_control(uint8_t state) {
    if (state) {
        P9OUT |= BIT7;  // Set Bit 7 High (LED ON)
    } else {
        P9OUT &= ~BIT7; // Clear Bit 7 Low (LED OFF)
    }
}
