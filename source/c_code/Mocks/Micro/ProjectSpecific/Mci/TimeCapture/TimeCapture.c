/**
 *  @file
 *  @brief      Capture time between consecutive digital input signal states.
 *
 *  @details    Specific implementation for time measurement between two digital input states. Time measurement
 *              is based on hardware time. Input signal state change is detected by EXTI peripheral of STM32.
 *              Additionally, this module can be configured to trigger interrupt every state change and another
 *              interrupt triggered after specified time between two capture event.
 *
 *  @Module_Owner {Lukasz Ochromowicz}
 *  $Revision: 1.18 $
 *
 *  Copyright 2010 Whirlpool Corporation. All rights reserved - CONFIDENTIAL.
 *
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "TimeCapture.h"

#include "Sim.h"
#include "MciSimConfig.h"

//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
//---------------------------------------------------------------------------------------------------------------------
//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
// Additional variables for SimArch
uint16 TIMER_TRESHOLD; // fire angle treshold
uint16 TIMER_VALUE;    // global timer value
float TIMER_SCALE;    // global timer scale

#define MAX_CMCOR_VALUE       0xFFFF

BOOL_TYPE Interrupt_Status;
//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      It Initializes the module time capture and its variables
 *
 */
void TimeCapture__Initialize(void)
{

}




/**
 *  @brief      MOCKUP - Global Timer handler - every call increases counter value
 *
 */
void TimeCapture__GlobalTimerHandler(void)
{
    TIMER_VALUE += TIMER_SCALE;
}



//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief  Initialize/configure selected timer and channel.
 *
 *  @param  input_number    : Selected channel number - specified time capture channel
 *  @param  event           : Capture time on specified/defined event
 *  @param  frequency       :
 */
void TimeCapture__ChannelConfig(TIME_CAPTURE_INPUT_TYPE input_number,CHANNEL_EVENT_TYPE event, unsigned long frequency)
{

    //CMT1.CMCOR = (uint16)MAX_CMCOR_VALUE;        // set the compare register at max during initialization
    TIMER_TRESHOLD = (uint16)MAX_CMCOR_VALUE;      // set the compare register at max during initialization (MOCKUP)

    //Global Timer Scale
    TIMER_SCALE = GLOBAL_TIMER_SCALE;

    Interrupt_Status = FALSE;
}


//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief  Intialize hardware Timer ISR delayed after capture event.
 *
 */
void TimeCapture__EnableEventInterrupt(TIME_CAPTURE_INPUT_TYPE input_number)
{

}


//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief  Intialize hardware Timer ISR delayed after capture event.
 *
 *  @param  input_number    : Selected channel number - specified time capture channel
 */
void TimeCapture__EnablePostEventInterrupt(TIME_CAPTURE_INPUT_TYPE input_number)
{

}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief  Start/enable time capture for selected timer channel
 *
 *  @param  input_number    : Defines the specific Time capture channel
 */
void TimeCapture__Start(TIME_CAPTURE_INPUT_TYPE input_number)
{

}
//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief Stop time capture for selected timer channel
 *
 *  @param  input_number    : Defines the specific Time capture channel
 */
void TimeCapture__Stop( TIME_CAPTURE_INPUT_TYPE input_number)
{

}
//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief  Last measure event time in time tick
 *
 *  @param  input_number    : Defines the specific Time capture channel
 *
 *  @retval Last capture time in timer tick
 */
unsigned short  TimeCapture__ReadEventTime( TIME_CAPTURE_INPUT_TYPE input_number)
{
    TIMER_VALUE = 0x0000; /* new implementation */
    Interrupt_Status = TRUE;
}
//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief  Get Current timer tick value
 *
 *  @param  input_number    : Defines the specific Time capture channel
 *
 *  @retval Current time value in timer tick
 */
unsigned short  TimeCapture__ReadTimerCnt( TIME_CAPTURE_INPUT_TYPE input_number)
{
    return(TIMER_VALUE); /* new implementation */
}
//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief  Get basic timer tick frequency - value in MHz
 *
 *  @param  input_number    : Defines the specific Time capture channel
 *
 *  @retval Basic timer tick frequency in MHz unit
 */
unsigned long  TimeCapture__GetTimerTickFreq( TIME_CAPTURE_INPUT_TYPE input_number)
{

}
//---------------------------------------------------------------------------------------------------------------------
/**
 * Configure hardware timer interrupt by specyfying time after last capture event
 */
void TimeCapture__SetPostEventInterruptDelay(TIME_CAPTURE_INPUT_TYPE input_number, unsigned long delay_ticks)
{
    TIMER_TRESHOLD = delay_ticks; //Set CMCOR according to the proper information to trigger the triac (MOCKUP)
}
//---------------------------------------------------------------------------------------------------------------------
/**
 * Handler called every capture event
 *
 * It debounces input signal state 5 times and then stores time between previous input state change
 */
void TimeCapture__InterruptHandler(void)
{
    //TIMER_TRESHOLD = (uint16)MAX_CMCOR_VALUE;      // set the compare register at max during initialization (MOCKUP)

	if(Interrupt_Status == TRUE)
	{
		Mci__TriacFireHandler();
	}
    Interrupt_Status = FALSE;
}

//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================


// Function to get fire angle treshold do compare in the main control loop of MCI sfunction
uint16 TimeCapture__GetThresholdValue(void)
{
    return(TIMER_TRESHOLD);
}
