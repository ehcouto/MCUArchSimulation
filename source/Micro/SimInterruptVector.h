/**
 *  @file       
 *
 *  @brief      Basic description of file contents
 *
 *  @section    Applicable_Documents
 *					List here all the applicable documents if needed. <tr>	
 *
 *  $Header: $
 *
 *  @copyright  Copyright 2022-$Date$. Whirlpool Corporation. All rights reserved - CONFIDENTIAL
 */
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
#ifndef SIMULATION_SOURCE_MOCKS_DRIVER_MICRO_SIMINTERRUPTVECTOR_H_
#define SIMULATION_SOURCE_MOCKS_DRIVER_MICRO_SIMINTERRUPTVECTOR_H_

//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
void SimInterruptVector__SystemTimer(void);
void SimInterruptVector__MCAtodEOC(void);

#endif // SIMULATION_SOURCE_MOCKS_DRIVER_MICRO_SIMINTERRUPTVECTOR_H_


