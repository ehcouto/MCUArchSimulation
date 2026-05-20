/*
 * Sim_prm.h
 *
 *  Created on: 03 lug 2017
 *      Author: alessio.beato
 */

#ifndef SIM_PRM_H_
#define SIM_PRM_H_

// SIMULINK SIL\PIL begin-------------
// defines indexes associated to MUTs execution
typedef enum
{
	SIM_LOOP_INDEX = 0,
	SIM_MCI_INDEX,
    SIM_FORCE_MICRO_RESET_INDEX,
    NUMBER_OF_MUTS
} MUT_INDEX_TYPE;

#define SIM_FORCE_RESET_IO 0


//// Define the interfaces between the Simulink Environment and the Embedded code
// When adding more inputs, the mux router in the simulink needs to have its
// appended at END of the router


typedef enum
{
	SIM_LOOP_IN_OMEGA_MECH = 0,
	SIM_LOOP_IN_TACHO_CAPT    ,
	SIM_LOOP_IN_I_A           ,
	SIM_LOOP_IN_I_B           ,
	SIM_LOOP_IN_I_C           ,
	SIM_LOOP_IN_VDC           ,
	SIM_LOOP_NUMBER_OF_INPUTS ,
} SIM_LOOP_INPUT;


typedef enum
{
	SIM_LOOP_OUT_DUTY_A       = 0,
	SIM_LOOP_OUT_DUTY_B       ,
	SIM_LOOP_OUT_DUTY_C       ,
	SIM_LOOP_OUT_PWM_STATUS   ,
	SIM_LOOP_NUMBER_OF_OUTPUTS,
} SIM_LOOP_OUTPUT;



typedef enum
{
	SIM_MCI_IN_CMD = 0,
	SIM_MCI_IN_PRM1 	,
	SIM_MCI_IN_PRM2   	,
	SIM_MCI_NUMBER_OF_INPUTS ,
} SIM_MCI_INPUT;


typedef enum
{
	SIM_MCI_OUT_RET1       = 0,
	SIM_MCI_NUMBER_OF_OUTPUTS,
} SIM_MCI_OUTPUT;


typedef enum
{
	MCI_CMD_RUN = 0,
	MCI_CMD_STOP,

} SIM_MCI_CMD_TYPE;


typedef unsigned char input[255];
typedef unsigned char output[255];



// SIMULINK SIL PIL end-------------------------------------------


#define NUMBER_OF_PARAMETERS        1  // the MUT ID


#define SIL_MODE 1
#define PIL_MODE 2

#ifndef SIM_MODE
#define SIM_MODE    PIL_MODE
#endif

#if (SIM_MODE == SIL_MODE)
    #define TICKS       1
    #define CMP_TMR     1
    #define TMR_INTERRUPT_INTERVAL  1
    #include <math.h>
    #include <stdlib.h>
#endif

#if (SIM_MODE == PIL_MODE)
#include "TimerInterrupt_prm.h"

#define SCHEDULER_SIM_PRESCALER 1  // FIXME to be taken from Simulation Environment

// FAST INIT
#define FAST_ADC_INIT
#define SKIP_MOTOR_MOVING_CHECK

// Target board definition
#define SIM_KV31_EVALUATION_BOARD 1
#define SIM_RX62T_EVALUATION_BOARD 0

    #if (SIM_KV31_EVALUATION_BOARD == 1)
        #include "DWT_macros.h"
        #define TICKS   (SYSTICK.VAL)
        #define CMP_TMR (SYSTICK.LOAD)
        #define TMR_INTERRUPT_INTERVAL  (INTERRUPT_INTERVAL)
    #endif

    #if (SIM_RX62T_EVALUATION_BOARD == 1)
        #define TICKS   (CMT0.CMCNT)
        #define CMP_TMR (CMT0.CMCOR)
    #endif
#endif



#if(WINDY_INTERNATION_BOARD)
#define SIM__ADC0_RA Sim_Loop_Input[SIM_LOOP_IN_I_C]
#define SIM__ADC0_RB Sim_Loop_Input[SIM_LOOP_IN_I_B]
#define SIM__ADC1_RA Sim_Loop_Input[SIM_LOOP_IN_I_A]
#define SIM__ADC1_RB Sim_Loop_Input[SIM_LOOP_IN_VDC]
#else
#define SIM__ADC0_RA Sim_Loop_Input[SIM_LOOP_IN_I_C]
#define SIM__ADC0_RB Sim_Loop_Input[SIM_LOOP_IN_VDC]
#define SIM__ADC1_RA Sim_Loop_Input[SIM_LOOP_IN_I_A]
#define SIM__ADC1_RB Sim_Loop_Input[SIM_LOOP_IN_I_B]
#endif

// Renesas project
// ARYA v1  Board
#define SIM_AN_102_REG()   Sim_Loop_Input[SIM_LOOP_IN_I_A]//<! Phase U - on schematic is PHASE_OUT_A
#define SIM_AN_100_REG()   Sim_Loop_Input[SIM_LOOP_IN_I_B]//<! Phase V - on schematic is PHASE_OUT_B
#define SIM_AN_101_REG()   Sim_Loop_Input[SIM_LOOP_IN_I_C]//<! Phase W - on schematic is PHASE_OUT_C
#define SIM_AN_103_REG()   Sim_Loop_Input[SIM_LOOP_IN_VDC]//<! DC Bus  - on schematic is BUS_VOLT


#define SIM_PWM_MODULUS  32768.0f      // put here the expected modulus value calculated as Bus_Clock / Pwm_Freq

#define SIM_DUTY_A	Sim_Loop_Output[SIM_LOOP_OUT_DUTY_A]
#define SIM_DUTY_B  Sim_Loop_Output[SIM_LOOP_OUT_DUTY_B]
#define SIM_DUTY_C  Sim_Loop_Output[SIM_LOOP_OUT_DUTY_C]


#define SIM__GET_PWM_A          (sint32)(SIM_DUTY_A*SIM_PWM_MODULUS)
#define SIM__GET_PWM_B          (sint32)(SIM_DUTY_B*SIM_PWM_MODULUS)
#define SIM__GET_PWM_C          (sint32)(SIM_DUTY_C*SIM_PWM_MODULUS)

#define SIM__SET_PWM_STATUS_ON()    {Sim_Loop_Output[SIM_LOOP_OUT_PWM_STATUS] = 1;}
#define SIM__SET_PWM_STATUS_OFF()   {Sim_Loop_Output[SIM_LOOP_OUT_PWM_STATUS] = 0;}



#define SIM_OMEGA_MECH	Sim_Loop_Input[SIM_LOOP_IN_OMEGA_MECH]
#define SIM__GET_TACHO_TRIG()   (Sim_Loop_Input[SIM_LOOP_IN_TACHO_CAPT])&&(Sim_Loop_Input[SIM_LOOP_IN_OMEGA_MECH]!=0)


#define SIM__GET_ADC_DIAGNOSTIC_FEEDBACK        SR_MCATOD_ERROR_PERIPHERAL_SAFE
#define SIM__GET_PWM_DIAGNOSTIC_FEEDBACK        SR_MCPWM_ERROR_PERIPHERAL_SAFE
#define SIM__GET_PWM_HW_FAULT_STATUS            FALSE

#define SIM_SR_MOTOR_SAFETY_MGR__AVG_FREQUENCY_ABOVE_THREHOLD()
#define SIM_SR_MOTOR_SAFETY_MGR__AVG_FREQUENCY_BELOW_THREHOLD()


#endif /* SIM_PRM_H_ */
