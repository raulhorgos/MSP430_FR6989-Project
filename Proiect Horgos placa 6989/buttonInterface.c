/*
 * buttonInterface.c
 *
 * Created on: Jan 20, 2026
 * Description: Reads Button S1 (P1.1) to toggle System State
 */

#include "buttonInterface.h"

// Initialize the system as ARMED by default
volatile bool g_systemArmed = true;

void initButton(void)
{
    // Configure P1.1 (Button S1)
    P1DIR &= ~BIT1; // Set as Input
    P1REN |= BIT1;  // Enable Internal Resistor
    P1OUT |= BIT1;  // Select Pull-Up (High)

    // Note: P1.1 reads '1' when open, '0' when pressed.
}

void taskButton(void)
{
    static bool buttonWasPressed = false;

    // Check if P1.1 is Low (Pressed)
    if ((P1IN & BIT1) == 0)
    {
        // 2. CHECK THE LOCK: Have we already handled this press?
        if (buttonWasPressed == false)
        {
            // Edge Detected: Button just went down  --- THIS RUNS EXACTLY ONCE ---
            g_systemArmed = !g_systemArmed; // Toggle State
            buttonWasPressed = true;        // Remember it's down
            // 3. LOCK IT: Prevent this block from running again while held
        }
    }
    else
    {
        // Button is High (Released) 4. RESET: Button is released, so we unlock it for the next press
        buttonWasPressed = false;
    }
}
