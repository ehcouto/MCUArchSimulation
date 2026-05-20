/* MOCKUP */

/* to read the data from simulation environment and pass directly to Mci__ZeroCrossHandler*/

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "MOCKUP_MciZeroCross.h"
#include "Mci.h"
#include "C_Extensions.h"
#include "Compiler_defs.h"
#include "TimeCapture.h" 
#include "Sim.h"
#include "Mci_prm.h"
#include "C_Extensions_prm.h"
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
static BOOL_TYPE Previous_Input = FALSE;
//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

//---------------------------------------------------------------------------------------------------------------------
/**
*  @brief       Process ZC signal - interface between Simulation Environment and MCI Module
*  @details
*               Function is running with MCI sfunction frequency and it's called when ZC event occurs
*
*  @param[in]   ZC signal from Simulation Environment
*  @param[out]  ZC event, ccr_timer to MCI
*  @return
*/
void MOCKUP__MciZeroCross__ProcessSignal(void)
{
    static uint16 ccr_timer;
    static BOOL_TYPE input;
    static TC_EVENT_TYPE tc_event;
    
    tc_event = TC_UNKNOWN_EVENT;
    
    //get the ZC signal from simulation environment
    input = Sim_Loop_Input[SIM_LOOP_IN_VZC];
    
    tc_event = input;
    
    //check the input status
    if(input != Previous_Input)
    {   
        if(input == FALSE)
        {
            tc_event = TC_FALLING_EDGE_EVENT;
        }
        else
        {
            tc_event = TC_RISING_EDGE_EVENT;
        }

        ccr_timer = TimeCapture__ReadTimerCnt(0);
        //Sim_Loop_Output[SIM_LOOP_OUT_DEBUG1] = ccr_timer; //DEBUG
        //MCI_ZEROCROSSING_EVENT(tc_event,ccr_timer); //#define MCI_ZEROCROSSING_EVENT(event,value)     TimeCapture__ResetTimer(); Mci__ZeroCrossHandler(event,value)
        TimeCapture__ReadEventTime(0);
        Mci__ZeroCrossHandler(tc_event,ccr_timer);
        Previous_Input = input;
    }
    
    /* Global Timer handler*/
    else
    {
        TimeCapture__GlobalTimerHandler(); //increase timer value
    }      
}

