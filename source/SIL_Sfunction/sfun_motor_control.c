/*  File    : dsfunc.c
 *  Abstract:
 *
 *      Example C-file S-function for defining a discrete system.  
 *
 *      x(n+1) = Ax(n) + Bu(n)
 *      y(n)   = Cx(n) + Du(n)
 *
 *      For more details about S-functions, see simulink/src/sfuntmpl_doc.c.
 * 
 *  Copyright 1990-2006 The MathWorks, Inc.
 *  $Revision: 1.7 $
 */

#define S_FUNCTION_NAME sfun_motor_control
#define S_FUNCTION_LEVEL 2


#include "simstruc.h"

// Include the required files from the embedded simulation
#include "C_Extensions.h"
#include "Sim.h"
#include "SFloader.h"
#ifdef CMDMANAGER
#include "CommandManager.h"
#endif

#include <Windows.h>
#include "MciSimCommon.h"
#include "Mci.h"
#include "Pathcch.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef SIL_EXTENDED
#include "Uart.h"
// Win Log variables
char Winlog_Filename[256];
double Sim_Time;
#define PACKET_MAX_SIZE  100

#include "InjFail.h"

#endif
#define U(element) (*uPtrs[element])        // Pointer to Input Port0

//// Define the interfaces between the Simulink Environment and the Embedded code
// When adding more inputs, the mux router in the simulink needs to have its
// appended at END of the router

//====================
// S-function methods
//====================

// Function: mdlInitializeSizes ===============================================
// Abstract:
//    The sizes information is used by Simulink to determine the S-function
//    block's characteristics (number of inputs, outputs, states, etc.).
//
static void mdlInitializeSizes(SimStruct *S)
{

#ifdef SIL_EXTENDED
     ssSetNumSFcnParams(S, 3);       // Number of expected parameters (log file for extended)
#else
     ssSetNumSFcnParams(S, 2);       // Number of expected parameters
#endif

    if(ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        return;                     // Parameter mismatch will be reported by Simulink
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    // INPUTS - WARNING - DYMOLA PORTS ONLY ACCEPTS SINGLE INPUT/OUTPUT S-FUNCTIONS
    if(!ssSetNumInputPorts(S, 1))
    {
        return;
    }
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortWidth(S, 0, SIM_LOOP_NUMBER_OF_INPUTS);
    
   // OUTPUTS
#ifndef SIL_EXTENDED
    if(!ssSetNumOutputPorts(S, 1))
    {
        return;
    }
    ssSetOutputPortWidth(S, 0, SIM_LOOP_NUMBER_OF_OUTPUTS);
#else
    if(!ssSetNumOutputPorts(S, 3))// outputs include win packet sending + flag
    {
        return;
    }
    ssSetOutputPortWidth(S, 0, SIM_LOOP_NUMBER_OF_OUTPUTS);
    ssSetOutputPortWidth(S, 1, PACKET_MAX_SIZE);  // WIN PACKET SEND
    ssSetOutputPortWidth(S, 2, 1);  // SEND FLAG

    ssSetOutputPortDataType(S, 1, SS_UINT8);
    ssSetOutputPortDataType(S, 2, SS_UINT8);
#endif
//    ssSetNumSampleTimes(S, 1); // Uncomment to have continous states.
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    // Take care when specifying exception free code - see sfuntmpl_doc.c
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
    
    // Setting File reading
    char * FileName;
    int_T buflen;
    int_T status;

    buflen = mxGetN((ssGetSFcnParam(S, 1)))*sizeof(mxChar)+1;
    FileName = mxMalloc(buflen);
    status = mxGetString((ssGetSFcnParam(S, 1)), FileName,buflen);

    if(SFloader__Initialize(FileName) == 0)
    {
        static char msg[512];
        sprintf(msg,"Unable to open the setting file binary: %s",FileName);
        ssSetErrorStatus(S,msg);
    }

#ifdef SIL_EXTENDED
    // Win Log file preparation
    buflen = mxGetN((ssGetSFcnParam(S, 2)))*sizeof(mxChar)+1;
    char *Winlog_Filename_Ptr = mxMalloc(buflen);
    status = mxGetString((ssGetSFcnParam(S, 2)), Winlog_Filename_Ptr,buflen);
    memcpy(&(Winlog_Filename[0]),Winlog_Filename_Ptr,buflen);
#endif

    // Initialize here the embedded code...
    Sim__Initialize();

}


/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    real_T* chosen_step = (real_T*)mxGetData(ssGetSFcnParam(S,0));
    ssSetSampleTime(S, 0, *chosen_step);
    ssSetOffsetTime(S, 0, 0.0);

}

#define MDL_INITIALIZE_CONDITIONS
static void mdlInitializeConditions(SimStruct *S)
{


}

#define MDL_START
int var_base_addr = 60;
static void mdlStart(SimStruct *S)
{
    MciStruct* mci;
    void* lib = NULL;
	char FullPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, FullPath);
    strcat(FullPath, "\\tools\\MciAPI\\MciStruct.dll");
    lib = LoadLibrary(FullPath);
    if(NULL == lib)
    {
        ssSetErrorStatus(S,"Failed to load lib.");
    } else {
        ssSetPWorkValue(S, 0, lib);
        mci = (MciStruct*)GetProcAddress((HMODULE)ssGetPWorkValue(S,0), "Mci");
        mci->methods[MCI_RUN] = Mci__Run;
        mci->methods[MCI_STP] = Mci__Stop;
        mci->methods[MCI_GET_DIG] = Mci__GetDigital;
        mci->methods[MCI_GET_ANG] = Mci__GetAnalog;
        mci->methods[MCI_SET_DIG] = Mci__SetDigital;
        mci->methods[MCI_SET_ANG] = Mci__SetAnalog;
        #if MCI_FVT_TESTS == ENABLED
        mci->methods[MCI_FVT_START] = Mci__FvtStart;
        #endif
        mci->methods[VAR_BASE_ADDR] = &var_base_addr;
        #ifdef SIL_EXTENDED
        mci->methods[WIN_UART] = Uart__Read;
        mci->methods[INJFAIL_SRMCATOD_DIAGN] = InjFail__SetSRMCAtodDiagnFbk;
        mci->methods[INJFAIL_SRMCPWM_DIAGN]  = InjFail__SetSRMCPwmDiagnFbk;
        mci->methods[INJFAIL_SRMCPWM_HWOC]  = InjFail__SetSRMCPwmHWFault;
		mci->methods[INJFAIL_SETFAILURE] = InjFail__SetFailure;
        #endif
		#ifdef CMDMANAGER
        mci->methods[CM_RUNLOAD] = CommandManager__RunLoad;
        #endif
        mci->methods[MCI_GET_ERROR_LIST] = Mci__GetErrorList;
    }
}

#define MDL_UPDATE
static void mdlUpdate(SimStruct *S, int_T tid) {}



// Function: mdlOutputs =======================================================


float counter_test = 0;
uint8 power_up_cnt = 0;
static void mdlOutputs(SimStruct *S, int_T tid)
{
    int i;
    // Output vector
    real_T            *y      = ssGetOutputPortRealSignal(S,0);
#ifdef SIL_EXTENDED
    uint8             *packet = ssGetOutputPortSignal(S,1);
    uint8             *flag   = ssGetOutputPortSignal(S,2);
#endif

    // Input vector
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);
    
    // not used in single tasking mode
    UNUSED_ARG(tid);

    // Signal Routing - Inputs
    for (i=0; i < SIM_LOOP_NUMBER_OF_INPUTS; i++)
    {
    	Sim_Loop_Input[i] = U(i);
    }
    ///////////////////////////////////////////

    // Sim_ Execute
    Sim__Execute(SIM_LOOP_INDEX);

    /////////////////////////////

    // Signal Routing - Outputs
    for (i=0; i < SIM_LOOP_NUMBER_OF_OUTPUTS; i++)
    {
        y[i] = Sim_Loop_Output[i];
    }
    ///////////////////////////////////////////
	#ifdef SIL_EXTENDED
    // Update Simulation Time
    Sim_Time = ssGetT(S);
    *flag=Uart__GetTXPacket(packet);
    #endif
}

static void mdlTerminate(SimStruct *S)
{
    FreeLibrary(ssGetPWorkValue(S,0));
}
#ifdef  MATLAB_MEX_FILE    // Is this file being compiled as a MEX-file?
#include "simulink.c"      // MEX-file interface mechanism
#else
#include "cg_sfun.h"       // Code generation registration function
#endif
