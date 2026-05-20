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
    SIM_LOOP_IN_CURRENT = 0,
    SIM_LOOP_IN_VOLTAGE,
    SIM_LOOP_IN_HALL,
    SIM_LOOP_IN_VZC,
    SIM_LOOP_NUMBER_OF_INPUTS,
} SIM_LOOP_INPUT;


typedef enum
{
    SIM_LOOP_OUT_TRIG,
	SIM_LOOP_NUMBER_OF_OUTPUTS,
} SIM_LOOP_OUTPUT;






#endif /* SIM_PRM_H_ */
