/**
 *  @file       
 *
 *  @brief      Public interface file for the Mode module.
 *
 *  @copyright  Copyright 2015-$Date: 2015/07/01 13:51:11EDT $. Whirlpool Corporation. All rights reserved - CONFIDENTIAL
 */
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
#ifndef MODE_H_
#define MODE_H_
#include "C_Extensions.h"
//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================
typedef enum
{

    MODE_NORMAL                     = 0,
    MODE_PROGRAMMING                = 1,
    MODE_SETTINGFILE_NOT_CONSISTENT = 2, // Setting file can not be use. This mode can not be set from external.
                                         // it only is set by the system itself when it checks the settingfile CRC
    MODE_LOWPOWER                   = 3 // In this mode the code is running a very small task to check if it should

}MODE_TYPE;

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
void Mode__Initialize(void);

void Mode__SetMode(MODE_TYPE mode);
MODE_TYPE Mode__GetMode(void);
BOOL_TYPE Mode__IsProgrammingEngaged(void);


#endif // MODE_H_


