/**
 *  @file       
 *
 *  @brief      
 *
 *  $Header: $
 *
 *  @copyright  Copyright 2016-$Date$. Whirlpool Corporation. All rights reserved - CONFIDENTIAL
 */
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
#ifndef SETTINGFILEMOCK_PRV_H_
#define SETTINGFILEMOCK_PRV_H_

//=====================================================================================================================
//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
//=====================================================================================================================

/**
 * Allows the use of an ACU setting file that is linked as a binary file with the firmware.
 * Possible values are ENABLED or DISABLED
 */
#define USE_ACU_HARDCODED_SETTING_FILE  DISABLED

/**
 * Allows the use of an HMI setting file that is linked as a binary file with the firmware.
 * Possible values are ENABLED or DISABLED
 */
#define USE_HMI_HARDCODED_SETTING_FILE  DISABLED

/**
 *  @brief      Start address of the memory that contains the setting file data.
 *
 *  @details    In most cases, this macro should be removed from this file and the macro defined in SettingFile.c that
 *              uses the linker symbols defined the config.icf file should be used. In cases where the linker symbols
 *              cannot be used (Example: on a GUI project), this macro can be used to implement other functionality to
 *              get the start address of the setting file.
 */
//#define SF_START_ADDRESS

/**
 *  @brief      Size of the memory section that contains the setting file data.
 *
 *  @details    In most cases, this macro should be removed from this file and the macro defined in SettingFile.c that
 *              uses the linker symbols defined the config.icf file should be used. In cases where the linker symbols
 *              cannot be used (Example: on a GUI project), this macro can be used to implement other functionality to
 *              get the size of the setting file.
 */
//#define SF_SIZE
//////// SETTING FILE MOCK //////
#ifdef COMPILE_4_SIMULINK
extern uint32 SF_size;
extern char *SF_ptr;

/**
 *  @brief      Start address of the memory that contains the setting file data.
 *
 *  @details    In most cases, this macro should be removed from this file and the macro defined in SettingFile.c that
 *              uses the linker symbols defined the config.icf file should be used. In cases where the linker symbols
 *              cannot be used (Example: on a GUI project), this macro can be used to implement other functionality to
 *              get the start address of the setting file.
 */
#define SF_START_ADDRESS  (SF_ptr)

/**
 *  @brief      Size of the memory section that contains the setting file data.
 *
 *  @details    In most cases, this macro should be removed from this file and the macro defined in SettingFile.c that
 *              uses the linker symbols defined the config.icf file should be used. In cases where the linker symbols
 *              cannot be used (Example: on a GUI project), this macro can be used to implement other functionality to
 *              get the size of the setting file.
 */
#define SF_SIZE (SF_size)
#endif

#endif // SETTINGFILEMOCK_PRV_H_
