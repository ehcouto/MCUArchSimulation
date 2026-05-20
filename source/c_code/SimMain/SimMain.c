/* Simulation Scheduler */
//-------------------------------------- Include Files ----------------------------------------------------------------
#include "SimMain.h"


typedef void (* const SIM_TASK_TYPE)(void);

//! A NULL pointer to use as a terminator for function lists.
#define SIM_NULL_TASK ((SIM_TASK_TYPE)0)

#include "SimMain_prv.h"

// MCI firmware components
#include "Mci.h"
#include "Mcl_prv.h"
#include "Mci_prm.h"

//MCI Mocks
#include "Timecapture.h"
#include "MciSimConfig.h"


static uint16 ControlTrig = 0x0000;
static uint16 ControlTrig_Threshold = 0x0000;

//-------------------------------------- PUBLIC (Function) -----------------------------------------------------------

void SimExecuteTasks(SIM_TASK_TYPE * task_list);

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

/* -------------- Initialization ----------------------*/

void SimMain__Initialize(void)
{
    SimExecuteTasks(Sim_Initialization_Tasks);
    
    /* Running Handler Call Rate Configuration */ //NEW IMPLEMENTATION
    
    ControlTrig = RUNNING_HANDLER_COUNTS;
    ControlTrig_Threshold = (RUNNING_HANDLER_COUNTS-1);

}

/* ------------ Control Handlers --------------------- */

void SimMain__ControlHandlers()
{
    /* ------------ Zero Cross ----------------------*/
    SimExecuteTasks(Mci_Zero_Cross_Tasks); 
    
    /* Running Handler *//* configurable call rate */
    if (ControlTrig >= ControlTrig_Threshold)
    {
        SimExecuteTasks(Mci_Running_Tasks);
        ControlTrig = 0x0000;
        
    }
    else
    {
        ControlTrig++;
    }
   
    /* ------------ Triac Fire Interrupt ------------ */
    if (TimeCapture__ReadTimerCnt(0) >= TimeCapture__GetThresholdValue())
    {
      SimExecuteTasks(Interrupt_Triac_Fire_Tasks);
    }
}

//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================


void SimExecuteTasks(SIM_TASK_TYPE * task_list)
{
    while (*task_list != SIM_NULL_TASK)
    {
        (*task_list)();
        task_list++;
    }
}