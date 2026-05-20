/**
 *  @file       SRMCAtod_macros.h
 *  @brief      Motor control conversion macros
 *
 *---------------------------------------------------------------------------------------------------------------------
 *------------------- Copyright 2012.  Whirlpool Corporation.  All rights reserved - CONFIDENTIAL ---------------------
 *---------------------------------------------------------------------------------------------------------------------
 */
#ifndef SRMCATOD_MACROS_H_
#define SRMCATOD_MACROS_H_
#include "Sim.h"
//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================
/**
 * There are definitions for data registers referred to according analog port
 */

#ifndef SIMULATION_INJFAIL_H_
#define SIM__SRMCATOD_INITIALIZE
#define SIM__GET_ADC_DIAGNOSTIC_FEEDBACK        SR_MCATOD_ERROR_PERIPHERAL_SAFE
#endif


#define SRMCATOD__ADC0_RA()							SIM__ADC0_RA //Sim.ADC_sat.IsABCRaw.C
#define SRMCATOD__ADC0_RB()     					SIM__ADC0_RB //Sim.ADC_sat.VdcRaw
#define SRMCATOD__ADC1_RA()     					SIM__ADC1_RA //Sim.ADC_sat.IsABCRaw.A
#define SRMCATOD__ADC1_RB()                     	SIM__ADC1_RB //Sim.ADC_sat.IsABCRaw.B

#define SRMCATOD__GET_DIAGNOSTIC_FEEDBACK           SIM__GET_ADC_DIAGNOSTIC_FEEDBACK
#define SRMCATOD__INITIALIZE                        SIM__SRMCATOD_INITIALIZE


// defines for Renesas RX24T micro
#define SRMCATOD_AN_100_REG                         SIM_AN_100_REG
#define SRMCATOD_AN_101_REG                         SIM_AN_101_REG
#define SRMCATOD_AN_102_REG                         SIM_AN_102_REG
#define SRMCATOD_AN_103_REG                         SIM_AN_103_REG
#if 0
#define SRMCATOD__SET_DELAY_1ST_CONV_CH0(value)     {PDB0.CH0DLY0 = value; PDB0.SC |= PDB_SC_LDOK_MASK;}
#define SRMCATOD__SET_DELAY_2ND_CONV_CH0(value)     {PDB0.CH0DLY1 = value; PDB0.SC |= PDB_SC_LDOK_MASK;}
#define SRMCATOD__SET_DELAY_1ST_CONV_CH1(value)     {PDB0.CH1DLY0 = value; PDB0.SC |= PDB_SC_LDOK_MASK;}
#define SRMCATOD__SET_DELAY_2ND_CONV_CH1(value)     {PDB0.CH1DLY1 = value; PDB0.SC |= PDB_SC_LDOK_MASK;}

#define SR_MCATOD_MINIMUM_12BITS_AD_VALUE      		0x0000
#define SR_MCATOD_MAXIMUM_12BITS_AD_VALUE      		0x0FFF
#define SR_MCATOD_HALF_RANGE_12BITS_AD_VALUE        0x051E          // 1.05V / 3.3V * 4096 (12bits resolution)
#endif

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

#endif // MCATOD_MACROS_H_
