#include <msp430.h> 
#include "timer.h"
#include "clksystem.h"
#include "scheduler.h"
#include "led.h"
#include "uartInterface.h"
#include "adcInterface.h"
#include "alarmTask.h"  // <--- NEW: Include the Alarm Task Header
#include "buttonInterface.h"

/**
 * main.c
 * Integrated System: Scheduler + ADC + UART + Alarm Logic
 */

tCB taskList[TASK_COUNT];

void main(void)
{
    // --- 1. System Hold & Power ---
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Unlock GPIOs (Vital for FR series)

    // --- 2. GPIO Initialization ---
    // LED 1 (Red) - P1.0 (Heartbeat)
    P1DIR |= BIT0;
    P1SEL0 &= ~BIT0;
    P1SEL1 &= ~BIT0;

    // LED 2 (Green) - P9.7 (Alarm Indicator)
    // Controlled by alarmTask.c
    P9DIR |= BIT7;
    P9SEL0 &= ~BIT7;
    P9SEL1 &= ~BIT7;

    // --- 3. Peripheral Initialization ---
    initClkPort();
    initClkSystem();    // Sets SMCLK to 4MHz

    initUartPorts();    // P3.4 / P3.5
    adcPortInit();      // P8.4 (A7)
    initButton(); // <--- Initialize P1.1

#ifdef DEBUG_SCHEDULER
    timer_init_task_statistics();
#endif

    initUartInterface(); // Configures 115200 Baud UART
    adcInit();           // Configures ADC12
    timer_init();        // Configures Scheduler Timer

    // --- 4. Scheduler Task Setup ---

    /* Task 0: Heartbeat LED (Red)
     * Period: 3 ticks. Just to show the CPU is alive. */
    taskList[0] = initTask(led_toggle_led1, 3, 2, true);

    /* Task 1: Alarm Logic (Green LED Control)
     * Period: 2 ticks. Checks if ADC > 2000.
     * Replaces the old "toggle" task with real logic. */
    taskList[1] = initTask(taskAlarmLogic, 2, 0, true);

    /* Task 2: UART Transmission
     * Period: 5 ticks. Sends "ADC: value [ALARM]" to PC. */
    taskList[2] = initTask(taskUart, 5, 0, true);

    /* Task 3: ADC Sampling
     * Period: 7 ticks. Reads sensor and updates g_adcResult. */
    taskList[3] = initTask(adcTask, 7, 2, true);
    // Add Button Task (Run frequently, e.g., every 1 tick for responsiveness)
    taskList[4] = initTask(taskButton, 1, 0, true);


    // --- 5. Start Execution ---
    __bis_SR_register(GIE);           // Enable Global Interrupts

    timer_start(); // Start Scheduler Timer
    adcStart();    // Start first ADC conversion

    while(1){
        __no_operation(); // Idle loop, work is done in ISRs
    }
}
