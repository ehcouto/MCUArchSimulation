/** MOCKUP
/**
 *  @file
 *
 *  @brief      Public declarations that define the type of system the micro is supporting.
 *
 *  @details    Add descriptions of all selectable features to the following list:
 *
 *  API005_CONTROL_CYCLES_FEATURE                   Allows API005 to control appliance cycles
 *  API005_USE_LOADS_AND_GIS_FEATURE                Allows API005 to set and get Loads and GIs through Hbl
 *  API005_USE_OBJECTS_AND_EVENTS_FEATURE           Allows API005 to set objects and get events through HblHmi
 *  API005LOWLEVEL_FEATURE                          Provides PC control of the board I/O
 *  API010_USES_FIXED_VARIABLES_FEATURE             Indicates that API010 uses the Variables module for fixed variables.
 *  API010POLLVAR_FEATURE                           Reports platform variables and memory mapped variables over WIN.
 *  API013_CLIENT_FEATURE                           Controls application-layer functions on remote boards.
 *  API013_SERVER_FEATURE                           Provides application-layer functions through communications.
 *  API018_CLIENT_FEATURE                           Requests fault information and can generate a fault.
 *  API018_SERVER_FEATURE                           Publishes fault information and stores it in nonvolatile memory.
 *  API019_BOARD_DATA_FEEDBACK                      Indicates that the board supports API019 board data feedback for displaying on an HMI.
 *  API220MOTORCONTROL_FEATURE                      Enables API220 functionality on motor control boards with MCI.
 *  API221_CLIENT_FEATURE                           Sends motor control messages and receives motor status messages.
 *  API221_SERVER_FEATURE                           Receives motor control messages and sends motor status messages.
 *  CALIBRATION_DATA_FEATURE                        Uses Calibration Data to calibrate some GIs on FVT/EOL using API019
 *  COMMUNICATION_MONITOR_FEATURE                   Monitors the Communication faults
 *  CONNECTIVITY_FEATURE                            Enables connectivity data model, API147, and API151.
 *  CONNECTIVITY_HMI_FEATURE                        Enables API144 and API141.  Requires CONNECTIVITY_FEATURE ENABLED.
 *  FAULT_MANAGEMENT_FEATURE                        Enables firmware that depends on the Fault module to track error conditions and report faults.
 *  HBLACU_ZEROCROSS_FEATURE                        Enables Zerocross handling on HblAcu (Default: Enabled with SYSTEM_ACU_HANDLING defined, Disabled for other cases)
 *  HBLHMI_LLI_INITIALIZATION_FEATURE               Enables the initialization of LLIs in the HblHmi module (Disabled for P1)
 *  HMI_ACUVARIABLE_MODULE_FEATURE                  Enables the module that declares ACU variables instances for a P3 HMI
 *  HMI_VARIABLE_FEATURE                            Defines if Variable module handles HmiVariables indexes
 *  NVDATA_STORE_STATIC_FEATURE                     Allows API019 to store static data on supported board types.
 *  NVDATA_STORE_APPLIANCE_AND_STATISTICS_FEATURE   Allows management of the Appliance and Statistics segment data using the NVData module
 *  RECEIVE_STATUS_VARIABLES_FEATURE                Allows status variables to be updated over API011
 *  SETTINGFILE_MASTER_FILE_FEATURE                 Indicates that the board contains the master setting file for the system.
 *  SETTINGFILE_SECTION_DOWNLOAD_FEATURE            Indicates that the board will download a section of the setting file from the Main ACU.
 *  SFUPDATER_ACU_SECTION_ID                        The SF_ID_TYPE for the ACU section of the setting file. For ACU Expansion boards.
 *  SFUPDATER_HMI_SECTION_ID                        The SF_ID_TYPE for the HMI section of the setting file. For HMI and HMI Expansion boards.
 *  SFUPDATER_MCU_SECTION_ID                        The SF_ID_TYPE for the MCU section of the setting file. For MUC boards.
 *  TIME_ESTIMATION_FEATURE                         Enables cycle time estimation -- provides an Estimated_Remaining_Time[] variable.
 *
 *  @copyright  Copyright 2016-$Date$. Whirlpool Corporation. All rights reserved - CONFIDENTIAL
 */
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
#ifndef _SYSTEMCONFIG_H_
#define _SYSTEMCONFIG_H_

#include "C_Extensions.h"
//#include "SRSystemConfig.h"
//#include "SystemConfig_prm.h"


//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================


//---------------------------------------------------------------------------------------------------------------------
// Public Declarations that are not dependent on the type of project (ACU, HMI, MCU, etc.)
//---------------------------------------------------------------------------------------------------------------------


#endif // _SYSTEMCONFIG_H_
