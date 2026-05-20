/**
 *  @file       
 *  @brief      Parametrs for SRMain module related to non safety relevant tasks
 *
 *  $Header: Main_prv.h 1.7 2016/01/22 14:08:21CET Maciej  Kobuszewski (KOBUSM) Exp  $
 *
 *  @copyright  *****  Copyright 2008-2011.  Whirlpool Corporation.  All rights reserved - CONFIDENTIAL  *****
 */
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------


#ifndef MAIN_PRV_PRM_H_INCLUDED
#define MAIN_PRV_PRM_H_INCLUDED


//-------------------------------------- Include Files ----------------------------------------------------------------
//! Basic
#include "C_Extensions.h"
#include "Sim.h"
#include "SettingFile.h"

//! MCI Mocks
#include "MOCKUP_MciZeroCross.h"
#include "TimeCapture.h"

//! MCI firmware components
#include "Mci.h"

// -------------- MCI tasks -------------------------
 
/* Initialization */

SIM_TASK_TYPE Sim_Initialization_Tasks[] =
{	 
    Mci__Initialize,
    SIM_NULL_TASK
};
 
/* Triac Fire Interrupt */
 
SIM_TASK_TYPE Interrupt_Triac_Fire_Tasks[] =
  {
    TimeCapture__InterruptHandler,
    SIM_NULL_TASK
  };
 
/* Zero Cross */
SIM_TASK_TYPE Mci_Zero_Cross_Tasks[] =
{
  MOCKUP__MciZeroCross__ProcessSignal,
  NULL_TASK
};
 
/* MCI Running Handler */

SIM_TASK_TYPE Mci_Running_Tasks[] =
{
    Mci__MotorControlHandler,
	NULL_TASK
};

// --------------------------------------------------

#endif                                              // MAIN_PRV_PRM_H_INCLUDED
