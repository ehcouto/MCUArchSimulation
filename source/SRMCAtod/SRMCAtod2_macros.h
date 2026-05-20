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

//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================
/**
 * There are definitions for data registers referred to according analog port
 */


#define SRMCATOD2__ADC0_RA()                         SIM__ADC0_RA_2 //Sim.ADC_sat.IsABCRaw.C
#define SRMCATOD2__ADC0_RB()                         SIM__ADC0_RB_2 //Sim.ADC_sat.VdcRaw
#define SRMCATOD2__ADC1_RA()                         SIM__ADC1_RA_2 //Sim.ADC_sat.IsABCRaw.A
#define SRMCATOD2__ADC1_RB()                         SIM__ADC1_RB_2 //Sim.ADC_sat.IsABCRaw.B

#define SRMCATOD2__GET_DIAGNOSTIC_FEEDBACK           SIM__GET_ADC_DIAGNOSTIC_FEEDBACK
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
