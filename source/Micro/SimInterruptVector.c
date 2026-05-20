/**
 *  @file     InterruptVector.c
 *  @defgroup   CLASS_B
 *  @brief    This file contains the calling of interruptions functions
 *  @details  Interrupt function are called according to interrupt vector number.These interrupt
 *              function are defined in prm file and can be configured according to application.
 *
 *  @section    Applicable_Documents
 *                  List here all the applicable documents if needed. <tr>
 *
 *  $Header: $
 *
 *  @copyright  Copyright 2015-$Date$. Whirlpool Corporation. All rights reserved - CONFIDENTIAL
 */
//-------------------------------------- Include Files ----------------------------------------------------------------
#include "C_Extensions.h"
#include "SRMain.h"
#include "TimerInterrupt.h"
#include "SimInterruptVector.h"
#include "SRMCAtod.h"


uint8 TimerInterrupt__GetNextSlot(void);

#ifndef INTERRUPT_VECTOR_RTOS  // to be defined from Simulation
    #define INTERRUPT_VECTOR_RTOS   DISABLED
#endif

#if (INTERRUPT_VECTOR_RTOS == ENABLED)
    #include "RTOS.h"
#endif


void SimInterruptVector__SystemTimer(void)
{
    uint32 time_slot = TimerInterrupt__GetNextSlot();
#if (defined TIMERINTERRUPT_SYSTEM_TICK_INTERVAL && defined NUCLEUS_FAST_TIMER_ISR)
    #if(TIMERINTERRUPT_SYSTEM_TICK_INTERVAL< 1000)
        if(TimerInterrupt__IsLongInterval() == FALSE)
        {
            SRMain__FastTimerISR();
        }

    #endif

    if(time_slot == 0)
    {
            SRMain__TimerISR();
        #if (INTERRUPT_VECTOR_RTOS == ENABLED)
            OS_TICK_Handle();
        #endif
    }
#else
    //old drivers
    SRMain__TimerISR();
#endif

}

void SimInterruptVector__MCAtodEOC(void)
{
    SRMCAtod__ISR();
}

