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
//#define SIM_PWM_MODULUS  6000
#define PWM_OFF_CHANNELS ()

#define SRMCPWM2__LOADALLPWMVALUES(pwm_a, pwm_b, pwm_c)    SRMCPwm2__LoadAllPwmValues(pwm_a, pwm_b, pwm_c)


#define SRMCPWM2__GETMAXPWM()                              (SIM_PWM_MODULUS)
#define SRMCPWM2__GET_DEAD_TIME()
#define SRMCPWM2__GET_LOWERS_ON_PWM()                      (0)

#define SRMCPWM2__LOADPWM_A(value)       				  { ;}
#define SRMCPWM2__LOADPWM_B(value)                         { ;}
#define SRMCPWM2__LOADPWM_C(value)                         { ;}

#define SRMCPWM2__GET_PWM_A()  							    SIM__GET_PWM_A_2
#define SRMCPWM2__GET_PWM_B()                              	SIM__GET_PWM_B_2
#define SRMCPWM2__GET_PWM_C()                              	SIM__GET_PWM_C_2

#define SRMCPWM2__OUT_STATE()

#define SRMCPWM2__GET_HW_FAULT_STATUS                        SIM__GET_PWM_HW_FAULT_STATUS
#define SRMCPWM2__GET_DIAGNOSTIC_FEEDBACK                    SIM__GET_PWM_DIAGNOSTIC_FEEDBACK

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
#endif // SRMCPWM_MACROS_H_


