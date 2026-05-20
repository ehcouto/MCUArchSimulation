/**
 *  @file
 *  @defgroup   CLASS_B
 *
 *  @brief      This module implements the standard API (Application Programming Interface) for
 *              Rx66T SRMicro module.
 *
 *  @details    This module provides the interface to the application to configure the controller and to perform the
 *              CLASSB safety relevant controller tests.
 *
 *              Configuring the Controller such as-
 *              Initializing microcontroller bus clock, configuring clock for microcontroller,
 *              Configures the controller to work either in slow, normal or sleep mode of operation,
 *              servicing Window and Independent watchdog,
 *              enabling/disabling or store/restoring of the interrupts,
 *              Providing FLASH size ,RAM size and ID of microcontroller,
 *              provision to detect Low voltage.
 *
 *              CLASS B safety-relevant controller test during boot as well as run time such as -
 *              CPU Register Test,
 *              Watchdog test,
 *              RAM test,
 *              Flash test
 *              stack test
 *
 *  @section    Applicable_Documents
 *                  List here all the applicable documents if needed. <tr>
 *
 *  $Header: $
 *
 *    @copyright  Copyright 2016-$Date$. Whirlpool Corporation. All rights reserved - CONFIDENTIAL
 */
//-------------------------------------- Include Files ----------------------------------------------------------------
#include "C_Extensions.h"
#include "uc.h"
#include "Micro.h"
#include "Crc8.h"
#include "string.h"


//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
 const uint8 MICRO_ID[] = {'P','C','S','I','M'};
 static const MICRO_ID_TYPE MICRO_CPU_IDENTIFICATION = {(uint8 *)MICRO_ID,'5'};
static uint32 Micro_Execute_BootTest;

#define MICRO_RAM_SIZE()     (0xffff)
#define MICRO_FLASH_SIZE()   (0xffff)
#define MICRO_CPU_ID()       ((MICRO_ID_TYPE * )(&MICRO_CPU_IDENTIFICATION))

//---------------------------------------------------------------------------------------------------------------------
/**
 * List all the generic structures, variable, private function prototype
 */


#define MICRO_RESETINFO_STRING_SIZE             44

PACKED typedef struct
{
    uint8 Header[MICRO_RESETINFO_STRING_SIZE];

    //The Reset member shall be always after the Header memeber
    MICRO_LAST_RESET_TYPE Reset;
    MICRO_LAST_RESET_TYPE Actual_Reset;
    MICRO_RESET_MODE_TYPE Mode;
    MICRO_WARM_RESET_ACTION_TYPE Warm_Reset_Actions;
    uint8 Loop_Reset_Count;
    uint8 Warm_Reset_Count;

    //This variable shall always be at the end of the structure
    uint8 Crc8_Data_Integrator;
}MICRO_RESET_INFO_HEADER_TYPE;

//! Holds the Clock status
static MICRO_CLOCK_DEF  Micro_ClocksStatus;

const uint8 MICRO_RESETINFO_HEADER[MICRO_RESETINFO_STRING_SIZE] =      {"Dream is not the thing you see in sleep but"};
const uint8 MICRO_RESETINFO_FOOTER[MICRO_RESETINFO_STRING_SIZE] =      {"it is that thing that doesn't let you sleep"};


static MICRO_RESET_INFO_HEADER_TYPE Micro_ResetInfo;

static uint8 Micro_ResetInfo_Footer[MICRO_RESETINFO_STRING_SIZE];

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method initializes the Micro module
 *    @details  This method is used to initialize clock, Nested Vectored Interrupt (NVIC) and
 *              window watchdog configuration. It should be called prior to any other application method is called
 *              since it initializes micro module.
 *              The SRGpio module must be re-initialized if the Micro__Initialize() is called in the middle
 *              of the Application code.
 */
void Micro__Initialize(void)
{
    ;
}

//DZ
//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    Configure the microcontroller bus clock in low speed mode
 *    @details  Low speed mode is implemented using the HOCO oscillator (as LOCO speed is too low, only 240Khz).
 *    			When using the internal clock this is made by using 16Mhz clock with no usage of PLL.
 *    			This function initializes system bus frequency cpu clock/MICRO_LOWSPEED_SYSTEM_CLOCK_DIVIDER for low speed
 *              in power save mode. This method provides a way to switch from normal to slow mode of operation
 *              with this method system frequency can reduce up to 0.25Mhz.
 *              Flash clock should not go below 4Mhz.
 *              Make sure when this method call then again initialize all peripheral like(UART,PWM,SPI,I2C etc)
 *    @image    html SRMicro_Low_Normal_Speed_Test.jpg
 *    Note - 1. The low speed peripheral clock should not be set less than system clock.
 *           2. Use the Internal clock source during the low speed.
 */

void Micro__SetLowSpeedMode(void)
{
    ;
}

//---------------------------------------------------------------------------------------------------------------------
/**   @brief    This method configured the Low Voltage Detection if the feature is available.
 *    @details  For Voltage monitor1 interrupt occurs on VCC < 3.9v
 *    @image    html SRMicro_LVD.jpg
 *
 */

void Micro__ConfigureLvd(void)
{
    ;
}
//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief This method should be called from the Low Voltage detection interrupt handle which is application specific.
 *        This function only clear the register related to the interruption if need.
 *        This is not the handler for the interrupt, this code should be managed by the Application specific code which knows
 *        what must be done during the LVD ISR.
 */
void Micro__ClearLvdIsrRegisters(void)
{
    ;
}
//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief This method returns the current state of the LVD
 * @return MICRO_LVD_DISABLED_NOT_DETECTING,MICRO_LVD_DISABLED_DETECTING,MICRO_LVD_ENABLED_NOT_DETECTING or  MICRO_LVD_ENABLED_DETECTING
 */
MICRO_LVD_STATUS_TYPE  Micro__GetLvdStatus(void)
 {
	MICRO_LVD_STATUS_TYPE lvdreturn;

	lvdreturn = MICRO_LVD_DISABLED;

	return (lvdreturn);
}

//------------------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This clock is generated by the CAC module periodically
 *    @details  As per the configuration the interrupt is generated every 65.536 milli seconds
 *
 *              Calls the handler when the time reaches to the configured one
 */
#if((MICRO_GENERATE_PERIODIC_INTERRUPT_FROM_INDEPENDENT_CLOCK_EVERY_NUMBER_OF_MILLISECONDS > 0) && (MICRO_SR_FEATURE_TEST == ENABLED))
void Micro__IndependentClockISR(void)
{
    ;
}
#endif

//---------------------------------------------------------------------------------------------------------------------
// Class B Only methods -----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

/**
 * @brief This method overwrites the default __low_level_init and in a class B project it calls the Micro__BootTest
 * @return always 1
 */

//---------------------------------------------------------------------------------------------------------------------
/**
 * List all the generic API's used across different micro
 */

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method performs the Boot test during the system boot.
 *    @details  This method is the first function to be executed in the system and from this function the code
 *              goes to the main function.
 *
 *              This method is responsible for:
 *              CPU Register Boot Test,
 *              Watchdog Boot test,
 *              RAM MarchC test,
 *              Flash Boot test
 *              and writing stack test pattern at the boundaries of stack memory.
 *              After this it calls the system startup routine.
 *
 *
 *              Note-1. The Independent watchdog refresh time should be big enough to perform the boot test
 *                   2. The boot test should not be performed when the application is running.
 */
void Micro__BootTest(void)
{
    ;
}
//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method performs volatile memory (CPU register, Stack) test periodically.
 *    @details  This method is responsible for:
 *              CPU Registers Test,
 *              Stack memory complete test
 *              Stack overflow and underflow test.
 *
 *              MICRO_NUM_BYTE_FOR_RAM_CONTINUOUS_TEST configuration macro defined in the SRMicro_prv.h file
 *              Defines how many bytes will be processed during each interaction of the Continuous stack memory Test.
 *
 *
 *              The time taken for complete stack memory test is calculated below-
 *              FULL RAM TEST (in ms) = (Stack Size/ MICRO_NUM_BYTE_FOR_RAM_CONTINUOUS_TEST) *
 *                                       Call rate(of Micro__RamTest())
 *
 *             For example-
 *              Stack memory  size is 2048bytes,  number of bytes processed in each call are 4 and the call rate is 100ms then,
 *              FULL  Stack memory(in ms) =  (2048/4)*100 ms
 *                                        =  51200 ms
 *
 *              Along with this it provides the flow control log and exception control for each tests.
 *
 *              This API is been called from ApplienceMgr Thread at every 100ms
 */
void Micro__SRRamTest(void)
{
    ;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method performs non-volatile memory (FLASH) test periodically.
 *    @details  This method is responsible for checking the FLASH memory consistency.
 *              Run time Flash Test which calculates CRC couple bytes each time and keeps on continuing until it
 *              reaches the FLASH memory end and compare the calculated CRC against a CRC value stored
 *              in FLASH memory.
 *
 *              INBUILT_FLASH_CRC_CALCULATOR macro defines the CRC calculation engine either Inbuilt or External.
 *
 *              MICRO_NUM_WORD_FOR_FLASH_CONTINUOUS_TEST configuration macro defined in the SRMicro_prv.h file
 *              Defines how many words will be processed each interaction of the Continuous Flash Test.
 *
 *              The time taken for complete FLASH test is calculated below-
 *              For the inbuilt CRC tool(IELF) -
 *              FULL FLASH TEST (in ms) =
 *                 (((FLASH Size in words)-4)/ MICRO_NUM_WORD_FOR_FLASH_CONTINUOUS_TEST) * Call rate(of Micro__FlashTest())
 *
 *              If the external CRC tool(IELF) is used-
 *              FULL FLASH TEST (in ms) =
 *                  (((FLASH Size in bytes)-4)/ MICRO_NUM_WORD_FOR_FLASH_CONTINUOUS_TEST) * Call rate(of Micro__FlashTest())
 *
 *              In the calculation FLASH Size-4 because the last 4- bytes of the flash memory is used to
 *              hold the calculated CRC value on which the Flash test is not performed.
 *
 *
 *              For example
 *              Flash size is 32768 in words,  number of bytes processed in each call are 4 and the call rate is 5ms
 *              then time taken by the inbuilt CRC calculator is-
 *              FULL FLASH TEST (in ms) =  ((32768-4) /4)  * 5 ms
 *                                      = 2047.75ms
 *
 *              Along with this it provides the flow control log and exception control for each tests.
 *              Note- Should be called at every 5ms or 25ms slot.
 */
void Micro__SRFlashTest(void)
{
    ;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method makes the controller to work at Normal speed or resumes the controller from Low Speed mode
 *    @details  This method provides a way to switch from slow to normal mode of operation
 */
void Micro__SetNormalSpeedMode(void)
{
    ;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method puts the micro in WAIT mode
 *    @details  The CPU clock is stopped, reducing the power consumption of the microcontroller.
 *              When an internal or external interrupt request occurs,
 *              the CPU wakes-up from Wait mode and resumes processing
 */
void Micro__GoSleep(void)
{
    ;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief   This method refreshes the watchdog
 * @details This method should be called periodically to refresh the WWDG (window watchdog)
 *          and/or IWDG (Independent watchdog) depending on the configuration.
 *
 *          Can be used to resolve processor malfunctions due to hardware or software failures.
 *          Watchdog should be refreshed at every 5ms
 */
void Micro__ServiceWatchdog(void)
{
    ;
}
//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    It reset the micro when a not handled interruption occurs
 *    @details  This method is used to reset the micro when an interrupt appears which was not handled
 */
void Micro__Trap(void)
{
    ;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method provides information about the clocks
 *    @details  This method provides information about clocks such as
 *              System clock frequency (SYSCLK_Frequency),
 *              AHB Clock frequency (HCLK_Frequency),
 *              APB1 Clock frequency( PCLK1_Frequency),
 *              APB2 Clock frequency( PCLK2_Frequency),
 *              And HSE(High speed External) initialization status.
 *
 *    @return   MICRO_CLOCK_DEF* : pointer to the clock registers structure
 */
MICRO_CLOCK_DEF * Micro__GetClock(void)
{
    return (&Micro_ClocksStatus);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method adds the delay to the execution
 *    @details  Adds the delay by executing the NOP(No Operation)
 *    @param    delay : Defines the number times the NOP opcode is executed
 */
void Micro__DelayNumNops(uint16 delay)
{
    ;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method provides a reason for last system reset.
 *    @details  This method is used to provides information about the source from where reset to system occurs
 *    @return   MICRO_LAST_RESET_TYPE* : pointer to system reset status register structure
 *                                      Reset by Debugger,
 *                                      Reset by Low Voltage Detector (LVD),
 *                                      Reset by Clock failure,
 *                                      Reset by EMC,
 *                                      Reset by illegal opcode execution,
 *                                      Reset by watchdog,
 *                                      Reset by External,
 *                                      And Power on reset.
 */
MICRO_LAST_RESET_TYPE * Micro__GetLastResetstatus(void)
{
    return (&(Micro_ResetInfo.Reset));
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief - This API assert the reset
 *
 * @param reset_mode
 *
 */
void Micro__ForceReset(MICRO_RESET_MODE_TYPE reset_mode)
{
    if (reset_mode == MICRO_RESET_MODE_WARM)
    {
        //warm reset
        SYSTEM_RESET();
    }
    else
    {
        //Cold reset
        //Corrupt the signature
        Micro_ResetInfo.Header[0] = 0;
        Micro_ResetInfo_Footer[0] = 0;

        SYSTEM_RESET();
    }
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief - This API reads the reset mode
 * @return MICRO_RESET_MODE_TYPE:
 *
 */
MICRO_RESET_MODE_TYPE Micro__GetResetMode(void)
{
    return(Micro_ResetInfo.Mode);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief - This API is used to Enable the warm reset action if the next reset is warn reset type
 * @param warm_reset_action
 */
void Micro__EnableWarmResetAction(MICRO_WARM_RESET_ACTION_TYPE warm_reset_action)
{
    ;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief - This API is used to Disable the warm reset action if the next reset is warn reset type
 * @param warm_reset_action
 */
void Micro__DisableWarmResetAction(MICRO_WARM_RESET_ACTION_TYPE warm_reset_action)
{
    ;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief - This API is used to read the warm reset actions set
 * @return MICRO_WARM_RESET_ACTION_TYPE
 */
MICRO_WARM_RESET_ACTION_TYPE Micro__GetWarmResetAction(void)
{
    return(Micro_ResetInfo.Warm_Reset_Actions);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief Returns the Warm Reset Count
 * @details - We keep the count on how many times the Warm reset type occurred in the micro ranging from 0 to 20.
 * 			  After 20th Warm reset type we are forcing the cold reset which does clears the RAM memory
 *
 * @return uint8 : Returns the Current Warm reset counts
 * 	@retval
 */
uint8 Micro__GetWarmResetCount(void)
{
    return(Micro_ResetInfo.Warm_Reset_Count);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief Returns the Loop Reset Count
 * @details - We keep the count on how many times the Loop reset type occurred in the micro after a POR or a CRC check failure.
 *
 * @return uint8 : Returns the Current Loop reset counter
 *  @retval
 */
uint8 Micro__GetLoopResetCount(void)
{
    return(Micro_ResetInfo.Loop_Reset_Count);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief Reset the Loop Reset Count in a valid Micro_ResetInfo structure.
 *
 */
void Micro__ResetLoopResetCount(void)
{
    Micro_ResetInfo.Loop_Reset_Count = 0;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method returns the Flash size of microcontroller
 *    @return   uint16 : Returns the flash size
 */
uint32 Micro__GetFlashSize(void)
{
    return (MICRO_FLASH_SIZE());
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *    @brief    This method returns the RAM size of microcontroller.
 *    @return   uint32 : It returns the ram size.
 */
uint32 Micro__GetRamSize(void)
{
    return (MICRO_RAM_SIZE());
}
//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      This method returns the revision of the microcontrollers core.
 *  @return     uint8 : Revision of the Microcontroller Core
 */
MICRO_ID_TYPE * Micro__GetCoreID(void)
{
    return (MICRO_CPU_ID());
}

//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
