/**
 *  @defgroup   CLASS_B
 *  @file       SRMain.h
 *  @brief      Public interface to the Main module.
 *
 *  
 *
 *  @copyright  *****  Copyright 2008-2011.  Whirlpool Corporation.  All rights reserved - CONFIDENTIAL  *****
 */
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------


#ifndef SRMAIN_H_INCLUDED
	#define SRMAIN_H_INCLUDED

#include "Micro.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
#ifdef COMPILE_4_SIMULINK
void main_init(void);
#else
void main(void);
#endif
INTERRUPT_DIRECTIVE void SRMain__TimerISR(void);
INTERRUPT_DIRECTIVE void SRMain__FastTimerISR(void);

#ifdef COMPILE_4_SIMULINK
void mainloop();
#endif


#endif                                              // MAIN_H_INCLUDED
