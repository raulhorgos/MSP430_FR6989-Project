/*
 * led.h
 *
 *  Created on: Nov 12, 2025
 *      Author: cosmi
 */

#ifndef LED_H_
#define LED_H_

#include <msp430.h>
#include <stdint.h>

void led_toggle_led1();
void led_toggle_led2();
void led2_control(uint8_t state); // 1 = ON, 0 = OFF
#endif /* LED_H_ */
