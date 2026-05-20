/**
 *  @file       Sim.c
 *  @brief
 *
 *  $Header: $
 *
 *  @copyright  Copyright 2016-$Date: $. Whirlpool Corporation. All rights reserved - CONFIDENTIAL
 */
//-------------------------------------- Include Files ----------------------------------------------------------------

#include "Sim_prv.h"
#include "Sim.h"
#include "Sim_api.h"




// I/O Buffer declaration for MUTs simulation

// Buffers for Simulink simulation
float Sim_Loop_Input[SIM_LOOP_NUMBER_OF_INPUTS];
float Sim_Loop_Output[SIM_LOOP_NUMBER_OF_OUTPUTS];

// Arrays of pointers to I/O simulation buffer
void * Sim_Input_Array[NUMBER_OF_MUTS];
void * Sim_Output_Array[NUMBER_OF_MUTS];

// Arrays of length of I/O simulation buffer

const unsigned int SIM_INPUT_LEN_ARRAY[] = {
		SIM_LOOP_NUMBER_OF_INPUTS * 4,
		//SIM_MCI_NUMBER_OF_INPUTS * 4,
		SIM_FORCE_RESET_IO * 4,

};

const unsigned int SIM_OUTPUT_LEN_ARRAY[] = {
		SIM_LOOP_NUMBER_OF_OUTPUTS * 4,
		//SIM_MCI_NUMBER_OF_OUTPUTS * 4,
		SIM_FORCE_RESET_IO *4,
};


//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------

static volatile uint16 sim_index;



//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------

void MutSimulinkSilSrMciInit(void);
void MutSimulinkSil(void *input, void *output, void *dbg);


//! Register MUT Functions///////////////////////////////
 MUT_FUNC_TYPE MUT_functions[] =
 {
     MutSimulinkSil,

 };
////////////////////////////////////////////////////////
MUT_INIT_TYPE MUT_init_functions[] =
{
    MutSimulinkSilSrMciInit,

};

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================


void Sim__Initialize()
{

    SimMain__Initialize();
    /* put here the calls to MUT init functions */
	(*MUT_init_functions[SIM_LOOP_INDEX])();
	
}

/////////////////////////////////////////////
void Sim__Execute(uint16 index)
{
         (*MUT_functions[index])(Sim_Input_Array[index], Sim_Output_Array[index], NULL);
 }
/////////////////////////////////////////////////


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
void MutSimulinkSilSrMciInit()
{
	uint32 i = 0;

	// I/O Buffers initialization
	for(i = 0; i < SIM_LOOP_NUMBER_OF_INPUTS; i++)
	{
		Sim_Loop_Input[i] = 0.0f;
	}

	for(i = 0; i < SIM_LOOP_NUMBER_OF_OUTPUTS; i++)
	{
		Sim_Loop_Output[i] = 0.0f;
	}

	// Init buffer pointers
	Sim_Input_Array[SIM_LOOP_INDEX] 	= &Sim_Loop_Input;
	Sim_Output_Array[SIM_LOOP_INDEX] 	= &Sim_Loop_Output;


}

void MutSimulinkSil(void *input, void *output, void *dbg)
 {

         SimMain__ControlHandlers();
 }





