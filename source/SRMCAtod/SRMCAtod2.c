/**
 *  @file       SRMCAtod.c
 *  @brief      This module treats analog conversions for motor control
 *
 *  @details    Analog conversions are triggered by PDB timer event in order minimize ringing noise.
 *              Trigger for all 3 currents and DC bus voltage occur at the same time
 *
 *---------------------------------------------------------------------------------------------------------------------
 *------------------- Copyright 2012.  Whirlpool Corporation.  All rights reserved - CONFIDENTIAL ---------------------
 *---------------------------------------------------------------------------------------------------------------------
 */

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "Sim.h"

#ifdef DUAL_MOTOR

#include "uc.h"
#include "Compiler_defs.h"
#include "C_Extensions.h"
#include "Micro.h"
#include "SRData.h"
#include "SRMCAtod2.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------
//-------------------------------------- AUTOMATIC TEST VARIABLES -----------------------------------------------------
uint32 Dbg_2_R1_021_A = 0;
uint32 Dbg_2_R1_021_B = 0;
uint32 Dbg_2_R1_021_C = 0;
//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
//-------------------------------------- Safety Relevant Variables ----------------------------------------------------
static SRMCATOD_DIAG_STATE_TYPE SR_State;
static SRMCATOD_DIAG_ERROR_TYPE SR_Fault_Holder;
static signed short int SR_Threshold;

static SRMCATOD_DIAG_STATE_TYPE NSR_State;
static SRMCATOD_DIAG_ERROR_TYPE NSR_Fault_Holder;
static signed short int NSR_Threshold;

//---------------------------------------- Macros -----------------------------------------------------

#if(1)
// CHECK Macro defs
#define SR_MCATOD_CHECK_STATE()                         SRData__CheckByte((unsigned char *)&SR_State, (unsigned char *)&NSR_State)
#define SR_MCATOD_CHECK_FAULT_HOLDER()                  SRData__CheckByte((unsigned char *)&SR_Fault_Holder, (unsigned char *)&NSR_Fault_Holder)
#define SR_MCATOD_CHECK_THRESHOLD()                     SRData__CheckShort((unsigned short int *)&SR_Threshold, (unsigned short int *)&NSR_Threshold)

// UPDATE Macro defs
#define SR_MCATOD_UPDATE_STATE(value)                   SRData__UpdateByte((unsigned char *)&SR_State, (unsigned char *)&NSR_State, (unsigned char)(value))
#define SR_MCATOD_UPDATE_FAULT_HOLDER(value)            SRData__UpdateByte((unsigned char *)&SR_Fault_Holder, (unsigned char *)&NSR_Fault_Holder, (unsigned char)(value))
#define SR_MCATOD_UPDATE_THRESHOLD(value)               SRData__UpdateShort((unsigned short int *)&SR_Threshold, (unsigned short int *)&NSR_Threshold, (unsigned short int)(value))


#else
// CHECK Macro defs
#define SR_MCATOD_CHECK_STATE()                         SRDATA_OK
#define SR_MCATOD_CHECK_FAULT_HOLDER()                  SRDATA_OK
#define SR_MCATOD_CHECK_THRESHOLD()                     SRDATA_OK

// UPDATE Macro defs
#define SR_MCATOD_UPDATE_STATE(value)                   SR_State = (value)
#define SR_MCATOD_UPDATE_FAULT_HOLDER(value)            SR_Fault_Holder = (value)
#define SR_MCATOD_UPDATE_THRESHOLD(value)               SR_Threshold = (value)

#endif
//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static void SRInitializeAD0(void);
static void SRInitializeAD1(void);
static void SRCalibrateAD0(void);
static void SRCalibrateAD1(void);
static void SRInitializePDB0(void);
static void DisableEndOfConversionInteruption(SRMCATOD_CONVERTER_TYPE engine);
static void EnableEndOfConversionInteruption(SRMCATOD_CONVERTER_TYPE engine);
static void SREnableSelfDiagMode(SRMCATOD_CONVERTER_TYPE engine, SRMCATOD_DIAG_CONFIG_TYPE mode);
static SRMCATOD_DIAG_ERROR_TYPE IsConverterSafe(SRMCATOD_CONVERTER_TYPE engine,signed short int thresold, SRMCATOD_DIAG_CONFIG_TYPE mode);

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      It Initializes the module MCAtod peripheral and its variables
 *
 *
 *  @param      none
 *  @return     none
 */
void SRMCAtod2__Initialize(void)
{
	;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      End of engine 0 conversion.
 *
 *  This is supposed to be simultaneous to the end of engine 1, since they are triggered together.
 *
 *  @param      none
 *  @return     none
 */
INTERRUPT_DIRECTIVE void SRMCAtod2__ISR(void)
{
	;
}
//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      PDB interrupt service routine
 *
 *
 *  @param      none
 *  @return     none
 */
INTERRUPT_DIRECTIVE void SRMCPDB2__ISR(void)
{
	;	
}
//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      ADC Diagnostic handler
 *
 *  This function is a handler used to check 12 bits AD registers and converters status.
 *  May be used to test stuck at register failure and conversion errors. Checks all converters with all possible fixed values.
 *  this handler has no time dependency, may be used on handlers at 16KHz, 250us, 1ms 5ms or 25ms.
 *  Use functions to start tests and get feedbacks
 *
 *  @param      none
 *  @return     none
 */
void SRMCAtod2__DiagnosticHandler(void)
{
	;
}
//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Enable AtoD Diagnostic features.
 *
 *  This function is a handler used to start checking 12 bits AD registers and converters status.
 *  Only restarts if feedback was updated or it's waiting for a check request.
 *
 *  @param      commanded_threshold Threshold used for the correct level detection
 *  @return     none
 */
void SRMCAtod2__EnableDiagnostic(signed short int commanded_threshold)
{
    SR_MCATOD_CHECK_STATE();
    SR_MCATOD_CHECK_THRESHOLD();

	if ((SR_State == SR_MCATOD_WAITING_TO_CHECK)||(SR_State == SR_MCATOD_FEEDBACK_UPDATED))
	{
	    SR_MCATOD_UPDATE_STATE(SR_MCATOD_START_EVAL);						// Gets to next state to get feedbacks from this test
		SR_MCATOD_UPDATE_THRESHOLD(commanded_threshold);
	}												// Defines new threshold for this verification
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Get diagnostic status.
 *
 *  This function gets converters status.
 *
 *  @param      none
 *  @return     returns if all converters tests result: TEST_NOT_PERFORMED, TEST_NOT_INITIALIZED, REGISTER_BIT_STUCK_AT_0,
 *  REGISTER_BIT_STUCK_AT_1, CONVERTER_ERROR or PERIPHERAL_SAFE
 */
SRMCATOD_DIAG_ERROR_TYPE SRMCAtod2__GetDiagnosticFeedback(void)
{
	SRMCATOD_DIAG_ERROR_TYPE current_status;

	current_status = SRMCATOD2__GET_DIAGNOSTIC_FEEDBACK;
	return (current_status);						// Returns status
}

#if (SRMCATOD_ENABLE_ADDITIONAL_READING == 1)
//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Convert a sample value with a manual request.
 *
 *  @details    This function starts a new conversion using a SW trigger and returns when the conversion has finished.
 *
 *  @remark     The engine and channel to use need to be configured in the prm file and / or calling the
 *              SRMCAtod2__ConfigureManualReading function
 *
 *  @remark     Call this function with caution!
 *              This function stops the Motor Control framework until the requested value is converted.
 *              If not called properly, this may cause the application to malfunction or even damage the board!
 *
 */
void SRMCAtod2__ConvertManualSample(void)
{
    ;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Get the last manually converted value.
 *
 *  @remark     Call the SRMCAtod2__ConvertManualSample function first to ensure an updated value
 *
 *  @return     The converted value, in AD Counts.
 */
sint16 SRMCAtod2__GetLastManualSample(void)
{
    sint16 ret = 0;
    return ret;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Configure the manual reading operation
 *
 *  @param      engine      ADC engine to use for the manual reading
 *              channel     The channel number, according to the SRMCATOD_CHANNEL_DEF type
 *              use_mux     MUX select setting for the selected additional channel
 *
 *  @return
 */
void SRMCAtod2__ConfigureManualReading(SRMCATOD_CONVERTER_TYPE engine, SRMCATOD_CHANNEL_DEF channel, BOOL_TYPE use_mux)
{
    ;
}
#endif
//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================

/**
 *  @brief      Initialization of ADC0
 *
 *  This function configures ADC0 to sample 2 channels triggered by PDB0 delay in respect to FTM0 event.
 *
 *  @param      none
 *  @return     none
 */
static void SRInitializeAD0(void)
{
	;
}
/**
 *  @brief      ADC self calibration procedure start
 *
 *  Recommended on AN3949 to operate with ADC clock between 2MHz and 4MHz, in high speed mode and 32 samples averaged.
 *  Calibration should be run with both VDDA and VREFH at or above 3V.
 *  The input channel, conversion mode setting, compare function values, resolution, and differential and single-ended
 *  settings have no effect on the calibration result.
 *  Software trigger selected: ADCx_SC2 bit ADTRG must be cleared before calibration.
 *  Disable interruptions during calibration.
 *  Calibration must be performed at least every reset.
 *  For single ended calibrations, minus side gain register can be skipped.
 *  Calibration may take as long as 15,000 ADCK cycles + 100 bus cycles
 *
 *  @param      none
 *  @return     none
 */
static void SRCalibrateAD0(void)
{
	;
}
/**
 *  @brief      Initialization of ADC1
 *
 *  This function configures ADC1 to sample 2 channels triggered by PDB0 delay in respect to FTM0 event.
 *
 *  @param      none
 *  @return     none
 */
static void SRInitializeAD1(void)
{
	;
}
/**
 *  @brief      ADC self calibration procedure start
 *
 *  Recommended on AN3949 to operate with ADC clock between 2MHz and 4MHz, in high speed mode and 32 samples averaged.
 *  Calibration should be run with both VDDA and VREFH at or above 3V.
 *  The input channel, conversion mode setting, compare function values, resolution, and differential and single-ended
 *  settings have no effect on the calibration result.
 *  Software trigger selected: ADCx_SC2 bit ADTRG must be cleared before calibration.
 *  Disable interruptions during calibration.
 *  Calibration must be performed at least every reset.
 *  For single ended calibrations, minus side gain register can be skipped.
 *  Calibration may take as long as 15,000 ADCK cycles + 100 bus cycles
 *
 *  @param      none
 *  @return     none
 */
static void SRCalibrateAD1(void)
{
	;
}

/**
 *  @brief      PDB0 peripheral initialization
 *
 *  @param      none
 *  @return     none
 */
static void SRInitializePDB0(void)
{
	;
}

/**
 *  @brief      This function enables conversion interruption for selected engine.
 *
 *  @param      engine selected may be AD_ENGINE_0 or AD_ENGINE_1
 *  @return     none
 */
static void EnableEndOfConversionInteruption(SRMCATOD_CONVERTER_TYPE engine)
{
	;
}

/**
 *  @brief      This function disables conversion interruption for selected engine.
 *
 *  @param      engine selected may be AD_ENGINE_0 or AD_ENGINE_1
 *  @return     none
 */
static void DisableEndOfConversionInteruption(SRMCATOD_CONVERTER_TYPE engine)
{
	;
}


/**
 *  @brief      Enable self diagnostic mode
 *
 *  This function is used to enable/disable self check hardware for converter and register integrity.
 *  Drives to VREFH0, (VREFH0 x 1/2) and (VREFH0 x 0)
 *
 *  @param engine defines which converter will be configured: AD_ENGINE_0 or AD_ENGINE_1
 *  @param mode defines configuration mode:
 *  SELF_TEST_DISABLED,SELF_TEST_VREFH0_SCALE_0,SELF_TEST_VREFH0_SCALE_0_5,SELF_TEST_VREFH0_SCALE_1, AUTOMATED_SELF_TEST
 *  @return     none
 */
static void SREnableSelfDiagMode(SRMCATOD_CONVERTER_TYPE engine, SRMCATOD_DIAG_CONFIG_TYPE mode)
{
	;
}
/**
 * This function is used to check register and converter status.
 * May be used to test stuck at register failure and conversion errors.
 * @param engine defines which engine will be tested
 * @param threshold allows adjustable error for 1/2 VREFH0 conversion
 * @param mode The test mode that we need to check:
 * SELF_TEST_DISABLED,SELF_TEST_VREFH0_SCALE_0,SELF_TEST_VREFH0_SCALE_0_5,SELF_TEST_VREFH0_SCALE_1, AUTOMATED_SELF_TEST
 * @return returns if peripheral test result TEST_NOT_PERFORMED, REGISTER_BIT_STUCK_AT_0,
 * REGISTER_BIT_STUCK_AT_1, CONVERTER_ERROR or PERIPHERAL_SAFE
 */
/**
 *  @brief      Detect if the peripheral is in safe status
 *
 *  This function is used to check register and converter status.
 *  May be used to test stuck at register failure and conversion errors.
 *
 *  @param engine defines which engine will be tested
 *  @param threshold allows adjustable error for 1/2 VREFH0 conversion
 *  @param mode The test mode that we need to check:
 *  SELF_TEST_DISABLED,SELF_TEST_VREFH0_SCALE_0,SELF_TEST_VREFH0_SCALE_0_5,SELF_TEST_VREFH0_SCALE_1, AUTOMATED_SELF_TEST
 *  @return returns if peripheral test result TEST_NOT_PERFORMED, REGISTER_BIT_STUCK_AT_0,
 *  REGISTER_BIT_STUCK_AT_1, CONVERTER_ERROR or PERIPHERAL_SAFE
 */
static SRMCATOD_DIAG_ERROR_TYPE IsConverterSafe(SRMCATOD_CONVERTER_TYPE engine,signed short int local_threshold, SRMCATOD_DIAG_CONFIG_TYPE mode)
{
    SRMCATOD_DIAG_ERROR_TYPE status;                // returns test result

	status = SR_MCATOD_ERROR_PERIPHERAL_SAFE;
	

    return (status);                                // Returns status
}
#endif