/**
 *  @file       SRMCPwm_macros.h
 *  @brief      Basic description of file contents
 *
 *---------------------------------------------------------------------------------------------------------------------
 *------------------- Copyright 2012.  Whirlpool Corporation.  All rights reserved - CONFIDENTIAL ---------------------
 *---------------------------------------------------------------------------------------------------------------------
 */
#ifndef SRMCPWM_MACROS_H_
#define SRMCPWM_MACROS_H_
#include "Sim.h"

//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================
#ifndef SIMULATION_INJFAIL_H_
#define SIM__SRMCPWM_INITIALIZE
#define SIM__GET_PWM_DIAGNOSTIC_FEEDBACK        SR_MCPWM_ERROR_PERIPHERAL_SAFE
#define SIM__GET_PWM_HW_FAULT_STATUS            FALSE
#endif

//#define SIM_PWM_MODULUS  6000
#define PWM_OFF_CHANNELS ()

#define SRMCPWM__LOADALLPWMVALUES(pwm_a, pwm_b, pwm_c)    SRMCPwm__LoadAllPwmValues(pwm_a, pwm_b, pwm_c)


#define SRMCPWM__GETMAXPWM()                              (SIM_PWM_MODULUS)
#define SRMCPWM__GET_DEAD_TIME()                          
#define SRMCPWM__GET_LOWERS_ON_PWM()                      (0)

#define SRMCPWM__LOADPWM_A(value)       				  { ;}
#define SRMCPWM__LOADPWM_B(value)                         { ;}
#define SRMCPWM__LOADPWM_C(value)                         { ;}

#define SRMCPWM__GET_PWM_A()  							    SIM__GET_PWM_A
#define SRMCPWM__GET_PWM_B()                              	SIM__GET_PWM_B
#define SRMCPWM__GET_PWM_C()                              	SIM__GET_PWM_C

#define SRMCPWM__OUT_STATE()							  

#define SRMCPWM__GET_HW_FAULT_STATUS                        SIM__GET_PWM_HW_FAULT_STATUS
#define SRMCPWM__GET_DIAGNOSTIC_FEEDBACK                    SIM__GET_PWM_DIAGNOSTIC_FEEDBACK
#define SRMCPWM__INITIALIZE                                 SIM__SRMCPWM_INITIALIZE

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
#endif // SRMCPWM_MACROS_H_


