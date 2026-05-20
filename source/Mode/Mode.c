/**
 *  @file       
 *
 *  @brief      This module controls the overall mode (state) of the appliance
 *
 *  @details

    @startuml {SubMode_state_machine.jpg}
        title SubMode State Machine

        State Initialize
        State SubModeNormalSupervisor
        State SubModeError
        State SubModeNormalExtControlEntering
        State SubModeNormalExtControlEngaged


        [*] --> Initialize

        Initialize : do /\t HandleRequestedSubMode()
        Initialize --> SubModeNormalSupervisor : evReqSubModeSupervisor \n [IsReqSubModeInitialize()]
        Initialize --> SubModeError : evReqSubModeError \n [IsReqSubModeError()]

        SubModeNormalSupervisor : enter /\t SetReqSubModeNone() \n\t\t PublishMode()
        SubModeNormalSupervisor : do /\t HandleRequestedSubMode()
        SubModeNormalSupervisor --> SubModeError                    : evReqSubModeError
        SubModeNormalSupervisor --> SubModeNormalExtControlEntering : evReqSubModeExtControlEntering \n [EnableSystemTimer()]
        SubModeNormalSupervisor --> SubModeNormalSupervisor         : evReqSubModeSupervisor

        SubModeNormalExtControlEntering : do /\t VerifyTimerIsRunning() \n\t HandleRequestedSubMode()
        SubModeNormalExtControlEntering --> SubModeNormalExtControlEngaged  : evReqSubModeExtControlEngaged
        SubModeNormalExtControlEntering --> SubModeNormalSupervisor         : evReqSubModeSupervisor \n/ ReleaseSystemTimer()
        SubModeNormalExtControlEntering --> SubModeNormalSupervisor         : evTimerExpired \n/ ReleaseSystemTimer()

        SubModeNormalExtControlEngaged : enter /\t SetTimer() \n\t\t PublishMode()
        SubModeNormalExtControlEngaged : do /\t VerifyTimerIsRunning() \n\t HandleRequestedSubMode()
        SubModeNormalExtControlEngaged : exit /\t ReleaseSystemTimer()
        SubModeNormalExtControlEngaged --> SubModeNormalSupervisor  : evReqSubModeSupervisor
        SubModeNormalExtControlEngaged --> SubModeNormalSupervisor  : evTimerExpired

    @enduml

 *
 *  @copyright  Copyright 2015-$Date: 2015/08/06 16:33:50EDT $. Whirlpool Corporation. All rights reserved - CONFIDENTIAL
 */
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "Mode.h"

static MODE_TYPE Mode;

//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      It Initializes the module Mode and its variables
 *
 */
void Mode__Initialize(void)
{
    Mode = MODE_NORMAL;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief   Sets the mode of the machine and causes a warm reset (except for MODE_SETTINGFILE_NOT_CONSISTENT)
 * @param   mode: See MODE_TYPE
 */
void Mode__SetMode(MODE_TYPE mode)
{
    if (Mode != mode)
    {
        Mode = mode;
    }
}


//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief   Get the current mode of the machine.
 * @return  See MODE_TYPE.
 */
MODE_TYPE Mode__GetMode(void)
{
    return (Mode);
}




//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief This method exposes if the board is in programming allowed mode
 * @return BOOL_TYPE
 *    @retval TRUE - Programming allowed .
 *    @retval FALSE - Programming not allowed .
 */
BOOL_TYPE Mode__IsProgrammingEngaged(void)
{
    return (((Mode == MODE_PROGRAMMING) || (Mode == MODE_SETTINGFILE_NOT_CONSISTENT)) ? TRUE : FALSE);
}


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================

//=====================================================================================================================
//  --- Private State Machine Customization Functions -----------------------------------------------------------------
//=====================================================================================================================


