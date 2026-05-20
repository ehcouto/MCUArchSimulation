#include "MciStruct.h"

enum {
    MCI_RUN = 0,
    MCI_STP = 1,
	MCI_GET_DIG = 2,
    MCI_GET_ANG = 3,
	MCI_SET_DIG = 4,
	MCI_SET_ANG = 5,
	MCI_FVT_START = 6,
    VAR_BASE_ADDR = 7,
    CM_RUNLOAD = 8,
    WIN_UART = 9,
    MCI_GET_ERROR_LIST = 10,
    INJFAIL_SRMCATOD_DIAGN = 11,
    INJFAIL_SRMCPWM_DIAGN  = 12,
    INJFAIL_SRMCPWM_HWOC  = 13,
	INJFAIL_SETFAILURE = 14,
//----------------------------------    
    NUM_METHODS
//----------------------------------
};

typedef void (*gen_fun)();

typedef signed char (*fun_mci_run)(unsigned char, signed long int, signed long int);
typedef signed char (*fun_mci_stop)(unsigned char, signed long int);
typedef unsigned char (*fun_mci_getdigital)(unsigned char, unsigned char);
typedef signed long int (*fun_mci_getanalog)(unsigned char, unsigned char);
typedef unsigned char (*fun_mci_setdigital)(unsigned char, unsigned char, unsigned char);
typedef unsigned char (*fun_mci_setanalog)(unsigned char, unsigned char, signed long int);
typedef unsigned char (*fun_mci_fvtstart)(unsigned char);
typedef unsigned char (*fun_commandmanager_runload)(unsigned char, signed long int, signed long int);
typedef unsigned long int (*fun_mci_geterrorlist)(unsigned char);
typedef void (*fun_injfail_srmcatod_diagn)(unsigned char);
typedef void (*fun_injfail_srmcpwm_diagn)(unsigned char);
typedef void (*fun_injfail_srmcpwm_hwoc)(unsigned char);
typedef void (*fun_injfail_setfailure)(unsigned char);


#define FUNC_CALL_MCI_RUN(y,u)                     *(y) = ((fun_mci_run)(GenericFuncCall))(u[0], u[1], u[2])
#define FUNC_CALL_MCI_STP(y,u)                     *(y) = ((fun_mci_stop)(GenericFuncCall))(u[0], u[1])
#define FUNC_CALL_MCI_GET_DIG(y,u)                 *(y) = ((fun_mci_getdigital)(GenericFuncCall))(u[0], u[1])
#define FUNC_CALL_MCI_GET_ANG(y,u)                 *(y) = ((fun_mci_getanalog)(GenericFuncCall))(u[0], u[1])
#define FUNC_CALL_MCI_SET_DIG(y,u)                 *(y) = ((fun_mci_setdigital)(GenericFuncCall))(u[0], u[1], u[2])
#define FUNC_CALL_MCI_SET_ANG(y,u)                 *(y) = ((fun_mci_setanalog)(GenericFuncCall))(u[0], u[1], u[2] )
#define FUNC_CALL_MCI_FVT_START(y,u)               *(y) = ((fun_mci_fvtstart)(GenericFuncCall))(u[0])
#define FUNC_CALL_VAR_BASE_ADDR(y,u)
#define FUNC_CALL_CM_RUNLOAD(y,u)                  *(y) = ((fun_commandmanager_runload)(GenericFuncCall))(u[0], u[1], u[2])
#define FUNC_CALL_WIN_UART(y,u)
#define FUNC_CALL_MCI_GET_ERROR_LIST(y,u)          *(y) = ((fun_mci_geterrorlist)(GenericFuncCall))(u[0])
#define FUNC_CALL_INJFAIL_SRMCATOD_DIAGN(y,u)             ((fun_injfail_srmcatod_diagn)(GenericFuncCall))(u[0])
#define FUNC_CALL_INJFAIL_SRMCPWM_DIAGN(y,u)              ((fun_injfail_srmcpwm_diagn)(GenericFuncCall))(u[0])
#define FUNC_CALL_INJFAIL_SRMCPWM_HWOC(y,u)               ((fun_injfail_srmcpwm_hwoc)(GenericFuncCall))(u[0])
#define FUNC_CALL_INJFAIL_SETFAILURE(y,u)			   	  ((fun_injfail_setfailure)(GenericFuncCall))(u[0])


#define ENUMERATE_THINGS(y,u) \
    ENUMERATE_THING(MCI_RUN,y,u) \
    ENUMERATE_THING(MCI_STP,y,u) \
    ENUMERATE_THING(MCI_GET_DIG,y,u) \
    ENUMERATE_THING(MCI_GET_ANG,y,u) \
    ENUMERATE_THING(MCI_SET_DIG,y,u) \
    ENUMERATE_THING(MCI_SET_ANG,y,u) \
    ENUMERATE_THING(MCI_FVT_START,y,u) \
    ENUMERATE_THING(VAR_BASE_ADDR,y,u) \
    ENUMERATE_THING(CM_RUNLOAD,y,u) \
    ENUMERATE_THING(WIN_UART,y,u) \
    ENUMERATE_THING(MCI_GET_ERROR_LIST,y,u)\
    ENUMERATE_THING(INJFAIL_SRMCATOD_DIAGN,y,u)\
    ENUMERATE_THING(INJFAIL_SRMCPWM_DIAGN,y,u)\
    ENUMERATE_THING(INJFAIL_SRMCPWM_HWOC,y,u) \
	ENUMERATE_THING(INJFAIL_SETFAILURE,y,u)

#define ENUMERATE_THING(thing,y,u) case thing: FUNC_CALL_ ##thing(y,u); break;
