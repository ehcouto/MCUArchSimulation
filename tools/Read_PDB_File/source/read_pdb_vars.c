/*
 * sfuntmpl_basic.c: Basic 'C' template for a level 2 S-function.
 *
 * Copyright 1990-2013 The MathWorks, Inc.
 */


/*
 * You must specify the S_FUNCTION_NAME as the name of your S-function
 * (i.e. replace sfuntmpl_basic with the name of your S-function).
 */

#define S_FUNCTION_NAME  read_pdb_vars
#define S_FUNCTION_LEVEL 2

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simstruc.h"
#include "MciSimCommon.h"
#include "ReadPdb.h"
#include <Windows.h>
#include <string.h>
void* Initial_Address = NULL;
long long Initial_addr_offset = 0;


#define GET_STRING(S)     (ssGetSFcnParam(S,0))

#define MAX_PATH_SIMARCH    256

//  typedef void (*Load_t)(char* path);
//  typedef void (*Get_t)(char* var, return_type* ret);
// 
//  Load_t LoadPdb = NULL;
//  Get_t GetVariable = NULL;

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
    char buffer[32];
    return_type pdb_out;
    

    ssSetNumSFcnParams(S, 1);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 0)) return;
    //ssSetInputPortWidth(S, 0, 1);
    //ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    /*
     * Set direct feedthrough flag (1=yes, 0=no).
     * A port has direct feedthrough if the input is used in either
     * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
     */
    //ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 1)) return;
    ssSetOutputPortWidth(S, 0, 1);
//     void* lib = NULL;
//     lib = LoadLibrary("ReadPdb.dll");
//     if(NULL == lib)
//     {
//       ssSetErrorStatus(S,"Failed to load pdb lib.");
//     } 
//     LoadPdb = (Load_t)GetProcAddress((HMODULE)lib, "LoadPdb");
//     GetVariable = (Get_t)GetProcAddress((HMODULE)lib, "GetVariable");
    char FullPath[MAX_PATH_SIMARCH];
	GetCurrentDirectory(MAX_PATH_SIMARCH, FullPath);
    strcat(FullPath, "\\exe\\sfun_motor_control.xml");
    LoadPdb(FullPath);
    
    GetVariable("var_base_addr", &pdb_out);
    Initial_addr_offset = pdb_out.addr_list[0].address;
    printf("var_base_addr address: %llX\n", pdb_out.addr_list[0].address);

    GetVariable(mxArrayToString(GET_STRING(S)), &pdb_out);
    printf("Chosen var address: %llX\n", pdb_out.addr_list[0].address);
//    num_offset = pdb_out.num_offset;
//     for (int i = 0; i < num_offset; i++)
//     {
//         offsets[i].address = pdb_out.addr_list[i].address;
//         offsets[i].pointer = pdb_out.addr_list[i].pointer;
//     }
    
    wcstombs( buffer, pdb_out.type, sizeof(buffer));
    if ( strstr(buffer, "unsigned") != NULL )
    {
        if ( (strstr(buffer, "long") != NULL) || (strstr(buffer, "int") != NULL))
            ssSetOutputPortDataType(S, 0, SS_UINT32);
        else if ( strstr(buffer, "short") != NULL )
            ssSetOutputPortDataType(S, 0, SS_UINT16);
        else if ( strstr(buffer, "char") != NULL )
            ssSetOutputPortDataType(S, 0, SS_UINT8);
        
    }
    else 
    {
        if ( (strstr(buffer, "long") != NULL) || (strstr(buffer, "int") != NULL))
            ssSetOutputPortDataType(S, 0, SS_INT32);
        else if ( strstr(buffer, "short") != NULL )
            ssSetOutputPortDataType(S, 0, SS_INT16);
        else if ( strstr(buffer, "char") != NULL )
            ssSetOutputPortDataType(S, 0, SS_INT8);
        else if ( strstr(buffer, "double") != NULL )
            ssSetOutputPortDataType(S, 0, SS_DOUBLE);
        else if ( strstr(buffer, "float") != NULL )
            ssSetOutputPortDataType(S, 0, SS_SINGLE);
        else if ( strstr(buffer, "bool") != NULL )
            ssSetOutputPortDataType(S, 0, SS_BOOLEAN);
    }
    
    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 1);
    ssSetNumIWork(S, 1);
    ssSetNumPWork(S, 2);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);


    /* Specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    ssSetOptions(S,0);
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
		  Initial_Address = mci->methods[VAR_BASE_ADDR];
		  if (Initial_Address == NULL)
		  {
              Mci_MethodsLoadedFlag = 0;
//			  ssSetErrorStatus(S, "Could not load mci api, make sure Mci block is in your model.");
		  }
	  }
      ssSetIWorkValue(S, 0, 0);
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
	  char FullPath[MAX_PATH_SIMARCH];
	  GetCurrentDirectory(MAX_PATH_SIMARCH, FullPath);
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
    
    long long value_ptr;
    DTypeId output_type;
    output_type = ssGetOutputPortDataType(S,0);
    return_type pdb_out;
    address_type* offsets;
    int num_offset;

    MciStruct* mci;
    if(!Mci_MethodsLoadedFlag)
    {
        mci = (MciStruct*)GetProcAddress((HMODULE)ssGetPWorkValue(S,0), "Mci");
        if((mci != NULL) && (!ssRTWGenIsCodeGen(S)))
        {
            Initial_Address = mci->methods[VAR_BASE_ADDR];
            if (Initial_Address == NULL)
            {
              ssSetErrorStatus(S, "Could not load mci api, make sure Mci block is in your model.");			  
            }
            else
            {
              Mci_MethodsLoadedFlag = 1;
            }
        }
    }
    
    if (ssGetIWorkValue(S,0) == 0)
    {
        GetVariable(mxArrayToString(GET_STRING(S)), &pdb_out);
        num_offset = pdb_out.num_offset;
        offsets = pdb_out.addr_list;
        value_ptr = (long long)Initial_Address - (long long)Initial_addr_offset;
        for (int i = 0; i < num_offset; i++)
        {
            value_ptr = (long long)value_ptr + (long long)offsets[i].address;
            if (offsets[i].pointer)
            {   
                long long* temp_address = (long long*)(value_ptr); 
                value_ptr = (long long)*temp_address;
            }

        }
        ssSetPWorkValue(S, 1, (void*)value_ptr);
        ssSetIWorkValue(S, 0, 1);
    }
    
    if (output_type == SS_INT32)
    {
        int* temp_value = (int*)ssGetPWorkValue(S,1);
        int* y = (int *)ssGetOutputPortSignal(S,0);
        y[0] = *temp_value;
    }else
    if (output_type == SS_INT16)
    {
        short int* temp_value = (short int*)ssGetPWorkValue(S,1);
        short int* y = (short int *)ssGetOutputPortSignal(S,0);
        y[0] = *temp_value;
    }else
    if (output_type == SS_INT8)
    {
        char* temp_value = (char*)ssGetPWorkValue(S,1);
        char* y = (char *)ssGetOutputPortSignal(S,0);
        y[0] = *temp_value;
    }else
    if (output_type == SS_UINT32)
    {
        unsigned int* temp_value = (unsigned int*)ssGetPWorkValue(S,1);
        unsigned int* y = (unsigned int *)ssGetOutputPortSignal(S,0);
        y[0] = *temp_value;
    }else
    if (output_type == SS_UINT16)
    {
        unsigned short int* temp_value = (unsigned short int*)ssGetPWorkValue(S,1);
        unsigned short int* y = (unsigned short int *)ssGetOutputPortSignal(S,0);
        y[0] = *temp_value;
    }else
    if (output_type == SS_UINT8)
    {
        unsigned char* temp_value = (unsigned char*)ssGetPWorkValue(S,1);
        unsigned char* y = (unsigned char *)ssGetOutputPortSignal(S,0);
        y[0] = *temp_value;
    }else
    if (output_type == SS_DOUBLE)
    {
        double* temp_value = (double*)ssGetPWorkValue(S,1);
        double* y = (double *)ssGetOutputPortSignal(S,0);
        y[0] = *temp_value;
    }else
    if (output_type == SS_SINGLE)
    {
        float* temp_value = (float*)ssGetPWorkValue(S,1);
        float* y = (float *)ssGetOutputPortSignal(S,0);
        y[0] = *temp_value;
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
}


/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
