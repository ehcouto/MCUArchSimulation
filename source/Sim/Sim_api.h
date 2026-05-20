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
extern void * Sim_Debug_Array[];

extern const unsigned int SIM_INPUT_LEN_ARRAY[];

extern const unsigned int SIM_OUTPUT_LEN_ARRAY[];


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================



void Sim__Initialize(void);
void Sim__Execute(uint16 index);
void Sim__Copy(uint8 index, uint8 *address, BOOL_TYPE to_from);
void Sim__Handler(void);



#endif /* SIM_API_H_ */
