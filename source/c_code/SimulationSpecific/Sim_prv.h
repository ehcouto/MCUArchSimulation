/*
 * Sim_prv.h
 *
 *  Created on: 05 set 2017
 *      Author: lab.motori2
 */

#ifndef SIM_PRV_H_
#define SIM_PRV_H_

// Specific Includes for the MUTs

#include "SimMain.h"
#include "stdlib.h"
#include <string.h>

//! A constant pointer to a MUT function.
typedef void (* const MUT_FUNC_TYPE)(void *input, void *output, void *dbg);
typedef void (* const MUT_INIT_TYPE)(void);



#endif /* SIM_PRV_H_ */
