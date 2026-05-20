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
#if SIM_MODE == SIL_MODE
    #include "SimInterruptVector.h"
    #include "SRMain.h"
#else
    #include "SimMain.h"
    #define SimInterruptVector__MCAtodEOC()
    #define SimInterruptVector__SystemTimer()
#endif



// I/O Buffer declaration for MUTs simulation

// Buffers for Simulink simulation
float Sim_Loop_Input[SIM_LOOP_NUMBER_OF_INPUTS];
float Sim_Loop_Output[SIM_LOOP_NUMBER_OF_OUTPUTS];

// Buffers for Simulink simulation
int Sim_Mci_Input[SIM_MCI_NUMBER_OF_INPUTS];
int Sim_Mci_Output[SIM_MCI_NUMBER_OF_OUTPUTS];

// Arrays of pointers to I/O simulation buffer
void * Sim_Input_Array[NUMBER_OF_MUTS];
void * Sim_Output_Array[NUMBER_OF_MUTS];

// Arrays of length of I/O simulation buffer

const unsigned int SIM_INPUT_LEN_ARRAY[] = {
		SIM_LOOP_NUMBER_OF_INPUTS * 4,
		SIM_MCI_NUMBER_OF_INPUTS * 4,
		SIM_FORCE_RESET_IO * 4,

};

const unsigned int SIM_OUTPUT_LEN_ARRAY[] = {
		SIM_LOOP_NUMBER_OF_OUTPUTS * 4,
		SIM_MCI_NUMBER_OF_OUTPUTS * 4,
		SIM_FORCE_RESET_IO *4,
};

volatile uint16 dbg_cnt = 0;

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
static uint8 SysIntCntr;
static uint8 McIntCntr;


static float tick_to_ns;
static float tick_to_us;

static volatile uint32 dwt_cycles;
static volatile uint16 sim_index;

#define SIM_POWER_UP_THR 5

#ifndef BASE_RADIAL
#define BASE_RADIAL BASE_ANGLE_RAD
#endif

//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
void MutSimulinkSilInit(void);
void MutSimulinkSil(void *input, void *output, void *dbg);
void MutMciCmdInit(void);
void MutMciCmd(void *input, void *output, void* dbg);

void MutForceMicroReset(void *input, void *output, void *dbg);



//! Register MUT Functions
MUT_FUNC_TYPE MUT_functions[] =
{
    MutSimulinkSil,
	MutMciCmd,
	MutForceMicroReset,
};

MUT_INIT_TYPE MUT_init_functions[] =
{
    MutSimulinkSilInit,
    MutMciCmdInit,
};

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
void Sim__Handler()
{
#if SIM_MODE == PIL_MODE
    SIMPIL__HANDLER();
#endif
}

void Sim__Initialize()
{

    /* put here the calls to MUT init functions */
	(*MUT_init_functions[SIM_LOOP_INDEX])();
	(*MUT_init_functions[SIM_MCI_INDEX])();

}


void Sim__Execute(uint16 index)
{
        (*MUT_functions[index])(Sim_Input_Array[index], Sim_Output_Array[index], NULL);
}

void Sim__Copy(uint8 index, uint8 *address, BOOL_TYPE to_from)
{
	// Simulation loop variables
	if (to_from == 0)
	{
		memcpy((uint8 *)Sim_Input_Array[index], address, SIM_INPUT_LEN_ARRAY[index]);
	}
	else
	{
		memcpy(address, (uint8 *)Sim_Output_Array[index], SIM_OUTPUT_LEN_ARRAY[index]);
	}

}

//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
void MutSimulinkSilInit()
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

	// Reset function does not need buffers
	Sim_Input_Array[SIM_FORCE_MICRO_RESET_INDEX] 	= &Sim_Loop_Input;
	Sim_Output_Array[SIM_FORCE_MICRO_RESET_INDEX] 	= &Sim_Loop_Output;

	McIntCntr = MC_INT_PRSC;
	SysIntCntr = SYS_INT_PRSC;
#if SIM_MODE == SIL_MODE
	main_init();
#endif
#if SIM_MODE == PIL_MODE
	SIMPIL__INITIALIZE();
	SimMain__Initialize();
#endif



}

void MutMciCmdInit()
{
	uint32 i = 0;

	// I/O Buffers initialization
	for(i = 0; i < SIM_MCI_NUMBER_OF_INPUTS; i++)
	{
		Sim_Mci_Input[i] = 0;
	}
	for(i = 0; i < SIM_MCI_NUMBER_OF_OUTPUTS; i++)
	{
		Sim_Mci_Output[i] = 0;
	}

	// Init buffer pointers
	Sim_Input_Array[SIM_MCI_INDEX] 		= &Sim_Mci_Input;
	Sim_Output_Array[SIM_MCI_INDEX] 	= &Sim_Mci_Output;


}

void MutSimulinkSil(void *input, void *output, void *dbg)
{
    static uint16 power_up_cnt = 0;
    float *SimInput;
    float *SimOutput;
    SimInput  = (float*)(input);
    SimOutput = (float*)(output);

    // Board Power up mockup /////
    if (power_up_cnt< SIM_POWER_UP_THR)
    {
        power_up_cnt++;
    }
    else
    {
        power_up_cnt = SIM_POWER_UP_THR;

        if (McIntCntr >= MC_INT_PRSC)
        {
            SimInterruptVector__MCAtodEOC();
            McIntCntr = 0;
        }
        else
        {
            McIntCntr++;
        }

        if (SysIntCntr >= SYS_INT_PRSC)
        {
            // call for the scheduler interrupt
            SimInterruptVector__SystemTimer();
            SysIntCntr = 0;
        }
        else
        {
            SysIntCntr++;
        }
#if SIM_MODE == SIL_MODE
    mainloop();
#endif
#if SIM_MODE == PIL_MODE
    SimMain__PwmHandler();
#endif
    }

}



void MutMciCmd(void *input, void *output, void *dbg)
{
	int *ptr;
	int mci_fbk;

	ptr = (int*) input;

	switch(ptr[SIM_MCI_IN_CMD])
	{
		case MCI_CMD_RUN:
			// Mci__Run
			mci_fbk = Mci__Run(0, ptr[SIM_MCI_IN_PRM1], ptr[SIM_MCI_IN_PRM2]);
			break;

		case MCI_CMD_STOP:
			// Mci__Stop
			mci_fbk = Mci__Stop(0, ptr[SIM_MCI_IN_PRM1]);
			break;

		default:
			break;
	}

	ptr = (int*) output;
	ptr[SIM_MCI_OUT_RET1] = mci_fbk;
}


void MutForceMicroReset(void *input, void *output, void *dbg)
{
#ifndef NO_SIM_RESET
	SRMicro__ForceReset(MICRO_RESET_MODE_COLD);
#endif
}
