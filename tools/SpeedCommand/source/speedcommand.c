#define S_FUNCTION_NAME  speedcommand
#define S_FUNCTION_LEVEL 2

#include "simstruc.h"
#include "MciSimCommon.h"
#include "Mci.h"
#include <Windows.h>
#include <string.h>
typedef MCI_CMD_RESPONSE_TYPE (*mcirun)(MOTOR_ENUM_TYPE motor, int speed_rpm, int ramp_rpm_per_s);
mcirun Mci_Run = NULL;

typedef MCI_CMD_RESPONSE_TYPE (*mcistop)(MOTOR_ENUM_TYPE motor, int ramp_rpm_per_s);
mcistop Mci_Stop = NULL;
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
    ssSetNumSFcnParams(S, 2);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 0)) return;
//    ssSetInputPortWidth(S, 0, 1);
//    ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    /*
     * Set direct feedthrough flag (1=yes, 0=no).
     * A port has direct feedthrough if the input is used in either
     * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
     */
//    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 0)) return;
//     ssSetOutputPortWidth(S, 0, 1);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    ssSetOptions(S, 0);
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
    if(mci!=NULL)
    {
        Mci_Run = mci->methods[MCI_RUN];
        Mci_Stop = mci->methods[MCI_STP];
        if (Mci_Run == NULL)
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
        ssSetErrorStatus(S,"Failed to load lib.");
    } else {
        ssSetPWorkValue(S, 0, lib);
    }
  }
#endif /*  MDL_START */
  
enum {
    SET,
    RUN,
    WAIT
}state = SET;

/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
// static float current = 0;
// static float increment = 0;
static int duration_counter = 0;
static float target = 0 ;
static float accel = 0;
static int duration_in_samples = 0;
static int wait_in_samples = 0;
static int step_idx = 0;
static void mdlOutputs(SimStruct *S, int_T tid)
{
//    const real_T *u = (const real_T*) ssGetInputPortSignal(S,0);
//     real_T *y = ssGetOutputPortSignal(S,0);
    real_T* mctrl = (real_T*)mxGetData(ssGetSFcnParam(S,1));
    real_T *commands = mxGetPr(ssGetSFcnParam(S,0));
    int rows = 0;
    time_T step_size = ssGetFixedStepSize(S);
    MCI_CMD_RESPONSE_TYPE response;

if (*mctrl == 1)
{    
    MciStruct* mci;
    if(!Mci_MethodsLoadedFlag)
    {
        mci = (MciStruct*)GetProcAddress((HMODULE)ssGetPWorkValue(S,0), "Mci");
        if((mci != NULL) && (!ssRTWGenIsCodeGen(S)))
        {
            Mci_Run = mci->methods[MCI_RUN];
            if (Mci_Run == NULL)
            {
              ssSetErrorStatus(S, "Could not load mci api, make sure Mci block is in your model.");
            }
            else
            {
              Mci_MethodsLoadedFlag = 1;
            }
            Mci_Stop = mci->methods[MCI_STP];
            if (Mci_Stop == NULL)
            {
              ssSetErrorStatus(S, "Could not load mci api, make sure Mci block is in your model.");
            }
            else
            {
              Mci_MethodsLoadedFlag = 1;
            }
        }
    }
    

    if (commands != NULL)
    {
        rows = mxGetM(ssGetSFcnParam(S,0));
    }
    
    switch(state)
    {
        case WAIT:
            wait_in_samples--;
            if (wait_in_samples <= 0)
                state = SET;
            break;
        case SET:
            if(step_idx < rows)
            {
                target = commands[step_idx];
                accel = commands[step_idx + rows];
//                 increment = accel * step_size; 
                duration_in_samples = (commands[step_idx + (2*rows)]) / step_size; 
                wait_in_samples = 0.5 / step_size;
                if (target != 0)
                {
                    if(Mci_Run!=NULL)
                    {

                        response = Mci_Run(MOTOR0, target, accel);
                        if (response == MCI_CMD_ACCEPTED )
                        {
                            step_idx++;
                            state = RUN;
                        }
                        else
                        {
                            state = WAIT;
                        }
                        printf("Command sent: speed - %f; acceleration - %f\nResponse: %i\n", target, accel, response);
                    }
                    else
                        ssSetErrorStatus(S,"Failed to call Mci__Run.");
                }
                else
                {
                    if(Mci_Stop!=NULL)
                    {
                        response = Mci_Stop(MOTOR0, accel);
                        if (response == MCI_CMD_ACCEPTED )
                        {
                            step_idx++;
                            state = RUN;
                        }
                        else
                        {
                            state = WAIT;
                        }
                        printf("Command sent: speed - %f; acceleration - %f\nResponse: %i\n", target, accel, response);
                    }
                    else
                        ssSetErrorStatus(S,"Failed to call Mci__Stop.");
                }
            }
            break;
        case RUN:
//             if (target > current)
//             {
//                 current+=increment;
//                 if (current >= target)
//                 {
//                     current=target;
//                 }
//             } else if (target < current)
//             {
//                 current-=increment;
//                 if (current <= target)
//                 {
//                     current=target;
//                 }
//             }
            
            duration_counter++;
            if(duration_counter == duration_in_samples)
            {
                state = SET;
                duration_counter = 0;
            }
            
            break;
    }
    //counter = step[2] / step_size;
//     if(arg != NULL)
//      *y = arg[2];
//     else
//         *y = 10;
}   
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
    step_idx = 0;
    FreeLibrary(ssGetPWorkValue(S,0));
}


/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
