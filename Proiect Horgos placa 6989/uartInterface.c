/*
 * uartInterface.c
 *
 * Created on: Dec 3, 2025
 * Modified: Jan 20, 2026
 * Description: UART Driver that prints ADC values and Alarm Status
 */

#include "uartInterface.h"
#include "stdint.h"
#include "adcInterface.h" // Needed to see 'g_adcResult'

// Buffer to hold the text string we want to send
char txBuffer[60]; // Increased size to fit the Alarm message

// Define the same threshold used in your alarmTask
#define ALARM_THRESHOLD 2000

void initUartPorts()
{
    P3SEL1 &= ~(BIT4 | BIT5 );
    P3SEL0 |= (BIT4 | BIT5 );
}

void initUartInterface()
{
    UCA1CTLW0 |= UCSWRST; /* UART in RESET state */
    UCA1CTLW0 |= UCSSEL__SMCLK; /* BRCLK <- SMCLK */

    /* SMCLK = 4000000 (4MHz)
     * Baud rate: 115200
     */
    UCA1BR0 = 0x02;
    UCA1BR1 = 0x00;
    UCA1MCTLW = 0xBB00 | UCOS16 | UCBRF_2;
    UCA1IFG &= ~UCRXIFG;

    UCA1CTLW0 &= ~UCSWRST; /* UART is active */
}

/* Helper function to send a string of characters */
void sendString(char *str)
{
    while(*str) // Loop until we hit the null terminator \0
    {
        while ((UCA1IFG & UCTXIFG) == 0)
        {
            // Wait until TX buffer is empty
        }
        UCA1TXBUF = *str; // Send the current character
        str++;            // Move to the next character
    }
}

void taskUart()
{
    // Check if the global ADC result exceeds the threshold
    if (g_adcResult > ALARM_THRESHOLD)
    {
        // Format string WITH warning message
        sprintf(txBuffer, "ADC: %d  [*** ALARM ACTIVE ***]\r\n", g_adcResult);
    }
    else
    {
        // Format string normally
        sprintf(txBuffer, "ADC: %d\r\n", g_adcResult);
    }

    // Send the final string to the PC
    sendString(txBuffer);
}
/*Seeing 0x000A here confirms your code reached the end of taskUart and successfully loaded the "New Line" character into the buffer.*/
