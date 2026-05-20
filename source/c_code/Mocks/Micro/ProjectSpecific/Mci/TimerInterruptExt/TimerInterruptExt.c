/**
 *  @file
 *  @brief      Driver provides interface to setup timer interrupts.
 *
 *  @details
 *
 *  @Module_Owner{Maciej Kobuszewski}
 *  $Revision: 1.6 $
 *
 *  @copyright  Copyright 2011-$Date: 2016/06/24 07:58:02EDT $. Whirlpool Corporation. All rights reserved - CONFIDENTIAL
 */

//  --- Include Files -------------------------------------------------------------------------------------------------

// -- This Module --
#include "C_Extensions.h"
#include "TimerInterruptExt.h"

// -- ANSI/ISO --

// -- Project --

#include "Micro.h"


//  --- Public Variables ----------------------------------------------------------------------------------------------

//  --- Private Properties --------------------------------------------------------------------------------------------

//  --- Private Function Prototypes -----------------------------------------------------------------------------------


//=====================================================================================================================
//  --- Public Functions ----------------------------------------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
/**
 * Function which setups periodic timer interrupt and enables it.
 *
 * @param freq  - interrupt frequency
 */
void TimerInterruptExt__SetupPerInt(unsigned short freq, unsigned char preemption_priority, unsigned char sub_priority)
{

}
//---------------------------------------------------------------------------------------------------------------------
/**
 * This procedure starts periodic interrupt event.
 *
 */
void TimerInterruptExt__StartPerInt(void)
{

}
//---------------------------------------------------------------------------------------------------------------------
/**
 * This procedure stops periodic interrupt event.
 *
 */
void TimerInterruptExt__StopPerInt(void)
{

}
//---------------------------------------------------------------------------------------------------------------------
/**
 * This procedure starts periodic interrupt event.
 *
 */
void TimerInterruptExt__ResetPerInt(void)
{

}
//---------------------------------------------------------------------------------------------------------------------
/**
 * This procedure clear periodic interrupt flag (update event flag).
 *
 * Should be called at begining of timer interrupt.
 *
 */
void TimerInterruptExt__ClearPerIntF(void)
{

}
//---------------------------------------------------------------------------------------------------------------------
/**
 * Function which setups event timer interrupt.
 *
 * @param event   - interrupt frequency
 * @param channel - channel for interrupt generation
 */
void TimerInterruptExt__SetupEventInt(unsigned char channel, unsigned char event)
{

}
//---------------------------------------------------------------------------------------------------------------------
/**
 * This procedure clears event interrupt flag.
 *
 * Should be called at begining of timer.
 */
void TimerInterruptExt__ClearEvtIntF(unsigned char channel)
{
    //For future extension
}
//=====================================================================================================================
//  --- Private Functions ---------------------------------------------------------------------------------------------
//=====================================================================================================================
