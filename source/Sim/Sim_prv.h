/*
 * Sim_prv.h
 *
 *  Created on: 05 set 2017
 *      Author: lab.motori2
 */

#ifndef SIM_PRV_H_
#define SIM_PRV_H_

// Specific Includes for the MUTs

#include "SRMain.h"
#include "SRMicro.h"
#include "SRMCPwm_prm.h"
#include "TimerInterrupt_prm.h"

#include "stdlib.h"
#include <string.h>

//! A constant pointer to a MUT function.
typedef void (* const MUT_FUNC_TYPE)(void *input, void *output, void *dbg);
typedef void (* const MUT_INIT_TYPE)(void);


// prescaler values
// FS_SIM coming from Matlab
// SR_PWM_FREQUENCY_HZ  from SRMCPwm_prm.h
// TIMERINTERRUPT_SYSTEM_TICK_INTERVAL  from TimerInterrupt_prm (expressed in us)
#ifndef TIMERINTERRUPT_SYSTEM_TICK_INTERVAL
    //old drivers
    #define TIMERINTERRUPT_SYSTEM_TICK_INTERVAL INTERRUPT_INTERVAL
#endif


#define MC_INT_PRSC   ((FS_SIM/SR_PWM_FREQUENCY_HZ)-1)
#define SYS_INT_PRSC  (((FS_SIM*TIMERINTERRUPT_SYSTEM_TICK_INTERVAL)/1000000)-1)


#endif /* SIM_PRV_H_ */
