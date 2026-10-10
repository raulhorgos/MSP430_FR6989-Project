#include "alarmTask.h"
#include "adcInterface.h"
#include "buttonInterface.h" // <--- Include this to see the flag

void taskAlarmLogic(void)
{
    // If System is DISARMED, force LED OFF and exit
    if (g_systemArmed == false)
    {
        P9OUT &= ~BIT7;
        return;
    }

    // Otherwise, run normal threshold logic
    if (g_adcResult > 2000)
    {
        P9OUT |= BIT7;
    }
    else
    {
        P9OUT &= ~BIT7;
    }
}
