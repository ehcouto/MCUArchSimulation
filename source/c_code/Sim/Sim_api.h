/*
 * Sim_api.h
 *
 *  Created on: 19 set 2017
 *      Author: alessio.beato
 */

#ifndef SIM_SIM_API_H_
#define SIM_SIM_API_H_
#include "C_Extensions.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================

// Arrays of pointers to I/O simulation buffer
extern void * Sim_Input_Array[];
extern void * Sim_Output_Array[];
//extern void * Sim_Debug_Array[];

extern const unsigned int SIM_INPUT_LEN_ARRAY[];

extern const unsigned int SIM_OUTPUT_LEN_ARRAY[];


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

extern void Sim__Initialize(void);
extern void Sim__Execute(uint16 index);

#endif /* SIM_API_H_ */
