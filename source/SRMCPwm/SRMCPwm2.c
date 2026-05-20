/*e*
 *  @file       SRMCPwm2.c
 *  @brief      Motor Control PWM driver
 *
 *  @details    Motor control PWM initializer, control functions, and ISR
 *
 *---------------------------------------------------------------------------------------------------------------------
 *------------------- Copyright 2012.  Whirlpool Corporation.  All rights reserved - CONFIDENTIAL ---------------------
 *---------------------------------------------------------------------------------------------------------------------
*/

//-------------------------------------- Include Files ----------------------------------------------------------------

#include "Sim.h"

#ifdef DUAL_MOTOR
#include "Micro.h"
#include "Gpio.h"
#include "SRData.h"
#include "SRMCPwm2.h"
#include "Comparator.h"

#include "mci_prm.h"



//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------

// Configuration constants
#define MILLION         1000000.0
#define BILLION         1000000000.0

typedef enum
{
    PWM_MOTOR_DRIVER_IDLE,
    PWM_MOTOR_DRIVER_STARTED,
    PWM_MOTOR_DRIVER_DEVICES_OFF,
    PWM_MOTOR_DRIVER_ACTIVE,
    PWM_MOTOR_DRIVER_LOWERS_ON,
    PWM_MOTOR_DRIVER_UPPERS_ON
} PWM_DRIVE_STATE_TYPE;

static unsigned short int MaxPwm;
static unsigned short int PwmFrequency;
static unsigned short int DeadTimeNanosec;


//-------------------------------------- Safety Relevant Variables ------------------------------------------------

static SRMCPWM_DIAG_STATE_TYPE SR_MCPwm_Diag_State;
static unsigned long SR_MCPwm_Zero_Timeout;
static unsigned long SR_MCPwm_One_Timeout;
static SRMCPWM_DIAG_ERROR_TYPE SR_MCPwm_Errors;
static unsigned short int SR_MCPwm_Max_Pulse_Duration;
static unsigned long int SR_MCPwm_Tmp_Pulse_Duration;
static unsigned long int SR_MCPwm_Pulse_Active_Level;
static unsigned long int SR_MCPwm_Pulse_Default_Level;


static SRMCPWM_DIAG_STATE_TYPE NSR_MCPwm_Diag_State;
static unsigned long NSR_MCPwm_Zero_Timeout;
static unsigned long NSR_MCPwm_One_Timeout;
static SRMCPWM_DIAG_ERROR_TYPE NSR_MCPwm_Errors;
static unsigned long int NSR_MCPwm_Max_Pulse_Duration;
static unsigned long int NSR_MCPwm_Tmp_Pulse_Duration;
static unsigned long int NSR_MCPwm_Pulse_Active_Level;
static unsigned long int NSR_MCPwm_Pulse_Default_Level;


//-------------------------------------- Definitions ------------------------------------------------


#define PWM_OUTPUT_OFF()            SIM__SET_PWM_STATUS_OFF_2()
#define PWM_OUTPUT_ON()             SIM__SET_PWM_STATUS_ON_2()
#define PWM_TIMER_START()			{;} //Not functional
#define PWM_TIMER_STOP()			{;} //Not functional

//---------------------------------------- Macros -----------------------------------------------------

#if(1)
// CHECK Macro defs
#define SR_MCPWM_CHECK_DIAG_STATE()                         SRData__CheckByte((unsigned char *)&SR_MCPwm_Diag_State, (unsigned char *)&NSR_MCPwm_Diag_State)
#define SR_MCPWM_CHECK_ZERO_TIMEOUT()                       SRData__CheckLong((unsigned long *)&SR_MCPwm_Zero_Timeout, (unsigned long *)&NSR_MCPwm_Zero_Timeout)
#define SR_MCPWM_CHECK_ONE_TIMEOUT()                        SRData__CheckLong((unsigned long *)&SR_MCPwm_One_Timeout, (unsigned long *)&NSR_MCPwm_One_Timeout)
#define SR_MCPWM_CHECK_ERRORS()                             SRData__CheckByte((unsigned char *)&SR_MCPwm_Errors, (unsigned char *)&NSR_MCPwm_Errors)
#define SR_MCPWM_CHECK_MAX_PULSE_DURATION()                 SRData__CheckByte((unsigned char *)&SR_MCPwm_Max_Pulse_Duration, (unsigned char *)&NSR_MCPwm_Max_Pulse_Duration)
#define SR_MCPWM_CHECK_TMP_PULSE_DURATION()                 SRData__CheckByte((unsigned char *)&SR_MCPwm_Tmp_Pulse_Duration, (unsigned char *)&NSR_MCPwm_Tmp_Pulse_Duration)
#define SR_MCPWM_CHECK_ACTIVE_PULSE_DURATION()              SRData__CheckByte((unsigned char *)&SR_MCPwm_Pulse_Active_Level, (unsigned char *)&NSR_MCPwm_Pulse_Active_Level)
#define SR_MCPWM_CHECK_DEFAULT_PULSE_DURATION()             SRData__CheckByte((unsigned char *)&SR_MCPwm_Pulse_Default_Level, (unsigned char *)&NSR_MCPwm_Pulse_Default_Level)

// UPDATE Macro defs
#define SR_MCPWM_UPDATE_DIAG_STATE(value)                   SRData__UpdateByte((unsigned char *)&SR_MCPwm_Diag_State, (unsigned char *)&NSR_MCPwm_Diag_State, (unsigned char)(value))
#define SR_MCPWM_UPDATE_ZERO_TIMEOUT(value)                 SRData__UpdateLong((unsigned long *)&SR_MCPwm_Zero_Timeout, (unsigned long *)&NSR_MCPwm_Zero_Timeout, (unsigned long)(value))
#define SR_MCPWM_UPDATE_ONE_TIMEOUT(value)                  SRData__UpdateLong((unsigned long *)&SR_MCPwm_One_Timeout, (unsigned long *)&NSR_MCPwm_One_Timeout, (unsigned long)(value))
#define SR_MCPWM_UPDATE_ERRORS(value)                       SRData__UpdateByte((unsigned char *)&SR_MCPwm_Errors, (unsigned char *)&NSR_MCPwm_Errors, (unsigned char)(value))
#define SR_MCPWM_UPDATE_MAX_PULSE_DURATION(value)           SRData__UpdateByte((unsigned char *)&SR_MCPwm_Max_Pulse_Duration, (unsigned char *)&NSR_MCPwm_Max_Pulse_Duration, (unsigned char)(value))
#define SR_MCPWM_UPDATE_TMP_PULSE_DURATION(value)           SRData__UpdateByte((unsigned char *)&SR_MCPwm_Tmp_Pulse_Duration, (unsigned char *)&NSR_MCPwm_Tmp_Pulse_Duration, (unsigned char)(value))
#define SR_MCPWM_UPDATE_ACTIVE_PULSE_DURATION(value)        SRData__UpdateByte((unsigned char *)&SR_MCPwm_Pulse_Active_Level, (unsigned char *)&NSR_MCPwm_Pulse_Active_Level, (unsigned char)(value))
#define SR_MCPWM_UPDATE_DEFAULT_PULSE_DURATION(value)       SRData__UpdateByte((unsigned char *)&SR_MCPwm_Pulse_Default_Level, (unsigned char *)&NSR_MCPwm_Pulse_Default_Level, (unsigned char)(value))

#else
// CHECK Macro defs
#define SR_MCPWM_CHECK_DIAG_STATE()                         SRDATA_OK // SR_MCPwm_Diag_State
#define SR_MCPWM_CHECK_ZERO_TIMEOUT()                       SRDATA_OK // SR_MCPwm_Zero_Timeout
#define SR_MCPWM_CHECK_ONE_TIMEOUT()                        SRDATA_OK // SR_MCPwm_One_Timeout
#define SR_MCPWM_CHECK_ERRORS()                             SRDATA_OK // SR_MCPwm_Errors
#define SR_MCPWM_CHECK_MAX_PULSE_DURATION()                 SRDATA_OK // SR_MCPwm_Max_Pulse_Duration
#define SR_MCPWM_CHECK_TMP_PULSE_DURATION()                 SRDATA_OK // SR_MCPwm_Tmp_Pulse_Duration
#define SR_MCPWM_CHECK_ACTIVE_PULSE_DURATION()              SRDATA_OK // SR_MCPwm_Pulse_Active_Level
#define SR_MCPWM_CHECK_DEFAULT_PULSE_DURATION()             SRDATA_OK // SR_MCPwm_Pulse_Active_Level

// UPDATE Macro defs
#define SR_MCPWM_UPDATE_DIAG_STATE(value)                   SR_MCPwm_Diag_State = (value)
#define SR_MCPWM_UPDATE_ZERO_TIMEOUT(value)                 SR_MCPwm_Zero_Timeout = (value)
#define SR_MCPWM_UPDATE_ONE_TIMEOUT(value)                  SR_MCPwm_One_Timeout = (value)
#define SR_MCPWM_UPDATE_ERRORS(value)                       SR_MCPwm_Errors = (value)
#define SR_MCPWM_UPDATE_MAX_PULSE_DURATION(value)           SR_MCPwm_Max_Pulse_Duration = (value)
#define SR_MCPWM_UPDATE_TMP_PULSE_DURATION(value)           SR_MCPwm_Tmp_Pulse_Duration = (value)
#define SR_MCPWM_UPDATE_ACTIVE_PULSE_DURATION(value)        SR_MCPwm_Pulse_Active_Level = (value)
#define SR_MCPWM_UPDATE_DEFAULT_PULSE_DURATION(value)       SR_MCPwm_Pulse_Default_Level = (value)

#endif

//-------------------------------------- PRIVATE Function Prototypes ------------------------------------------------
static BOOL_TYPE SRMCPwm2__FaultState(void);
static BOOL_TYPE SRMCPwm2__FaultFlagState(void);
static void SRMCPwm2__ClearFaultFlag(void);
//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

/**
 *  @brief      It Initializes the module MCPwm and its variables.
 *              FTM0 is selected for PWM outputs
 *  @pwm_frequency defines the PWM frequency in Hz.
 *  @dead_time_ns defines the dead time inserted between complementary channels. This is defined in nanoseconds.
 */
void SRMCPwm2__Initialize(unsigned short int pwm_frequency, unsigned short int dead_time_ns)
{
    SR_MCPWM_UPDATE_ZERO_TIMEOUT(0);

    SR_MCPWM_UPDATE_ONE_TIMEOUT(0);

    SR_MCPWM_UPDATE_MAX_PULSE_DURATION(0);
    SR_MCPWM_UPDATE_TMP_PULSE_DURATION(0);

    SR_MCPWM_UPDATE_ACTIVE_PULSE_DURATION(0);
    SR_MCPWM_UPDATE_DEFAULT_PULSE_DURATION(0);

    SR_MCPWM_UPDATE_ERRORS(SR_MCPWM_ERROR_PERIPHERAL_NOT_SAFE);

    SR_MCPWM_UPDATE_DIAG_STATE(SR_MCPWM_WAITING_TO_CHECK);

    PWM_OUTPUT_ON();
}

/**
 * Get the max PWM counts configured in the peripheral.
 * Note that this method uses a shadowed variable, which was set during the initialization of this module.
 * @return Max PWM in timer counts.
 */
unsigned short int SRMCPwm2__GetMaxPwm(void)
{
    return(MaxPwm);
}

/**
 * ISR for the PWM. This is configured to happen at the end of each PWM period.
 */
INTERRUPT_DIRECTIVE void SRMCPwm2__PwmISR(void)
{
	;
}

/**
 * Turn ON ALL LOW GATES. This is related to the driver input and NOT to the PWM output.
 */
void SRMCPwm2__TurnOnLowSideGates(void)
{
	SRMCPWM2__LOADALLPWMVALUES(0, 0, 0);
    PWM_OUTPUT_ON();
}

/**
 * Turn OFF ALL LOW GATES. This is related to the driver input and NOT to the PWM output.
 */
void SRMCPwm2__TurnOffLowSideGates(void)
{
	SRMCPwm2__DisablePwmOutput(SR_MCPWM_GATE_ALL_LO);
}

/**
 * Turn ON ALL HIGH GATES. This is related to the driver input and NOT to the PWM output.
 */
void SRMCPwm2__TurnOnHighSideGates(void)
{
	SRMCPWM2__LOADALLPWMVALUES(SRMCPWM2__GETMAXPWM() , SRMCPWM2__GETMAXPWM() , SRMCPWM2__GETMAXPWM());

	PWM_OUTPUT_ON();
}

/**
 * Turn OFF ALL HIGH GATES. This is related to the driver input and NOT to the PWM output.
 */
void SRMCPwm2__TurnOffHighSideGates(void)
{
	SRMCPwm2__DisablePwmOutput(SR_MCPWM_GATE_ALL_HI);
}


/**
 * This method is created and reconfigure on fly the Gpio output, because
 * the LOCK bits can be used and the OCx/OCxN will not be able to be
 * reconfigured on fly.
 */
void SRMCPwm2__TurnOffAllGates(void)
{
	PWM_OUTPUT_OFF();	
}

/**
 * Load the user pwm duty to the respective registers. All parameters are given in pwm counts.
 * @param pwm_a
 * @param pwm_b
 * @param pwm_c
 */
void SRMCPwm2__LoadAllPwmValues(unsigned short int pwm_a, unsigned short int pwm_b, unsigned short int pwm_c)
{
    SIM_DUTY_A_2 = (float) pwm_a / SIM_PWM_MODULUS;
    SIM_DUTY_B_2 = (float) pwm_b / SIM_PWM_MODULUS;
    SIM_DUTY_C_2 = (float) pwm_c / SIM_PWM_MODULUS;
}

/**
 * Start the PWM timer counter.
 */
void SRMCPwm2__StartCounter(void)
{
	PWM_TIMER_START();
	PWM_OUTPUT_ON();
}

/**
 * Stop the timer counter.
 * This method also turns off the Pwm ISR because the timer will be stopped.
 */
void SRMCPwm2__StopCounter(void)
{
	PWM_OUTPUT_OFF();
	PWM_TIMER_STOP();
}

/**
 * Enable the PWM output according the parameter gate_name. It connects the PWM output
 * to the internal PWM peripheral.
 * @param gate_name selects the gate to be connected.
 */
void SRMCPwm2__EnablePwmOutput(SRMCPWM_GATE_NAME_TYPE gate_name)
{
    switch(gate_name)
    {
        case SR_MCPWM_GATE_A_HI:
        case SR_MCPWM_GATE_B_HI:
        case SR_MCPWM_GATE_C_HI:
        case SR_MCPWM_GATE_ALL_HI:
        case SR_MCPWM_GATE_A_LO:
        case SR_MCPWM_GATE_B_LO:
        case SR_MCPWM_GATE_C_LO:
        case SR_MCPWM_GATE_ALL_LO:
            /* Not Yet Supported in SIM Mode */
            break;
        case SR_MCPWM_GATE_ALL_6GATES:
            PWM_OUTPUT_ON()
            break;
        default:
            break;
    }
}


/**
 * Disables PWM output according the parameter gate_name. It disconnects the PWM output
 * to the internal PWM peripheral.
 * @param gate_name selects the gate to be disconnected.
 */
void SRMCPwm2__DisablePwmOutput(SRMCPWM_GATE_NAME_TYPE gate_name)
{
    switch(gate_name)
    {
        case SR_MCPWM_GATE_A_HI:
        case SR_MCPWM_GATE_B_HI:
        case SR_MCPWM_GATE_C_HI:
        case SR_MCPWM_GATE_ALL_HI:
        case SR_MCPWM_GATE_A_LO:
        case SR_MCPWM_GATE_B_LO:
        case SR_MCPWM_GATE_C_LO:
        case SR_MCPWM_GATE_ALL_LO:
            /* Not Yet Supported in SIM Mode */
            break;
        case SR_MCPWM_GATE_ALL_6GATES:
            PWM_OUTPUT_OFF();
            break;
        default:
            break;
    }

}


/**
 * Get the specified PWM frequency.
 * @return frequency in Hertz, decimal and no fractional number.
 */
unsigned short int SRMCPwm2__GetPwmFrequencyHz(void)
{
	return (PwmFrequency);
}

/**
 * Get the configured dead time in the PWM peripheral.
 * @return dead time in nanoseconds, decimal and no fractional number.
 */
unsigned short int SRMCPwm2__GetDeadtimeNanosec(void)
{
	return (DeadTimeNanosec);
}
/**
 * This function returns over current or over temperature error from driver module
 */
unsigned char SRMCPwm2__GetHwFaultStatus(void)
{
    unsigned char temp = FALSE;                     // Starts with no fault reported

    temp = SRMCPWM2__GET_HW_FAULT_STATUS;

    return(temp);                                   // Returns status
}

/**
 * Checks active level pulse duration in IPM SD pin
 */
void SRMCPwm2__Handler250us(void)
{
    unsigned long temp1;
    unsigned long temp2;

    temp1 = SR_MCPWM_CHECK_DIAG_STATE();            // Checks state data
    temp1 += SR_MCPWM_CHECK_MAX_PULSE_DURATION();   // Checks variable data
    temp1 += SR_MCPWM_CHECK_TMP_PULSE_DURATION();   // Checks variable data

    if(temp1 == SRDATA_OK)                          // If data is not corrupted
    {
        temp1 = SR_MCPwm_Diag_State;

        if( (temp1 == SR_MCPWM_FEEDBACK_UPDATED) ||
        (temp1 == SR_MCPWM_WAITING_TO_CHECK) )      // Checks if it already finished a check or not started
        {

            if ((SRMCPwm2__FaultState() == SR_MCPWM_SHUTDOWN_ACTIVE_POLARITY)||(SRMCPwm2__FaultFlagState() != 0))
            {                                       // Checks SD pin
                temp1 = SR_MCPwm_Tmp_Pulse_Duration;
                temp2 = SR_MCPwm_Max_Pulse_Duration;
                if (temp1 < 65535)
                {
                    ++ temp1;                       // Increments timer if active
                    SR_MCPWM_UPDATE_TMP_PULSE_DURATION(temp1);

                    if(temp1 > temp2)
                    {                               // Updates max pulse duration in real time
                        SR_MCPWM_UPDATE_MAX_PULSE_DURATION(temp1);
                    }
                }
            }
            else
            {
                SR_MCPWM_UPDATE_TMP_PULSE_DURATION(0);      // Clears the counter but keeps max duration captured until it get read
            }
        }
    }
}


/*
 * @brief       Triggers the handler to start, if the handler is available.
 * @parameter   timeout_to_zero: counts the time that the micro will force the signal to zero logic
 *              timeout_to_one: counts the time that the micro will force the signal to one logic
 */
void SRMCPwm2__StartDiagIfAvailable(unsigned long timeout_to_zero, unsigned long timeout_to_one)
{
	
	;

}
 
void SRMCPwm2__EnableDiagnostic(uint32 timeout_to_zero, uint32 timeout_to_one)
{
	
	;

}
/*
 * @brief   Diagnostic handler manipulates the shut down input in order to perform
 *          the plausibility check.
 */
void SRMCPwm2__DiagnosticHandler(void)
{
    unsigned long temp;
    unsigned long temp1;
    unsigned long temp2;

    temp = SR_MCPWM_CHECK_DIAG_STATE();             // Checks state integrity state
    if(temp == SRDATA_OK)                           // Continues check if OK, in case of corruption a reset will be forced
    {
        temp = SR_MCPwm_Diag_State;                 // Saves state into temp

        if(temp == SR_MCPWM_WAITING_TO_CHECK)       // Keeps here waiting for an update, but is always checking state
        {
            temp = 0;     // Read errors
            SR_MCPWM_UPDATE_ERRORS((SRMCPWM_DIAG_ERROR_TYPE)temp);
            SR_MCPWM_UPDATE_DIAG_STATE(SR_MCPWM_FEEDBACK_UPDATED);
        }
        else if(temp == SR_MCPWM_FEEDBACK_UPDATED)
        {
            // Stay here until the feedback is read by the caller.
        }
        else
        {
            // Should never reach this region.
            // Just in case, should force to a safe condition here
        }
    }
}


/*
 * @brief Get the feedback of the plausibility check
 */
SRMCPWM_DIAG_ERROR_TYPE SRMCPwm2__GetDiagFeedback(void)
{
    SRMCPWM_DIAG_ERROR_TYPE status;

    status = SRMCPWM2__GET_DIAGNOSTIC_FEEDBACK;

    return(status);                                 // Returns status
}
 
SRMCPWM_DIAG_ERROR_TYPE SRMCPwm2__GetDiagnosticFeedback(void)
{
    SRMCPWM_DIAG_ERROR_TYPE status;

    status = SRMCPWM2__GET_DIAGNOSTIC_FEEDBACK;

    return(status);                                 // Returns status
}

//=====================================================================================================================
//-------------------------------------- Private Functions -------------------------------------------------------------
//=====================================================================================================================
//

static BOOL_TYPE SRMCPwm2__FaultState(void)
{
	BOOL_TYPE response;
	uint16 temp;


	response = FALSE;

	return (response);
}


static BOOL_TYPE SRMCPwm2__FaultFlagState(void)
{
	BOOL_TYPE response;
	uint16 temp;

	response = FALSE;

	return (response);
}


static void SRMCPwm2__ClearFaultFlag(void)
{
	;
}

#endif
