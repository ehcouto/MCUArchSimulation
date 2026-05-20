/**
 *    @file
 *    @brief    This module implements standard TimerInterrupt API(Application Programming
 *              Interface) for Renesas Rx66T family
 *    @details  The TimerInterrupt module for Renesas Rx66T gives the Timer interrupt service
 *              to the application, basically it’s initialized and after that every defined
 *              interval an interruption is generated which execute some methods from the
 *              Application.
 *              This feature uses the CMT0 peripheral ().
 *              Normal and long intervals are configured in TimerInterrupt_prm.h
 *
 *  @copyright  Copyright 2016. Whirlpool Corporation. All rights reserved - CONFIDENTIAL
*/

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "C_Extensions.h"
#include "Compiler_defs.h"
#include "TimerInterrupt.h"
#include "SRMicro.h"

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
static BOOL_TYPE    Is_Long_Interval;
static uint8        Tick_Divider;

#ifndef TIMERINTERRUPT_SYSTEM_TICK_INTERVAL
    //old drivers
    #define TIMERINTERRUPT_SYSTEM_TICK_INTERVAL INTERRUPT_INTERVAL
#endif


void TimerInterrupt__Initialize(void)
{
    Is_Long_Interval = FALSE;                                       // this is NOT a LONG interval
    Tick_Divider = 1000/TIMERINTERRUPT_SYSTEM_TICK_INTERVAL;
}


//=====================================================================================================================
/**
 *    @brief    It returns next timer slot (if TIMERINTERRUPT_SYSTEM_TICK_INTERVAL is less than 1000)
 *    @return   Next time slot to run
 *
 */
uint8 TimerInterrupt__GetNextSlot(void)
{
    uint8 next_slot = 0;

    #if(TIMERINTERRUPT_SYSTEM_TICK_INTERVAL < 1000)
        if(Is_Long_Interval == FALSE)
        {
            next_slot = Tick_Divider+1;
            if(next_slot >= (1000/TIMERINTERRUPT_SYSTEM_TICK_INTERVAL))
            {
                next_slot = 0;
            }
            Tick_Divider = next_slot;
        }
    #endif
    return(next_slot);
}

void TimerInterrupt__SetLongInterval(void)
{
    // Execute if Micro is using Low Speed clock
    if((Micro__GetWarmResetAction() & MICRO_WARM_RESET_ACTION_ENTER_LOWPOWER) != 0)
    {
        Is_Long_Interval = TRUE;
        Tick_Divider = 0;
    }
}

//=====================================================================================================================
/**
 *    @brief    It returns if Long Interval is set
 *    @return   TRUE if Long Interval is set, FALSE otherwise
 *
 */
BOOL_TYPE TimerInterrupt__IsLongInterval(void)
{
    return(Is_Long_Interval);
}
