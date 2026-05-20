/**
 *  @file
 *  @brief      All the possible configurations are defined for Atod module.
 *
 * <pre>
 *               Following table contains the ADC Channel, Port, Pin associated with ADC module for STM32F0x
 *                --------------------------------------
 *               | ATOD Channel   |  Port    |   Pin    |
 *               |----------------|----------|----------|
 *               |    ATOD_CH0    |   PORTA  |    0     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH1    |   PORTA  |    1     |
 *               | ---------------|----------|----------|
 *               |    ATOD_CH2    |   PORTA  |    2     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH3    |   PORTA  |    3     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH4    |   PORTA  |    4     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH5    |   PORTA  |    5     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH6    |   PORTA  |    6     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH7    |   PORTA  |    7     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH8    |   PORTB  |    0     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH9    |   PORTB  |    1     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH10   |   PORTC  |    0     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH11   |   PORTC  |    1     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH12   |   PORTC  |    2     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH13   |   PORTC  |    3     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH14   |   PORTC  |    4     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH15   |   PORTC  |    5     |
 *               |----------------|----------|----------|
 *               |    ATOD_CH16   |  Internal Channel   |
 *               |                | (Temperature Sensor)|
 *               |----------------|----------|----------|
 *               |    ATOD_CH17   |  Internal Channel   |
 *               |                |     (Vrefint)       |
 *               |----------------|----------|----------|
 *               |    ATOD_CH18   |  Monitoring Vbat    |
 *               |                | Power supply (Vbat) |
 *                -------------------------------------- </pre>
 *
 *  $Header: Atod_prm.h 1.1 2015/06/24 15:02:17EDT MANOEL GARBUIO DE SOUZA (SOUZAMG) Exp  $
 *
 *  @copyright  Copyright 2011-$Date: 2015/06/24 15:02:17EDT $. Whirlpool Corporation. All rights reserved - CONFIDENTIAL
 */
//-------------------------------------- Include Files ----------------------------------------------------------------
#ifndef ATOD_PRM_H
    #define ATOD_PRM_H

//=====================================================================================================================
/**
 * @brief  -  If the application is reading the ADC conversion in the fixed resolution provided that all the channels use the
 *              resolution then its recommenced to use the below macro in order to reduce the code.
 *
 *              Comment this macro to use the Dynamic Resolution configuration
 *
 * @param  -    4      for 4 bits resolution
 *              8      for 8 bits resolution
 *              10     for 10 bits resolution
 *              12     for 12 bits resolution
 *              14     for 14 bits resolution
 *              16     for 16 bits resolution
 *
 * @note   - Following are the Examples\n
 *           "#define ATOD_HARDCODED_RESOLUTION           12" //12-bit hard-coded resolution is enabled\n
 *           "#define ATOD_HARDCODED_RESOLUTION           4" //4-bit hard-coded resolution is enabled
 */
//=====================================================================================================================
//#define ATOD_HARDCODED_RESOLUTION           12


//! ADC Channel definition for common diagnostic input
#define COMMON_DIAG_CHANNEL                 ATOD_CH8
//! ADC Channel definition for DC fan diagnostic input
#define DCFAN_DIAG_CHANNEL                  ATOD_CH2
//! ADC Channel definition for LITT
#define LITT_CHANNEL                        ATOD_CH15       // ADC Unsued Channel for M0 Project
//! ADC Channel definition for wash motor current measurement
#define MCI_CURRENT_CHANNEL                 ATOD_CH17
//! ADC Channel definition for Hall sensor input
#define MCI_HALL_CHANNEL                    ATOD_CH2
//! ADC Channel definition for wash motor voltage measurement
#define MCI_VOLTAGE_CHANNEL                 ATOD_CH7
//! ADC Channel definition for NTC1 input
#define NTC_THERMISTOR_CHANNEL              ATOD_CH7
//! ADC Channel definition for NTC2 input
#define NTC2_THERMISTOR_CHANNEL             ATOD_CH13       // ADC Unsued Channel for M0 Project
//! ADC Channel definition for internal on chip temperature measurement
#define ON_CHIP_TEMP_CHANNEL                ATOD_CH16       // ADC Unsued Channel for M0 Project
//! ADC Channel definition for OWI input
#define OWI_CHANNEL                         ATOD_CH3
//! ADC Channel definition for salt level measurement
#define SALT_LOW_CHANNEL                    ATOD_CH6
//! ADC Channel definition for HW Timer
#define HW_TIMER_CHANNEL                    ATOD_CH9
#endif

#define ATOD_ONE_SHOT       0

#include "Atod.h"
#define Atod__Initialize(channel, res)
#define Atod__Start(chl, cfg)
#define Atod__Read(chl)       Atod__Convert(chl,ATOD_RESOLUTION_12BITS);
