/*
 * sfuntmpl_basic.c: Basic 'C' template for a level 2 S-function.
 *
 * Copyright 1990-2013 The MathWorks, Inc.
 */


/*
 * You must specify the S_FUNCTION_NAME as the name of your S-function
 * (i.e. replace sfuntmpl_basic with the name of your S-function).
 */

#define S_FUNCTION_NAME  mci_run
#define S_FUNCTION_LEVEL 2

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"
#include "MciSimCommon.h"
#include "Mci.h"
#include <Windows.h>
#include <string.h>
MCI_CMD_RESPONSE_TYPE (*MciRun)(MOTOR_ENUM_TYPE motor, sint32 speed_rpm, sint32 ramp_rpm_per_s);
/* Error handling
 * --------------
 *
 * You should use the following technique to report errors encountered within
 * an S-function:
 *
 *       ssSetErrorStatus(S,"Error encountered due to ...");
 *       return;
 *
 * Note that the 2nd argument to ssSetErrorStatus must be persistent memory.
 * It cannot be a local variable. For example the following will cause
 * unpredictable errors:
 *
 *      mdlOutputs()
 *      {
 *         char msg[256];         {ILLEGAL: to fix use "static char msg[256];"}
 *         sprintf(msg,"Error due to %s", string);
 *         ssSetErrorStatus(S,msg);
 *         return;
 *      }
 *
 */

/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 0);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }
//    ssSetSFcnParamTunable(S,READ_DATA,false);
//    ssSetSFcnParamTunable(S,READ_DATA_CMD,false);

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 2)) return;
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortWidth(S, 1, 1);
    ssSetInputPortDataType(S, 0, SS_INT32);
    ssSetInputPortDataType(S, 1, SS_INT32);
    ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    ssSetInputPortRequiredContiguous(S, 1, true); /*direct input signal access*/
    /*
     * Set direct feedthrough flag (1=yes, 0=no).
     * A port has direct feedthrough if the input is used in either
     * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
     */
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortDirectFeedThrough(S, 1, 1);

    if (!ssSetNumOutputPorts(S, 1)) return;
    ssSetOutputPortWidth(S, 0, 1);
    int dataTypeIdReg;
    ssRegisterTypeFromNamedObject(S, "MCI_CMD_RESPONSE_TYPE", &dataTypeIdReg);
    ssSetOutputPortDataType(S, 0, dataTypeIdReg);
    ssSetOutputPortOutputExprInRTW(S, 0, 1);
    
    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    ssSetOptions(S,
            SS_OPTION_USE_TLC_WITH_ACCELERATOR |
            SS_OPTION_CAN_BE_CALLED_CONDITIONALLY |
            SS_OPTION_EXCEPTION_FREE_CODE |
            SS_OPTION_WORKS_WITH_CODE_REUSE |
            SS_OPTION_SFUNCTION_INLINED_FOR_RTW);
    ssSetModelReferenceNormalModeSupport(S, MDL_START_AND_MDL_PROCESS_PARAMS_OK);
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, -1);
    ssSetOffsetTime(S, 0, 0.0);

}



#define MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
  /* Function: mdlInitializeConditions ========================================
   * Abstract:
   *    In this function, you should initialize the continuous and discrete
   *    states for your S-function block.  The initial states are placed
   *    in the state vector, ssGetContStates(S) or ssGetRealDiscStates(S).
   *    You can also perform any other initialization activities that your
   *    S-function may require. Note, this routine will be called at the
   *    start of simulation and if it is present in an enabled subsystem
   *    configured to reset states, it will be call when the enabled subsystem
   *    restarts execution to reset the states.
   */
  char Mci_MethodsLoadedFlag = 1;
  static void mdlInitializeConditions(SimStruct *S)
  {
	  MciStruct* mci;

	  mci = (MciStruct*)GetProcAddress((HMODULE)ssGetPWorkValue(S,0), "Mci");
	  if((mci != NULL) && (!ssRTWGenIsCodeGen(S)))
	  {
		  MciRun = mci->methods[MCI_RUN];
		  if (MciRun == NULL)
		  {
              Mci_MethodsLoadedFlag = 0;
			  //ssSetErrorStatus(S, "Could not load mci api, make sure Mci block is in your model.");
		  }
	  }
  }
#endif /* MDL_INITIALIZE_CONDITIONS */



#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
	  void* lib = NULL;
	  char FullPath[MAX_PATH];
	  GetCurrentDirectory(MAX_PATH, FullPath);
      strcat(FullPath, "\\tools\\MciAPI\\MciStruct.dll");
      lib = LoadLibrary(FullPath);
	  if(NULL == lib)
	  {
		  ssSetErrorStatus(S,"Failed to load mci library.");
	  } else {
		  ssSetPWorkValue(S, 0, lib);
	  }
  }
#endif /*  MDL_START */



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    real_T       *y = ssGetOutputPortSignal(S,0);
    int32_T       *u0 = ssGetInputPortSignal(S,0);
    int32_T       *u1 = ssGetInputPortSignal(S,1);
    
    MciStruct* mci;
    if(!Mci_MethodsLoadedFlag)
    {
        mci = (MciStruct*)GetProcAddress((HMODULE)ssGetPWorkValue(S,0), "Mci");
        if((mci != NULL) && (!ssRTWGenIsCodeGen(S)))
        {
            MciRun = mci->methods[MCI_RUN];
            if (MciRun == NULL)
            {
              ssSetErrorStatus(S, "Could not load mci api, make sure Mci block is in your model.");
            }
            else
            {
              Mci_MethodsLoadedFlag = 1;
            }
        }
    }
    
    if ( MciRun != NULL)
        *y = MciRun(MOTOR0, *u0, *u1); 
}



#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
  /* Function: mdlUpdate ======================================================
   * Abstract:
   *    This function is called once for every major integration time step.
   *    Discrete states are typically updated here, but this function is useful
   *    for performing any tasks that should only take place once per
   *    integration step.
   */
  static void mdlUpdate(SimStruct *S, int_T tid)
  {
  }
#endif /* MDL_UPDATE */



#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
  /* Function: mdlDerivatives =================================================
   * Abstract:
   *    In this function, you compute the S-function block's derivatives.
   *    The derivatives are placed in the derivative vector, ssGetdX(S).
   */
  static void mdlDerivatives(SimStruct *S)
  {
  }
#endif /* MDL_DERIVATIVES */



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
	FreeLibrary(ssGetPWorkValue(S,0));
    Mci_MethodsLoadedFlag = 1;
}

#undef MDL_RTW                        /* Change to #undef to remove function */
#if defined(MDL_RTW)
/* Function: mdlRTW ============================================================
 * Abstract:
 *    This function is called when the Real-Time Workshop is generating the
 *    model.rtw file. In this routine, you can call the following functions
 *    which add fields to the model.rtw file.
 *
 *    Important! Since this s-function has this mdlRTW method, it is required
 *    to have a correcponding .tlc file so as to work with RTW. You will find
 *    the sfun_directlook.tlc in <matlaroot>/toolbox/simulink/blocks/tlc_c/.
 */
static void mdlRTW(SimStruct *S)
{
    int_T buflen, status;
    char* read_data;
    
    buflen = mxGetN(GET_READ_DATA_CMD(S))*sizeof(mxChar)+1;
    read_data = mxMalloc(buflen);
    status = mxGetString((GET_READ_DATA_CMD(S)), read_data, buflen);
    
    if (!ssWriteRTWParamSettings(S, 1,
                                     SSWRITE_VALUE_STR, "read_data", read_data))
    {
        return;/* An error occurred which will be reported by Simulink */
    }
}
#endif

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
